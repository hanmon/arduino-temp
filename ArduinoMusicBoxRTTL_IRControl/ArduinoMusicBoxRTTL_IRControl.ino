#include <avr/pgmspace.h>
#include <Tone.h>

/*設定RTTL格式的簡譜，參考

   電玩遊戲:http://arcadetones.emuunlim.com/arcade.htm
*/
const char song01[] PROGMEM = "MissionImp:d=16,o=6,b=95:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,a#,g,2d,32p,a#,g,2c#,32p,a#,g,2c,a#5,8c,2p,32p,a#5,g5,2f#,32p,a#5,g5,2f,32p,a#5,g5,2e,d#,8d";
const char song02[] PROGMEM = "SuperMarioBroMainTheme:d=4,o=5,b=100:16e6,16e6,32p,8e6,16c6,8e6,8g6,8p,8g,8p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,16p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16c7,16p,16c7,16c7,p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16d#6,8p,16d6,8p,16c6";
const char song03[] PROGMEM = "SuperMarioBroUnderGround:d=4,o=6,b=100:32c,32p,32c7,32p,32a5,32p,32a,32p,32a#5,32p,32a#,2p,32c,32p,32c7,32p,32a5,32p,32a,32p,32a#5,32p,32a#,2p,32f5,32p,32f,32p,32d5,32p,32d,32p,32d#5,32p,32d#,2p,32f5,32p,32f,32p,32d5,32p,32d,32p,32d#5,32p,32d#";
const char song04[] PROGMEM = "StarWars:d=4,o=5,b=45:32p,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#.6,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#6";
const char song05[] PROGMEM = "Xfiles:d=4,o=5,b=125:e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,g6,f#6,e6,d6,e6,2b.,1p,g6,f#6,e6,d6,f#6,2b.,1p,e,b,a,b,d6,2b.,1p,e,b,a,b,e6,2b.,1p,e6,2b.";
const char song06[] PROGMEM = "MichaelJacksonTriller:d=4,o=6,b=127:8e5,g5,b5,g,e,p,e,8f_,e,d,p,8d,p,8e5,g5,b5,g,e,p,e,8f_,e,d";
const char song07[] PROGMEM = "MichaelJacksonBillieJean:d=4,o=6,b=125:8e,8e,8d,p,8b5,32e,16p,32p,e,d,2p,32e,16p,32p,32e,16p,32p,8e,8d,p,8b5,8e,8g,16p,32p,a,8g,8f_,2e,8p,16p,8e,8p,8e,b,a,8e,c,2b5,16b,16g,16e,16c,2b5";
const char song08[] PROGMEM = "PhantomOf:d=4,o=6,b=100:e5,a5,e5,g5,8f5,2f5,d5,g5,8d5,1e5,e5,a5,e5,g5,8f5,2f5,d5,g5,8d5,1e5,e5,a5,c,e,8d,2d,d,g,8d,1e,e,1a,8g,8f,8e,8d,8c,8b5,8a5,1g_5,f5,f5,8e5,1e5";
char songStrBuffer[512];
Tone tone1;
int btnPin[] = {19,18,17,16,15,14,6,7};

const char *const songTable[] PROGMEM =
{
  song01, song02, song03, song04, song05, song06, song07, song08
};

void setup(void)
{
  Serial.begin(115200);
  tone1.begin(4);
  for (int i = 0; i < 8; i++) {
    pinMode(btnPin[i], INPUT_PULLUP);
  }
  initIRecv();
}



void loop(void)
{
  int songIndex = checkButtonPressed();
  if(songIndex=-1){
    songIndex = doIRDecode();
  }
  if (songIndex>=0) {
    strcpy_P(songStrBuffer, (char*)pgm_read_word(&(songTable[songIndex])));
    Serial.println(songStrBuffer);
    play_rtttl(songStrBuffer);
    Serial.println("Done.");
  }
}


int checkButtonPressed() {
  bool btnState[8] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
  for (int i = 0; i < 8; i++) {
    if (digitalRead(btnPin[i]) != HIGH) {
    delay(50);
      if (digitalRead(btnPin[i]) != HIGH) {
      btnState[i] = digitalRead(btnPin[i]);
        return i;
      }
    }
  }
  return -1;
}
