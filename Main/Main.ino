//Copyright stuff for Atlas
//Specify Arduino model

//import Arduino libraries 
//Bluetooth?
//Thread? (protothread, since there are no true "threads" on Arduino)


#include "Atlas_Leg.h"
/*
 * Each leg's device is its own object, from class "Leg". (imported from "Atlas_Leg.h")
 * Object contains the motor functions and means of retreiving data. 
 * Uses H-Bridge and Touch sensor interface (and Biosignal processing later on). 
 */


void setup() {

  //initialize each Leg object
  //initialize what's require from custom libraries


  //initize threads for walking loop

}

/* LIST OF protothreads TO RUN (May need simplication due to limited processing power)
 * 
 * 1) walking loop for Leg1
 * 2) walking loop for Leg2
 * 3) Bluetooth loop to communicate data to computer (or a loop to log data at least)
 * 
 */


 
/* Proposed basic walking algorithm:  
 *  
 *  Each Leg object runs this loop independently of the other. Therefore, protothreads required
 *  
 *  1) Wait for increase in pressure
 *  2) Wait for reasonable decrease in pressure
 *  3) Actuate (wind spool)
 *  4) Unwind spool
 */
 
void loop() {

}
