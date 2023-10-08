void updateState(byte aState) {
  if (aState == currentState) {
    return;  // If the new state is the same as the current state, no need to update
  }
  // Perform state change
  switch (aState) {
    case STATE_STARTING:
      StateWaitTime = 1000;  // Set wait time for the starting state
      break;
    case STATE_WAITING:
      StateWaitTime = 0;  // No wait time for the waiting state
      break;
    case STATE_SCAN_INVALID:
      if (currentState == STATE_SCAN_MASTER) {
        addReadCard();  // Add the read card to the list
        aState = STATE_ADDED_CARD;  // Change state to indicate a card has been added
        StateWaitTime = 2000;  // Set wait time after adding the card
      } else if (currentState == STATE_REMOVED_CARD) {
        return;  // If the current state is card removal, do nothing
      } else {
        StateWaitTime = 2000;  // Set default wait time for other cases
      }
      break;
    case STATE_SCAN_VALID:
      if (currentState == STATE_SCAN_MASTER) {
        removeReadCard();  // Remove the read card from the list
        aState = STATE_REMOVED_CARD;  // Change state to indicate a card has been removed
        StateWaitTime = 2000;  // Set wait time after removing the card
      } else if (currentState == STATE_ADDED_CARD) {
        return ;  // If the current state is card addition, do nothing
      } else {
        StateWaitTime = 2000;  // Set default wait time for other cases
        displayWrite(0, 0, 1, granted_text, true, 5);  // Display granted text with blinking
        displayWrite(0, 0, 1, unlocked_text, false, 0);  // Display unlocked text
        digitalWrite(Relay, LOW);  // Activate the relay
        delay(3000);  // Wait for 3 seconds
        digitalWrite(Relay, HIGH);  // Deactivate the relay
      }
      break;
    case STATE_SCAN_MASTER:
      StateWaitTime = 5000;  // Set wait time for the master card scanning state
      break;
  }
  currentState = aState;  // Update the current state
  LastStateChangeTime = millis();  // Update the time of the last state change
}
