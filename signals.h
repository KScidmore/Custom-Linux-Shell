/*---------- ID HEADER -------------------------------------
/  Author(s):   Andrew Boisvert, Kyle Scidmore
/  Email(s):    abois526@mtroyal.ca, kscid125@mtroyal.ca
/  File Name:   signals.h
/
/  Program Purpose(s):
/    User-defined header file for signals.c. 
/---------------------------------------------------------*/

#ifndef SIGNAL_H
#define SIGNAL_H


void child_signal(int sig);
void interrupt_block(int sig);

#endif