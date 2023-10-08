int readCardState() {     // Function to read the card ID
  int index;
  Serial.print("Card Data - ");
  for (index = 0; index < 4; index++) {
    readCard[index] = mfrc522.uid.uidByte[index];   // Read the card ID
    Serial.print(readCard[index]);
    if (index < 3) {
      Serial.print(",");   // Separate the 4 bytes with a comma
    }
  }
  Serial.println(" ");
  // Check Master Card
  if ((memcmp(readCard, masterCard, 4)) == 0) {   // Compare the ID with the Master Card using the memcmp function
    return STATE_SCAN_MASTER;     // If the card ID matches the Master Card ID, return the corresponding state
  }
  if (cardsStored == 0) {
    return STATE_SCAN_INVALID;  // If the card is not found, return the corresponding state
  }

  for (index = 0; index < cardsStored; index++) {
    if ((memcmp(readCard, cardArr[index], 4)) == 0) {     // If the card is registered, return the corresponding state
      return STATE_SCAN_VALID;                            
    }
  }
  return STATE_SCAN_INVALID;   // If no condition is met, return the corresponding state
}
