int btnPin[]={30,28,26,24};
int redPin = 8;   // 設定 RGB R-Pin
int greenPin = 9;  // 設定 RGB G-Pin
int bluePin = 10;  // 設定 RGB B-Pin
#define COMMON_ANODE
void setup(){
  Serial.begin(115200);
  for(int i=0;i<4;i++){
    pinMode(btnPin[i],INPUT_PULLUP);
  }

}

int getBtn(){
  static bool btnState[]={1,1,1,1};
  for(int i=0;i<4;i++){
    if(digitalRead(btnPin[i])!=btnState[i]){
      delay(20);
      if(digitalRead(btnPin[i])!=btnState[i]){
        btnState[i]=digitalRead(btnPin[i]);
        if(btnState[i]==LOW){
          return i;
        }
        
      }
      
    }
  }
  return -1;
}

void loop(){
  int btnNum=getBtn();
  static int r=0,g=0,b=0;
  static int increment=5;
  switch(btnNum){
    case 0:
    Serial.println("Btn "+String(0)+" pressed");
    r+=increment;
    if(r<=255 && r>=0){
      setColor(r,g,b);
    }
    else {
      increment=-increment;
    }
    Serial.println("r,g,b:"+String(r)+","+String(g)+","+String(b));
      break;
    case 1:
    Serial.println("Btn "+String(1)+" pressed");
    g+=increment;
    if(g<=255 && g>=0){
      setColor(r,g,b);
    }
    else {
      increment=-increment;
    }
    Serial.println("r,g,b:"+String(r)+","+String(g)+","+String(b));
    Serial.println("increment:"+String(increment));
      break;
      
    case 2:
    Serial.println("Btn "+String(2)+" pressed");
    b+=increment;
    if(b<=255 && b>=0){
      setColor(r,g,b);
    }
    else {
      increment=-increment;
    }
    Serial.println("r,g,b:"+String(r)+","+String(g)+","+String(b));
      break;
    
    case 3:
    Serial.println("Btn "+String(3)+" pressed");
    r=g=b=0;
    setColor(r,g,b);
    Serial.println("r,g,b:"+String(r)+","+String(g)+","+String(b));
    break;  
  }
}

void setColor(int red, int green, int blue)
{
  
#ifdef COMMON_ANODE
red = 255 - red;
green = 255 - green;
blue = 255 - blue;
#endif

analogWrite(redPin, red);
analogWrite(greenPin, green);
analogWrite(bluePin, blue);
}
