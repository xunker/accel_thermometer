#ifndef TEXT_BUFFER_H
#define TEXT_BUFFER_H

#include <stdio.h>

#define DEFAULT_FONT_WIDTH 17
#define DEFAULT_FONT_HEIGHT 24
#define DEFAULT_EMPTY_CELL_CHAR ' '
#define DEFAULT_INCLUDE_PARTIAL_CELLS true

class TextBuffer {
public:
    char * charBuffer;

    // TODO: make these private, add public getters
    unsigned char fontWidth;
    unsigned char fontHeight;

    // TODO: make these private, add public getters
    unsigned char fontRows;
    unsigned char fontColumns;

    // TODO: make these private, add public getters
    unsigned short physicalWidth;
    unsigned short physicalHeight;

    // TODO: make these private, add public getters
    unsigned short charBufferSize;

    // TODO: make these private, add public getters
    unsigned char currentRow;
    unsigned char currentColumn;

    char emptyCellChar;

    // Must call updateFontDimensions() after changing this
    bool includePartialCells;

    /* Args:
        Screen width in pixels,
        Screen height in pixels,
        Buffer of the text currently on the screen */
    TextBuffer(unsigned short, unsigned short, char  *);

    // ~TextBuffer();

    void updateFontDimensions();
    void clearCharBuffer(char);
    void clearCharBuffer();
    void printCharBuffer();
    void printToBuffer(char *);

    unsigned char setRow(unsigned char);
    unsigned char setColumn(unsigned char);
    void setPosition(unsigned char, unsigned char);

    void home();

    /* Set the current font dimensions. Args: width in pixels, height in pixels */
    void setFontDimensions(unsigned char, unsigned char);
  private:

};

#endif /* TEXT_BUFFER_H */

/* END OF FILE */
