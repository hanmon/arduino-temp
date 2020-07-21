int redPin = 8;   // 設定 RGB R-Pin
int greenPin = 9;  // 設定 RGB G-Pin
int bluePin = 10;  // 設定 RGB B-Pin
//uncomment this line if using a Common Anode LED
#define COMMON_ANODE
void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(115200);
  initIRecv();
}

void loop()
{
  int cmd = doIRDecode();
  if (cmd > 0) {
    switch (cmd) {
      case 1:
        setColor(255, 0, 0);
        break;
      case 2:
        setColor(255, 25, 0);
        break;
      case 3:
        setColor(255, 255, 0);
        break;
      case 4:
        setColor(0, 255, 0);
        break;
      case 5:
        setColor(0, 0, 255);
        break;
      case 6:
        setColor(0, 125, 255);
        break;
      case 7:
        setColor(148, 0, 255);
        break;
//      default:
//        setColor(255, 255, 255);
//        break;
    }
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

/*
  setColor(255, 0, 0); // red
  delay(1000);
  setColor(0, 255, 0); // green
  delay(1000);
  setColor(0, 0, 255); // blue
  delay(1000);
  setColor(80, 0, 80); // purple
  delay(1000);
  setColor(255, 255, 0); //yellow
  delay(1000);
  setColor(0, 255, 255); //aqua
  delay(1000);*/
