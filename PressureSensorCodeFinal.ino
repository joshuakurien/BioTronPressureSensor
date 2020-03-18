/*
Project: BioTron Code
January 8, 2020

Author: Joshua Kurien
*/

//pins used to control which sensor reading you are getting from mux by sending an output to the mux
#define OUTPUT1 11 
#define OUTPUT2 12
#define OUTPUT3 13

#define SENSOR_PIN1 A0
#define SENSOR_PIN2 A1

int binaryVals[9][3]={{0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1}, {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}}; //binary vals to get readings from all pins connected to mux

int sensorReading[9] = {0};

void setup()
{
  Serial.begin(9600);
  pinMode(OUTPUT1, OUTPUT);
  pinMode(OUTPUT2, OUTPUT);
  pinMode(OUTPUT3, OUTPUT);
  pinMode(SENSOR_PIN1, INPUT);
  pinMode(SENSOR_PIN2, INPUT);
}

void readMux (int binRange) { //sends signal to mux for which sensor you are readinga and then reads at that sensor value
   digitalWrite(OUTPUT1, binaryVals[binRange][0]);
   digitalWrite(OUTPUT2, binaryVals[binRange][1]);
   digitalWrite(OUTPUT3, binaryVals[binRange][2]);

   sensorReading[binRange] = analogRead(SENSOR_PIN1);
}

void sendVals (int num) { //sends sensor values to serial port
   Serial.print("Value at sensor ");
   Serial.print(num + 1);
   Serial.print(" is ");
   Serial.println(sensorReading[num]);
}

void loop() {
  for (int binRange = 0; binRange < 8; binRange++) //used to cycle through mux
  {
    readMux(binRange);
    sendVals(binRange);
    delay(2000);
  }
  sensorReading[8] = analogRead(SENSOR_PIN2);
  sendVals(8);
}
