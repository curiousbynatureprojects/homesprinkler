#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define OLED pins
#define OLED_RESET   D2  // Reset pin
#define OLED_DC      D3  // Data/Command pin
#define OLED_CS      D8  // Chip Select pin

// Create display object for SPI communication
Adafruit_SSD1306 display(128, 32, &SPI, OLED_DC, OLED_RESET, OLED_CS);

const char* name = "Daksh";  // Text to display
int textWidth;               // To hold the width of the text
int xPos = 128;              // Starting position for scrolling (off-screen to the right)

void setup() {
  // Initialize serial monitor
  Serial.begin(115200);

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 initialization failed!"));
    while (true);  // Stay here if the initialization fails
  }

  // Clear the display
  display.clearDisplay();

  // Set text size and color
  display.setTextSize(1);  // Change the text size to 2
  display.setTextColor(SSD1306_WHITE);

  // Calculate the text width based on the text size
  textWidth = strlen(name) * 12;  // (12px per character) * text size (2)
}

void loop() {
  // Clear the display each time before printing new text
  display.clearDisplay();

  // Set the cursor at the current position
  display.setCursor(xPos, 20);  // Adjust Y position for vertical alignment

  // Print the name
  display.println(name);

  // Move the text left by 1 pixel for scrolling effect
  xPos--;

  // If the text is completely off-screen, reset the position to the right
  if (xPos < -textWidth) {
    xPos = 128;  // Reset position to start from the right
  }

  // Update the display
  display.display();

  // Wait for a short delay before moving the text again
  delay(50);  // Adjust this value to control the scroll speed
}
