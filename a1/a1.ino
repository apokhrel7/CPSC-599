
// defining pin numbers
const int trig_Pin = 10;
const int echo_Pin = 11;
const int buzzerPin = 12;
const int button_Pin = 8;


long duration;
int distance;  // distance of hand from ultrasonic sensor

int buttonState = 0;  // reading the button state


void setup() {
  pinMode(trig_Pin, OUTPUT); // Sets the trig_Pin as an Output
  pinMode(echo_Pin, INPUT); // Sets the echo_Pin as an Input
  Serial.begin(9600); // Starts the serial communication
}
void loop() {
  // Clears the trig_Pin
  digitalWrite(trig_Pin, LOW);
  delayMicroseconds(2);

  digitalWrite(trig_Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_Pin, LOW);

  buttonState = digitalRead(button_Pin);  //read button state

  duration = pulseIn(echo_Pin, HIGH);
  
  // Calculating the distance
  distance = duration * 0.0344 / 2;

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);



  // notes
  int notes[7] = {261, 294, 329, 349, 392, 440, 494};


  //if button is not pressed and hand is not in front
  if (distance < 0 || distance > 40 || buttonState == LOW) { 

    noTone(12); //dont play music

  }

  //if button is pressed
  else if (buttonState == HIGH) {  

    int sound = map(distance, 0, 50, 0, 6);  
    tone(buzzerPin, notes[sound]);  // play notes depending on the distance of hand

  }

}