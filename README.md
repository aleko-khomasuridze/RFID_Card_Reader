# RFID_Card_Reader

### Project Overview:

The project involves an Arduino-based system with the following components:

1. **RFID Module (MFRC522):**
   - Connected via SPI (Serial Peripheral Interface).
   - Used to read RFID cards placed near the RFID scanner.

2. **OLED Display (SSD1306):**
   - Utilizes the Adafruit_GFX and Adafruit_SSD1306 libraries.
   - Displays various messages and feedback to the user.

3. **Buzzer:**
   - Connected to a digital pin (BUZZ_PIN).
   - Used for generating sound feedback.

4. **Relay:**
   - Connected to a digital pin (Relay).
   - Controls an external device (e.g., a lock) based on access permissions.

### States and State Machine:

The system operates based on different states, managed by a state machine. States include:
   - `STATE_STARTUP`: Initial state before the system starts.
   - `STATE_STARTING`: State during the initialization phase.
   - `STATE_WAITING`: State when waiting for card presentation.
   - `STATE_SCAN_INVALID`: State when an invalid card is scanned.
   - `STATE_SCAN_VALID`: State when a valid card is scanned.
   - `STATE_SCAN_MASTER`: State when scanning the master card.
   - `STATE_ADDED_CARD`: State after successfully adding a card.
   - `STATE_REMOVED_CARD`: State after successfully removing a card.

### Functions:

1. **`setup()` Function:**
   - Initializes hardware components (RFID, OLED display).
   - Sets initial states and pins.
   - Displays a welcome message and a card waiting message.

2. **`loop()` Function:**
   - Checks for changes in the system state and updates if needed.
   - Monitors the RFID module for new card presentations.
   - Calls `readCardState()` to determine the state of the presented card.
   - Updates the system state based on the card state.
   - Updates the OLED display with relevant messages.

3. **`updateState()` Function:**
   - Manages state transitions and associated actions.
   - Controls the relay based on access permissions.
   - Triggers the buzzer for certain events.

4. **`displayWrite()` Function:**
   - Manages the OLED display, showing messages and handling blinking effects.

### Additional Notes:

- The `cardArr` array stores the IDs of authorized cards, and the `masterCard` array contains the ID of the master card.

- The project aims to provide access control based on RFID card presentations, with different responses for valid and invalid cards.

- It includes feedback on the OLED display and audible cues through the buzzer.

- The relay is used to control an external device, and its state is adjusted based on access permissions.

This code demonstrates a practical implementation of an RFID-based access control system using Arduino and additional peripherals.
