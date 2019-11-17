/*
 * File: Inverter.ino
 * Purpose: openMicroInverter example project. This sketch establishes a voltage-mode inverter without output voltage control (open loop).
 * Version: 1.0.0
 * Date: 16-11-2019
 *
 * URL: https://github.com/MartinStokroos/openMicroInverter
 *
 * License: MIT License
 *
 * Copyright (c) M.Stokroos 2019
 *
 *
 *
 * This sketch has been tested on the openMicroInverter_dev hardware.
 *
 */

#include <digitalWriteFast.h>  // library for high performance digital reads and writes by jrraines
                // see http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1267553811/0
                // and http://code.google.com/p/digitalwritefast/

#include <TrueRMS.h> // https://github.com/MartinStokroos/TrueRMS
#include <PowerSys.h> // https://github.com/MartinStokroos/openMicroInverter

// switching mode:
#define UNIPOL    // unipolar switching
//#define BIPOL   // bipolar switching
//#define HYBRID  // bipolar switching, bottom H-bridge=LF

#define LPERIOD 1000000    // loop period time in us. In this case 1s.
#define RMSWINDOW 20 // RMS window, number of samples used for the RMS calculation.

#define PIN_LED 13    // PLL locking status indicator LED
#define PIN_H_PWMA 9  // Timer1 OCR1A 10-bit PWM
#define PIN_H_PWMB 10 // Timer1 OCR1B 10-bit PWM
#define PIN_H_AHI 3   // H-bridge control pin
#define PIN_H_BHI 11  // H-bridge control pin
#define PIN_H_DIS 8   // enable inverter
#define PIN_GRID_RELAY 2  // output relay
#define PIN_DEBUG 4 // debugging output pin

//scaling calibration
const float outputVoltRange = 660.0; //Vp-p full scale.
const float outputCurrRange = 4.5; //Ap-p full scale.
const float vBattRange = 1.00; //Vbatt max, temporary used for magnitude control.
const float iBattRange = 10.00;

// ADC vars
volatile int adcVal;
volatile int adcMuxIdx = 0;  // multiplexer index

// PWM DAC
unsigned int ndac_out;  // DAC magnitude value
unsigned int pdac_out;
int dac_out;

// inverter
const float TD = 1/6000.0; //time step for f=6000 Hz
const float f0 = 50.0; // output frequency in Hz

// define instances for ac/dc voltage, current and power metering and DDS
Power2 outputMeas;
Average vBatt;
Average iBatt;
PowerControl outputWave;

unsigned long nextLoop;



// ******************************************************************
// Setup
// ******************************************************************
void setup(){
  cli(); // enable interrupts

  // initialize serial communications:
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_H_PWMA, OUTPUT);
  pinMode(PIN_H_PWMB, OUTPUT);
  pinMode(PIN_H_AHI, OUTPUT);
  pinMode(PIN_H_BHI, OUTPUT);
  pinMode(PIN_GRID_RELAY, OUTPUT);
  pinMode(PIN_H_DIS, OUTPUT);
  pinMode(PIN_DEBUG, OUTPUT);

  // initialize ADC for continuous sampling mode
  DIDR0 = 0x3F; // digital inputs disabled for ADC0D to ADC5D
  bitSet(ADMUX, REFS0); // Select Vcc=5V as the ADC reference voltage
  bitClear(ADMUX, REFS1);
  bitClear(ADMUX, MUX0); // selecting ADC CH# 0
  bitClear(ADMUX, MUX1);
  bitClear(ADMUX, MUX2);
  bitClear(ADMUX, MUX3);
  bitSet(ADCSRA, ADEN); // AD-converter enabled
  bitSet(ADCSRA, ADATE); // auto-trigger enabled
  bitSet(ADCSRA, ADIE); // ADC interrupt enabled

  bitSet(ADCSRA, ADPS0);  // ADC clock prescaler set to 128
  bitSet(ADCSRA, ADPS1);
  bitSet(ADCSRA, ADPS2);

  bitClear(ADCSRB, ACME); // Analog Comparator (ADC)Multiplexer enable OFF
  bitClear(ADCSRB, ADTS0); // triggered by Timer/Counter1 Overflow
  bitSet(ADCSRB, ADTS1);
  bitSet(ADCSRB, ADTS2);
  bitSet(ADCSRA, ADSC);    // start conversion

  /* TIMER1 configured for phase and frequency correct PWM-mode 8, top=ICR1 */
  // prescaler = 1:
  bitSet(TCCR1B, CS10);
  bitClear(TCCR1B, CS11);
  bitClear(TCCR1B, CS12);
  // mode 8:
  bitClear(TCCR1A, WGM10);
  bitClear(TCCR1A, WGM11);
  bitClear(TCCR1B, WGM12);
  bitSet(TCCR1B, WGM13);
  // top value. Foc=fclk/(2*N*TOP)
  ICR1 = 0x0535; //f=6kHz, min 0x03FF;
  #define ICR1_OFFSET 0x09B;

  #ifdef UNIPOL
    bitClear(TCCR1A, COM1A0);  // Compare Match PWM 10
    bitSet(TCCR1A, COM1A1);
    bitClear(TCCR1A, COM1B0);  // Compare Match PWM 9
    bitSet(TCCR1A, COM1B1);
  #endif
  #ifdef BIPOL
    bitClear(TCCR1A, COM1A0);  // Compare Match PWM 10
    bitSet(TCCR1A, COM1A1);
    bitSet(TCCR1A, COM1B0);  // Compare Match PWM9, inverted
    bitSet(TCCR1A, COM1B1);
  #endif
  #ifdef HYBRID
    bitClear(TCCR1A, COM1A0);  // Compare Match PWM 10
    bitSet(TCCR1A, COM1A1);
    bitClear(TCCR1A, COM1B0);  // Compare Match PWM 9
    bitSet(TCCR1A, COM1B1);
  #endif

  // enable timer compare interrupt
  bitSet(TIMSK1, TOIE1); // enable Timer1 Interrupt

  outputMeas.begin(outputCurrRange, outputVoltRange, RMSWINDOW, ADC_10BIT, BLR_ON, CNT_SCAN);
  vBatt.begin(vBattRange, RMSWINDOW, ADC_10BIT, CNT_SCAN);
  iBatt.begin(iBattRange, RMSWINDOW, ADC_10BIT, CNT_SCAN);
  outputMeas.start();
  vBatt.start();
  iBatt.start();

  outputWave.osgBegin(f0, TD); // initilize the DDS (frequency, startphase, update period time)

  sei(); // enable interrupts
  nextLoop = micros() + LPERIOD; // Set the loop timer variable for the next loop interval.
}




