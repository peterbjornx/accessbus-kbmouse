
/*
const char *vnd_Name = "pbx     ";
const char *dev_Name = "Emul. KB";
const char *dev_Ver  = "V0.99  ";
uint32_t dev_Id      = 0x13374242;

const char *cap_String = 
"("
"prot(keyb)"
"type(keyboard)"
"model(LK501-AA)"
"keymap(LK501-AA)"
"feedback(click(15)bell(15)led(2(scr)3(cap)4(num)))\n"
")";*/
#include "ps2mouse.h"
#define DATA_PIN 4
#define CLOCK_PIN 3

PS2Mouse mouse(CLOCK_PIN, DATA_PIN);

const char *vnd_Name = "pbx     ";
const char *dev_Name = "MouseEmu";
const char *dev_Ver  = "V0.99  ";
uint32_t dev_Id      = 13374242;

const char *cap_String = 
"("
"prot(locator)"
"type(mouse)"
"model(VSXXX-AA)"
"buttons(1(L)2(R)3(M)"
"dim(2) rel res(200 inch) range(-127 127)\n"
"d0(dname(x))"
"d1(dname(x))"
")";
#include "ab_func.h"
//#include "kb_i2c.h"

void setup() {
  AB_SetAddress( 0x6E );
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(115200);           // start serial for output
  mouse.initialize();
}
short oldbtns = 0;

short clipabs(short a, short b ){
  if ( a < -b )
    return -b;
  if ( a > b)
    return b;
  return a;
}
void loop() {
  uint16_t btns;
  short poss[2];
  static long om = millis(),nm;
  int a;
  // put your main code here, to run repeatedly:
  delay(1);
  handle();
  nm = millis();
  if ( (nm-om) > 25 && lcl_Addr != 0x6e ) {
    MouseData data = mouse.readData();
    btns = data.status & 7;
    poss[0] = clipabs(data.position.x,127);
    poss[1] = clipabs(data.position.y,127);
    if ( btns != oldbtns || poss[0] || poss[1] ) {
      sendLocator(0x50, btns, poss, 2 );
      oldbtns = btns;
    }
  
    om = nm;
  }
  //handleKB();

}