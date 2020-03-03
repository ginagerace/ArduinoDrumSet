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


// include tone library for musical notes
#include <Tone.h>
Tone tone1;
Tone tone2;
Tone tone3;

// set up pins for Serial communication
int ardin = 0;
int ardout = 1;

// these constants won't change:
const int drum1 = A0;       // a piezo sensor is connected to analog pin 0
const int drum2 = A1;       // a piezo sensor is connected to analog pin 1
const int drum3 = A2;       // a piezo sensor is connected to analog pin 2
const int drum4 = A3;       // a piezo sensor is connected to analog pin 3
const int drum5 = A4;       // a piezo sensor is connected to analog pin 4
const int threshold = 100;  // threshold value to decide when the detected sound is a knock or not
const int buzzer = 7;       // the piezo buzzer is connected to digital pin 7

// variables to store the value read from the sensor pin
int reading1 = 0;
int reading2 = 0;
int reading3 = 0;
int reading4 = 0;
int reading5 = 0;      

// array to store the frequency for each drum
int freq[] = {0, NOTE_B1, NOTE_B2, NOTE_GS3, NOTE_F5, NOTE_A6};

// variables to be used for serial communication
int hold, drum = 0;

// create an array of all the pitches to cycle through
int notes[] = {0,0,0,0,0,0,0,0,0,0,NOTE_B0, NOTE_C1, NOTE_CS1, NOTE_D1, NOTE_DS1, NOTE_E1, NOTE_F1, NOTE_FS1, NOTE_G1, NOTE_GS1, NOTE_A1, NOTE_AS1, NOTE_B1, 
NOTE_C2, NOTE_CS2, NOTE_D2, NOTE_DS2, NOTE_E2, NOTE_F2, NOTE_FS2, NOTE_G2, NOTE_GS2, NOTE_A2, NOTE_AS2, NOTE_B2, 
NOTE_C3, NOTE_CS3, NOTE_D3, NOTE_DS3, NOTE_E3, NOTE_F3, NOTE_FS3, NOTE_G3, NOTE_GS3, NOTE_A3, NOTE_AS3, NOTE_B3, 
NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4, 
NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5, 
NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6, 
NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7, 
NOTE_C8, NOTE_CS8, NOTE_D8, NOTE_DS8};

void setup() {
  // declare the drum pins as INPUT
  pinMode(drum1, INPUT);
  pinMode(drum2, INPUT);
  pinMode(drum3, INPUT);
  pinMode(drum4, INPUT);
  pinMode(drum5, INPUT);

  //initialize pins for Serial communication
  pinMode(ardin, INPUT); 
  pinMode(ardout, OUTPUT);
  Serial.begin(9600);       // use the serial port

  // prepare buzzer pin to play notes
  // allow up to three notes to be played at once
  tone1.begin(buzzer);      
  tone2.begin(buzzer);  
  tone3.begin(buzzer);   
}

void loop() {
  // read information sent from other arduino
  while(Serial.available() > 0){
    hold = Serial.read();
    // see which drum is selected on other arduino
    if(hold < 6)
      drum = hold;
    // update selected drum's frequency
    else{  
      if(drum == 1)
        freq[1] = notes[hold];
      else if(drum == 2)
        freq[2] = notes[hold];
      else if(drum == 3)
        freq[3] = notes[hold];
      else if(drum == 4)
        freq[4] = notes[hold];
      else if(drum == 5)
        freq[5] = notes[hold];
    }
  }
  
  // read the sensors and store in variables:
  reading1 = analogRead(drum1);
  reading2 = analogRead(drum2);
  reading3 = analogRead(drum3);
  reading4 = analogRead(drum4);
  reading5 = analogRead(drum5);

  // if the sensor1 reading is greater than the threshold play note
  if (reading1 >= threshold) 
    tone1.play( freq[1], 100 );
  
  // if the sensor2 reading is greater than the threshold play note
  if (reading2 >= threshold) 
    tone2.play( freq[2], 100 );
  
  // if the sensor3 reading is greater than the threshold play note
  if (reading3 >= threshold)
    tone3.play( freq[3], 100 );
 
  // if the sensor4 reading is greater than the threshold play note
  if (reading4 >= threshold) 
    tone2.play( freq[4], 100 );
  
  // if the sensor5 reading is greater than the threshold play note
  if (reading5 >= threshold) 
    tone1.play( freq[5], 100 );
  
}
