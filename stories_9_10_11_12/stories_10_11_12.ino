#include <NewPing.h>

// Green
int const LEFT_FORWARD = 11;
int const RIGHT_FORWARD = 7;
// Red
int const LEFT_REVERSE = 12;
int const RIGHT_REVERSE = 8;
// Yellow
int const onOff_LEFT = 10;
int const onOff_RIGHT = 9;

//Echo
int const TRIGGER_PIN  4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
int const ECHO_PIN     5  // Arduino pin tied to echo pin on the ultrasonic sensor.
int const MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

//light_sensors
  
const int LEFT_LDR = A7;
const int CENTRE_LDR = A6;
const int RIGHT_LDR = A2;

int rotations = 870;

int turnLeftSpeedSlow = 100; //parameters used when turning gradual left
int turnLeftSpeedFast = 250;
int turnRightSpeedSlow = 100; //parameters used when turning gradual right
int turnRightSpeedFast = 250;
int leftSpeed = 100; 
int rightSpeed = 100;
int diff; //difference between left and right motor readings

const int RIGHT_FEEDBACK = 2; // Pin numbers on Rover
const int LEFT_FEEDBACK = 3;

volatile int leftcounter = 0; // initiate counter to zero for start
volatile int rightcounter = 0; // counter could always be reset

//Echo down
const int TRIGGER_DOWN = 13;
const int ECHO_DOWN = 17;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
NewPing down_sonar(TRIGGER_DOWN, ECHO_DOWN, MAX_DISTANCE);


void setup()
{
  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(LEFT_REVERSE, OUTPUT);
  pinMode(RIGHT_REVERSE, OUTPUT);
  pinMode(onOff_LEFT, OUTPUT);
  pinMode(onOff_RIGHT, OUTPUT);
  pinMode(LEFT_LDR, INPUT);
  pinMode(CENTRE_LDR, INPUT);
  pinMode(RIGHT_LDR, INPUT);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(LEFT_FEEDBACK),LeftMotorISR,RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_FEEDBACK),RightMotorISR,RISING);
  sonar.ping.cm();
  down_sonar.ping.cm();
}

void loop()
{
 story11();
}

void story11()
{

    // read the value from the sensor
  int leftLight = analogRead(LEFT_LDR);
  int centreLight = analogRead(CENTRE_LDR);
  int rightLight = analogRead(RIGHT_LDR);
    int lowestReading = 1200;
    int currentPosition = 0;
    int bestPosition = 0;
  // print the sensor reading so you know its range
  Serial.print(" Centre light " + String(centreLight));
    // while initial 360 turn we will check brightness
    //once 360 completed, turn to best position and go forward
    
}

void checkBrightness(){
    hard_left(255,255);
    delay(250);
    currentPosition = currentPosition + 45;
  Serial.print(" Centre light " + String(centreLight));
    if (centreLight < lowestReading) {
    lowestReading = centreLight;
    bestPosition = currentposition;
  }
}

