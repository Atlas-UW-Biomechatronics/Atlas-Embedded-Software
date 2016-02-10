//Documentation

#ifndef _HBRIDGE_CONTROL_
#define _HBRIDGE_CONTROL_

class HBridge {
public:

	//function prototypes
	HBridge(/* parameters, such as pins */);

	bool ifOn();
	bool isForward();

	void turnOn();
	void turnOff();
	void forward();
	void backward();

private:

	//variables

	int pin1; //an example of a class variable. This can store one analog pin that the HBridge uses to function

	bool isOn;
	bool isForward;

};

#endif