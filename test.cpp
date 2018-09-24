// gcc -Wall -o test test.cpp text_buffer.cpp && ./test

#include <stdio.h>
#include "text_buffer.h"

#define TEXT_BUFFER_SCREEN_WIDTH 200
#define TEXT_BUFFER_SCREEN_HEIGHT 200
#define MINIMUM_FONT_WIDTH 5
#define MINIMUM_FONT_HEIGHT 8

char charBuffer[((TEXT_BUFFER_SCREEN_WIDTH/MINIMUM_FONT_WIDTH)*(TEXT_BUFFER_SCREEN_HEIGHT/MINIMUM_FONT_HEIGHT))];

TextBuffer tb(200, 200, charBuffer);

int main() {
  // tb.setFontDimensions(5, 8);
  tb.setFontDimensions(17, 24);

  printf("Font Width: "); printf("%d", tb.fontWidth); printf("\n");
  printf("Font Height: "); printf("%d", tb.fontHeight); printf("\n");
  printf("Screen Width: "); printf("%d", tb.physicalWidth); printf("\n");
  printf("Screen Height: "); printf("%d", tb.physicalHeight); printf("\n");
  printf("Font Columns: "); printf("%d", tb.fontColumns); printf("\n");
  printf("Fot Rows: "); printf("%d", tb.fontRows); printf("\n");
  printf("%lu", sizeof(tb.charBuffer)); printf("\n");

  // tb.includePartialCells = false;
  // tb.updateFontDimensions();

  tb.emptyCellChar = '.';
  tb.clearCharBuffer();

  // tb.printToBuffer((char *)"abcdefghijkl\n");
  // tb.printToBuffer((char *)"abcdefghijk\n");
  // tb.printToBuffer((char *)"abcdefghij\n");
  // tb.printToBuffer((char *)"abcdefghi\n");
  // tb.printToBuffer((char *)"abcdefgh\n");
  // tb.printToBuffer((char *)"abcdefg\n");
  // tb.printToBuffer((char *)"abcdef\n");
  // tb.printToBuffer((char *)"abcde\n");
  // tb.printToBuffer((char *)"abcd\n");
  // tb.printToBuffer((char *)"abc\n");

  tb.setRow(3);
  tb.setColumn(1);
  tb.setPosition(4,4);
  tb.printToBuffer((char *)"abc");
  tb.home();
  tb.printToBuffer((char *)"def");

  tb.printCharBuffer();
}
