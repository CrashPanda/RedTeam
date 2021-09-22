// Green
int const LEFT_FORWARD = 11;
int const RIGHT_FORWARD = 7;
// Red
int const LEFT_REVERSE = 12;
int const RIGHT_REVERSE = 8;
// Yellow
int const onOff_LEFT = 10;
int const onOff_RIGHT = 9;

int my_number = 345;

void setup()
{
  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(LEFT_REVERSE, OUTPUT);
  pinMode(RIGHT_REVERSE, OUTPUT);
  pinMode(onOff_LEFT, OUTPUT);
  pinMode(onOff_RIGHT, OUTPUT);
}

void loop()
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

void story3()
{
  digitalWrite(onOff_LEFT, HIGH);
  digitalWrite(onOff_RIGHT, HIGH);
  digitalWrite(LEFT_FORWARD, HIGH);
  digitalWrite(RIGHT_FORWARD, HIGH);
  delay(5000); // Wait for 5000 millisecond(s)
  digitalWrite(LEFT_FORWARD, LOW);
  digitalWrite(RIGHT_FORWARD, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(LEFT_REVERSE, HIGH);
  digitalWrite(RIGHT_REVERSE, HIGH);
  delay(2000); // Wait for 2000 millisecond(s)
  digitalWrite(LEFT_REVERSE, LOW);
  digitalWrite(RIGHT_REVERSE, LOW);
  delay(10000); // Wait for 10000 millisecond(s)
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
