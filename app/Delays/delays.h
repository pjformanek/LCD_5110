//*****************************************************************************
//
//! File: 			delays.h
//! Version:		1.0.0.0
//! Date:			Oct 10, 2017
//! Author:			PFormanek
//!
//!	Contains the delays functions prototypes
//!
//***********************************************************
#ifndef _DELAYS_H
#define _DELAYS_H

#include "stdint.h"

extern volatile uint32_t TimingDelay;

void DelayMs(uint32_t nTime);
void TimingDelay_Decrement(void);

#endif // END OF _DELAYS_H
