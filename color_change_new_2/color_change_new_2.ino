#include <SoftwareSerial.h>
#include <Wire.h>//Include libraries: SoftwareSerial & Wire
SoftwareSerial BT(11,12); //Define PIN11 & PIN12 as RX and TX pins

int sound_sensor = 2;
//RGB LED Pins
int R_LED = 8;
int G_LED = 10;
int B_LED = 9;
//RED LED at Pin 13
int RED_LED = 13;
String RGB = ""; //store RGB code from BT
String RGB_Previous = "255.255.255)"; //preserve previous RGB color for LED switch on/off, default White
String ON = "ON"; //Check if ON command is received
String OFF = "OFF"; //Check if OFF command is received
boolean RGB_Completed = false;

void setup() {
  Serial.begin(9600); //Arduino serial port baud rate：9600
  BT.begin(9600);//My HC-05 module default baud rate is 9600
  RGB.reserve(30);

  pinMode(sound_sensor, INPUT);
  pinMode(RED_LED, OUTPUT); 
  //Set pin13 as output for LED, 
}

void loop() {
  // put your main code here, to run repeatedly: 

  int status_sensor = digitalRead(sound_sensor);
      if (status_sensor == 1){
               digitalWrite(13, LOW);
      
        



 
  //Read each character from Serial Port(Bluetooth)
  while(BT.available()){
    char ReadChar = (char)BT.read();

    // Right parentheses ) indicates complet of the string
    if(ReadChar == ')'){
      RGB_Completed = true;
    }else{
       RGB += ReadChar;
    }
  }
  
  //When a command code is received completely with ')' ending character
  if(RGB_Completed){
   //Print out debug info at Serial output window
      Serial.print("RGB:");
      Serial.print(RGB);
      Serial.print("     PreRGB:");
      Serial.println(RGB_Previous);
      
      if(RGB==ON){
          digitalWrite(13,HIGH);
          RGB = RGB_Previous; //We only receive 'ON', so get previous RGB color back to turn LED on
          Light_RGB_LED();          

      }else if(RGB==OFF){
          digitalWrite(13,LOW);
          RGB = "0.0.0)"; //Send OFF string to turn light off
          Light_RGB_LED();
      }else{
          //Turn the color according the color code from Bluetooth Serial Port
          Light_RGB_LED();   
          RGB_Previous = RGB;
    
      }
      //Reset RGB String  

      RGB = "";
      RGB_Completed = false;

    
  }//end if of check if RGB completed


}
  
     else {
               digitalWrite(13, HIGH);
      }
  
} // end of loop

void Light_RGB_LED(){

  int SP1 = RGB.indexOf('.');
  int SP2 = RGB.indexOf('.', SP1+1);
  int SP3 = RGB.indexOf('.', SP2+1);
  String R = RGB.substring(0, SP1);
  String G = RGB.substring(SP1+1, SP2);
  String B = RGB.substring(SP2+1, SP3);

  //Print out debug info at Serial output window
  Serial.print("R=");
  Serial.println( constrain(R.toInt(),0,255));
  Serial.print("G=");
  Serial.println(constrain(G.toInt(),0,255));
  Serial.print("B=");
  Serial.println( constrain(B.toInt(),0,255));
  //Light up the LED with color code

  analogWrite(R_LED,  (R.toInt()));
  analogWrite(G_LED, (G.toInt()));
  analogWrite(B_LED,  (B.toInt()));

}


