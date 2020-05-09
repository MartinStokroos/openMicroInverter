/*
 *
 * File: Metering.ino
 * Purpose: openMicroInverter example project demonstrating power and energy metering.
 * Version: 1.0.2
 * Date: 09-05-2020
 * Release date: 07-11-2019
 * 
 * URL: https://github.com/MartinStokroos/openMicroInverter
 * 
 * License: MIT License
 *
 * Copyright (c) M.Stokroos 2019
 *
 *
 * This sketch has been tested with openMicroInverter_dev hardware.
 */

#include <digitalWriteFast.h>	// library for high performance digital reads and writes by jrraines
								// see http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1267553811/0
								// and http://code.google.com/p/digitalwritefast/

#include <TrueRMS.h>  // https://github.com/MartinStokroos/TrueRMS


#define PIN_LED 13
#define PIN_DEBUG 4

#define LPERIOD 50000    // slow control loop period in us. In this case 50ms.
//#define RMS_WINDOW 20   // rms window of 20 samples, means 2 periods @50Hz
#define RMS_WINDOW 40   // rms window of 40 samples, means 4 periods @50Hz
//#define RMS_WINDOW 25   // rms window of 25 samples, means 3 periods @60Hz
//#define RMS_WINDOW 50   // rms window of 50 samples, means 6 periods @60Hz

//scaling of measured quantities
const int gridVoltRange = 660.0; //Vpeak-to-peak full scale.
const float voltRange = 660.0; //Vpeak-to-peak full scale.
const float currRange = 4.5; //Apeak-to-peak full scale.

// ADC vars
volatile int adcVal;
volatile int adcMuxIdx = 0;  // multiplexer index


// define instances of class Rms2 and Power2
Rms2 gridVolt; // create instance of Rms
Power2 acPower; //create instance of Power


unsigned long nextLoop;
unsigned char printMuxIdx=0;
char rxByte;
bool publish;
int pubIdx=0; //counter publishing rate



// ******************************************************************
// Setup
// ******************************************************************
void setup(){
  cli(); // disable interrupts

  // initialize serial communications:
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
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

  bitClear(ADCSRA, ADPS0);	// ADC clock prescaler set to 64 (250kHz). We'll lose some accuracy...
  bitSet(ADCSRA, ADPS1);	// Timer 1 triggers the ADC. When the conversion is ready, the ADC ISR is called.
  bitSet(ADCSRA, ADPS2);	// Timer 1 ISR should be ready before the ADC is ready.

  bitClear(ADCSRB, ACME); // Analog Comparator (ADC)Multiplexer enable OFF
  bitClear(ADCSRB, ADTS0); // select trigger from timer 1
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

  // init measurements
  gridVolt.begin(gridVoltRange, RMS_WINDOW, ADC_10BIT, BLR_ON, CNT_SCAN);
  gridVolt.start();
  acPower.begin(currRange, voltRange, RMS_WINDOW, ADC_10BIT, BLR_ON, CNT_SCAN);
  acPower.start();

  // enable timer compare interrupt
  bitSet(TIMSK1, TOIE1); // enable Timer1 Interrupt
  
  sei(); // enable interrupts
  nextLoop = micros() + LPERIOD; // Set the loop timer variable.
}




// ******************************************************************
// Main loop
// ******************************************************************
void loop(){
	//digitalWriteFast(PIN_DEBUG, HIGH);  // for checking slow control loop rate and to check the execution time.

	gridVolt.publish();
	acPower.publish();

  if(pubIdx <= 0) {
    publish=true;
    pubIdx=10; //print every 0.5s.
  }

    if(publish){
		switch (printMuxIdx) {
    		case 0:
    			Serial.print(gridVolt.rmsVal, 1); // grid voltage
    			Serial.print(", ");
    		break;
    		case 1:
    			Serial.print(acPower.rmsVal2, 1); // voltage behind the grid connection relay
    			Serial.print(", ");
    			break;
    		case 2:
    			Serial.print(acPower.rmsVal1, 2); // output current
    			Serial.print(", ");
    		break;
    		case 3:
    			Serial.print(acPower.apparentPwr, 0);
    			Serial.print(", ");
    		break;
    		case 4:
    			Serial.print(acPower.realPwr, 0);
    			Serial.print(", ");
    		break;
    		case 5:
    			Serial.print(acPower.pf, 2);
    			Serial.print(", ");
    		break;
    		case 6:
          Serial.print(acPower.energy/3600, 2);
    		break;
		}
		if(printMuxIdx==6) {
			Serial.println();
			printMuxIdx=0;
			publish=false;
		}
		else{
			printMuxIdx++;
		}
  }
  pubIdx--;

  //digitalWriteFast(PIN_DEBUG, LOW);

  while(nextLoop > micros()) {;}  // wait until the end of the time interval
  nextLoop += LPERIOD;  // set next loop time at current time + LOOP_PERIOD
}





/* ******************************************************************
* ADC ISR. The ADC is triggered by Timer1.
* *******************************************************************/
ISR(ADC_vect) {
  digitalWriteFast(PIN_DEBUG, HIGH);  // checking ADC sampling frequency and the execution time.

  // read the current ADC input channel
  adcVal=ADCL; // store low byte
  adcVal+=ADCH<<8; // store high byte

  switch (adcMuxIdx) {
    case 0:  // sample the grid voltage
    	gridVolt.update(adcVal);
    break;

    case 1: // sample the inverter current
      acPower.update1(adcVal);
    break;

    case 2: // sample the inverter voltage
      acPower.update2(adcVal);
    break;

    case 3: 
      // slot 3
    break;

    case 4:
      // slot 4
    break;

    case 5:
      // slot 5
    break;
  }

  adcMuxIdx++;
  if (adcMuxIdx > 5){
    adcMuxIdx = 0;
  }
  ADMUX = (ADMUX & B11110000) | adcMuxIdx;   // set the ADC MUX-channel for the next run.

  digitalWriteFast(PIN_DEBUG, LOW); //pin low
} // runtime about 90us max.






/* ******************************************************************
*  Timer1 ISR running at 6000Hz. 
*********************************************************************/
ISR(TIMER1_OVF_vect) {
  // Empty ISR. Required here to trigger the ADC.
  // Important: ADC_vect ISR must be completed before the next call.
}
