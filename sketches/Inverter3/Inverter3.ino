/*
 * File: Inverter3.ino
 * Purpose: openMicroInverter example project.
 *
 * This sketch establishes a voltage-mode inverter without output voltage control (open loop).
 * It synchronizes the output wave to the grid voltage. Do not connect the inverter output in parallel with
 * the grid with this example! There is no current control yet.
 *
 * Version: 1.0.0
 * Release date: 30-10-2020
 * Last update:
 *
 * URL: https://github.com/MartinStokroos/openMicroInverter
 *
 * License: MIT License
 *
 * Copyright (c) M.Stokroos 2019
 *
 *
 *
 * This sketch has been tested with the openMicroInverter_dev hardware.
 *
 */

#include <digitalWriteFast.h>  // library for high performance digital reads and writes by jrraines
                               // see http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1267553811/0
                               // and http://code.google.com/p/digitalwritefast/

#include <TrueRMS.h> // https://github.com/MartinStokroos/TrueRMS
#include <PowerSys.h> // https://github.com/MartinStokroos/openMicroInverter
#include <cordic.h> // https://github.com/MartinStokroos/fastCORDIC

// H-bridge switching mode:
#define UNIPOL    // unipolar switching
//#define BIPOL   // bipolar switching
//#define HYBRID  // bipolar switching, bottom H-bridge=LF. LF+PWM dive. Not working correctly yet...

#define LPPERIOD 10000    // main loop period time in us. In this case 100Hz.
#define RMSWINDOW 40 // RMS window, number of samples used for the RMS calculation.
#define PHINC 143166L // phase increment for +0.5Hz
#define GRID_UNDERVOLT 500 // mains under voltage detection threshold value (CORDIC amplitude, not RMS!)

#define PIN_LED 13    // PLL locking status indicator LED
#define PIN_H_PWMA 9  // Timer1 OCR1A 10-bit PWM
#define PIN_H_PWMB 10 // Timer1 OCR1B 10-bit PWM
#define PIN_H_AHI 3   // H-bridge control pin
#define PIN_H_BHI 11  // H-bridge control pin
#define PIN_H_DIS 8   // enable inverter
#define PIN_GRID_RELAY 2  // output relay
#define PIN_DEBUG 4 // debugging output pin
//#define PIN_ANCREF 6  // AN comparator reference input
//#define PIN_ANCIN 7     // AN comparator input for ZCD

// input scaling calibration
const float gridVoltRange = 660.0; // Vp-p full scale
const float outputVoltRange = 660.0; // Vp-p full scale
const float outputCurrRange = 4.5; // Ap-p full scale
const float vBattRange = 5.00; // Vbatt max, not scaled yet
const float iBattRange = 5.00; // Ibatt, not scaled yet
const float potmeterRange = 1024; // debug potmeter for phase setting range. Increase or decrease the range here.

// ADC vars
volatile int adcVal;
volatile int adcMuxIdx = 0;  // multiplexer index
volatile int vGridIqIdx = 0;
volatile int refIqsIdx = 0;
volatile int refInstVal;

// PWM DAC
unsigned int ndac_out;  // DAC magnitude value
unsigned int pdac_out;
int dac_out;

// DDS
const float TD = 1/6000.0; //time step for f=6000 Hz
const float f0 = 50.0; // output frequency in Hz
const float f_min = 49.8; //minimal output frequency in Hz.
long phaseIncrement;

// PLL vars
volatile int U0, U1, U2, U3; //IQ sampling vars
volatile int V0, V1, V2, V3;
volatile int M0, M1, M2, M3; //IQ sampling vars
volatile int N0, N1, N2, N3;
int XG, YG, XR, YR;
unsigned int gridCordicPhase, prevGridCordicPhase;
unsigned int cordicAmplitude;
unsigned int refCordicPhase, prevRefCordicPhase;
int deltaGridPhase, deltaRefPhase;
int extendedGridPhase, extendedRefPhase;
int rateError, phaseError;
long deltaPhase;
unsigned long phaseOffset = 265289728; //phase offset between rfbk and rsin
cordic10 gridCordic;
cordic10 refCordic;
bool mains_present;
unsigned char pll_lock_cnt=0;
bool pll_locked;

