#define SET_COMMAND 's'
#define ABORT_COMMAND 'a'
#define REQUEST_COMMAND 'r'

//TODO:  define all the pins we need i.e. assign all motor controller inputs as a pin 
#define ledPin LED_BUILTIN

//we will call this blink function when we want to verify that something works
void blink(){
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);
}
//reads the desired rpm sent by the gui
int read_sent_rpm(){
  byte lower_byte = Serial.read();
  byte upper_byte = Serial.read();
  return (upper_byte << 8) | lower_byte;
}
//TODO: based off of rpm, calculate pwm duty cycle needed to set controller to proper rpm
float calc_pwm(int rpm){
  return 0.0;
}
//TODO: implement functionality to set controller inputs to get designated rpm
void set_rpm(){
  int rpm = read_sent_rpm();
  float duty_cycle = calc_pwm(rpm);
  //generate pwm with calculated duty cycle
}
//TODO: set controller inputs such that the motor is turned off and controller returns to default state
void turn_off_motor(){
  
}
//TODO: implement a way to measure the rpm via the rpm output of the controller(it sends a frequency back, measure it using a timer).
//hint: you will most likely get a number with decimals, we don't care about that, round the value down to an integer
int measure_rpm(){
  return 0;
}
//sends the measured rpm back to the gui
void send_rpm(){
  int measured_rpm = measure_rpm();
  byte lower_byte = measured_rpm & 0x00FF;
  byte upper_byte = (measured_rpm & 0xFF00) >> 8;
  Serial.write(lower_byte);
  Serial.write(upper_byte);
}

void setup() 
{
  Serial.begin(9600);
  //TODO: initialize all controller pins as either outputs or inputs
  //TODO: Set all pins to their default state i.e. controller enable should initally be off
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}


void loop() 
{
  if (Serial.available() > 0){
    byte incomingData = Serial.read();
    //set rpm command
    if (incomingData == SET_COMMAND){
      set_rpm();
    }
    //abort command (turn off motor)
    else if (incomingData == ABORT_COMMAND){
       turn_off_motor();
    }
    //request RPM command (send measured rpm back to gui)
    else if (incomingData == REQUEST_COMMAND){
       send_rpm();
    }
  }
}
