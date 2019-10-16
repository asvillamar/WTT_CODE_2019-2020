//TODO:
//add an option for selecting the speed range we want
//make the set rpm fit into the resolution of the controller



//Library Imports
import controlP5.*;
import processing.serial.*;

//Global objects
final int READ_PERIOD = 500;
ControlP5 cp5;  //controlp5 object 
Serial port;  //port to communciate with arduino
String port_name = "COM3";
String state = "motor off";
int measured_rpm = -1;
Textfield tf;
Bang bang;
ControlTimer rpm_timer;

//same as arduino
void setup(){
  //prints a list of fonts to choose from
  //String[] fontlist = PFont.list();
  //printArray(fontlist);
  
  size(700,400);  //window size
  cp5 = new ControlP5(this); 
  rpm_timer = new ControlTimer();
  //port = new Serial(this,port_name,115200);  //instantiate port with port name and baudrate
  
  
  
  //numberbox for setting rpm
  
  tf = cp5.addTextfield("Target RPM")
  .setPosition(int(width/35),int(height/20))
  .setSize(int(width/2.3),int(height/5))
  .setFont(createFont("arial",50))
  .setAutoClear(false);
  
  /*
  //control event to send numberbox text to arduino
  cp5.addBang("Set")
  .setPosition(180,20)
  .setSize(40,40)
  .setFont(createFont("arial",12))
  .getCaptionLabel().align(CENTER, CENTER)
  ;
  */
  
  
  //control event to shut down motor
  cp5.addBang("STOP")
  .setPosition(500,20)
  .setSize(150,80)
  .setFont(createFont("arial",30))
  //.setColorBackground(color(255,0,0))
  .setColorForeground(color(255,0,0))
  .setColorActive(color(255,0,0))
  .setColorValue(color(0,0,0))
  .getCaptionLabel().align(CENTER, CENTER)
  ; 
}

long ms = 0;
void draw(){
  fill(85);
  rect(0,0,width,height/2);
  fill(102);
  rect(0,height/2,width,height/2);
  
  if(state == "motor on"){
    //update rpm timer
    rpm_timer.update();
    //check if a read period t has occurred
    if(rpm_timer.time() >= ms + READ_PERIOD){
      ms = rpm_timer.time();
      //int rpm = read_rpm();
      read_rpm();
    }
  }
  
  //button press color change for stop button
  if(cp5.getController("STOP").isMousePressed()){
    cp5.getController("STOP").setColorActive(color(0,0,0));
  }
  else{
    cp5.getController("STOP").setColorActive(color(255,0,0));
  } 
  
  //measured rpm 
  noStroke();
  fill(220,220,0);
  rect(20,220,int(width/2.3),int(height/5));
  fill(255);
  textSize(30);
  if(measured_rpm == -1){text("Motor Off",20,270);}
  else{text(measured_rpm,20,270);}
  text("Measured RPM",20,330);
}

void set_data(){
  state = "motor on";
  
  String rpmS = cp5.get(Textfield.class,"Target RPM").getText();
  //verify that rpm is a positive integer
  int rpm = parseInt(rpmS);
  if(rpm > 0){
    print("Setting RPM to: ");
    println(rpm);
    //command: set       data: rpm
    //create data
    byte[] data = new byte[5];
    data[0] = byte('s');
    data[1] = byte(rpm & 0xFF);
    data[2] = byte((rpm >> 8) & 0xFF);
    data[3] = 0;
    data[4] = 0;
    //send data
    //port.write(data);
  }
  else{
    println("Invalid RPM");
  }
  println();
  
}

void STOP(){
  state = "motor off";
  measured_rpm  = -1;
  //command: abort       data: none
  //create data
  byte data = byte('A');
  //send data
  //port.write(data);
  println("Stopping motor");
  println();
}



void keyPressed(){
  if(key == '\n'){
    if(tf.isFocus()){
      set_data();
    }  
  }
}

void request_rpm(){
  //command: request       data: none
  //create data
  byte data = byte('R');
  //send data
  //port.write(data);
}

int read_rpm(){
  request_rpm();
  //buffer contains 4 bytes becuase the arduino will send rpm as an int
  byte[] inBuffer = new byte[4];
  //port.readBytes(inBuffer);
  //measured_rpm = int(inBuffer);
  measured_rpm+=1;
  return 0;
}
