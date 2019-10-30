/*
*
* File: PowerSys.cpp
* Purpose:
* Version: 1.0.0
* Date: 17-10-2019
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



//*********** Orthogonal Signal Generator initialize ****//
void PowerControl::osgBegin(float _freq, float _deltat) {
	// calculate DDS tuning word
	tuningWord=(unsigned long)(pow(2,32)*_freq*_deltat);
}



//*********** Orthogonal Signal Generator with phase update. Must be called regularly at fixed time intervals *****//
void PowerControl::osgUpdate(unsigned long _phaseInc, unsigned long _phaseOffset){
	phaseAccu1 += (tuningWord + _phaseInc);
	phaseAccu2 = (phaseAccu1 + _phaseOffset);
	rfbk = pgm_read_word(sinlut1024 + (unsigned int)(phaseAccu1>>22))-0x1FF; // feedback to PLL
	rsin = pgm_read_word(sinlut1024 + (unsigned int)(phaseAccu2>>22))-0x1FF; // reference sine wave output
	rcos = pgm_read_word(sinlut1024 + (unsigned int)((phaseAccu2 + PHASE_OFFS_270)>>22))-0x1FF; // reference cosine output
}



// Park transform
void PowerControl::park(long _alpha, long _beta){
	alpha = _alpha;
	beta = _beta;
	d = alpha*rcos + beta*rsin;
	q = beta*rcos - alpha*rsin;
}



// inverse Park transform
void PowerControl::ipark(long _d, long _q){
	d=_d;
	q=_q;
	alpha = d*rcos - q*rsin;
	beta = d*rsin + q*rcos;
}
