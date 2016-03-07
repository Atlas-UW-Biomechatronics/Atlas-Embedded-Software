//Header file to be used to develop the further library

#ifndef ATLAS_PRESSURE_SENSOR
#define ATLAS_PRESSURE_SENSOR

class Atlas_Pressure_Sensor{

	class SensorState{
		int RoC; //value that we get from the function defined in before.
		bool isTouching;
        
    public:

		SensorState();
		~SensorState();
		SensorState(unsigned int nRoC, bool isTouchingNow);

		int getRoC();
		bool isItTouching();

	};

		int[] resistance_;
    
    public:
		//Find out whether or not the values are changing throughout.
		int changeInResistance(int[] resistance);
		int changeInResistance(int[] resistance, SensorState* state);

		//Checking whether or not the foot is on the ground
		bool onGround(int[] resistance);
		bool onGround(int[] resistance, SensorState* state);

		//return the force that is applied to the system
		int getForce(unsigned int resistance, unsigned int voltage);

};

#endif