void story10()
{
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(down_sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  if (down_sonar.ping_cm > 14)
  {
    fastBrake();
    delay(1000);
    // ?put a while loop here left counter + 44 rotations
    //how do we know when 5cm from drop ?use this to calculate 10cm
    reverse();//for 10cm using a method above
    delay(500);
    fastBrake();
    exit(0);
  }
  else 
  {
    forwards();
  }
}

void story9() 
{
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  if ((sonar.ping_cm() > 0) and (sonar.ping_cm() < 13)) 
  {
      fastBrake();
      delay(1000);
      reverse();
      delay(500);
      brake();
      delay(250);
      hard_left(255,255);
      delay(500);
      brake();
  }
  else 
  {
      forwards();
  }
}


void story8()
{
  forwardsAndLeftTurn(1500, 500);
  forwardsAndLeftTurn(1500, 500);
  forwardsAndLeftTurn(1500, 500);
  forwardsAndLeftTurn(1500, 500);
  forwardsAndRightTurn(1500, 600);
  forwardsAndRightTurn(1500, 600);
  forwardsAndRightTurn(1500, 600);
  forwardsAndRightTurn(1500, 600);
  exit(0);
}

void story7()
{
 forwards();
 delay(1500);
 brake();
 delay(1000);
 hard_left(255, 255);//turn 1
 delay(500);
 brake();
 delay(1000);
 
 forwards();
 delay(1500);
 brake();
 delay(1000);
 hard_left(255, 255);//turn 2
 delay(500);
 brake();
 delay(1000);
  
 forwards();
 delay(1500);
 brake();
 delay(1000);
 hard_left(255, 255);//turn 3
 delay(500);
 brake(); 
 delay(1000);
 
 forwards();
 delay(1500);
 brake();
 delay(1000);
 hard_left(255, 255);//turn 4
 delay(500);
 brake();
  
 exit(0);
}

void story7_v2()
{
  forwardsAndLeftTurn(1500, 500);
  forwardsAndLeftTurn(1500, 500);
  forwardsAndLeftTurn(1500, 500);
  forwardsAndLeftTurn(1500, 500);
  exit(0);
}

void forwardsAndLeftTurn(int forwardsTime, int turnTime)
{
 forwards();
 delay(forwardsTime);
 brake();
 delay(1000);
 hard_left(255, 255);
 delay(turnTime);
 brake();
 delay(1000);
}

void forwardsAndRightTurn(int forwardsTime, int turnTime)
{
 forwards();
 delay(forwardsTime);
 brake();
 delay(1000);
 hard_right(255, 255);
 delay(turnTime);
 brake();
 delay(1000);
}

void story6() //added print statements to debug, consider smaller sharper turns and reduce speed?
{
  //Serial.println(millis());
  while(millis() < 10000)
  {
    
    diff = leftcounter - rightcounter;
    if(diff < -2) //if right counter is higher rover is vearing left so needs to correct by turning to right
    { 
      gradual_right(); //left motor faster than right motor
      //Serial.println("turning right ");
    }
    else if(diff > 2) //if left counter is higher rover is vearing to right so needs to correct by turning to left
    { 
      gradual_left(); //right motor faster than left motor
      //Serial.print("turning left ");
    }
    else 
    {
      forwards();
      //Serial.print("going straight ");
    }
  }
  
  Serial.print("Has reached 10 secs");
  fastBrake();
  delay(1000);
  exit(0);
  
}

void story6_v2() //changed to controlled_forward with slower speed
{
  
  while(millis() < 10000)
  {
    
    diff = leftcounter - rightcounter;
    if(diff < -2) //if right counter is higher rover is vearing left so needs to correct by turning to right
    { 
      gradual_right(); //left motor faster than right motor
      
    }
    else if(diff > 2) //if left counter is higher rover is vearing to right so needs to correct by turning to left
    { 
      gradual_left(); //right motor faster than left motor
      
    }
    else 
    {
      forwardControlled(100,100);  
    }
  }
  
  Serial.print("Has reached 10 secs");
  fastBrake();
  delay(1000);
  exit(0);
  
}

void story6_v3() //delay added on corrections
{
  
  while(millis() < 10000)
  {
    
    diff = leftcounter - rightcounter;
    if(diff < -2) //if right counter is higher rover is vearing left so needs to correct by turning to right
    { 
      gradual_right(); //left motor faster than right motor
      delay(50);
      
    }
    else if(diff > 2) //if left counter is higher rover is vearing to right so needs to correct by turning to left
    { 
      gradual_left(); //right motor faster than left motor
      delay(50);
    }
    else 
    {
      forwardControlled(100,100);  
    }
  }
  
  Serial.print("Has reached 10 secs");
  fastBrake();
  delay(1000);
  exit(0);
  
}

void story6_v4() //increasing motor speed
{
  
  while(millis() < 10000)
  {
    
    diff = leftcounter - rightcounter;
    if(diff < -2) //if right counter is higher, diff is negative and rover is vearing left so needs to correct by turning to right
    { 
      leftSpeed = leftSpeed + 10;
      turn(leftSpeed, rightSpeed); //left motor faster than right motor
      
    }
    else if(diff > 2) //if left counter is higher, diff is positive, rover is vearing to right so needs to correct by turning to left
    { 
      rightSpeed = rightSpeed + 10;
      turn(leftSpeed, rightSpeed);
    }
    else 
    {
      forwardControlled(100,100);
      
    }
  }
} 
  
void story6_v5() //increasing motor speed
{
  while(millis() < 10000)
  {
      forwardControlled(150,150);
  }
  
  Serial.print("Has reached 10 secs");
  fastBrake();
  delay(1000);
  exit(0);
}

void story5()
{
  forwards();
  delay(1000);
  while(millis() < 10000){
    gradual_left();
    delay(2000);
    gradual_right();
    delay(2000);
  }
  Serial.print("Has reached 10 secs");
  fastBrake();
  delay(1000);
  exit(0);
}
 


void story4()
{
  if(leftcounter >= rotations){
    Serial.print("Left Counter ");
    Serial.println(leftcounter); 
    Serial.print("Right Counter ");
    Serial.println(rightcounter);
    Serial.println("Counter has reached 870");
    brake();
    delay(3000);
    exit(0);
  }
  // Just print out the values to show counter operating
  Serial.print("Left Counter ");
  Serial.println(leftcounter); 
 // This is printing then a new Line after
  Serial.print("Right Counter ");
  Serial.println(rightcounter);
  forwards();
  
}

void story3()
{
 forwards();
 delay(5000);
 brake();
 delay(1000);
 reverse();
 delay(2000);
 brake();
 delay(1000);
}
  
void forwardControlled(int leftMotorSpeed, int rightMotorSpeed) //change this function to accept parameters
{
  analogWrite(onOff_LEFT, leftMotorSpeed); 
  analogWrite(onOff_RIGHT, rightMotorSpeed);
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(RIGHT_FORWARD, HIGH); 
  digitalWrite(LEFT_REVERSE, LOW);
  digitalWrite(RIGHT_REVERSE, LOW);
  
}

void forwards()
{
  digitalWrite(onOff_LEFT, HIGH);
  digitalWrite(onOff_RIGHT, HIGH);
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(RIGHT_FORWARD, HIGH); 
  digitalWrite(LEFT_REVERSE, LOW);
  digitalWrite(RIGHT_REVERSE, LOW);
  
}

void gradual_right() //change this to turn? add parameter?
{
  analogWrite(onOff_LEFT, turnRightSpeedFast);
  analogWrite(onOff_RIGHT, turnRightSpeedSlow);
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(RIGHT_FORWARD, HIGH); 
  digitalWrite(LEFT_REVERSE, LOW);
  digitalWrite(RIGHT_REVERSE, LOW);
}

void gradual_left() //change this to turn? add parameters?
{
  analogWrite(onOff_LEFT, turnLeftSpeedSlow);
  analogWrite(onOff_RIGHT, turnLeftSpeedFast);
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(RIGHT_FORWARD, HIGH); 
  digitalWrite(LEFT_REVERSE, LOW);
  digitalWrite(RIGHT_REVERSE, LOW);
}

void turn(int leftSpeed, int rightSpeed)
{
  analogWrite(onOff_LEFT, leftSpeed);
  analogWrite(onOff_RIGHT, rightSpeed);
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(RIGHT_FORWARD, HIGH); 
  digitalWrite(LEFT_REVERSE, LOW);
  digitalWrite(RIGHT_REVERSE, LOW);
}

void reverse()
{
  digitalWrite(onOff_RIGHT, HIGH);
  digitalWrite(onOff_LEFT, HIGH);
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(LEFT_REVERSE, HIGH);
  digitalWrite(RIGHT_REVERSE, HIGH); 
}

void brake()
{
  digitalWrite(onOff_LEFT, LOW);
  digitalWrite(onOff_RIGHT, LOW);
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(RIGHT_FORWARD, LOW); 
  digitalWrite(LEFT_REVERSE, LOW);
  digitalWrite(RIGHT_REVERSE, LOW);
}

void fastBrake()
{
  digitalWrite(onOff_LEFT, HIGH);
  digitalWrite(onOff_RIGHT, HIGH);
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(RIGHT_FORWARD, LOW); 
  digitalWrite(LEFT_REVERSE, LOW);
  digitalWrite(RIGHT_REVERSE, LOW);
}
  
void hard_right(int leftSpeed, int rightSpeed) //add parameter?
{
  analogWrite(onOff_LEFT, leftSpeed);
  analogWrite(onOff_RIGHT, rightSpeed);
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(RIGHT_FORWARD, LOW); 
  digitalWrite(LEFT_REVERSE, LOW);
  digitalWrite(RIGHT_REVERSE, HIGH);
}
  

void hard_left(int leftSpeed, int rightSpeed) //add parameters?
{
  analogWrite(onOff_LEFT, leftSpeed);
  analogWrite(onOff_RIGHT, rightSpeed);
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(RIGHT_FORWARD, HIGH); 
  digitalWrite(LEFT_REVERSE, HIGH);
  digitalWrite(RIGHT_REVERSE, LOW);
}

void LeftMotorISR(){
// adds one to the counter on each motor revolution
leftcounter++;
}

void RightMotorISR(){
// adds one to the counter on each motor revolution
rightcounter++;
}