// create instances for ac/dc voltage, current and power metering and DDS
Rms2 gridVolt;
Power2 outputMeasurements;
//Average vBatt;
//Average iBatt;
Average potmeter; //debug control potmeter
PowerControl outputWave;
volatile boolean inv_enable = true;
volatile boolean grid_conn = false;

unsigned long nextLoop;
int taskIdx=0;

//function prototypes
void io_update(void);



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
  ICR1 = 0x0535; //0x0536, f=6kHz, min 0x03FF;

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

  // enable timer compare interrupt
  bitSet(TIMSK1, TOIE1); // enable Timer1 Interrupt

  gridVolt.begin(gridVoltRange, RMSWINDOW, ADC_10BIT, BLR_ON, CNT_SCAN);
  outputMeasurements.begin(outputCurrRange, outputVoltRange, RMSWINDOW, ADC_10BIT, BLR_ON, CNT_SCAN);
  //vBatt.begin(vBattRange, RMSWINDOW, ADC_10BIT, CNT_SCAN);
  //iBatt.begin(iBattRange, RMSWINDOW, ADC_10BIT, CNT_SCAN);
  potmeter.begin(potmeterRange, RMSWINDOW, ADC_10BIT, CNT_SCAN);
  gridVolt.start();
  outputMeasurements.start();
  //vBatt.start();
  //iBatt.start();
  potmeter.start();

  outputWave.osgBegin(f_min, TD); // initilize the DDS (frequency, startphase, timestep)

  Serial.println("grid_phase inverter_phase"); //Arduino plotter legend. For this experiment only phase information output is printed. 

  sei(); // enable interrupts
  nextLoop = micros() + LPPERIOD; // Set the loop timer variable for the next loop interval.
}




// ******************************************************************
// Main loop
// ******************************************************************
void loop(){
  //digitalWriteFast(PIN_DEBUG, HIGH);

  gridVolt.publish(); //publish results at the loop-rate
  outputMeasurements.publish();
  //vBatt.publish();
  //iBatt.publish();
  potmeter.publish();
  
  phaseOffset = potmeter.average;
  phaseOffset = phaseOffset<<20;

  switch(taskIdx){ //100Hz/5=20Hz
    case 0:
      XG = U0+U1+U2+U3; // down sample the grid voltage
      YG = V0+V1+V2+V3;
      XR = M0+M1+M2+M3; // down sample the reference wave
      YR = N0+N1+N2+N3;
      taskIdx++;
    break;
    case 1:
       //digitalWriteFast(PIN_DEBUG1, HIGH);
       gridCordic.atan2sqrt(XG, YG);
       //digitalWriteFast(PIN_DEBUG1, LOW);
       gridCordicPhase = gridCordic.angle;
       cordicAmplitude = gridCordic.radius;
       //OCR0B = gridCordicPhase; // debug pwm output pin5
       taskIdx++;
     break;
     case 2:
       refCordic.atan2sqrt(XR, YR);
       refCordicPhase = refCordic.angle;
       taskIdx++;
     break;
     case 3:
       deltaGridPhase = gridCordicPhase - prevGridCordicPhase;
       prevGridCordicPhase = gridCordicPhase;
       extendedGridPhase += deltaGridPhase;
       deltaRefPhase = refCordicPhase - prevRefCordicPhase;
       prevRefCordicPhase = refCordicPhase;
       extendedRefPhase += deltaRefPhase;
       taskIdx++;
       break;
      case 4: //pll-control (when grid is available)
        //rateError = deltaRefPhase - deltaGridPhase;
        phaseError = refCordicPhase - gridCordicPhase;
        deltaPhase = extendedRefPhase - extendedGridPhase; //for absolute phase control
        if(cordicAmplitude >= GRID_UNDERVOLT){ //controller on, above minimum grid voltage
          mains_present = true;
          if (deltaPhase >= 2000) {deltaPhase = 2000;} // clamp the integral to limit max frequency droop
          if (deltaPhase <= -2000) {deltaPhase = -2000;}
          //phaseIncrement = PHINC + 1024*round(potmeter.average - 512); // open loop manual control of output phase
          phaseIncrement = PHINC + 32*deltaPhase; // closed loop
        }
        else {
          phaseIncrement = PHINC; //increment for default 49.8Hz+0.2Hz=50.0Hz
          mains_present = false;
        }
        if( (phaseError > -2048)&&(phaseError < 2048) ) { pll_locked = true; }
        else { pll_locked = false; }
        
        Serial.print(gridCordicPhase);
        Serial.print(" ");
        Serial.println(refCordicPhase);
        
        taskIdx = 0;
      break;
    }

  //Serial.print(round(gridVolt.rmsVal));
  //Serial.print(", ");
  //Serial.print(round(outputMeasurements.rmsVal2)); // print the RMS output voltage
  //Serial.print(", ");
  //Serial.print(outputMeasurements.rmsVal1, 1); // print the RMS output current
  //Serial.print(", ");
  //Serial.print(round(outputMeasurements.apparentPwr)); // print power output VA's
  //Serial.print(", ");
  //Serial.print(round(outputMeasurements.realPwr)); // print power output Watts
  //Serial.print(", ");
  //Serial.print(vBatt.average, 1);
  //Serial.print(", ");
  //Serial.print(iBatt.average, 1);
  //Serial.println();

  // update IO-pin status
  io_update();

  //digitalWriteFast(PIN_DEBUG, LOW);

  while(nextLoop > micros()) {;}  // wait until the end of the time interval
  nextLoop += LPPERIOD;  // set next loop time at current time + LOOP_PERIOD
}






