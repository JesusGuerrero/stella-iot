Sound_Sensor_LED

int sound_sensor = 2;
int RLED = 8;
int GLED = 10;
int BLED = 9;

void setup() {
  pinMode(sound_sensor, INPUT);
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);

}

void loop() {
  int status_sensor = digitalRead(sound_sensor);
  if (status_sensor == 1){
          digitalWrite(RLED, LOW);
          digitalWrite(GLED, LOW);
          digitalWrite(BLED, LOW);
          
  }

  
  else {
          digitalWrite(RLED, HIGH);
          digitalWrite(GLED, HIGH);
          digitalWrite(BLED, HIGH);
  }


}
