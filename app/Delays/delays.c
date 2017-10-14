//****************************************************************************
//
//! File: 			delays.c
//! Version:		1.0.0.0
//! Date:			Oct. 10, 2017
//! Author:			PFormanek
//!
//!	Contains the delays functions
//!
//***********************************************************
#include "delays.h"

void DelayMs(uint32_t nTime){
	TimingDelay = nTime;
	while(TimingDelay != 0);
}

void TimingDelay_Decrement(void){
	if(TimingDelay != 0)
		TimingDelay--;
}
