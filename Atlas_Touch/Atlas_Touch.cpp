#include <iostream>
#include <string>
using namespace std;


#include "Atlas_Touch.hpp"

Atlas_Pressure_Sensor::Sensor_State::Sensor_State(){

}

Atlas_Pressure_Sensor::Sensor_State::Sensor_State(int nRoC, bool isTouchingNow){

}

Atlas_Pressure_Sensor::Sensor_State::~Sensor_State(){

}

Atlas_Pressure_Sensor::Sensor_State::getRoC(){
	return RoC;
}

Atlas_Pressure_Sensor::Sensor_State::isItTouching(){
	return isTouchingNow;
}

Atlas_Pressure_Sensor::changeInResistance(int[] resistance){

}

Atlas_Pressure_Sensor::changeInResistance(int[] resistance, Sensor_State state*){

}

Atlas_Pressure_Sensor::onGound(int resistance){

} 

Atlas_Pressure_Sensor::onGound(int resistance, Sensor_State* state){

}

Atlas_Pressure_Sensor::getForce(unsigned int resistance, unsigned int voltage){

}