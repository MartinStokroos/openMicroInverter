/*
 * File: Inverter1b.ino
 * Purpose: openMicroInverter example project. This sketch establishes a voltage-mode inverter without output voltage control (open loop).
 * It uses the Dual Channel H-bridge Motor Shield (8A/22V) from Elecrow. This sketch has been adapted from example Inverter1.ino version 1.2.1.
 * Version: 1.0.0
 * Release date: 22-06-2021
 * 
 * Last update: -
 * 
 * URL: https://github.com/MartinStokroos/openMicroInverter
 *
 * License: MIT License
 *
 * Copyright (c) M.Stokroos 2021
 *
 */

#include <digitalWriteFast.h>  // library for high performance digital reads and writes by jrraines
                               // see http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1267553811/0
                               // and http://code.google.com/p/digitalwritefast/

#include <TrueRMS.h> // https://github.com/MartinStokroos/TrueRMS
#include <PowerSys.h> // https://github.com/MartinStokroos/openMicroInverter

// H-bridge switching mode:
#define UNIPOL    // unipolar switching - Complementary sin waves drive L+R legs of the H-bridge.
//#define BIPOL   // bipolar switching - Complementary gate drive applied to both legs of the H-bridge.
//#define HYBRID  // bipolar switching - Bottom FET's of the H-bridge are LF switched, top FET's are PWM driven.

#define LPPERIOD 1000000    // main loop period time in us. In this case 1s.
#define RMSWINDOW 20 // RMS window, number of samples used for the RMS calculation.

#define PIN_LED 13    // LED 
#define PIN_H_P_1 9  // Timer1 OCR1A 10-bit PWM
#define PIN_H_P_2 10 // Timer1 OCR1B 10-bit PWM
#define PIN_H_1A 4
#define PIN_H_1B 5
#define PIN_H_2A 7
#define PIN_H_2B 8
#define PIN_H_EN 6
#define PIN_DEBUG 3 // debugging output pin

//scaling calibration
const float gridVoltRange = 660.0; //Vp-p full scale.
const float outputVoltRange = 660.0; //Vp-p full scale.
const float outputCurrRange = 4.5; //Ap-p full scale.
const float vBattRange = 5.00; //Vbatt scaled max, not scaled correctly yet.
const float iBattRange = 5.00; //Ibatt scaled max, not scaled correctly yet.
const float vPotRange = 1.00; //Vpotmeter scaled max, used for amplitude control of the output wave.

// ADC vars
volatile int adcVal;
volatile int adcMuxIdx = 0;  // multiplexer index

// PWM DAC
float mgain = 1.0;
float amplitude;
unsigned int ndac_out;  // DAC magnitude value
unsigned int pdac_out;
int dac_out;

// inverter
const float TD = 1/6000.0; //time step for f=6000 Hz
const float f0 = 50.0; // output frequency in Hz

