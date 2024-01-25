#include "pitches.h"  // library with pitches

//notes in the melody
int melody[] = { 
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_G5
  
};  

// pin numbers
const int button_pin = 12;
const int buzzer_pin = 7;

const int red_led_pin = 3;    
const int yellow_led_pin = 4; 
const int green_led_pin = 5;  

//note durations
int noteDurations[] = {  
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8,
  2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4
  
  }; 

int button_state = 0;        // current state of the button
int prev_button_state = 0;    // previous state of the button

void setup() {
  //make the button's pin input
  pinMode(button_pin, INPUT);
  pinMode(red_led_pin, OUTPUT);
  pinMode(yellow_led_pin, OUTPUT);
  pinMode(green_led_pin, OUTPUT);
}

void loop() {
  //read the input pin
  button_state = digitalRead(button_pin);

  int size = sizeof(noteDurations) / sizeof(int);


  if (button_state != prev_button_state) {
    //if the button is pressed
    if (button_state == HIGH) {
      //iterate over the notes of the melody
      for (int thisNote = 0; thisNote < size; thisNote++) {
        // blink the three LEDs in sequence
        if (thisNote % 3 == 0) {
          digitalWrite(red_led_pin, HIGH);
          digitalWrite(yellow_led_pin, LOW);
          digitalWrite(green_led_pin, LOW);
        } else if (thisNote % 3 == 1) {
          digitalWrite(red_led_pin, LOW);
          digitalWrite(yellow_led_pin, HIGH);
          digitalWrite(green_led_pin, LOW);
        } else if (thisNote % 3 == 2) {
          digitalWrite(red_led_pin, LOW);
          digitalWrite(yellow_led_pin, LOW);
          digitalWrite(green_led_pin, HIGH);
        }

        //to calculate the note duration, take one second. Divided by the note type
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(buzzer_pin, melody[thisNote], noteDuration);

        // to distinguish the notes, set a minimum time between them
        int pauseBetweenNotes = noteDuration * 1.5;
        delay(pauseBetweenNotes);

        // stop the tone playing
        noTone(buzzer_pin);
      }
    }
  }

  prev_button_state = button_state;
  // turn off all LEDs after the tone is done playing
  digitalWrite(red_led_pin, LOW);
  digitalWrite(yellow_led_pin, LOW);
  digitalWrite(green_led_pin, LOW);
}
