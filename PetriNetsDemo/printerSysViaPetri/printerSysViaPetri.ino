// Define the pins for LEDs and buttons
const int redLedPin = 2;
const int yellowLedPin = 3;
const int greenLedPin = 4;
const int user1ButtonPin = 5;
const int user2ButtonPin = 6;

// Define Petri net places as variables
int printerState = 0;  // 0: Idle, 1: Printing, 2: Error
int user1Request = 0;  // 0: No request, 1: Requested
int user2Request = 0;  // 0: No request, 1: Requested


void setup() {
  // Intialize pins
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(user1ButtonPin, INPUT_PULLUP);
  pinMode(user2ButtonPin, INPUT_PULLUP);

  digitalWrite(redLedPin, HIGH);
  
}

void loop() {
// Check if User 1 or User 2 pressed their respective buttons
  user1Request = digitalRead(user1ButtonPin) == LOW ? 1 : 0;
  user2Request = digitalRead(user2ButtonPin) == LOW ? 1 : 0;

  // Implement Petri net transitions
  if (printerState == 0 && (user1Request || user2Request)) {
    // Transition from Idle to Printing
    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
    printerState = 1;
  } else if (printerState == 1 && (user1Request || user2Request)) {
    // Transition from Printing to Error (Conflict)
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
    printerState = 2;
    } else if (printerState == 1 && !user1Request && !user2Request) {
    // Transition from Printing to Idle (Job completed)
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    printerState = 0;
  } else if (printerState == 2 && (!user1Request || !user2Request)) {
    // Transition from Error to Idle (Conflict resolved)
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    printerState = 0;
  }
  // Delay for stability (adjust as needed)
  delay(100);
}
