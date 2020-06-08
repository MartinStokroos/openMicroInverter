/*
   File: ZeroCrossingDetector.ino
   Purpose: openMicroInverter example project demonstrating Zero Crossing Detection (ZCD) with the analog comparator from the ATMEGA328.
   Version: 1.0.0
   Date: 16-11-2019

   URL: https://github.com/MartinStokroos/openMicroInverter

   License: MIT License

   Copyright (c) M.Stokroos 2019

   This sketch has been tested with the openMicroInverter_dev hardware.

*/

#include <digitalWriteFast.h>  // library for high performance digital reads and writes by jrraines
// see http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1267553811/0
// and http://code.google.com/p/digitalwritefast/

#include <TrueRMS.h> // https://github.com/MartinStokroos/TrueRMS
#include <PowerSys.h> // https://github.com/MartinStokroos/openMicroInverter
#define LPERIOD 1000
// switching mode:
//#define UNIPOL    // unipolar switching
#define BIPOL   // bipolar switching
//#define HYBRID  // bipolar switching, bottom H-bridge=LF


#define PIN_LED 13    // PLL locking status indicator LED
#define PIN_ZCD_OUT 4   // ZCD output pin
#define PIN_ANCREF 6  // AN comparator reference input biased on 2.5V.
#define PIN_ANCIN 7   // AN comparator input for ZCD. Scaled line voltage input biased on 2.5V
//#define PIN_LED 13    // PLL locking status indicator LED
#define PIN_H_PWMA 9  // Timer1 OCR1A 10-bit PWM
#define PIN_H_PWMB 10 // Timer1 OCR1B 10-bit PWM
#define PIN_H_AHI 3   // H-bridge control pin
#define PIN_H_BHI 11  // H-bridge control pin
#define PIN_H_DIS 8   // enable inverter
#define PIN_GRID_RELAY 2  // output relay

//#define RMS_WINDOW 20   // rms window of 20 samples, means 2 periods @50Hz
//#define RMS_WINDOW 40   // rms window of 40 samples, means 4 periods @50Hz
#define RMS_WINDOW 25   // rms window of 25 samples, means 3 periods @60Hz
//#define RMS_WINDOW 50   // rms window of 50 samples, means 6 periods @60Hz
#define ADC_DEAD_BAND 25 // margin around ADC base line to detect the polarity of the mains voltage

volatile int adcValue;
volatile int adcMuxIdx = 0;  // multiplexer index
volatile bool sign = LOW;   // current sign of input wave; 0=neg, 1=pos

//scaling calibration
const float outputVoltRange = 230.0; //Vp-p full scale.
const float outputCurrRange = 5.0; //Ap-p full scale.
const float vBattRange = 12.0; //Vbatt max, temporary used for magnitude control.
const float iBattRange = 10.00;

// PWM DAC
unsigned int ndac_out;  // DAC magnitude value
unsigned int pdac_out;
int dac_out;

// inverter
const float TD = 1 / 6000.0; //time step for f=6000 Hz
const float f0 = 60.0; // output frequency in

// define instances for ac/dc voltage, current and power metering and DDS
Power2 inverterPower;
Average vBatt;
Average iBatt;
PowerControl outputWave;
const int surnecoVoltRange = 230.0; //Vpeak-to-peak full scale.
Rms2 surnecoVolt; //from the grid
unsigned long nextLoop;
//unsigned long nextLoop;
unsigned char printMuxIdx = 0;
char rxByte;
bool publish;
int pubIdx = 0; //counter publishing rate





// ******************************************************************
// Setup
// ******************************************************************
void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_ZCD_OUT, OUTPUT);
  pinMode(PIN_ANCREF, INPUT);
  pinMode(PIN_ANCIN, INPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_H_PWMA, OUTPUT);
  pinMode(PIN_H_PWMB, OUTPUT);
  pinMode(PIN_H_AHI, OUTPUT);
  pinMode(PIN_H_BHI, OUTPUT);
  pinMode(PIN_GRID_RELAY, OUTPUT);
  pinMode(PIN_H_DIS, OUTPUT);


  cli(); // disable interrupts
  // initialize ADC for continuous sampling mode
  DIDR0 = 0x3F; // digital inputs disabled for A0 to A5
  bitSet(ADMUX, REFS0); // Select Vcc=5V as the ADC reference voltage
  bitClear(ADMUX, REFS1);
  bitClear(ADMUX, MUX0); // selecting ADC CH#0
  bitClear(ADMUX, MUX1);
  bitClear(ADMUX, MUX2);
  bitClear(ADMUX, MUX3);
  bitSet(ADCSRA, ADEN); // AD-converter enabled
  bitSet(ADCSRA, ADATE);  // auto-trigger enabled
  bitSet(ADCSRA, ADIE); // ADC interrupt enabled
  bitSet(ADCSRA, ADPS0);  // ADC clock prescaler set to 32 (500kHz). We'll lose some accuracy...
  bitClear(ADCSRA, ADPS1);
  bitSet(ADCSRA, ADPS2);
  bitClear(ADCSRB, ACME); // Analog Comparator (ADC)Multiplexer enable OFF
  bitClear(ADCSRB, ADTS0);  // select trigger from timer 1
  bitSet(ADCSRB, ADTS1);
  bitSet(ADCSRB, ADTS2);
  bitSet(ADCSRA, ADSC);    // start conversion

  /* TIMER1 configured for phase and frequency correct PWM (mode 8), top=ICR1 */
  // prescaler=1
  bitSet(TCCR1B, CS10);
  bitClear(TCCR1B, CS11);
  bitClear(TCCR1B, CS12);
  bitClear(TCCR1A, WGM10);
  // mode 8
  bitClear(TCCR1A, WGM11);
  bitClear(TCCR1B, WGM12);
  bitSet(TCCR1B, WGM13);
  // top value. f=fclk/(2*N*TOP)
  ICR1 = 0x0535; //f=6kHz, min 0x03FF;
