/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

const int FILTERSIZE = 15;

int readings[FILTERSIZE] = {0};

int highPass (){

  readings[0] = abs(analogRead(A0) - 330);

  for(int i = FILTERSIZE-1; i > 0; i--){
    readings[i] = readings [i-1];
  }

  int sum = 0;

  for (int i = 0; i<FILTERSIZE; i++){
    sum += readings[i];
  }

  return sum/FILTERSIZE;
}


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = highPass();
  // print out the value you read:
  Serial.println(sensorValue);
  delay(1);        // delay in between reads for stability
}
