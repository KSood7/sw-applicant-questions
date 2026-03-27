/*
 * PROJECT: Arduino Reaction Time Tester
 * AUTHOR: Krishh Sood
 * Date: 2024-06-20
 * For Bluesat Software Applicant Technical Assessment
 * 
 * DESCRIPTION: A game that tests human reaction speed. The system pulses 
 * an LED at low brightness while waiting a random amount of time. If the user 
 * presses early, it logs a False Start. Once the LED goes 
 * solid, the user must press the button as fast as possible. 
 * The system calculates the reaction time, averages it over 
 * multiple attempts, and provides visual LED feedback.
 * 
 * */

// constants
const int ledPin = 11;
const int buttonPin = 2;

// variables
int numAttempts = 0;
long totalTime = 0;
int numFalse = 0;

int brightness = 0;             // 0 brightness to begin
int fadeAmount = 4;             // How many steps it takes at a time //fix
unsigned long lastFadeTime = 0; // A stopwatch just for the fading //fix

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  
  Serial.begin(9600);
  randomSeed(analogRead(A0));   // truely random seed
  Serial.println("Click the button to start a round!");
}

void loop() {
  // IDLE
  // LED is off
  // The system waits for a button press to arm the device.
  if (digitalRead(buttonPin) == HIGH) {
    
    // a delay to prevent accidental double presses
    delay(300); 

    // random wait time
    int waitTime = random(2000, 10000);
    long startWait = millis();
    bool falseStart = false;

    // ARMED
    // LED slowly pulses
    // The device waits a random duration between 2 and 10 seconds
    // If the button is pressed during this phase, record a false start
    while (millis() - startWait < waitTime) {
      
      // led pulsing
      // check every 50 milliseconds for a slow fade
      if (millis() - lastFadeTime > 50) {

        brightness = brightness + fadeAmount;   // Take a step (adds 5)

        // the brightness pulses from 68 to 0 with increments of 4
        // 68 and not 255, since 255 brightness should be distinct for when the LED is fully on
        if (brightness <= 0 || brightness >= 68) {
          fadeAmount = -fadeAmount;             // flip the sign and traverse backwards
        }

        analogWrite(ledPin, brightness);
        lastFadeTime = millis();
      }

      // false start
      if (digitalRead(buttonPin) == HIGH) {
        falseStart = true;
        break;
      }
    }

    // false start check
    if (falseStart == true) {
      numFalse++;
      Serial.println("False Start! You pressed the button too early.");
      Serial.print("Total False Starts: ");
      Serial.println(numFalse);
      
      // quick flash for 2 seconds
      for (int i = 0; i < 10; i++) {
        digitalWrite(ledPin, HIGH);
        delay(100);
        digitalWrite(ledPin, LOW);
        delay(100);
      }
      return;
    }

    // Reaction
    // LED turns on instantly as the signal
    // Start the timer and record the reaction time when the button is pressed
    digitalWrite(ledPin, HIGH);
    long startTiming = millis();

    while (digitalRead(buttonPin) == LOW) {
      // wait
    }

    // reaction time calculation
    long reactionTime = millis() - startTiming;
    numAttempts++;

    totalTime = totalTime + reactionTime;
    long averageTime = totalTime / numAttempts;

    Serial.print("Attempt: "); Serial.println(numAttempts);
    Serial.print("Reaction: "); Serial.print(reactionTime); Serial.println(" ms");
    Serial.print("Average: "); Serial.print(averageTime); Serial.println(" ms");
    Serial.print("False Starts: "); Serial.println(numFalse);
    Serial.println("--------------------");

    digitalWrite(ledPin, LOW);  // turn off

    // OUTPUT AND FEEDBACK
    if (reactionTime < 200) {
      // fast blink
      for (int i = 0; i < 8; i++) { digitalWrite(ledPin, HIGH); delay(80); digitalWrite(ledPin, LOW); delay(80); }
    } 
    else if (reactionTime < 350) {
      // medium blink
      for (int i = 0; i < 5; i++) { digitalWrite(ledPin, HIGH); delay(250); digitalWrite(ledPin, LOW); delay(250); }
    } 
    else {
      // slow blink
      for (int i = 0; i < 2; i++) { digitalWrite(ledPin, HIGH); delay(400); digitalWrite(ledPin, LOW); delay(400); }
    }

    // wait before next round
    delay(1000); 
  }
}