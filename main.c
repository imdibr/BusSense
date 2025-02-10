// Pin Definitions
const int sensor1Pin = 2;  // Sensor 1 OUT pin
const int sensor2Pin = 3;  // Sensor 2 OUT pin

// Variables
int passengerCount = 0;      // Initial passenger count
bool sensor1Triggered = false;  // Tracks Sensor 1 activation
bool sensor2Triggered = false;  // Tracks Sensor 2 activation

void setup() {
  pinMode(sensor1Pin, INPUT);
  pinMode(sensor2Pin, INPUT);
  Serial.begin(9600); // Initialize Serial Monitor
  Serial.println("System Initialized");
  Serial.println("Passenger Count: 0");
}

void loop() {
  // Read sensor states
  int sensor1State = digitalRead(sensor1Pin);
  int sensor2State = digitalRead(sensor2Pin);

  // Entry Detection (Sensor 1 → Sensor 2)
  if (sensor1State == HIGH && !sensor1Triggered) {
    sensor1Triggered = true; // Sensor 1 triggered
  }
  if (sensor1Triggered && sensor2State == HIGH && !sensor2Triggered) {
    sensor2Triggered = true; // Sensor 2 triggered
    passengerCount++; // Increment passenger count
    notifyAction("Passenger Entered", passengerCount);
    resetSensors(); // Reset sensor states
  }

  // Exit Detection (Sensor 2 → Sensor 1)
  if (sensor2State == HIGH && !sensor2Triggered) {
    sensor2Triggered = true; // Sensor 2 triggered
  }
  if (sensor2Triggered && sensor1State == HIGH && !sensor1Triggered) {
    sensor1Triggered = true; // Sensor 1 triggered
    if (passengerCount > 0) { // Ensure count doesn't go negative
      passengerCount--; // Decrement passenger count
      notifyAction("Passenger Left", passengerCount);
    } else {
      notifyAction("Passenger Left (No Passengers)", passengerCount);
    }
    resetSensors(); // Reset sensor states
  }

  delay(3000); // Small delay for debounce
}

// Function to Reset Sensor States
void resetSensors() {
  sensor1Triggered = false;
  sensor2Triggered = false;
}

// Function to Notify Action
void notifyAction(String action, int count) {
  Serial.print(action);
  Serial.print(". Total Passengers: ");
  Serial.println(count);
}
