//Library Imports
import controlP5.*;
import processing.serial.*;

//Global objects
ControlP5 cp5;  //controlp5 object 
Serial port;  //port to communciate with arduino
String port_name = "COM3";

//same as arduino
void setup(){
  //prints a list of fonts to choose from
  //String[] fontlist = PFont.list();
  //printArray(fontlist);
  
  size(500,500);  //window size
  cp5 = new ControlP5(this); 
  //port = new Serial(this,port_name,115200);  //instantiate port with port name and baudrate
  
  
  //numberbox for setting rpm
  cp5.addTextfield("Target RPM")
  .setPosition(20,20)
  .setSize(150,40)
  .setFont(createFont("arial",20))
  .setAutoClear(false);
  
  //control event to send numberbox text to arduino
  cp5.addBang("Set")
  .setPosition(180,20)
  .setSize(40,40)
  .setFont(createFont("arial",12))
  .getCaptionLabel().align(CENTER, CENTER)
  ;
  //control event to shut down motor
  cp5.addBang("STOP")
  .setPosition(400,20)
  .setSize(80,80)
  .setFont(createFont("arial",30))
  //.setColorBackground(color(255,0,0))
  .setColorForeground(color(255,0,0))
  .setColorActive(color(255,0,0))
  .getCaptionLabel().align(CENTER, CENTER)
  ;
  
  
}

void draw(){
  background(0,0,0);
}

void Set(){
  String rpmS = cp5.get(Textfield.class,"Target RPM").getText();
  //verify that rpm is an integer
  int rpm = parseInt(rpmS);
  if(rpm != 0){
    print("Setting RPM to: ");
    println(rpm);
    
    //command: set       data: rpm
    //create data
    byte[] data = new byte[3];
    data[0] = byte('s');
    data[1] = byte(rpm & 0xFF);
    data[2] = byte((rpm >> 8) & 0xFF);
    //send data
    //port.write(data);
  }
  else{
    println("Invalid RPM");
  }
  println();
  
}

void STOP(){
  //command: abort       data: none
  //create data
  byte data = byte('A');
  //send data
  //port.write(data);
  println("Stopping motor");
  println();
}
