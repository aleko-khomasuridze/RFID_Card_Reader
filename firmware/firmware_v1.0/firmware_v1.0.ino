/*
 * RFID Access Control System with OLED Display and Buzzer
 * Author: Aleko khomasuridze
 * Description:
 * This Arduino code implements an RFID-based access control system using the MFRC522 RFID module,
 * an OLED display (SSD1306), and a buzzer. The system manages access permissions for RFID cards
 * and controls an external device (e.g., a lock) through a relay. The code utilizes a state machine
 * to handle different system states and provides feedback through the OLED display and buzzer.
 * 
 * Components:
 * - RFID Module (MFRC522)
 * - OLED Display (SSD1306)
 * - Buzzer
 * - Relay
 * 
 * States:
 * - STATE_STARTUP: Initial state before the system starts.
 * - STATE_STARTING: State during the initialization phase.
 * - STATE_WAITING: State when waiting for card presentation.
 * - STATE_SCAN_INVALID: State when an invalid card is scanned.
 * - STATE_SCAN_VALID: State when a valid card is scanned.
 * - STATE_SCAN_MASTER: State when scanning the master card.
 * - STATE_ADDED_CARD: State after successfully adding a card.
 * - STATE_REMOVED_CARD: State after successfully removing a card.
 * 
 * Functions:
 * - setup(): Initializes hardware components and sets initial states.
 * - loop(): Monitors system state changes, RFID card presentations, and updates the display.
 * - updateState(): Manages state transitions and associated actions.
 * - displayWrite(): Handles OLED display messages and blinking effects.
 * 
 * Additional Notes:
 * - The code includes comments to explain each section and function.
 * - Access permissions are determined based on the scanned RFID cards.
 * - The relay controls an external device based on access permissions.
 * - The OLED display provides visual feedback, and the buzzer offers audible cues.
 * 
 * Make sure to connect the hardware components as per the provided pin configurations.
 */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MFRC522.h>

#define RST_PIN 5      // RFID reset pin
#define SS_PIN  10     // RFID SDA pin

#define STATE_STARTUP       0
#define STATE_STARTING      1
#define STATE_WAITING       2
#define STATE_SCAN_INVALID  3
#define STATE_SCAN_VALID    4
#define STATE_SCAN_MASTER   5
#define STATE_ADDED_CARD    6
#define STATE_REMOVED_CARD  7

#define BUZZ_PIN 3   // Pin for the buzzer
#define Relay 8      // Relay pin

const int cardArrSize = 10;   // Maximum number of stored cards
const int cardSize    = 4;    // Size of the ID
byte cardArr[cardArrSize][cardSize];   // Array to store card IDs
byte masterCard[cardSize] = {83, 5, 207, 50}; // Master card ID
byte readCard[cardSize];    // Array to store read card ID
byte cardsStored = 0;       // Number of stored cards

String granted_text[]  = {"Access", "granted"};
String unlocked_text[] = {"unlocked!", ""};
String cardWait_text[] = {"Please place your", "card near scanner!"};
String welcome_text[]  = {"Welcome!", ""};

MFRC522 mfrc522(SS_PIN, RST_PIN);    // Create RFID object

byte currentState = STATE_STARTUP;   // Initial state
unsigned long LastStateChangeTime;   // Variable to track time
unsigned long StateWaitTime;         // Variable to track time

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  SPI.begin();         // Init SPI Bus
  mfrc522.PCD_Init();  // Init MFRC522

  LastStateChangeTime = millis();  // Start timer
  updateState(STATE_STARTING);     // Set initial state
  pinMode(BUZZ_PIN, OUTPUT);       // Set buzzer pin
  pinMode(Relay, OUTPUT);          // Set relay pin
  digitalWrite(Relay, HIGH);       // Turn off the relay. Note: Make sure the relay is HIGH to start with.

  Serial.begin(9600);
  displayWrite(0, 0, 1, welcome_text, false, 0);  // Display welcome text on the OLED
  delay(1000);
  displayWrite(0, 0, 1, cardWait_text, false, 0); // Display card waiting text on the OLED
}

void loop() {
  byte cardState;  
  if ((currentState != STATE_WAITING) && (StateWaitTime > 0) && (LastStateChangeTime + StateWaitTime < millis())) 
    updateState(STATE_WAITING);

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
    return;

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
    return;
  cardState = readCardState();
  updateState(cardState);
  displayWrite(0, 0, 1, cardWait_text, false, 0);   // Display card waiting text on the OLED
}
