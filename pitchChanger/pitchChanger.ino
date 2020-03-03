// Team Number: 15
// Team: Ryan Gaul, rgaul2 & Gina Gerace, ggerac3
// Title: 8 Bit Drum Set
// Abstract: The project will be a Drum Kit made up of five piezo vibration sensors. 
//   There will also be the ability to change the pitch of each drum up or down, which 
//   is done by incrementing from drums 1-5, and then looping back around to 1. The 
//   piezo sensors will cause sounds to be played by the buzzer. The user will be able 
//   to change the pitch of each drum by a note, which will be displayed on the 16x2 
//   liquid crystal display. With 5 piezo sensors, 3 buttons, an LCD display, a 
//   potentiometer, and various wires and resistors, a drum set is made.


//set up pins for Serial communication
int ardin = 0;
int ardout = 1;

// include the library code:
#include <LiquidCrystal.h>
#include <Tone.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// set pin numbers for the buttons:
const int pickButton = 8;      //button used to choose which drum to change
const int upButton = 9;        //button used to increase metronome speed
const int downButton = 10;      //button used to decrease metronome speed

// variables to read status of buttons:
int pickState = 0;
int upState = 0;
int downState = 0;

int drum = 0;                  //will hold number of drum to change

// array to store the frequency for each drum
int index[] = {0, 12, 24, 33, 55, 70};

// create an array of all the notes to cycle through
int notes[] = {NOTE_B0, NOTE_C1, NOTE_CS1, NOTE_D1, NOTE_DS1, NOTE_E1, NOTE_F1, NOTE_FS1, NOTE_G1, NOTE_GS1, NOTE_A1, NOTE_AS1, NOTE_B1, 
NOTE_C2, NOTE_CS2, NOTE_D2, NOTE_DS2, NOTE_E2, NOTE_F2, NOTE_FS2, NOTE_G2, NOTE_GS2, NOTE_A2, NOTE_AS2, NOTE_B2, 
NOTE_C3, NOTE_CS3, NOTE_D3, NOTE_DS3, NOTE_E3, NOTE_F3, NOTE_FS3, NOTE_G3, NOTE_GS3, NOTE_A3, NOTE_AS3, NOTE_B3, 
NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4, 
NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5, 
NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6, 
NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7, 
NOTE_C8, NOTE_CS8, NOTE_D8, NOTE_DS8};

void setup() {
  // initialize the pushbutton pins as an input:
  pinMode(pickButton, INPUT);
  pinMode(upButton, INPUT);
  pinMode(downButton, INPUT);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  //initialize pins for Serial communication
  pinMode(ardin, INPUT); 
  pinMode(ardout, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // read the states of the pushbuttons:
  pickState = digitalRead(pickButton);
  upState = digitalRead(upButton);
  downState = digitalRead(downButton);

  // check if the pick button is pressed. If it is, the pickState is HIGH:
  if (pickState == HIGH) {
    // if button is pressed change which drum will be editted:
    drum++;
    if(drum > 5)
      drum = 1;         //circle back to 1 once you've gone through all choices
    
    Serial.write(drum);    
    lcd.clear();
  } 
  
  // check if the up button is pressed. If it is, the upState is HIGH:
  if (upState == HIGH) {
    lcd.clear();
    // increase frquency:
    if(index[drum] !=88)
      index[drum]++;
    Serial.write(index[drum] + 10);    // send new frequency
  }
  // check if the down button is pressed. If it is, the downState is HIGH:
  if (downState == HIGH) {
    lcd.clear();
    // decrease frequuency:
    if(index[drum]!=0)
      index[drum]--;
      Serial.write(index[drum] + 10);    // send new frequency
  }

  // print directions
  if(drum == 0){  
    lcd.setCursor(0,0);
    lcd.print("Press button");
    lcd.setCursor(0,1);
    lcd.print("on right");
  }
  else{
  //print frequency and drum # to lcd screen
  lcd.setCursor(0,0);
  lcd.print("Drum: " + String(drum));
  lcd.setCursor(0,1);
  lcd.print("Frequency: " + String(notes[index[drum]]));
  }
  delay(200);
}
