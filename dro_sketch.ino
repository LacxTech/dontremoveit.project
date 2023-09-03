// This code is made by LacxTech

const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 11;
const int ACTIVATE_DISTANCE = 5;      // Threshold to activate the alarm (object is more than 5 cm away)
const int DEACTIVATE_DISTANCE = 2;    // Threshold to deactivate the alarm (object is very close)
const int DEBOUNCE_COUNT = 3;          // Number of consecutive readings required

long duration;
int distance;
bool alarmActive = false;
int debounceCounter = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance
  distance = duration * 0.034 / 2;

  if (distance > ACTIVATE_DISTANCE && distance < 30 && !alarmActive) {
    debounceCounter++;
    if (debounceCounter >= DEBOUNCE_COUNT) {
      activateAlarm();
      debounceCounter = 0; // Reset debounce counter
    }
  } else if (distance <= DEACTIVATE_DISTANCE) {
    deactivateAlarm();
  } else {
    debounceCounter = 0; // Reset debounce counter
  }

  Serial.print("Distance: ");
  Serial.println(distance);
}

void activateAlarm() {
  alarmActive = true;
  tone(buzzer, 1000); // You can adjust the frequency as needed for you
}

void deactivateAlarm() {
  alarmActive = false;
  noTone(buzzer);
}
        