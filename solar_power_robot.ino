#include <BluetoothSerial.h> 
#include <ESP32Servo.h> 
BluetoothSerial SerialBT; 
const int motor1Pin1 = 2;    // Motor 1 (Front Left) IN1 
const int motor1Pin2 = 4;    // Motor 1 (Front Left) IN2 
const int motor2Pin1 = 15;    // Motor 1 (Front Left) IN1 
const int motor2Pin2 = 21;  
const int soilMoisturePin = 34; // Soil moisture sensor pin 
bool moveServo = false; 
// Servo motor for ploughing mechanism 
Servo myServo; 
const int PloughservoPin = 26; // Pin connected to the servo motor 
Servo seedServo; 
const int seedservoPin = 25; 
const int motorEN = 5; // EN1 on the L293D 
const int motorIn1 = 18; // IN1 on the L293D 
const int motorIn2 = 19; // IN2 on the L293D 
void setup() { 
// Initialize the serial communication with the Bluetooth terminal 
Serial.begin(115200); 
SerialBT.begin("ESP32_BT_Motor"); // Bluetooth name 
// Set motor pins as outputs 
pinMode(motor1Pin1, OUTPUT); 
pinMode(motor1Pin2, OUTPUT); 
pinMode(motor2Pin1, OUTPUT); 
pinMode(motor2Pin2, OUTPUT); 
                                                                                                     
pinMode(motorEN, OUTPUT); 
pinMode(motorIn1, OUTPUT); 
pinMode(motorIn2, OUTPUT);   
// Start with the motor stopped 
digitalWrite(motorIn1, LOW); 
digitalWrite(motorIn2, LOW); 
digitalWrite(motorEN, LOW);  
digitalWrite(motor1Pin1, LOW); 
digitalWrite(motor1Pin2, LOW); 
digitalWrite(motor2Pin1, LOW);    
digitalWrite(motor2Pin2, LOW); 
// Initialize soil moisture sensor pin 
pinMode(soilMoisturePin, INPUT); 
pinMode(seedservoPin,OUTPUT); 
pinMode(PloughservoPin, OUTPUT); 
// Attach the servo motor to the servo pin 
myServo.attach(PloughservoPin); 
seedServo.attach(seedservoPin); 
} 
void loop() { 
if (SerialBT.available()) { 
char command = SerialBT.read(); 
if (command == '1') { 
// Start moving the servo 
moveServo = true; 
Serial.println("Servo movement started"); 
} else if (command == '0') { 
// Stop moving the servo 
                                                                                                      
moveServo = false; 
Serial.println("Servo movement stopped"); 
} 
else if (command == '3'){ 
myServo.write(180); 
Serial.println("Servo at 180 degrees"); 
} 
else if (command == '4'){ 
myServo.write(0); 
Serial.println("Servo at 180 degrees"); 
} 
else if (command == 'F') 
{ // Forward command 
digitalWrite(motor1Pin1, HIGH); 
digitalWrite(motor1Pin2, LOW); 
digitalWrite(motor2Pin1, HIGH); 
digitalWrite(motor2Pin2, LOW); 
Serial.println("Motor moving forward"); 
} 
else if (command == 'B') { // Stop command 
digitalWrite(motor1Pin1, LOW); 
digitalWrite(motor1Pin2, HIGH); 
digitalWrite(motor2Pin1, LOW); 
digitalWrite(motor2Pin2, HIGH);  
Serial.println("Motor moving backward"); 
} 
else if (command == 'L'){ 
digitalWrite(motor1Pin1, LOW); 
                                                                                                    
digitalWrite(motor1Pin2, HIGH); 
digitalWrite(motor2Pin1, HIGH); 
digitalWrite(motor2Pin2, LOW); 
Serial.println("Motor moving left");   
} 
else if (command == 'R'){ 
digitalWrite(motor1Pin1, HIGH); 
digitalWrite(motor1Pin2, LOW); 
digitalWrite(motor2Pin1, LOW); 
digitalWrite(motor2Pin2, HIGH);       
Serial.println("Motor moving right"); 
} 
else if (command == 'S'){ 
digitalWrite(motor1Pin1, LOW); 
digitalWrite(motor1Pin2, LOW); 
digitalWrite(motor2Pin1, LOW); 
digitalWrite(motor2Pin2, LOW);      
} 
else if (command == 'M') { // Soil moisture sensing 
int sensorValue = analogRead(soilMoisturePin); // Read the analog value from the 
sensor 
float percentage = 100-map(sensorValue, 0, 4095, 0, 100); // Convert the analog value 
to a percentage (0-100) 
SerialBT.println("Soil Moisture: "); 
SerialBT.println(percentage); 
SerialBT.println("%"); 
if (percentage<=30) { 
SerialBT.println("Soil is dry!\n"); 
                                                                                                      
} 
else { 
SerialBT.println("Soil is wet!\n"); 
} 
} 
if (command == '7') 
{ 
digitalWrite(motorIn1, HIGH); 
digitalWrite(motorIn2, LOW); 
digitalWrite(motorEN, HIGH); 
} 
else if (command =='8') { 
digitalWrite(motorIn1, LOW); 
digitalWrite(motorIn2, LOW); 
digitalWrite(motorEN, LOW); 
} 
} 
if (moveServo) { 
for (int pos = 0; pos <= 50; pos++) { 
seedServo.write(pos); 
delay(20); // Delay to control the speed of the servo 
} 
for (int pos = 50; pos >= 0; pos--) { 
seedServo.write(pos); 
delay(20); // Delay to control the speed of the servo 
} 
} 
}