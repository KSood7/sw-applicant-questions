// Put this code in tinkercad with the circuit to see

// constants
const int ledPin = 11;
const int buttonPin = 2;

// variables
int numAttempts = 0;
long totalTime = 0;
int numFalse = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  
  Serial.begin(9600);
  randomSeed(analogRead(A0)); // truely random seed
  Serial.println("Click the button to start a round!");
}

void loop() {
  if (digitalRead(buttonPin) == HIGH) {
    delay(300); // prevent double press

    // random wait time
    int waitTime = random(2000, 10000);
    long startWait = millis();
    bool falseStart = false;

    // wait using millis() not delay() to allow detection for false starts
    while (millis() - startWait < waitTime) {
      if (digitalRead(buttonPin) == HIGH) {
        falseStart = true;
        break;
      }
    }

    if (falseStart == true) {
      numFalse++;
      Serial.println("False Start! You pressed the button too early.");
      Serial.print("Total False Starts: ");
      Serial.println(numFalse);
      delay(2000); // Penalty delay
      return;
    }

    // Reaction
    digitalWrite(ledPin, HIGH);
    long startTiming = millis();

    while (digitalRead(buttonPin) == LOW) { }

    long reactionTime = millis() - startTiming;
    numAttempts++;
    totalTime = totalTime + reactionTime;
    long averageTime = totalTime / numAttempts;

    Serial.print("Attempt: "); Serial.println(numAttempts);
    Serial.print("Reaction: "); Serial.print(reactionTime); Serial.println(" ms");
    Serial.print("Average: "); Serial.print(averageTime); Serial.println(" ms");
    Serial.print("False Starts: "); Serial.println(numFalse);
    Serial.println("--------------------");

    digitalWrite(ledPin, LOW); 
    delay(1000); 
  }
}