#ifdef UNIPOL
#define ICR1_OFFSET 0x09B;
  digitalWriteFast(PIN_H_AHI, HIGH);
  digitalWriteFast(PIN_H_BHI, HIGH);
  bitClear(TCCR1A, COM1A0);  // Compare Match PWM 10
  bitSet(TCCR1A, COM1A1);
  bitClear(TCCR1A, COM1B0);  // Compare Match PWM 9
  bitSet(TCCR1A, COM1B1);
#endif

#ifdef BIPOL
#define ICR1_OFFSET 0x09B;
  digitalWriteFast(PIN_H_AHI, HIGH);
  digitalWriteFast(PIN_H_BHI, HIGH);
  bitClear(TCCR1A, COM1A0);  // Compare Match PWM 10
  bitSet(TCCR1A, COM1A1);
  bitSet(TCCR1A, COM1B0);  // Compare Match PWM9, inverted
  bitSet(TCCR1A, COM1B1);
#endif

#ifdef HYBRID
#define ICR1_OFFSET 0x09B;
  digitalWriteFast(PIN_H_AHI, LOW);
  digitalWriteFast(PIN_H_BHI, LOW);
  bitSet(TCCR1A, COM1A0);  // Compare Match PWM 10
  bitSet(TCCR1A, COM1A1);
  bitSet(TCCR1A, COM1B0);  // Compare Match PWM 9
  bitSet(TCCR1A, COM1B1);
#endif

#define ICR1_OFFSET 0x09B;

  surnecoVolt.begin(surnecoVoltRange, RMS_WINDOW, ADC_10BIT, BLR_ON, CNT_SCAN);
  inverterPower.begin(outputCurrRange, outputVoltRange, RMS_WINDOW, ADC_10BIT, BLR_ON, CNT_SCAN);
  vBatt.begin(vBattRange, RMS_WINDOW, ADC_10BIT, CNT_SCAN);
  iBatt.begin(iBattRange, RMS_WINDOW, ADC_10BIT, CNT_SCAN);

  surnecoVolt.start();
  inverterPower.start();
  vBatt.start();
  iBatt.start();




  bitSet(TIMSK1, TOIE1); // enable Timer1 Interrupt

  // configure the ATmega328 analog comparator module from the ACSR register.
  bitClear(ACSR, ACD);    // Analog Comparator: Enabled
  bitClear(ACSR, ACBG);   // Analog Comparator Band-gap Select: AIN0 is applied to the positive input
  bitClear(ACSR, ACO);    // Analog Comparator Output: Off
  bitSet(ACSR, ACI);      // Analog Comparator Interrupt Flag: Clear Pending Interrupt
  bitSet(ACSR, ACIE);     // Analog Comparator Interrupt: Enabled
  bitClear(ACSR, ACIC);   // Analog Comparator Input Capture: Disabled
  bitClear(ACSR, ACIS0);    // Analog Comparator Interrupt Mode: Comparator Interrupt on output toggle
  bitClear(ACSR, ACIS1);



  outputWave.osgBegin(f0, TD); // initilize the DDS (frequency, startphase, update period time)


  sei(); // enable interrupts
  nextLoop = micros() + LPERIOD;
  // init RMS measurement

}





// ******************************************************************
// Main loop
// ******************************************************************
void loop() {
  digitalWriteFast(PIN_LED, HIGH);
  surnecoVolt.publish();
  vBatt.publish();
  iBatt.publish();
  inverterPower.publish();


  if (pubIdx <= 0) {
    publish = true;
    pubIdx = 10; //print every 0.5s.
  }

  if (publish) {
    switch (printMuxIdx) {
      case 0:
        Serial.print("grid: ");
        Serial.print(surnecoVolt.rmsVal, 1); 
        Serial.print(" ");
        break;
      case 1:
        Serial.print("INVERTER VOLTS: ");
        Serial.print(inverterPower.rmsVal2, 1);
        Serial.print(" ");
        break;
      case 2:
        Serial.print("INVERTER CURRENT: ");
        Serial.print(inverterPower.rmsVal1, 1);
        Serial.print(" ");
        break;
      case 3:
        Serial.print("aparent: ");
        Serial.print(inverterPower.apparentPwr, 0);
        Serial.print(" ");
        break;
      case 4:
        Serial.print("voltbat: ");
        Serial.print(vBatt.average, 1);
        Serial.print(" ");

        break;
      case 5:
        Serial.print("currenttbat: ");
        Serial.println(iBatt.average, 1);
        break;
      case 6:
        break;
    }
    if (printMuxIdx == 5) {
      Serial.println();
      printMuxIdx = 0;
      publish = false;
    }
    else {
      printMuxIdx++;
    }
  }
  pubIdx--;





  //  Serial.print("real: ");
  //  Serial.print(inverterPower.realPwr, 0);
  //  Serial.print(" ");


  while (nextLoop > micros()); // wait until the end of the time interval
  nextLoop += LPERIOD;  // set next loop time at current time + LOOP_PERIOD
  digitalWriteFast(PIN_LED, LOW);
}





