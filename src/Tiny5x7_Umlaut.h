#pragma once
#include <Adafruit_GFX.h>

const uint8_t Tiny5x7_UmlautBitmaps[] PROGMEM = {
  0x00  // Platzhalter-Bitmap
};

const GFXglyph Tiny5x7_UmlautGlyphs[] PROGMEM = {
  // Platzhalter-Glyphs für A-Z, ÄÖÜäöüß° usw.
  {0, 5, 7, 6, 0, -6}, // Beispielglyph (z.B. für 'A')
};

const GFXfont Tiny5x7_Umlaut PROGMEM = {
  (uint8_t*)Tiny5x7_UmlautBitmaps,
  (GFXglyph*)Tiny5x7_UmlautGlyphs,
  0x20, 0x7E, 8
};

// Tiny 5x7 Font mit ÄÖÜäöüß und ° für Adafruit_GFX