// ******************************************************************
// Update digital-IO's by direct write (fast!)
// ******************************************************************
void io_update(void) {
  if(inv_enable) {digitalWriteFast(PIN_H_DIS, LOW);}
  else {digitalWriteFast(PIN_H_DIS, HIGH);}

  if(grid_conn) {digitalWriteFast(PIN_GRID_RELAY, HIGH);}
  else {digitalWriteFast(PIN_GRID_RELAY, LOW);}

  if (pll_locked) {digitalWriteFast(PIN_LED, HIGH);}
  else {digitalWriteFast(PIN_LED, LOW);}
} // end of io_update







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
      //refInstVal = outputWave.rfbk; // sample the reference wave and control the inverter output phase with the potmeter, or.. (under case 2:)
    break;

    case 1:
      //time slot for sampling the inverter current
      outputMeasurements.update1(adcVal);
    break;

    case 2:
      //time slot for sampling the inverter voltage
      outputMeasurements.update2(adcVal);
      refInstVal = outputMeasurements.instVal2; // ..sample the inverter output voltage. Inverter output locks to the grid voltage.
    break;

    case 3:
      // time slot for sampling the battery current
      //iBatt.update(adcVal);

      // Do do the grid voltage IQ-down sampling here  to spread the computing burden:
      // multiply and sum samples with sequence 1  0  -1  0 for I channel
      // multiply and sum samples with sequence 0  1  0  -1 for Q channel
      if (vGridIqIdx == 0){
        U3=U2; U2=U1; U1=U0; U0=gridVolt.instVal;
        V3=V2; V2=V1; V1=V0; V0=0;
      }
      if (vGridIqIdx == 5){
        U3=U2; U2=U1; U1=U0; U0=0;
        V3=V2; V2=V1; V1=V0; V0=gridVolt.instVal;
      }
      if (vGridIqIdx == 10){
        U3=U2; U2=U1; U1=U0; U0=-gridVolt.instVal;
        V3=V2; V2=V1; V1=V0; V0=0;
      }
      if (vGridIqIdx == 15){
        U3=U2; U2=U1; U1=U0; U0=0;
        V3=V2; V2=V1; V1=V0; V0=-gridVolt.instVal;
      }
      vGridIqIdx++;
      if(vGridIqIdx == 20) { vGridIqIdx = 0; }
    break;

    case 4:
      // time slot for sampling the battery voltage
      //vBatt.update(adcVal);
    break;

    case 5:
      // sample the potentiometer voltage
      potmeter.update(adcVal); // sample the debug potmeter voltage
      
      // Do do the grid voltage IQ-down sampling here  to spread the computing burden:
      // multiply and sum samples with sequence 1  0  -1  0 for I channel
      // multiply and sum samples with sequence 0  1  0  -1 for Q channel
      if (refIqsIdx == 0) {
        M3=M2; M2=M1; M1=M0; M0=refInstVal;
        N3=N2; N2=N1; N1=N0; N0=0;
      }
      if (refIqsIdx == 5) {
        M3=M2; M2=M1; M1=M0; M0=0;
        N3=N2; N2=N1; N1=N0; N0=refInstVal;
      }
      if (refIqsIdx == 10) {
        M3=M2; M2=M1; M1=M0; M0=-refInstVal;
        N3=N2; N2=N1; N1=N0; N0=0;
      }
      if (refIqsIdx == 15) {
        M3=M2; M2=M1; M1=M0; M0=0;
        N3=N2; N2=N1; N1=N0; N0=-refInstVal;
      }
      refIqsIdx++;
      if(refIqsIdx == 20) {
        refIqsIdx = 0;
      }
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
  // the phaseOffset should be frequency dependent otherwise the phase between grid and the reference
  // will deviate for frequencies different from 50Hz.

  #ifdef UNIPOL
    // complementary sin waves drive both legs in H-bridge. High-side and low-side are PWM-switched. AHI=5V and BHI=5V.
    // (see HIP4082 application note; LF switched inverter ALI//BHI (pin4,2) and AHI//BLI (7,3) )
    outputWave.osgUpdate1(phaseIncrement, phaseOffset);
    pdac_out = outputWave.rcos; //make unsigned, 10 bit range
    ndac_out = (~pdac_out) & 0x3FF; //invert for n-channel.
    pdac_out += ICR1_OFFSET; // add offset to center between the BOTTOM to TOP value range of the timer.
    ndac_out += ICR1_OFFSET;
    // write to PWM output registers A&B (10bit).
    OCR1AH = pdac_out>>8; //MSB
    OCR1AL = pdac_out; //LSB
    //inverted output channel (dead-time correction is inside the H-bridge driver HIP4082):
    OCR1BH = ndac_out>>8; //MSB
    OCR1BL = ndac_out; //LSB
  #endif

  #ifdef BIPOL
    outputWave.osgUpdate1(phaseIncrement, phaseOffset);
    dac_out = outputWave.rcos;
    // complementary gate drives in both legs of the H-bridge. AHI=5V and BHI=5V.
    //dac_out += 0x1FF;
    dac_out += ICR1_OFFSET;
    OCR1AH = dac_out >> 8; // top 8 bits
    OCR1AL = dac_out; //bottom 8 bits
    OCR1BH = OCR1AH;  //Signal inverted with the output compare setting above.
    OCR1BL = OCR1AL;
  #endif

  #ifdef HYBRID
    outputWave.osgUpdate2(phaseIncrement, phaseOffset);
    dac_out = outputWave.rcos;
    // write magnitude data to PWM output registers A&B (10bit).
    if (dac_out >= 0) {
      digitalWriteFast(PIN_H_AHI, LOW);
      digitalWriteFast(PIN_H_BHI, HIGH);
      dac_out = dac_out<<1; //times 2
      OCR1AH = dac_out>>8; // top 8 bits
      OCR1AL = dac_out; // bottom 8 bits
    }
    else {
     digitalWriteFast(PIN_H_BHI, LOW);
     digitalWriteFast(PIN_H_AHI, HIGH);
     dac_out = (-dac_out)<<1; //times 2
     OCR1BH = dac_out>>8; // top 8 bits
     OCR1BL = dac_out; // bottom 8 bits
    }
  #endif
}
