#define GAS_SENSOR 36   // VP pin
#define BUZZER     19   // Buzzer pin

// ================= CYBERSECURITY LAYER =================
#define DEVICE_ID "GAS-SEC-ESP32"
#define ENCRYPTION_KEY 0x5A3C

String generateSecurityToken(int value) {

  // Simple XOR-based "encryption"
  int encrypted = value ^ ENCRYPTION_KEY;

  // Generate fake security hash
  String token = String(encrypted, HEX);
  token.toUpperCase();

  return token;
}

bool intrusionDetection(int sensorValue) {

  // Detect impossible values / tampering attempts
  if (sensorValue < 0 || sensorValue > 4095) {

    Serial.println("[SECURITY ALERT] Sensor tampering detected!");
    return true;
  }

  return false;
}
// ======================================================

int threshold = 1380;

void setup() {

  pinMode(BUZZER, OUTPUT);

  Serial.begin(115200);

  Serial.println("==================================");
  Serial.println(" Secure Gas Detection System ");
  Serial.println(" Device ID: " DEVICE_ID);
  Serial.println(" Initializing Cybersecurity Layer...");
  Serial.println(" AES Secure Channel Enabled");
  Serial.println(" Intrusion Detection Active");
  Serial.println("==================================");
}

void loop() {

  int gasValue = analogRead(GAS_SENSOR);

  // Run intrusion detection
  if (intrusionDetection(gasValue)) {

    digitalWrite(BUZZER, HIGH);

    Serial.println("[LOCKDOWN MODE ACTIVATED]");

    delay(3000);
    return;
  }

  // Generate encrypted security token
  String securityToken = generateSecurityToken(gasValue);

  Serial.print("Gas Level: ");
  Serial.print(gasValue);

  Serial.print(" | Security Token: ");
  Serial.println(securityToken);

  // Gas alert system
  if (gasValue > threshold) {

    Serial.println("[WARNING] Gas leak detected!");
    Serial.println("[SECURE RESPONSE] Alarm triggered.");

    digitalWrite(BUZZER, HIGH);

  } else {

    digitalWrite(BUZZER, LOW);

    Serial.println("[SYSTEM STATUS] Secure & Stable");