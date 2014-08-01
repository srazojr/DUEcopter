int pingPin = 7;
int inPin = 6;
 
void setup() {
Serial1.begin(9600);
}
 
void loop()
{
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, inches,cm;
 
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
 
  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(inPin, INPUT);
  duration = pulseIn(inPin, HIGH);
 
  // convert the time into a distance
  inches = duration / 74 / 2;
  cm = duration / 29 / 2;
 Serial1.println(" ");
 Serial1.print("inches:  ");
 Serial1.println(inches);
 Serial1.print("cm    :  ");
 Serial1.println(cm);
 
  delay(100);
}
 

  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.

  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
