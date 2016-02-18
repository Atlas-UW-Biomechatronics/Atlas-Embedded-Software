//Header file to be used to develop the further library

#ifenddef Atlas_Touch
#define Atlas_Touch

class Atlas_Touch{
	
	public:
		//Different functions that are used in terms of figuring out what happens in the process.

		void startPressureMonitor(double* force, int* );
		//Figure out whether or not the values are increasing 
		bool increasing(unsigned int resistance);

		//Return true if the resistance values are decreasing
		bool decreasing(unsigned int resistance);

		//Return true if it is in contact with the ground.
		bool ground(unsigned int resistance);

		//return true if it is not in contact with the round.
		bool notOnGround(unsigned int resistance);



		//return the force that is applied to the system
		int getForce(unsigned int resistance, unsigned int voltage);

	private:

	private:
		//Any different types of variables that are needed in the library.
		int voltage_, resistance_, force_;

};

#endif