/*
*
* File: PowerSys.cpp
* Purpose:
* Version: 1.1.0
* Initial release date: 17-10-2019
* Date: 06-08-2020
* URL: https://github.com/MartinStokroos/openMicroInverter
* License: MIT License
*
*
* Copyright (c) M.Stokroos 2019
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
* files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy,
* modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
* COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
*/

#include "PowerSys.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif



/*** Orthogonal Signal Generator (OSG) initialize ***/
void PowerControl::osgBegin(float _freq, float _deltat) {
	// calculate DDS tuning word
	tuningWord=(unsigned long)(pow(2,32) * _freq * _deltat);
}



/*** Orthogonal Signal Generators (OSG) with phase updating function. ***/

// FULL WAVE LUT, 10-bit OSG. rsin and rcos are raised (>=0)
void PowerControl::osgUpdate1(unsigned long _phaseInc, unsigned long _phaseOffset) {
	phaseAccu1 += (tuningWord + _phaseInc);
	phaseAccu2 = (phaseAccu1 + _phaseOffset);
	rfbk = pgm_read_word(fullwave_lut1024 + (unsigned int)(phaseAccu1>>22)) - 0x1FF; // PLL feedback output (signed)
	rsin = pgm_read_word(fullwave_lut1024 + (unsigned int)(phaseAccu2>>22)); // reference sine output
	rcos = pgm_read_word(fullwave_lut1024 + (unsigned int)((phaseAccu2 + PHASE_OFFS_270)>>22)); // reference cosine output
}

// FULL WAVE LUT, 10-bit OSG. rsin and rcos are signed (for use with Park transforms)
void PowerControl::osgUpdate2(unsigned long _phaseInc, unsigned long _phaseOffset) {
	phaseAccu1 += (tuningWord + _phaseInc);
	phaseAccu2 = (phaseAccu1 + _phaseOffset);
	rfbk = pgm_read_word(fullwave_lut1024 + (unsigned int)(phaseAccu1>>22)) - 0x1FF; // PLL feedback output
	rsin = pgm_read_word(fullwave_lut1024 + (unsigned int)(phaseAccu2>>22)) - 0x1FF; // reference sine output
	rcos = pgm_read_word(fullwave_lut1024 + (unsigned int)((phaseAccu2 + PHASE_OFFS_270)>>22))-0x1FF; // reference cosine output
}

// HALF WAVE LUT, 11-bit OSG. rsin and rcos are signed (for use with Park transforms)
void PowerControl::osgUpdate3(unsigned long _phaseInc, unsigned long _phaseOffset) {
	phaseAccu1 += (tuningWord + _phaseInc);
	phaseAccu2 = (phaseAccu1 + _phaseOffset);
	phaseIdx1 = phaseAccu1>>21;
	phaseIdx2 = phaseAccu2>>21;
	phaseIdx3 = (phaseAccu2 + PHASE_OFFS_270)>>21;
	
	if(phaseIdx1>=0 && phaseIdx1<1024) //to do: use 32 bit phase limits
		{
		rfbk = pgm_read_word(quarterwave_lut1024 + phaseIdx1); 
		}
	else if(phaseIdx1>=1024 && phaseIdx1<2048)
		{
		rfbk = -pgm_read_word(quarterwave_lut1024 + (2048 - phaseIdx1)); 
		}
	rfbk = rfbk>>1; // 10-bit test output
	
	if(phaseIdx2>=0 && phaseIdx2<1024)
		{
		rsin = pgm_read_word(quarterwave_lut1024 + phaseIdx2);
		}
	else if(phaseIdx2>=1024 && phaseIdx2<2048)
		{
		rsin = -pgm_read_word(quarterwave_lut1024 + (2048 - phaseIdx2));
		}
	rsin = rsin>>1; // 10-bit test output
	
	if(phaseIdx3>=0 && phaseIdx3<1024)
		{
		rcos = pgm_read_word(quarterwave_lut1024 + phaseIdx3);
		}
	else if(phaseIdx3>=1024 && phaseIdx3<2048)
		{
		rcos = -pgm_read_word(quarterwave_lut1024 + (2048 - phaseIdx3));
		}
 	rcos = rcos>>1; // 10-bit test output
}


