#define BATTERY_DIGITALPIN_EN 52
#define BATTERY_ANALOGPIN_PROBE 0
#define BATTERY_BATTERYTHRESHOLD 4.3


class Battery_handler{
  int digitalPinEN,analogPinPROBE;
  float batteryThreshold;
  public:
  void begin(int,int,float);//digital, analog, battery threshold
  void update(void);
  float voltage;
  bool acceptable;
  void thresholdRST(void){acceptable=true;};//used for debug. Normally the "acceptable" bool will be false if it falls below the threshold ever. 
} Battery;


void Battery_handler::begin(int digitalPin, int analogPin, float batteryTh){
  digitalPinEN=digitalPin;
  analogPinPROBE=analogPin;
  batteryThreshold=batteryTh;
  
  analogReadResolution(12);
  pinMode(digitalPinEN, OUTPUT);
  digitalWrite(digitalPinEN,LOW);
  acceptable=true;
  this->update();
}

void Battery_handler::update(void){
  int raw_voltage;
  digitalWrite(digitalPinEN,HIGH);
  raw_voltage=analogRead(analogPinPROBE);
  digitalWrite(digitalPinEN,LOW);
  voltage=raw_voltage*5*3.3;//5 is the voltage divider ratio, 3.3 is the ref.
  voltage/=4096;//12 bits 
  if (voltage>batteryThreshold){
    return;
  }
  acceptable=false;
  return;
}

void setup() {
  Serial1.begin(9600);
  Battery.begin(BATTERY_DIGITALPIN_EN,BATTERY_ANALOGPIN_PROBE,BATTERY_BATTERYTHRESHOLD);
  // put your setup code here, to run once:

}

void loop() {
  float bat_level;
  Battery.update();
  bat_level=Battery.voltage;
  
  Serial1.print("Batt: ");
  Serial1.print(bat_level);
  Serial1.print("        THRHLD: ");
  if (Battery.acceptable){
    Serial1.println("yes");
  } else {
    Serial1.println("no");
  }
  Battery.thresholdRST();
  delay(500);
  // put your main code here, to run repeatedly:
  
}
