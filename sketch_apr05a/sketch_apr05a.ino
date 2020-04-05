//I/O Pins
const int redPin = 5;
const int greenPin = 6;
const int bluePin = 3;

const unsigned char initRedValue = 254;
const unsigned char initGreenValue = 0;
const unsigned char initBlueValue = 0;
const unsigned char initBrightness = 254;

unsigned char redValue;
unsigned char greenValue;
unsigned char blueValue;
unsigned char brightness;

const unsigned int loopTicks = 5;
const unsigned int strobeTicks = 50;
const unsigned int randomStrobeOccurence = 4;

unsigned int loopCounter;
unsigned long lastTime;
int increment;

long strobeToggle;

void setup() {
  // put your setup code here, to run once:

  redValue = initRedValue;
  greenValue = initGreenValue;
  blueValue = initBlueValue;
  brightness = initBrightness;
  loopCounter = 0;

  lastTime = millis();
  increment = 1;

  strobeToggle = 0;
  //I/O Setup

}


void randomStrobe(){
  unsigned long timeNow = millis();
  

  //Loop Counter only increments every loopTicks milliseconds⌈
  if(timeNow > lastTime + strobeTicks){
    strobeToggle = random(254);
    lastTime = timeNow;
    loopCounter = loopCounter++;
    if(strobeToggle % randomStrobeOccurence == 0){
      redValue = random(254);
      greenValue = random(min(254,508 - redValue));
      blueValue = random(min(254, 508 -redValue - greenValue));
      brightness = 254;
    } else{
      brightness = 0;
    }
  }

  if(loopCounter == 254){
    loopCounter = 0;
  }
  
  //Toggle Strobe
  
    
  
}



void fade(){
  unsigned char tempRed;
  unsigned long timeNow = millis();
  

  //Loop Counter only increments every loopTicks milliseconds⌈
  if(timeNow > lastTime + loopTicks){
    lastTime = timeNow;
    loopCounter = loopCounter + increment;
  }
  
  
  //Light Cycle
  if((loopCounter == 254 && increment == 1) || (loopCounter == 0 && increment == -1)){
    
    //Only switch after a full cycle
    if(increment == -1){
      redValue = random(254);
      greenValue = random(254);
      blueValue = random(254);
    }

    increment = increment * -1;
  }

  brightness = loopCounter;
}




void loop() {
  // put your main code here, to run repeatedly:
  fade();
  //randomStrobe();

  unsigned char redOutput = (redValue * brightness)/255;
  unsigned char greenOutput = (greenValue * brightness)/255;
  unsigned char blueOutput = (blueValue * brightness)/255;

  analogWrite(redPin, redOutput);
  analogWrite(greenPin, greenOutput);
  analogWrite(bluePin, blueOutput);
}
