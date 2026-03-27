// constants
const int ledPin = 11;
const int buttonPin = 2;

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
    delay(waitTime); // Basic blocking delay for MVP

    // Reaction
    digitalWrite(ledPin, HIGH);
    long startTiming = millis();

    while (digitalRead(buttonPin) == LOW) {
      // wait for press
    }

    // reaction time calculation
    long reactionTime = millis() - startTiming;
    
    Serial.print("Reaction: "); Serial.print(reactionTime); Serial.println(" ms");

    digitalWrite(ledPin, LOW); // turn off
    delay(1000); 
  }
}