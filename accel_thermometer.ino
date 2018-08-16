/*
 * lcd_nav.ino - Example code using the menu system library
 *
 * This example shows using the menu system with a 16x2 LCD display
 * (controled over serial).
 *
 * Copyright (c) 2015 arduino-menusystem
 * Licensed under the MIT license (see LICENSE)
 */

#include <MenuSystem.h>

#include <Arduino.h>

#define I2C_ADDRESS 0x3C
// #include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
SSD1306AsciiWire oled;

boolean displayRemapMode = false;

const char* fontName[] = {
  "Adafruit5x7",
  "fixed_bold10x15",
  "font5x7",
  "font8x8",
  "lcd5x7",
  "newbasic3x5",
  "Stang5x7",
  "System5x7",
  "Wendy3x5",
  "X11fixed7x14",
  "X11fixed7x14B",
  "ZevvPeep8x16",
  "Iain5x7", // proportional
};
const uint8_t* fontList[] = {
  Adafruit5x7,
  fixed_bold10x15,
  font5x7,
  font8x8,
  lcd5x7,
  newbasic3x5,
  Stang5x7,
  System5x7,
  Wendy3x5,
  X11fixed7x14,
  X11fixed7x14B,
  ZevvPeep8x16,
  Iain5x7, // proportional
};
uint8_t nFont = sizeof(fontList)/sizeof(uint8_t*);
uint8_t currentFont = 9;

uint8_t fontHeight = 14;
uint8_t rowsOnScreen = 4; // based on font/screen height
uint8_t menuItemsOnScreen = rowsOnScreen - 1; // - 1 is for menu name
uint8_t screenWidthInChars = 10;

// pts == print to screen, with padding
void pts(const char * s) {

  // Serial.print("screenWidthInChars: "); Serial.print(screenWidthInChars); Serial.print(": ");
  oled.print(s);
  // Serial.print(s);

  if (strlen(s) < screenWidthInChars) {
    for (uint8_t i = strlen(s); i < screenWidthInChars; i++) {
      oled.print(" ");
      // Serial.print("_");
    }
  }
  // Serial.println("");
}

// widh newline at end
void ptsn(const char * s) {
  pts(s);
  oled.println("");
}

class MyRenderer : public MenuComponentRenderer {
public:
    void render(Menu const& menu) const {
        // Serial.println("BEGIN render()");

        // oled.clear();
        oled.setCursor(0,0);

        if (menu.get_name() != "") {
          pts(menu.get_name());
        } else {
          // oled.print("Main Menu");
          // oled.print(fontName[currentFont]);
          pts(fontName[currentFont]);// oled.print(printf("%5ld", fontName[currentFont]));


        }
        ptsn(""); // oled.println("");
        // oled.setCursor(0,1);

        /* oled */
        // Serial.println("BEGIN rendering get_num_components");
        uint8_t startComponent = 0;
        uint8_t endComponent = menu.get_num_components();
        uint8_t emptyRows = 0;
        if (menu.get_num_components() > menuItemsOnScreen) {
          // Serial.println("menu.get_num_components() > menuItemsOnScreen");
          if (menu.get_current_component_num() > (menuItemsOnScreen - 1)) {
            // Serial.println("** menu.get_current_component_num() > menuItemsOnScreen");
            endComponent = menu.get_current_component_num() + 1;
            startComponent = endComponent - menuItemsOnScreen;
          } else {
            endComponent = menuItemsOnScreen;
          }
        } else if (menu.get_num_components() < menuItemsOnScreen) {
          emptyRows = menuItemsOnScreen - menu.get_num_components();
        }

        // Serial.print("get_current_component_num(): "); Serial.print(menu.get_current_component_num());
        // Serial.print(", get_num_components(): "); Serial.println(menu.get_num_components());
        // Serial.print("menuItemsOnScreen: "); Serial.print(menuItemsOnScreen); Serial.print(", rowsOnScreen: "); Serial.println(rowsOnScreen);
        // Serial.print("startComponent: "); Serial.print(startComponent); Serial.print(", endComponent: "); Serial.println(endComponent);
        for (int i = startComponent; i < endComponent; ++i) {
            MenuComponent const* cp_m_comp = menu.get_menu_component(i);
            if (cp_m_comp->is_current()) {
                oled.print(">");
            } else {
                oled.print(" ");
            }
            cp_m_comp->render(*this);

            if (i != endComponent - 1)
              ptsn("");//oled.println("");
        }

        for (int i = 0; i <= emptyRows; ++i)
          ptsn("");//oled.println("");
        // Serial.println("END rendering get_num_components");
        // Serial.println("END render()\n");
    }

    void render_menu_item(MenuItem const& menu_item) const {
      // Serial.print("BEGIN render_menu_item(): ");
      // Serial.print(menu_item.get_name());
      // Serial.println("");

      pts(menu_item.get_name());

      // Serial.println("END render_menu_item()");
    }

    void render_back_menu_item(BackMenuItem const& menu_item) const {
        // Serial.print("BEGIN render_back_menu_item(): ");
        // Serial.print(menu_item.get_name());
        // Serial.println("");

        pts(menu_item.get_name());

        // Serial.println("END render_back_menu_item()");
    }

