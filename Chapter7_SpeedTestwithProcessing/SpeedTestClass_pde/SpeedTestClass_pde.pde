
import processing.serial.*;

Serial myPort;  // Create object from Serial class

import controlP5.*;
ControlP5 cp5;


int speed;//degrees per sec
int direction =1;
RadioButton r;
void setup() 
{
  printArray(Serial.list());
  String portName = Serial.list()[2];
  myPort = new Serial(this, portName, 115200);
  
  
  size(700,400);
  PFont font = createFont("arial",20);
  
  cp5 = new ControlP5(this);
  
  cp5.addSlider("speed",0,360,speed,100,150,255,30);
  
  
   r = cp5.addRadioButton("setDirect")
         .setPosition(100,200)
         .setSize(40,20)
         .setColorForeground(color(120))
         .setColorActive(color(255))
         .setColorLabel(color(255))
         .setItemsPerRow(2)
         .setSpacingColumn(50)
         .addItem("Forward",0)
         .addItem("Backward",1)
         ; 
  textFont(font);
    cp5.setColorCaptionLabel(0); 
    r.activate(0);

}

void draw()
{
  
}



void speed(int value ) {
  String str = str(value);
  myPort.write(str.length());

  if (direction == 1)
    myPort.write('F');
  else
    myPort.write('B');
    
  for (int i = 0; i < str.length(); i++) {
    myPort.write(str.charAt(i));
  }
  println("speed set value: "+ value*direction);

}




void setDirect(int a) {
  if (a == 0)
    direction = 1;
  else if (a == 1)
    direction = -1;
  
  println("Set Direction: " + direction);
}


void serialEvent(Serial myPort) {
  String read = myPort.readStringUntil(10);
  if (read != null) {
    println("from arduino: "+ read);
  }   
}