// define instances for ac/dc voltage, current and power measurements and wave generation
Rms2 gridVolt;
Power2 acOutput;
Average vBatt;
Average iBatt;
Average vPot;
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
  pinMode(PIN_H_P_1, OUTPUT);
  pinMode(PIN_H_P_2, OUTPUT);
  pinMode(PIN_H_1A, OUTPUT);
  pinMode(PIN_H_1B, OUTPUT);
  pinMode(PIN_H_2A, OUTPUT);
  pinMode(PIN_H_2B, OUTPUT);
  pinMode(PIN_H_EN, OUTPUT);   
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

  bitClear(ADCSRA, ADPS0);  // ADC clock prescaler set to 64 (250kHz)
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
  // top value. f_TIM1 = fclk/(2*N*TOP)
  ICR1 = 0x0536; //0x0535, f=6kHz, min 0x03FF;

  #ifdef UNIPOL
  #define ICR1_OFFSET 0x09B;
    digitalWriteFast(PIN_H_1A, HIGH); //XFMR between M1_A and M2_A. Tie M1_A and M1_B together. Also tie M2_A and M2_B together.
    digitalWriteFast(PIN_H_1B, HIGH);
    digitalWriteFast(PIN_H_2A, HIGH);
    digitalWriteFast(PIN_H_2B, HIGH);
    bitClear(TCCR1A, COM1A0);  // Compare Match PWM 10
    bitSet(TCCR1A, COM1A1);
    bitClear(TCCR1A, COM1B0);  // Compare Match PWM 9
    bitSet(TCCR1A, COM1B1);
  #endif

  #ifdef BIPOL
  #define ICR1_OFFSET 0x09B;
    digitalWriteFast(PIN_H_1A, HIGH); //XFMR between M1_A and M2_A. Tie M1_A and M1_B together. Also tie M2_A and M2_B together.
    digitalWriteFast(PIN_H_1B, HIGH);
    digitalWriteFast(PIN_H_2A, HIGH);
    digitalWriteFast(PIN_H_2B, HIGH);
    bitClear(TCCR1A, COM1A0);  // Compare Match PWM 10
    bitSet(TCCR1A, COM1A1);
    bitSet(TCCR1A, COM1B0);  // Compare Match PWM9, inverted
    bitSet(TCCR1A, COM1B1);
  #endif

  #ifdef HYBRID
  #define ICR1_OFFSET 0x09B;
    digitalWriteFast(PIN_H_1A, HIGH);
    digitalWriteFast(PIN_H_1B, LOW);
    digitalWriteFast(PIN_H_2A, HIGH);
    digitalWriteFast(PIN_H_2B, LOW);    
    bitSet(TCCR1A, COM1A0);  // Compare Match PWM 10
    bitSet(TCCR1A, COM1A1);
    bitSet(TCCR1A, COM1B0);  // Compare Match PWM 9
    bitSet(TCCR1A, COM1B1);
  #endif

  // enable timer compare interrupt
  bitSet(TIMSK1, TOIE1); // enable Timer1 Interrupt

  gridVolt.begin(gridVoltRange, RMSWINDOW, ADC_10BIT, BLR_ON, CNT_SCAN);
  acOutput.begin(outputCurrRange, outputVoltRange, RMSWINDOW, ADC_10BIT, BLR_ON, CNT_SCAN);
  vBatt.begin(vBattRange, RMSWINDOW, ADC_10BIT, CNT_SCAN);
  iBatt.begin(iBattRange, RMSWINDOW, ADC_10BIT, CNT_SCAN);
  vPot.begin(vPotRange, 4, ADC_10BIT, CNT_SCAN);

  gridVolt.start();
  acOutput.start();
  vBatt.start();
  iBatt.start();
  vPot.start();
  outputWave.osgBegin(f0, TD); // initilize the DDS (frequency, timestep)

  sei(); // enable interrupts
  nextLoop = micros() + LPPERIOD; // Set the loop timer variable for the next loop interval.
  
  digitalWriteFast(PIN_H_EN, HIGH); //enable H-bridge
}