    void render_numeric_menu_item(NumericMenuItem const& menu_item) const {
        // Serial.print("BEGIN render_numeric_menu_item(): ");
        // Serial.print(menu_item.get_name());
        // Serial.println("");

        pts(menu_item.get_name());

        // Serial.println("END render_numeric_menu_item()");
    }

    void render_menu(Menu const& menu) const {
        // Serial.print("BEGIN render_menu(): ");
        // Serial.print(menu.get_name());
        // Serial.println("");

        pts(menu.get_name());

        // Serial.println("END render_menu()");
    }
};
MyRenderer my_renderer;

// Forward declarations

void on_item1_selected(MenuComponent* p_menu_component);
void on_item2_selected(MenuComponent* p_menu_component);
void on_item3_selected(MenuComponent* p_menu_component);

// Menu variables

MenuSystem ms(my_renderer);
// MenuItem mm_mi1("Level 1 - Item 1 (Item)", &on_item1_selected);
MenuItem mm_mi1("L1 - I1", &on_item1_selected);
MenuItem mm_mi2("Level 1 - Item 2 (Item)", &on_item2_selected);
Menu mu1("Level 1 - Item 3 (Menu)");
MenuItem mu1_mi1("Level 2 - Item 1 (Item)", on_item3_selected);
MenuItem mm_mi3("Level 1 - Item 4 (Item)", &on_item4_selected);
MenuItem mm_mi4("Level 1 - Item 5 (Item)", &on_item5_selected);

// Menu callback function

void on_item1_selected(MenuComponent* p_menu_component) {
    displayRemapMode = !displayRemapMode;
    oled.displayRemap(displayRemapMode);

    // oled.setCursor(0,1);
    oled.clear();
    oled.print("Item1 Selected  ");
    delay(1500); // so we can look the result on the LCD
}

void on_item2_selected(MenuComponent* p_menu_component) {
    // oled.setCursor(0,1);
    currentFont++;
    if (currentFont >= nFont)
      currentFont = 0;
    oled.setFont(fontList[currentFont]);

    rowsOnScreen = 64 / oled.fontHeight();
    menuItemsOnScreen = rowsOnScreen - 1;
    screenWidthInChars = oled.displayWidth() / (oled.fontWidth() + oled.letterSpacing());

    oled.clear();
    // oled.print("Item2 Selected  ");
    oled.print(fontName[currentFont]);
    delay(500); // so we can look the result on the LCD
}

void on_item3_selected(MenuComponent* p_menu_component) {
    // oled.setCursor(0,1);
    oled.clear();
    oled.print("Item3 Selected  ");
    delay(1500); // so we can look the result on the LCD
}

void on_item4_selected(MenuComponent* p_menu_component) {
    // oled.setCursor(0,1);
    oled.clear();
    oled.print("Item4 Selected  ");
    delay(1500); // so we can look the result on the LCD
}

void on_item5_selected(MenuComponent* p_menu_component) {
    // oled.setCursor(0,1);
    oled.clear();
    oled.print("Item5 Selected  ");
    delay(1500); // so we can look the result on the LCD
}

void serial_print_help() {
    Serial.println("***************");
    Serial.println("w: go to previus item (up)");
    Serial.println("s: go to next item (down)");
    Serial.println("a: go back (right)");
    Serial.println("d: select \"selected\" item");
    Serial.println("?: print this help");
    Serial.println("h: print this help");
    Serial.println("***************");
}

void serial_handler() {
    char inChar;
    if ((inChar = Serial.read()) > 0) {
        switch (inChar) {
            case 'w': // Previus item
                ms.prev();
                ms.display();
                break;
            case 's': // Next item
                ms.next();
                ms.display();
                break;
            case 'a': // Back presed
                ms.back();
                ms.display();
                break;
            case 'd': // Select presed
                ms.select();
                ms.display();
                break;
            case '?':
            case 'h': // Display help
                serial_print_help();
                break;
            default:
                break;
        }
    }
}

// Standard arduino functions

void setup() {
    Serial.begin(9600);
    Wire.begin();
    oled.begin(&Adafruit128x64, I2C_ADDRESS);
    oled.setFont(fontList[currentFont]);
    fontHeight = oled.fontHeight();
    rowsOnScreen = 64 / oled.fontHeight();
    menuItemsOnScreen = rowsOnScreen - 1;
    screenWidthInChars = oled.displayWidth() / (oled.fontWidth() + oled.letterSpacing());

    oled.setScroll(false);
    // Use true, normal mode, since default for Adafruit display is remap mode.
    oled.displayRemap(displayRemapMode);

    oled.print("Hello world!xxxxxxxxxxxxxxxxxx");

    serial_print_help();

    ms.get_root_menu().add_item(&mm_mi1);
    ms.get_root_menu().add_item(&mm_mi2);
    ms.get_root_menu().add_menu(&mu1);
    ms.get_root_menu().add_item(&mm_mi3);
    ms.get_root_menu().add_item(&mm_mi4);
    mu1.add_item(&mu1_mi1);

    ms.display();
}

void loop() {
    serial_handler();
}
