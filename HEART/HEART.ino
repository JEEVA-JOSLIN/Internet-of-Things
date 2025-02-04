// Constants
const int pulsePin = A0;   // Pulse Sensor connected to A0
int sensorValue = 0;       // Variable to store sensor value
int threshold = 550;       // Threshold value to detect heartbeat

// Variables
long lastBeatTime = 0;     // Time of the last heartbeat
int beatCount = 0;         // Heartbeat count
int bpm = 0;               // Beats per minute (BPM)

// Timer for BPM calculation
long interval = 1000;      // 1-second interval for BPM calculation

void setup() {
  Serial.begin(9600);      // Initialize serial communication
  pinMode(pulsePin, INPUT);
}

void loop() {
  sensorValue = analogRead(pulsePin);  // Read the pulse sensor value
  
  if (sensorValue > threshold && millis() - lastBeatTime > 300) {
    // Detected a heartbeat
    lastBeatTime = millis();
    beatCount++;
  }
  
  if (millis() % interval < 50) {
    // Calculate BPM
    bpm = beatCount * 60;  // Beats per minute (BPM)
    beatCount = 0;
    
    Serial.print("Heart Rate: ");
    Serial.print(bpm);
    Serial.println(" BPM");
  }
}
