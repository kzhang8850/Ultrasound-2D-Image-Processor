
import processing.serial.*;

Serial myPort;

float xPos = 0;
float yPos = 0;
void setup(){
size(1000, 1000);
noSmooth();
background(0);
translate(500, 500);
noFill();
stroke(0,255,0);
strokeWeight(20);
point(0,0);
myPort = new Serial(this,"COM4", 9600);
myPort.bufferUntil('\n');

}

void draw(){
      stroke(255);     //stroke color
      strokeWeight(5);        //stroke wider
  point(xPos+500,yPos+500);
}

void serialEvent(Serial myPort){
  String mag = myPort.readStringUntil('t');
  mag = mag.substring(0,mag.length()-1);
  String angle = myPort.readStringUntil('\n');
   // println(mag);
  
  if(angle != null){

    angle = trim(angle);
    float degrees = float(angle);
  
     mag = trim(mag);
    float duration = float(mag);
    
    float distance = duration/10;

    
    xPos = distance * cos(radians(degrees));
    yPos = distance * sin(radians(degrees));
    println(distance);
    //println(degrees);    
  }
  //redraw();
  
  
 
  
}