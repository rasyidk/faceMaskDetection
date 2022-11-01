#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Servo.h> 

// firebase
#define FIREBASE_HOST "mask-162b2.firebaseio.com" //dbname
#define FIREBASE_AUTH "w4qi28xs02kKUFcs6e8gBpxowV9gBul4EZTapgA5" //authkey

//wifi
#define WIFI_SSID "PAXTONBUOS" //SSID
#define WIFI_PASSWORD "rollwithit" //Password

// ultrasonic
#define trigPin 4
#define echoPin 0

//servo
Servo myservo;          
int pos = 0;

void setup() {
 Serial.begin(9600);

 //WIFI
 WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 Serial.print("connecting");
 while (WiFi.status() != WL_CONNECTED) {
 Serial.print("v");
 delay(500);
 }
 Serial.println();
 Serial.print("konek");
 Serial.println(WiFi.localIP());
 Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

 //Ultrasonic
 pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //servo
  myservo.attach(2);  
}

void loop() {
  //Firebase
 int val = Firebase.getInt("val");
 Serial.println(val);

 //Ultrasonic
  long duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println(" cm");
 delay(100);

  
 if(distance < 10 && val == 1 ){
  for(pos = 0; pos < 120; pos += 1)  
 {
  myservo.write(pos);   
  delay(15);                  
 } 
 for(pos = 120; pos>=1; pos-=1)  
 {                               
  myservo.write(pos);                   
  delay(15);                        
 }
 }
}
