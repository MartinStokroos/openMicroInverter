/*
 * File: ZeroCrossingDetector.ino
 * Purpose: openMicroInverter example project demonstrating Zero Crossing Detection (ZCD) with the analog comparator from the ATMEGA328.
 * Version: 1.0.0
 * Date: 16-11-2019
 * 
 * URL: https://github.com/MartinStokroos/openMicroInverter
 * 
 * License: MIT License
 *
 * Copyright (c) M.Stokroos 2019
 *
 * This sketch has been tested with the openMicroInverter_dev hardware.
 *
 */

#include <digitalWriteFast.h>	// library for high performance digital reads and writes by jrraines
								// see http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1267553811/0
								// and http://code.google.com/p/digitalwritefast/

#include <TrueRMS.h> // https://github.com/MartinStokroos/TrueRMS


#define PIN_LED 13		// PLL locking status indicator LED
#define PIN_ZCD_OUT 4   // ZCD output pin
#define PIN_ANCREF 6	// AN comparator reference input biased on 2.5V.
#define PIN_ANCIN 7   // AN comparator input for ZCD. Scaled line voltage input biased on 2.5V

//#define RMS_WINDOW 20   // rms window of 20 samples, means 2 periods @50Hz
#define RMS_WINDOW 40   // rms window of 40 samples, means 4 periods @50Hz
//#define RMS_WINDOW 25   // rms window of 25 samples, means 3 periods @60Hz
//#define RMS_WINDOW 50   // rms window of 50 samples, means 6 periods @60Hz

#define ADC_DEAD_BAND 25 // margin around ADC base line to detect the polarity of the mains voltage


const int gridVoltRange = 660.0; //Vpeak-to-peak full scale.
Rms2 gridVolt; // create instance of Rms
volatile int adcValue;
volatile int adcMuxIdx = 0;  // multiplexer index
volatile bool sign = LOW;   // current sign of input wave; 0=neg, 1=pos


// ******************************************************************
// Setup
// ******************************************************************
void setup(){
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_ZCD_OUT, OUTPUT);
  pinMode(PIN_ANCREF, INPUT);
  pinMode(PIN_ANCIN, INPUT);
    
  // initialize serial communications:
  Serial.begin(115200);

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
  bitSet(TCCR1B, CS10);   // prescaler=1
  bitClear(TCCR1B, CS11);
  bitClear(TCCR1B, CS12);
  bitClear(TCCR1A, WGM10);   // mode 8
  bitClear(TCCR1A, WGM11);
  bitClear(TCCR1B, WGM12);
  bitSet(TCCR1B, WGM13);
  // top value. f=fclk/(2*N*TOP)
  ICR1 = 0x0535; //f=6kHz, min 0x03FF;
  #define ICR1_OFFSET 0x09B;
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
  sei(); // enable interrupts

  // init RMS measurement
  gridVolt.begin(gridVoltRange, RMS_WINDOW, ADC_10BIT, BLR_ON, CNT_SCAN);
  gridVolt.start();
}





// ******************************************************************
// Main loop
// ******************************************************************
void loop() {
  digitalWriteFast(PIN_LED, HIGH);
  gridVolt.publish();
  Serial.println(gridVolt.rmsVal, 1); // print the RMS grid voltage
  delay(500);
  digitalWriteFast(PIN_LED, LOW);
  delay(500);
}





/* ******************************************************************
* Analog comparator ISR
* Interrupts each time that the comparator output toggles.
* *******************************************************************/
ISR(ANALOG_COMP_vect) {
  if (sign){ // positive to negative edge
	  digitalWriteFast(PIN_ZCD_OUT, LOW);  // zcd out low
  }
  if (!sign){ // negative to positive edge
	  digitalWriteFast(PIN_ZCD_OUT, HIGH);  // zcd out high
  }
}




/* ******************************************************************
* ADC ISR. The ADC is triggered by Timer1.
* *******************************************************************/
ISR(ADC_vect){
  // read the current ADC-input channel
  adcValue=ADCL; // store low byte
  adcValue+=ADCH<<8; // store high byte

  switch (adcMuxIdx) {
    case 0:  // proces the grid voltage sample
      gridVolt.update(adcValue);
      if (gridVolt.instVal >= ADC_DEAD_BAND) {
        sign = true;
      }
      else if (gridVolt.instVal <= -ADC_DEAD_BAND) {
        sign = false;
      }
    break;

    case 1: // process the next sample...
    break;

    case 2:
    break;

    case 3: 
    break;

    case 4:
    break;

    case 5:
    break;
    
  }
  adcMuxIdx++;
  if (adcMuxIdx > 5){
    adcMuxIdx = 0;
  }
  ADMUX = (ADMUX & B11110000) | adcMuxIdx;   //set the ADC MUX-channel for the next run.
}



/* ******************************************************************
*  Timer1 ISR running at 6000Hz. 
*********************************************************************/
ISR(TIMER1_OVF_vect) {
  // Empty ISR. Only required here to trigger the ADC.
  // Important: The ADC_vect ISR must be completed before the next call.
}
