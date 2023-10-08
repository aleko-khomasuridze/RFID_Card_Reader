void addReadCard() {    // Function to add a card
  int cardIndex;        // Card index
  int index;

  if (cardsStored < 20) {  // If the number of stored cards is less than 20
    cardsStored++;  // Increment the count of stored cards by 1
    cardIndex = cardsStored;  // Set the card index to the current value of stored cards
    cardIndex--;  // Subtract one to avoid index overflow
  }

  for (index = 0; index < 4; index++) {
    cardArr[cardIndex][index] = readCard[index];    // Save the card ID bits in the array
  }
}

void removeReadCard() {   // Function to remove a card
  int cardIndex;          // Card index
  int index;
  boolean found = false;  // Variable to check if the card is found in the list

  for (cardIndex = 0; cardIndex < cardsStored; cardIndex++) {
    if (found == true) {  // If the card is found, start the removal process
      for (index = 0; index < 4; index++) {
        cardArr[cardIndex - 1][index] = cardArr[cardIndex][index];   // Erase the card ID bits
        cardArr[cardIndex][index] = 0;
      }
    }
    if ((memcmp(readCard, cardArr[cardIndex], 4)) == 0) {
      found = true;   // If the card ID is found, set 'found' to true
    }
  }
  if (found == true) {
    cardsStored--;   // After removing the card, decrease the count of stored cards by 1
  }
}