// ******************************************************************
// Main loop
// ******************************************************************
void loop(){
  digitalWriteFast(PIN_LED, HIGH);
  vBatt.publish();
  iBatt.publish();
  outputMeas.publish();
  Serial.print(outputMeas.rmsVal2, 1); // print the RMS output voltage
  Serial.print(", ");
  Serial.print(outputMeas.rmsVal1, 1); // print the RMS output current
  Serial.print(", ");
  Serial.print(outputMeas.apparentPwr, 0); // print the RMS output VA's
  Serial.print(", ");
  Serial.print(outputMeas.realPwr, 0); // print the RMS output Watts
  Serial.print(", ");
  Serial.print(vBatt.average, 1);
  Serial.print(", ");
  Serial.println(iBatt.average, 1);

  while(nextLoop > micros());  // wait until the end of the time interval
  nextLoop += LPERIOD;  // set next loop time at current time + LOOP_PERIOD
  digitalWriteFast(PIN_LED, LOW);
}




/* ******************************************************************
* ADC ISR. ADC is triggered by Timer1.
* *******************************************************************/
ISR(ADC_vect){
  digitalWriteFast(PIN_DEBUG, HIGH);
  // read the current ADC input channel
  adcVal=ADCL; // store low byte
  adcVal+=ADCH<<8; // store high byte
  switch (adcMuxIdx) {
    case 0:
      //sample the grid voltage
    break;

    case 1: //sample the inverter current
      //outputMeas.update1(adcVal);
    break;

    case 2: //sample the inverter voltage
      //outputMeas.update2(adcVal);
    break;

    case 3: // sample the battery current
      //iBatt.update(adcVal);
    break;

    case 4: //sample the battery voltage
      //vBatt.update(adcVal);
    break;

    case 5:
    break;
    // default:
  }
  adcMuxIdx++;
  if (adcMuxIdx > 5){
    adcMuxIdx = 0;
  }
  ADMUX = (ADMUX & B11110000) | adcMuxIdx;   // set the ADC-MUX channel for the next call
  digitalWriteFast(PIN_DEBUG, LOW);
}





/* ******************************************************************
*  Timer1 ISR running at 6000Hz
*********************************************************************/
ISR(TIMER1_OVF_vect) {
  // generate the reference sin wave with DDS.
  outputWave.osgUpdate(0, 0);

  #ifdef UNIPOL
    //complementary sin wave drive of both legs in H-bridge. High-side and low-side are PWM-switched. AHI=5V and BHI=5V.
    //(see HIP4082 application note; LF switched inverter ALI//BHI (pin4,2) and AHI//BLI (7,3) )
    pdac_out = outputWave.rcos + 0x1FF; //make unsigned, 10 bit range
    ndac_out = (~pdac_out) & 0x3FF; //invert for n-channel.
    pdac_out += ICR1_OFFSET; // add offset to center between the BOTTOM to TOP value range of the timer.
    ndac_out += ICR1_OFFSET;
    // write to PWM output registers A&B (10bit).
    OCR1AH = pdac_out>>8; //MSB
    OCR1AL = pdac_out; //LSB
    //inverted output channel (dead-time generation inside the H-bridge driver HIP4082):
    OCR1BH = ndac_out>>8; //MSB
    OCR1BL = ndac_out; //LSB
  #endif

  #ifdef BIPOL
      dac_out = outputWave.rcos;
      // complementary gate drive for top and bottom FET's. H-leg switching is done with the AHI, BHI signals.
      // write magnitude data to PWM output registers A&B (10bit).
      dac_out += 0x1FF;
      dac_out += ICR1_OFFSET;
        OCR1AH = dac_out >> 8; // top 8 bits
        OCR1AL = dac_out; //bottom 8 bits
        OCR1BH = OCR1AH;  //low side of H-bridge
        OCR1BL = OCR1AL;
  #endif

  #ifdef HYBRID // Not working! Control lines AHI, BHI not controlled yet...
      dac_out = outputWave.rcos;
    // write magnitude data to PWM output registers A&B (10bit).
    if (dac_out >=0) {
      OCR1AH = dac_out >> 8; // top 8 bits
      OCR1AL = dac_out; // bottom 8 bits
      OCR1BH = 0xFF; // low side of H-bridge is low frequency switched
      OCR1BL = 0xFF;
    }
    else {
      OCR1AH = dac_out >> 8; // top 8 bits
      OCR1AL = dac_out; // bottom 8 bits
      OCR1BH = 0xFF;
      OCR1BL = 0xFF;
    }
  #endif
}
