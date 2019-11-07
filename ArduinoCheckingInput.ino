<<<<<<< HEAD
#define SET_COMMAND 's'
#define ABORT_COMMAND 'a'
#define REQUEST_COMMAND 'r'

#define ledPin LED_BUILTIN
#define monitorPin 12
#define readyPin 11
#define digIN1Pin 10 //input of controller, output of Arduino
#define digIN2Pin 9
#define enablePin 8
#define directionPin 7
#define speedPin 6
#define zpol 1 //for the rpm function
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

  //desired rpm
  //current rpm
  //we DONT want overspin of turbine.
  //if turbine rpm is greater than requested,
  //    increase pwm to slow motor down.

  //int current_rpm = measure_rpm();

  //attenuation_curve0 (low atten)
  //double attenuation_curve0 = 0.25; 
  //attenuation_curve1 (med atten)
  //double attenuation_curve1 = 0.60;
  //attenuation_curve2 (max atten)
  //double attenuation_curve2 = 0.90;
  return 0.0;
}
//TODO: implement functionality to set controller inputs to get designated rpm
void set_rpm(){
  int rpm = read_sent_rpm();
  
  float n_min = 125;
  float n_max = 5000;
  float pwmVoltage = ((rpm - n_min) * 4.9 / (n_max - n_min)) + 0.1;
  pwmVoltage = pwmVoltage * (255 / 5); // convert to range 0-255
  Serial.write(int(pwmVoltage));
  analogWrite(speedPin, int (pwmVoltage));
  digitalWrite(enablePin, HIGH);
}

void turn_off_motor(){
  digitalWrite(ledPin, LOW); 
  digitalWrite(digIN1Pin, LOW);
  digitalWrite(digIN2Pin, HIGH); //matches specification
  digitalWrite(enablePin, LOW);
  digitalWrite(directionPin, LOW); //Clockwise
  digitalWrite(speedPin, LOW); 
}
//TODO: implement a way to measure the rpm via the rpm output of the controller(it sends a frequency back, measure it using a timer).
//hint: you will most likely get a number with decimals, round the value down to an integer
int measure_rpm(){
  while (digitalRead(monitorPin) == 1) //to get a starting point
  while (digitalRead(monitorPin) == 0);
  unsigned long measuringTime1 = millis(); //returns ms elapsed after program started running, returns long
  while (digitalRead(monitorPin) == 1);
  while (digitalRead(monitorPin) == 0);
  unsigned long measuringTime0 = millis();

  unsigned long periodMS = (measuringTime0 - measuringTime1); // one wave, ms
  float period = (float(periodMS) / 60000); //minutes
  float freq = (1 / period);
  float n = ((freq * 20) / zpol); //rpm
  return int(n);
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
  pinMode(ledPin, OUTPUT);
  pinMode(monitorPin, INPUT);
  pinMode(readyPin, INPUT);
  pinMode(digIN1Pin, OUTPUT);
  pinMode(digIN2Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  pinMode(speedPin, OUTPUT); //uses analogWrite instead of digitalWrite (it's PWM) 
  turn_off_motor();
}

void loop() 
{
  analogWrite(5,191);
  /*if (Serial.available() > 0){
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
  }*/
}
=======
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
>>>>>>> d37ba09dd7dd9b1cb900e0dcc21e578fb3fa801d