// HALF WAVE LUT, 11-bit OSG. rsin and rcos are unsigned (rectified wave)
void PowerControl::osgUpdate4(unsigned long _phaseInc, unsigned long _phaseOffset) {
	phaseAccu1 += (tuningWord + _phaseInc);
	phaseAccu2 = (phaseAccu1 + _phaseOffset);
	phaseIdx1 = phaseAccu1>>21;
	phaseIdx2 = phaseAccu2>>21;
	phaseIdx3 = (phaseAccu2 + PHASE_OFFS_270)>>21;
	
	if(phaseIdx1>=0 && phaseIdx1<1024)
		{
		rfbk = pgm_read_word(quarterwave_lut1024 + phaseIdx1); 
		}
	else if(phaseIdx1>=1024 && phaseIdx1<2048)
		{
		rfbk = -pgm_read_word(quarterwave_lut1024 + (2048 - phaseIdx1)); 
		}
	rfbk = rfbk>>1; // 10-bit test output
	
	if(phaseIdx2>=0 && phaseIdx2<1024)
		{
		rsin = pgm_read_word(quarterwave_lut1024 + phaseIdx2);
		}
	else if(phaseIdx2>=1024 && phaseIdx2<2048)
		{
		rsin = pgm_read_word(quarterwave_lut1024 + (2048 - phaseIdx2));
		}
 	rsin = rsin>>1; // 10-bit test output
	
	if(phaseIdx3>=0 && phaseIdx3<1024)
		{
		rcos = pgm_read_word(quarterwave_lut1024 + phaseIdx3);
		}
	else if(phaseIdx3>=1024 && phaseIdx3<2048)
		{
		rcos = pgm_read_word(quarterwave_lut1024 + (2048 - phaseIdx3));
		}
	rcos = rcos>>1; // 10-bit test output
}



// QUARTER WAVE LUT, 12-bit OSG. rsin and rcos are signed (for use with Park transforms)
void PowerControl::osgUpdate5(unsigned long _phaseInc, unsigned long _phaseOffset) {
	phaseAccu1 += (tuningWord + _phaseInc);
	phaseAccu2 = (phaseAccu1 + _phaseOffset);
	phaseIdx1 = phaseAccu1>>20;
	phaseIdx2 = phaseAccu2>>20;
	phaseIdx3 = (phaseAccu2 + PHASE_OFFS_270)>>20;

	if(phaseIdx1>=0 && phaseIdx1<1024)
		{
		rfbk = pgm_read_word(quarterwave_lut1024 + phaseIdx1); 
		}
	else if(phaseIdx1>=1024 && phaseIdx1<2048)
		{
		rfbk = -pgm_read_word(quarterwave_lut1024 + (2048 - phaseIdx1)); 
		}
	else if(phaseIdx1>=2048 && phaseIdx1<3072)
		{
		rfbk = -pgm_read_word(quarterwave_lut1024 + (phaseIdx1 - 2048)); 
		}
	else if(phaseIdx1>=3072 && phaseIdx1<4096)
		{
		rfbk = pgm_read_word(quarterwave_lut1024 + (4096 - phaseIdx1));
		}
	rfbk -= 0x3FF; // PLL feedback output
	rfbk = rfbk>>2; // 10-bit test output

	if(phaseIdx2>=0 && phaseIdx2<1024)
		{
		rsin = pgm_read_word(quarterwave_lut1024 + phaseIdx2);
		}
	else if(phaseIdx2>=1024 && phaseIdx2<2048)
		{
		rsin = -pgm_read_word(quarterwave_lut1024 + (2048 - phaseIdx2));
		}
	else if(phaseIdx2>=2048 && phaseIdx2<3072)
		{
		rsin = -pgm_read_word(quarterwave_lut1024 + (phaseIdx2 - 2048));
		}
	else if(phaseIdx2>=3072 && phaseIdx2<4096)
		{
		rsin = pgm_read_word(quarterwave_lut1024 + (4096 - phaseIdx2));
		}
	rsin -= 0x3FF;
	rsin = rsin>>2; // 10-bit test output
		
	if(phaseIdx3>=0 && phaseIdx3<1024)
		{
		rcos = pgm_read_word(quarterwave_lut1024 + phaseIdx3);
		}
	else if(phaseIdx3>=1024 && phaseIdx3<2048)
		{
		rcos = -pgm_read_word(quarterwave_lut1024 + (2048 - phaseIdx3));
		}
	else if(phaseIdx3>=2048 && phaseIdx3<3072)
		{
		rcos = -pgm_read_word(quarterwave_lut1024 + (phaseIdx3 - 2048));
		}
	else if(phaseIdx3>=3072 && phaseIdx3<4096)
		{
		rcos = pgm_read_word(quarterwave_lut1024 + (4096 - phaseIdx3));
		}
	rcos -= 0x3FF;
	rcos = rcos>>2; // 10-bit test output
}




// Park transform
void PowerControl::park(long _alpha, long _beta) {
	alpha = _alpha;
	beta = _beta;
	d = alpha*rcos + beta*rsin;
	q = beta*rcos - alpha*rsin;
}



// inverse Park transform
void PowerControl::ipark(long _d, long _q) {
	d=_d;
	q=_q;
	alpha = d*rcos - q*rsin;
	beta = d*rsin + q*rcos;
}
