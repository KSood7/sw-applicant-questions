// constants
const int ledPin = 11;
const int buttonPin = 2;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  
  Serial.begin(9600);
  Serial.println("No error so far");
}

void loop() {
    // check wiring
    if (digitalRead(buttonPin) == HIGH) {
        digitalWrite(ledPin, HIGH);
    } else {
        digitalWrite(ledPin, LOW);
    }
}