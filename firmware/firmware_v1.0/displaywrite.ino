void displayWrite(int x, int y, int fontSize, String text[], boolean Blink, int blinkAmount) {
  display.clearDisplay();  // Clear the screen
  display.display();       // Display the cleared screen
  if (Blink == false) {  // If we don't want the text to blink
    for (int i = 0; i < sizeof(text) / sizeof(text[0]); i++) {  // Display as many lines as the length of the text array
      display.setTextSize(fontSize);  // Set the font size
      display.setTextColor(WHITE);    // Set the text color
      display.setCursor(x, y + (i * 12));  // Set the cursor position for each element with a vertical spacing of 12 pixels
      display.println(text[i]);   // Display array elements on the screen
      display.display();
    }
  } else {  // If we want the text to blink
    for (int j = 0; j < blinkAmount; j++) {     // Blink for as many times as specified by blinkAmount
      for (int i = 0; i < sizeof(text) / sizeof(text[0]); i++) {  // Display as many lines as the length of the text array
        display.setTextSize(fontSize);   // Set the font size
        display.setTextColor(WHITE);     // Set the text color
        display.setCursor(x, y + (i * 12));   // Set the cursor position for each element with a vertical spacing of 12 pixels
        display.println(text[i]);   // Display array elements on the screen
        display.display();
        digitalWrite(BUZZ_PIN, HIGH);   // Turn on the buzzer
      }
      delay(100);
      display.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK); // Clear the screen to turn off the text
      digitalWrite(BUZZ_PIN, LOW);   // Turn off the buzzer
      display.display();
      delay(100);
    }
  }
}
