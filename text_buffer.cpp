#include "text_buffer.h"
#include <stdio.h>

TextBuffer::TextBuffer(unsigned short physicalWidth, unsigned short physicalHeight, char * charBuffer) {
  TextBuffer::charBuffer = charBuffer;

  fontWidth = DEFAULT_FONT_WIDTH;
  fontHeight = DEFAULT_FONT_HEIGHT;

  TextBuffer::physicalWidth = physicalWidth;
  TextBuffer::physicalHeight = physicalHeight;

  currentRow = 0;
  currentColumn = 0;

  emptyCellChar = DEFAULT_EMPTY_CELL_CHAR;

  includePartialCells = DEFAULT_INCLUDE_PARTIAL_CELLS;

  updateFontDimensions();
  clearCharBuffer();
}

// Destructor
// TextBuffer::~TextBuffer() {
// };

void TextBuffer::setFontDimensions(unsigned char width, unsigned char height) {
  fontWidth = width;
  fontHeight = height;
  updateFontDimensions();
}

void TextBuffer::updateFontDimensions() {
  fontRows = physicalHeight/fontHeight+(includePartialCells ? (physicalHeight % fontHeight ? 1 : 0) : 0);
  fontColumns = (physicalWidth/fontWidth)+(includePartialCells ? (physicalWidth % fontWidth ? 1 : 0) : 0);
  charBufferSize = fontRows * fontColumns;
}

void TextBuffer::clearCharBuffer(char clearChar = ' ') {
  for (unsigned short i = 0; i < charBufferSize; i++) {
    charBuffer[i] = clearChar;
  }
}

void TextBuffer::clearCharBuffer() {
  clearCharBuffer(emptyCellChar);
}

void TextBuffer::printCharBuffer() {
  unsigned char row = 0;
  unsigned char column = 0;
  printf("%d", row); printf("%c", ' ');
  for (unsigned short i = 0; i < charBufferSize; i++) {

    printf("%c", charBuffer[i]);

    column++;
    if (column >= fontColumns) {
      if (i < charBufferSize-1)  {
        row++;
        printf("%c", ' '); printf("%d", row-1);
        printf("\n");
        printf("%d", row); printf("%c", ' ');
        column = 0;
      } else {
        printf("%c", ' '); printf("%d", row);
      }
    }
  }
  printf("\n");
}

// Implement strlen to avoid including <string.h>
// https://stackoverflow.com/a/4180876/1424374
size_t strlen(const char *str)
{
  size_t i;

  for (i = 0; str[i]; i++);
  return i;
}

void TextBuffer::printToBuffer(char * str) {
  unsigned char endPos = strlen(str);
  if (endPos > fontColumns) {
    endPos = fontColumns;
  }

  for(unsigned char i=0; i < endPos; i++) {
    if (str[i] == '\n') {
      currentColumn = 0;
      currentRow++;
      if (currentRow >= fontRows) {
        // shift charBuffer up by one line
        for (unsigned char j = fontColumns; j < charBufferSize; j++) {
          charBuffer[j-fontColumns] = charBuffer[j];
        }
        // clear bottom line
        for (unsigned char j = charBufferSize-fontColumns; j < charBufferSize; j++) {
          charBuffer[j] = emptyCellChar;
        }
        currentRow--;
      }
    } else {
      charBuffer[(currentRow*fontColumns)+currentColumn] = str[i];
      currentColumn++;
    }
  }
}

unsigned char TextBuffer::setRow(unsigned char row) {
  if (row >= fontRows) {
    row = fontRows-1;
  }
  TextBuffer::currentRow = row;
  return row;
}

unsigned char TextBuffer::setColumn(unsigned char column) {
  if (column >= fontColumns) {
    column = fontColumns-1;
  }
  TextBuffer::currentColumn = column;
  return column;
}

void TextBuffer::setPosition(unsigned char column, unsigned char row) {
  setColumn(column);
  setRow(row);
}

void TextBuffer::home() {
  setPosition(0, 0);
}

/* END OF FILE */
