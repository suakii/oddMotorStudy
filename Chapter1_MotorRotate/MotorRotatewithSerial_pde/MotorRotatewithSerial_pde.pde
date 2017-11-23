
import processing.serial.*;

Serial myPort;  // Create object from Serial class

import controlP5.*;
ControlP5 cp5;

String rotateValue = "";

void setup() 
{
  printArray(Serial.list());
  String portName = Serial.list()[2];
  myPort = new Serial(this, portName, 115200);
  
  
  size(700,400);
  
  PFont font = createFont("arial",20);
  
  cp5 = new ControlP5(this);
  
  cp5.addTextfield("rValue")
     .setPosition(20,170)
     .setSize(200,40)
     .setFont(createFont("arial",20))
     .setAutoClear(false)
     ;
       
  PImage[] imgs = {loadImage("button_a.png"),loadImage("button_b.png"),loadImage("button_c.png")};
  cp5.addButton("Send")
     .setValue(128)
     .setPosition(250,170)
     .setImages(imgs)
     .updateSize()
     ;
     
     
  textFont(font);
}

void draw()
{
  
}



public void Send( ) {
   this.rotateValue = cp5.get(Textfield.class,"rValue").getText();
   if (rotateValue != "") {
     println("Send to Arduino: "+this.rotateValue);
     myPort.write(rotateValue);
   }
}

void serialEvent(Serial myPort) {
  String read = myPort.readStringUntil(10);
  if (read != null) {
    println("from arduino: "+ read);
  }   
}