// ******************************************************************
// Main loop
// ******************************************************************
void loop(){
  digitalWriteFast(PIN_LED, HIGH);

  gridVolt.publish();
  vBatt.publish();
  iBatt.publish();
  vPot.publish();
  acOutput.publish();

  mgain = vPot.average; // read amplitude control gain setting from potmeter.
                        // Note: amplitude setting is updated with the frequency of the main loop (slow)! 

  Serial.print(gridVolt.rmsVal, 0); // print the RMS input voltage
  Serial.print(", ");
  Serial.print(acOutput.rmsVal2, 0); // print the RMS output voltage
  Serial.print(", ");
  Serial.print(acOutput.rmsVal1, 2); // print the RMS output current
  Serial.print(", ");
  Serial.print(acOutput.apparentPwr, 0); // print power output VA's
  Serial.print(", ");
  Serial.print(acOutput.realPwr, 0); // print power output Watts
  Serial.print(", ");
  Serial.print(vBatt.average, 1);
  Serial.print(", ");
  Serial.println(iBatt.average, 1);

  digitalWriteFast(PIN_LED, LOW);
  
  while(nextLoop > micros()) {;}  // wait until the end of the time interval
  nextLoop += LPPERIOD;  // set next loop time at current time + LOOP_PERIOD
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
      //time slot for sampling the grid voltage
      gridVolt.update(adcVal);
    break;

    case 1:
      //time slot for sampling the inverter current
      acOutput.update1(adcVal);
    break;

    case 2:
      //time slot for sampling the inverter voltage
      acOutput.update2(adcVal);
    break;

    case 3: 
      // time slot for sampling the battery current
      iBatt.update(adcVal);
    break;

    case 4:
      // time slot for sampling the battery voltage
      vBatt.update(adcVal);
    break;

    case 5:
      // optional time slot
      vPot.update(adcVal);
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

  #ifdef UNIPOL
    // Complementary sin waves drive L+R legs of the H-bridge.
	  outputWave.osgMaSlUpdate2(0, 0); // generate signed reference wave with DDS.
    amplitude = (float)outputWave.rcos * mgain;
    pdac_out = (int)amplitude + 0x1FF; //make unsigned, 10 bit range
    ndac_out = (~pdac_out) & 0x3FF; //invert for n-channel.
    pdac_out += ICR1_OFFSET; // add offset to center between the BOTTOM to TOP value range of the timer.
    ndac_out += ICR1_OFFSET;
    // write to PWM output registers A&B (10bit).
    OCR1AH = pdac_out>>8; //MSB
    OCR1AL = pdac_out; //LSB
    // Inverted output channel
    OCR1BH = ndac_out>>8; //MSB
    OCR1BL = ndac_out; //LSB
  #endif

  #ifdef BIPOL
    // Complementary gate drive applied to both legs of the H-bridge.
	  outputWave.osgMaSlUpdate2(0, 0);     // generate the reference wave with DDS.
    amplitude = (float)outputWave.rcos * mgain;
    dac_out = (int)amplitude + 0x1FF;
    dac_out += ICR1_OFFSET;
    OCR1AH = dac_out >> 8; // top 8 bits
    OCR1AL = dac_out; //bottom 8 bits
    OCR1BH = OCR1AH;  //Inverted output with the inverting output compare setting above.
    OCR1BL = OCR1AL;
  #endif

  #ifdef HYBRID
    // LF+PWM dive. Not optimal yet... Reference wave should be half wave with 10bit or more amplitude range.
	  outputWave.osgMaSlUpdate2(0, 0); // generate the reference wave with DDS.
    amplitude = (float)outputWave.rcos * mgain;
    dac_out = (int)amplitude;
    if (dac_out >= 0) {
      //dac_out = dac_out + 0x1FF; //?
      digitalWriteFast(PIN_H_2A, LOW);
      digitalWriteFast(PIN_H_2B, LOW);
      digitalWriteFast(PIN_H_1A, HIGH);
      digitalWriteFast(PIN_H_1B, HIGH);
      //dac_out = dac_out<<1; //scaling incorrect - this should be fixed by lookup table in PowerSys lib...
      //dac_out += ICR1_OFFSET; //?
      OCR1AH = dac_out>>8; // top 8 bits
      OCR1AL = dac_out; // bottom 8 bits
    }
    else {
      digitalWriteFast(PIN_H_1A, LOW);
      digitalWriteFast(PIN_H_1B, LOW);
      digitalWriteFast(PIN_H_2A, HIGH);
      digitalWriteFast(PIN_H_2B, HIGH); 
      dac_out = -dac_out; // + ICR1_OFFSET; //?
      //dac_out = (-dac_out)<<1; //times 2
      OCR1BH = dac_out>>8; // top 8 bits
      OCR1BL = dac_out; // bottom 8 bits
    }
  #endif
}
