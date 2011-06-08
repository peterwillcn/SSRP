#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef DEBUG
const bool debug = true;
#else
const bool debug = false;
#endif

#define NASH_OUT

#ifdef NASH_OUT
const bool nash_out = true;
#else
const bool nash_out = false;
#endif

#endif