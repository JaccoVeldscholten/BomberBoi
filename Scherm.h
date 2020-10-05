#ifndef _SCHERMH_
#define _SCHERMH_
#pragma once
#include "libraries/Adafruit_ILI9341/Adafruit_ILI9341.h"
#include <stdint.h>

class Scherm
{
public:
    Adafruit_ILI9341 *tft;

    Scherm(Adafruit_ILI9341 &_tft);
    void getHighScore();
    void draw_text(uint8_t Xloc, uint8_t Yloc, uint8_t size, char *text, uint16_t colour);

private:
};
#endif
