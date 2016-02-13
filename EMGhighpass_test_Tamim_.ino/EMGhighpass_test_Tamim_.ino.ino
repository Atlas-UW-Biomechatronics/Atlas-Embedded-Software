const int FILTERSIZE = 15;

int readings[FILTERSIZE] = {0};

int rollingAvg (){

  //330 is the approximate average during testing. Line below normalizes and rectifies analog readings
  //and stores them in the first index of the array.
  readings[0] = abs(analogRead(A0) - 330);

  //Shifts data down the array. Will be replaced with linked list
  for(int i = FILTERSIZE-1; i > 0; i--){
    readings[i] = readings [i-1];
  }

  int sum = 0;

  //Finds the sum of the data in the array. Will be replaced by linked list
  for (int i = 0; i<FILTERSIZE; i++){
    sum += readings[i];
  }

  return sum/FILTERSIZE;
}

void setup() {
  // initialize serial communication at 9600 bits per second
  Serial.begin(9600);
}

void loop() {

  int sensorValue = rollingAvg();

  Serial.println(sensorValue); //prints serial readings to serial plotter for visualization
  delay(1); // delay in between reads for stability
}
