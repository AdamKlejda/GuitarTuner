/*
 * FFT.h
 *
 *  Created on: 3 maj 2018
 *      Author: St.Wasik
 */
#include "arm_math.h"

#ifndef FFT_H_
#define FFT_H_


#define BUFFER_INPUT_SIZE 1024

void buffer_add(uint16_t elem);

void FFT_init();

//FFT and display result on tm1637
void FFT();


#endif /* FFT_H_ */