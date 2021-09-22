// Green
int const LEFT_FORWARD = 11;
int const RIGHT_FORWARD = 7;
// Red
int const LEFT_REVERSE = 12;
int const RIGHT_REVERSE = 8;
// Yellow
int const onOff_LEFT = 10;
int const onOff_RIGHT = 9;

int rotations = 870;

const int RIGHT_FEEDBACK = 2; // Pin numbers on Rover
const int LEFT_FEEDBACK = 3;

volatile int leftcounter = 0; // initiate counter to zero for start
volatile int rightcounter = 0; // counter could always be reset

void setup()
{
  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(LEFT_REVERSE, OUTPUT);
  pinMode(RIGHT_REVERSE, OUTPUT);
  pinMode(onOff_LEFT, OUTPUT);
  pinMode(onOff_RIGHT, OUTPUT);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(LEFT_FEEDBACK),LeftMotorISR,RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_FEEDBACK),RightMotorISR,RISING);
}

void loop()
{
  story4();
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
  
void forwards()
{
  digitalWrite(onOff_LEFT, HIGH);
  digitalWrite(onOff_RIGHT, HIGH);
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

void LeftMotorISR(){
// adds one to the counter on each motor revolution
leftcounter++;
}

void RightMotorISR(){
// adds one to the counter on each motor revolution
rightcounter++;
}