/* ******************************************************************
  Analog comparator ISR
  Interrupts each time that the comparator output toggles.
* *******************************************************************/
ISR(ANALOG_COMP_vect) {
  if (sign) { // positive to negative edge
    digitalWriteFast(PIN_ZCD_OUT, LOW);  // zcd out low
  }
  if (!sign) { // negative to positive edge
    digitalWriteFast(PIN_ZCD_OUT, HIGH);  // zcd out high
  }
}




/* ******************************************************************
  ADC ISR. The ADC is triggered by Timer1.
* *******************************************************************/
ISR(ADC_vect) {
  // read the current ADC-input channel
  adcValue = ADCL; // store low byte
  adcValue += ADCH << 8; // store high byte

  switch (adcMuxIdx) {
    case 0:  // proces the grid voltage sample
      surnecoVolt.update(adcValue);
      if (surnecoVolt.instVal >= ADC_DEAD_BAND) {
        sign = true;
      }
      else if (surnecoVolt.instVal <= -ADC_DEAD_BAND) {
        sign = false;
      }
      break;

    case 1: // sample the inverter current
      inverterPower.update1(adcValue);
      //      surnecoVolt.update(adcValue);
      break;

    case 2:// sample the inverter voltage
      inverterPower.update2(adcValue);
      break;

    case 3:
      vBatt.update(adcValue);
      break;

    case 4:
       iBatt.update(adcValue);
      break;

    case 5:
     
      break;

  }
  adcMuxIdx++;
  if (adcMuxIdx > 5) {
    adcMuxIdx = 0;
  }
  ADMUX = (ADMUX & B11110000) | adcMuxIdx;   //set the ADC MUX-channel for the next run.
}



/* ******************************************************************
   Timer1 ISR running at 6000Hz.
*********************************************************************/
ISR(TIMER1_OVF_vect) {
  // generate the reference sin wave with DDS.
  outputWave.osgUpdate(0, 0);

#ifdef UNIPOL
  // complementary sin waves drive both legs in H-bridge. High-side and low-side are PWM-switched. AHI=5V and BHI=5V.
  // (see HIP4082 application note; LF switched inverter ALI//BHI (pin4,2) and AHI//BLI (7,3) )
  pdac_out = outputWave.rcos + 0x1FF; //make unsigned, 10 bit range
  ndac_out = (~pdac_out) & 0x3FF; //invert for n-channel.
  pdac_out += ICR1_OFFSET; // add offset to center between the BOTTOM to TOP value range of the timer.
  ndac_out += ICR1_OFFSET;
  // write to PWM output registers A&B (10bit).
  OCR1AH = pdac_out >> 8; //MSB
  OCR1AL = pdac_out; //LSB
  //inverted output channel (dead-time correction inside the H-bridge driver HIP4082):
  OCR1BH = ndac_out >> 8; //MSB
  OCR1BL = ndac_out; //LSB
#endif

#ifdef BIPOL
  dac_out = outputWave.rcos;
  // complementary gate drives in both legs of the H-bridge. AHI=5V and BHI=5V.
  dac_out += 0x1FF;
  dac_out += ICR1_OFFSET;
  OCR1AH = dac_out >> 8; // top 8 bits
  OCR1AL = dac_out; //bottom 8 bits
  OCR1BH = OCR1AH;  //Signal inverted with the output compare setting above.
  OCR1BL = OCR1AL;
#endif

#ifdef HYBRID // LF+PWM dive. Not optimal yet... Reference wave should be half wave with 10bit or more amplitude range.
  dac_out = outputWave.rcos;
  // write magnitude data to PWM output registers A&B (10bit).
  if (dac_out >= 0) {
    digitalWriteFast(PIN_H_AHI, LOW);
    digitalWriteFast(PIN_H_BHI, HIGH);
    dac_out = dac_out << 1; //times 2
    OCR1AH = dac_out >> 8; // top 8 bits
    OCR1AL = dac_out; // bottom 8 bits
  }
  else {
    digitalWriteFast(PIN_H_BHI, LOW);
    digitalWriteFast(PIN_H_AHI, HIGH);
    dac_out = (-dac_out) << 1; //times 2
    OCR1BH = dac_out >> 8; // top 8 bits
    OCR1BL = dac_out; // bottom 8 bits
  }
#endif
}
