
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal.h>

// =====================================
// PIN CONFIGURATION
// =====================================

// RC522 RFID Reader
#define RFID_SS_PIN 10
#define RFID_RST_PIN 9

// LEDs
#define GREEN_LED 4
#define RED_LED 5

// SG90 Servo
#define SERVO_PIN 6

// LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(2, 3, A0, A1, A2, A3);

// Create objects
MFRC522 rfid(RFID_SS_PIN, RFID_RST_PIN);
Servo doorServo;

// =====================================
// DOOR SETTINGS
// =====================================

const int LOCK_ANGLE = 0;
const int UNLOCK_ANGLE = 90;

const unsigned long UNLOCK_TIME = 5000;

// =====================================
// AUTHORISED RFID CARD UID
// CHANGE THIS TO YOUR CARD UID
// =====================================

byte authorizedUID[] = {
  0xA3, 0x7B, 0x21, 0x9C
};

const byte authorizedUIDLength =
  sizeof(authorizedUID);

// =====================================
// FUNCTION: LOCK DOOR
// =====================================

void lockDoor() {

  doorServo.write(LOCK_ANGLE);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);

  Serial.println("DOOR LOCKED");
}

// =====================================
// FUNCTION: DISPLAY MESSAGE
// =====================================

void displayMessage(const char *line1,
                    const char *line2) {

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(line1);

  lcd.setCursor(0, 1);
  lcd.print(line2);
}

// =====================================
// FUNCTION: READ AND DISPLAY UID
// =====================================

void displayCardUID() {

  Serial.print("CARD UID: ");

  for (byte i = 0; i < rfid.uid.size; i++) {

    if (rfid.uid.uidByte[i] < 0x10) {
      Serial.print("0");
    }

    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");
  }

  Serial.println();
}

// =====================================
// FUNCTION: CHECK AUTHORISED CARD
// =====================================

bool checkAuthorizedCard() {

  if (rfid.uid.size != authorizedUIDLength) {
    return false;
  }

  for (byte i = 0; i < authorizedUIDLength; i++) {

    if (rfid.uid.uidByte[i] != authorizedUID[i]) {
      return false;
    }
  }

  return true;
}

// =====================================
// FUNCTION: VALID CARD
// =====================================

void accessGranted() {

  Serial.println("ACCESS GRANTED");

  displayMessage("Access Granted",
                 "Door Unlocked");

  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);

  // Unlock door
  doorServo.write(UNLOCK_ANGLE);

  // Keep door unlocked for 5 seconds
  delay(UNLOCK_TIME);

  // Automatically lock door
  lockDoor();

  displayMessage("Door Locked",
                 "Scan Your Card");

  delay(1000);

}

// =====================================
// FUNCTION: INVALID CARD
// =====================================

void accessDenied() {

  Serial.println("ACCESS DENIED");

  displayMessage("Access Denied",
                 "Invalid Card");

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, HIGH);

  // Keep door locked
  doorServo.write(LOCK_ANGLE);

  delay(2000);

  digitalWrite(RED_LED, LOW);

  displayMessage("Access Control",
                 "Scan Your Card");

}

// =====================================
// SETUP
// =====================================

void setup() {

  Serial.begin(9600);

  // Configure LED pins
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);

  // Initialize LCD
  lcd.begin(16, 2);

  displayMessage("RFID DOOR LOCK",
                 "System Starting");

  // Initialize Servo
  doorServo.attach(SERVO_PIN);
  doorServo.write(LOCK_ANGLE);

  // Initialize RFID
  SPI.begin();
  rfid.PCD_Init();

  delay(2000);

  displayMessage("System Ready",
                 "Scan Your Card");

  Serial.println("========================");
  Serial.println("RFID DOOR LOCK SYSTEM");
  Serial.println("SYSTEM READY");
  Serial.println("========================");

  Serial.println("Scan your RFID card...");
}

// =====================================
// MAIN LOOP
// =====================================

void loop() {

  // Check for a new RFID card
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Read RFID card
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Display card UID
  displayCardUID();

  // Check card authorisation
  if (checkAuthorizedCard()) {

    accessGranted();

  } else {

    accessDenied();

  }

  // Stop RFID communication
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

}
