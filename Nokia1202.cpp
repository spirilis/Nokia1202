/* STE2007 LCD text driver
 * Compatible with Nokia 1202 B&W LCD display
 * Converted to C++ for Energia
 *
 * Copyright (C) 2013 Eric Brundick <spirilis@linux.com>
 *
 * References code and examples from John Honniball, Bristol UK and:
 * Copyright (c) 2012, Greg Davill
 *    All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *     Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the
 *     distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <Energia.h>
#include "Nokia1202.h"
#include "ste2007.h"


/*
 * font_5x7.h
 *
 *  Created on: Mar 15, 2012
 *      Author: RG1540
 */

const unsigned char font_5x7[][6] = {		// basic font
	 {0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 20
	,{0x00, 0x00, 0x5f, 0x00, 0x00, 0x00} // 21 !
	,{0x00, 0x07, 0x00, 0x07, 0x00, 0x00} // 22 "
	,{0x14, 0x7f, 0x14, 0x7f, 0x14, 0x00} // 23 #
	,{0x24, 0x2a, 0x7f, 0x2a, 0x12, 0x00} // 24 $
	,{0x23, 0x13, 0x08, 0x64, 0x62, 0x00} // 25 %
	,{0x36, 0x49, 0x55, 0x22, 0x50, 0x00} // 26 &
	,{0x00, 0x05, 0x03, 0x00, 0x00, 0x00} // 27 '
	,{0x00, 0x1c, 0x22, 0x41, 0x00, 0x00} // 28 (
	,{0x00, 0x41, 0x22, 0x1c, 0x00, 0x00} // 29 )
	,{0x14, 0x08, 0x3e, 0x08, 0x14, 0x00} // 2a *
	,{0x08, 0x08, 0x3e, 0x08, 0x08, 0x00} // 2b +
	,{0x00, 0x50, 0x30, 0x00, 0x00, 0x00} // 2c ,
	,{0x08, 0x08, 0x08, 0x08, 0x08, 0x00} // 2d -
	,{0x00, 0x60, 0x60, 0x00, 0x00, 0x00} // 2e .
	,{0x20, 0x10, 0x08, 0x04, 0x02, 0x00} // 2f /
	,{0x3e, 0x51, 0x49, 0x45, 0x3e, 0x00} // 30 0
	,{0x00, 0x42, 0x7f, 0x40, 0x00, 0x00} // 31 1
	,{0x42, 0x61, 0x51, 0x49, 0x46, 0x00} // 32 2
	,{0x21, 0x41, 0x45, 0x4b, 0x31, 0x00} // 33 3
	,{0x18, 0x14, 0x12, 0x7f, 0x10, 0x00} // 34 4
	,{0x27, 0x45, 0x45, 0x45, 0x39, 0x00} // 35 5
	,{0x3c, 0x4a, 0x49, 0x49, 0x30, 0x00} // 36 6
	,{0x01, 0x71, 0x09, 0x05, 0x03, 0x00} // 37 7
	,{0x36, 0x49, 0x49, 0x49, 0x36, 0x00} // 38 8
	,{0x06, 0x49, 0x49, 0x29, 0x1e, 0x00} // 39 9
	,{0x00, 0x36, 0x36, 0x00, 0x00, 0x00} // 3a :
	,{0x00, 0x56, 0x36, 0x00, 0x00, 0x00} // 3b ;
	,{0x08, 0x14, 0x22, 0x41, 0x00, 0x00} // 3c <
	,{0x14, 0x14, 0x14, 0x14, 0x14, 0x00} // 3d =
	,{0x00, 0x41, 0x22, 0x14, 0x08, 0x00} // 3e >
	,{0x02, 0x01, 0x51, 0x09, 0x06, 0x00} // 3f ?
	,{0x32, 0x49, 0x79, 0x41, 0x3e, 0x00} // 40 @
	,{0x7e, 0x11, 0x11, 0x11, 0x7e, 0x00} // 41 A
	,{0x7f, 0x49, 0x49, 0x49, 0x36, 0x00} // 42 B
	,{0x3e, 0x41, 0x41, 0x41, 0x22, 0x00} // 43 C
	,{0x7f, 0x41, 0x41, 0x22, 0x1c, 0x00} // 44 D
	,{0x7f, 0x49, 0x49, 0x49, 0x41, 0x00} // 45 E
	,{0x7f, 0x09, 0x09, 0x09, 0x01, 0x00} // 46 F
	,{0x3e, 0x41, 0x49, 0x49, 0x7a, 0x00} // 47 G
	,{0x7f, 0x08, 0x08, 0x08, 0x7f, 0x00} // 48 H
	,{0x00, 0x41, 0x7f, 0x41, 0x00, 0x00} // 49 I
	,{0x20, 0x40, 0x41, 0x3f, 0x01, 0x00} // 4a J
	,{0x7f, 0x08, 0x14, 0x22, 0x41, 0x00} // 4b K
	,{0x7f, 0x40, 0x40, 0x40, 0x40, 0x00} // 4c L
	,{0x7f, 0x02, 0x0c, 0x02, 0x7f, 0x00} // 4d M
	,{0x7f, 0x04, 0x08, 0x10, 0x7f, 0x00} // 4e N
	,{0x3e, 0x41, 0x41, 0x41, 0x3e, 0x00} // 4f O
	,{0x7f, 0x09, 0x09, 0x09, 0x06, 0x00} // 50 P
	,{0x3e, 0x41, 0x51, 0x21, 0x5e, 0x00} // 51 Q
	,{0x7f, 0x09, 0x19, 0x29, 0x46, 0x00} // 52 R
	,{0x46, 0x49, 0x49, 0x49, 0x31, 0x00} // 53 S
	,{0x01, 0x01, 0x7f, 0x01, 0x01, 0x00} // 54 T
	,{0x3f, 0x40, 0x40, 0x40, 0x3f, 0x00} // 55 U
	,{0x1f, 0x20, 0x40, 0x20, 0x1f, 0x00} // 56 V
	,{0x3f, 0x40, 0x38, 0x40, 0x3f, 0x00} // 57 W
	,{0x63, 0x14, 0x08, 0x14, 0x63, 0x00} // 58 X
	,{0x07, 0x08, 0x70, 0x08, 0x07, 0x00} // 59 Y
	,{0x61, 0x51, 0x49, 0x45, 0x43, 0x00} // 5a Z
	,{0x00, 0x7f, 0x41, 0x41, 0x00, 0x00} // 5b [
	,{0x02, 0x04, 0x08, 0x10, 0x20, 0x00} // 5c ¥
	,{0x00, 0x41, 0x41, 0x7f, 0x00, 0x00} // 5d ]
	,{0x04, 0x02, 0x01, 0x02, 0x04, 0x00} // 5e ^
	,{0x40, 0x40, 0x40, 0x40, 0x40, 0x00} // 5f _
	,{0x00, 0x01, 0x02, 0x04, 0x00, 0x00} // 60 `
	,{0x20, 0x54, 0x54, 0x54, 0x78, 0x00} // 61 a
	,{0x7f, 0x48, 0x44, 0x44, 0x38, 0x00} // 62 b
	,{0x38, 0x44, 0x44, 0x44, 0x20, 0x00} // 63 c
	,{0x38, 0x44, 0x44, 0x48, 0x7f, 0x00} // 64 d
	,{0x38, 0x54, 0x54, 0x54, 0x18, 0x00} // 65 e
	,{0x08, 0x7e, 0x09, 0x01, 0x02, 0x00} // 66 f
	,{0x0c, 0x52, 0x52, 0x52, 0x3e, 0x00} // 67 g
	,{0x7f, 0x08, 0x04, 0x04, 0x78, 0x00} // 68 h
	,{0x00, 0x44, 0x7d, 0x40, 0x00, 0x00} // 69 i
	,{0x20, 0x40, 0x44, 0x3d, 0x00, 0x00} // 6a j
	,{0x7f, 0x10, 0x28, 0x44, 0x00, 0x00} // 6b k
	,{0x00, 0x41, 0x7f, 0x40, 0x00, 0x00} // 6c l
	,{0x7c, 0x04, 0x18, 0x04, 0x78, 0x00} // 6d m
	,{0x7c, 0x08, 0x04, 0x04, 0x78, 0x00} // 6e n
	,{0x38, 0x44, 0x44, 0x44, 0x38, 0x00} // 6f o
	,{0x7c, 0x14, 0x14, 0x14, 0x08, 0x00} // 70 p
	,{0x08, 0x14, 0x14, 0x18, 0x7c, 0x00} // 71 q
	,{0x7c, 0x08, 0x04, 0x04, 0x08, 0x00} // 72 r
	,{0x48, 0x54, 0x54, 0x54, 0x20, 0x00} // 73 s
	,{0x04, 0x3f, 0x44, 0x40, 0x20, 0x00} // 74 t
	,{0x3c, 0x40, 0x40, 0x20, 0x7c, 0x00} // 75 u
	,{0x1c, 0x20, 0x40, 0x20, 0x1c, 0x00} // 76 v
	,{0x3c, 0x40, 0x30, 0x40, 0x3c, 0x00} // 77 w
	,{0x44, 0x28, 0x10, 0x28, 0x44, 0x00} // 78 x
	,{0x0c, 0x50, 0x50, 0x50, 0x3c, 0x00} // 79 y
	,{0x44, 0x64, 0x54, 0x4c, 0x44, 0x00} // 7a z
	,{0x00, 0x08, 0x36, 0x41, 0x00, 0x00} // 7b {
	,{0x00, 0x00, 0x7f, 0x00, 0x00, 0x00} // 7c |
	,{0x00, 0x41, 0x36, 0x08, 0x00, 0x00} // 7d }
	,{0x10, 0x08, 0x08, 0x10, 0x08, 0x00} // 7e ~
	,{0x00, 0x06, 0x09, 0x09, 0x06, 0x00} // 7f Deg Symbol
	,{0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0} // 80 Cursor
        ,{0x08, 0x18, 0x38, 0x3F, 0x1F, 0x3F} // 81 TI logo - left half
        ,{0x44, 0xF6, 0x3C, 0x1C, 0x18, 0x00} // 82 TI logo - right half
};
/* end of font */


/* Energia C++ constructor */
Nokia1202::Nokia1202(uint8_t csPin)
{
  _csPin = csPin;
  _contrast = 15;
  _useCursor = false;
  _tabSpacing = 4;
  _doFlush = true;
}

/* Command I/O functions */
void Nokia1202::issuecmd(uint8_t cmd, uint8_t arg, uint8_t argmask)
{
  digitalWrite(_csPin, LOW);
  SPI.transfer9( (uint16_t) (cmd | (arg & argmask)) );
  digitalWrite(_csPin, HIGH);
}

void Nokia1202::issue_compoundcmd(uint8_t cmd, uint8_t arg, uint8_t argmask)
{
  digitalWrite(_csPin, LOW);
  // Compound commands are sent by sending the command first, then data in a second transfer.
  SPI.transfer9( (uint16_t)cmd );
  SPI.transfer9( (uint16_t) (arg & argmask) );
  digitalWrite(_csPin, HIGH);
}

/* Logical LCD operations */
void Nokia1202::begin(boolean useCursor, uint8_t contrast, uint8_t tabSpacing)
{
  uint16_t i;

  _contrast = contrast;
  _useCursor = useCursor;
  _tabSpacing = tabSpacing;

  digitalWrite(_csPin, HIGH);
  pinMode(_csPin, OUTPUT);
  delay(1);

  issuecmd(STE2007_CMD_RESET, 0, STE2007_MASK_RESET);  // Soft RESET
  issuecmd(STE2007_CMD_DPYALLPTS, 0, STE2007_MASK_DPYALLPTS); // Powersave ALLPOINTS-ON mode turned OFF
  issuecmd(STE2007_CMD_PWRCTL, 7, STE2007_MASK_PWRCTL); // Power control set to max
  issuecmd(STE2007_CMD_ONOFF, 1, STE2007_MASK_ONOFF); // Display ON
  issuecmd(STE2007_CMD_COMDIR, 0, STE2007_MASK_COMDIR); // Display common driver = NORMAL
  issuecmd(STE2007_CMD_SEGMENTDIR, 0, STE2007_MASK_SEGMENTDIR); // Lines start at the left
  issuecmd(STE2007_CMD_ELECTVOL, _contrast, STE2007_MASK_ELECTVOL); // Electronic volume set to user specified contrast

  clear();

  issue_compoundcmd(STE2007_CMD_REFRESHRATE, 3, STE2007_MASK_REFRESHRATE); // Refresh rate = 65Hz
  issue_compoundcmd(STE2007_CMD_CHARGEPUMP, 0, STE2007_MASK_CHARGEPUMP); // Charge Pump multiply factor = 5x
  issuecmd(STE2007_CMD_SETBIAS, 6, STE2007_MASK_SETBIAS); // Bias ratio = 1/4
  issue_compoundcmd(STE2007_CMD_VOP, 0, STE2007_MASK_VOP);
  issuecmd(STE2007_CMD_DPYREV, 0, STE2007_MASK_DPYREV); // Display normal (not inverted)
}

/* Put the LCD in a powered-down state */
void Nokia1202::end()
{
  powersave(true);
  digitalWrite(_csPin, HIGH);
}

/* Fully erase DDRAM */
void Nokia1202::clear()
{
  int i;

  setxy(0, 0);
  digitalWrite(_csPin, LOW);
  for (i=0; i < NOKIA1202_COLUMNS * NOKIA1202_CHAR_WIDTH * (NOKIA1202_LINES+1); i++) {
    SPI.transfer9( 0x100 );  // Write 0
  }
  digitalWrite(_csPin, HIGH);
  _x = 0;
  _y = 0;
  setxy(0, 0);

#ifdef NOKIA1202_USE_FRAMEBUFFER
  // Clear framebuffer RAM
  for (i=0; i < NOKIA1202_COLUMNS * NOKIA1202_LINES; i++)
    _framebuffer[i] = ' ';
  // Clear dirtybits array
  for (i=0; i < NOKIA1202_LINES; i++)
    _dirtybits[i] = 0x0000;
#endif
  // Plant the cursor at its new position.
  if (_useCursor) {
#ifdef NOKIA1202_USE_FRAMEBUFFER
    _framebuffer[0] = 0x80;
#endif
    _writefont(0x80);
    setxy(0, 0);
  }

}

/* Set DDRAM cursor */
void Nokia1202::setxy(uint8_t x, uint8_t y)
{
  issuecmd(STE2007_CMD_LINE, y, STE2007_MASK_LINE);
  issuecmd(STE2007_CMD_COLMSB, x >> 4, STE2007_MASK_COLMSB);
  issuecmd(STE2007_CMD_COLLSB, x, STE2007_MASK_COLLSB);
}

/* Bulk-write data to DDRAM
 * Note: This function does not drive the Chip Select line but assumes that you will
 *       before & after running this.  Handy for multi-byte marathon writes.
 */
void Nokia1202::bulkwrite(const void *buf, uint16_t len)
{
  int i;
  uint8_t *ubuf = (uint8_t *)buf;

  for (i=0; i < len; i++) {
    SPI.transfer9( (uint16_t)(*ubuf++) | 0x100 );
  }
}

/* Just for fun... */
void Nokia1202::invert(boolean onoff)
{
  issuecmd(STE2007_CMD_DPYREV, onoff, STE2007_MASK_DPYREV);
}

/* STE2007 datasheet lists ONOFF=0, DPYALLPTS=1 as a "Power saver" mode. */
void Nokia1202::powersave(boolean onoff)  // 1 = power-saver mode, 0 = normal mode
{
  issuecmd(STE2007_CMD_DPYALLPTS, onoff, STE2007_MASK_DPYALLPTS);
  issuecmd(STE2007_CMD_ONOFF, !onoff, STE2007_MASK_ONOFF);
}

/* Set contrast; val is a scale from 0-31 and configures the Electronic Volume setting.
 * 16 is the default.
 */
void Nokia1202::contrast(uint8_t val)
{
  if (val > 31)  // Input validation
    val = 31;
  issuecmd(STE2007_CMD_ELECTVOL, val, STE2007_MASK_ELECTVOL);
}

/* Set LCD refresh rate, just for the heck of it.
 * Supported values: 65, 70, 75, 80 (Hz)
 */
void Nokia1202::refreshrate(uint8_t val)
{
  switch (val) {
    case 80:
      issue_compoundcmd(STE2007_CMD_REFRESHRATE, 0, STE2007_MASK_REFRESHRATE);
      break;

    case 75:
      issue_compoundcmd(STE2007_CMD_REFRESHRATE, 1, STE2007_MASK_REFRESHRATE);
      break;

    case 70:
      issue_compoundcmd(STE2007_CMD_REFRESHRATE, 2, STE2007_MASK_REFRESHRATE);
      break;

    default:
      issue_compoundcmd(STE2007_CMD_REFRESHRATE, 3, STE2007_MASK_REFRESHRATE);
  }
}

/* Write a single character, including driving the Chip Select line ourselves.
 * Resolves the ASCII character to the requisite font entry.  Only valid chars
 * from 0x20 to 0x80 allowed (>0x80 will result in a buffer overrun glitch)
 */
void Nokia1202::_writefont(uint8_t c)
{
  digitalWrite(_csPin, LOW);
  bulkwrite(font_5x7[c-' '], NOKIA1202_CHAR_WIDTH);
  digitalWrite(_csPin, HIGH);
}

/* High-level terminal management functions */

// Intelligent writing & processing of a single character
size_t Nokia1202::write(uint8_t c)
{
  uint8_t i = 0;

  // Process the character as-is
  if (c >= 0x20) {
#ifdef NOKIA1202_USE_FRAMEBUFFER
    _framebuffer[_y * NOKIA1202_COLUMNS + _x] = c;
    _dirtybits[_y] |= 1 << _x;
#else
    _writefont(c);
#endif
    _x++;
  } else {
    // Process control character
    switch (c) {
      case '\n':
        if (_useCursor) {
          // Erase the cursor presently at _x,_y before moving it
#ifdef NOKIA1202_USE_FRAMEBUFFER
          _framebuffer[_y * NOKIA1202_COLUMNS + _x] = ' ';
          _dirtybits[_y] |= 1 << _x;
#else
          _writefont(' ');
#endif
        }
        _x = 0;
        _y++;
// Note the "ifNdef" in this line:
#ifndef NOKIA1202_USE_FRAMEBUFFER
        setxy(_x * NOKIA1202_CHAR_WIDTH, _y);
#endif
        break;

      case '\t':
        if (_useCursor) {
          // Erase the cursor presently at _x,_y before moving it
#ifdef NOKIA1202_USE_FRAMEBUFFER
          _framebuffer[_y * NOKIA1202_COLUMNS + _x] = ' ';
          _dirtybits[_y] |= 1 << _x;
#else
          _writefont(' ');
#endif
        }
        if (_x % _tabSpacing == 0) {
          _x += _tabSpacing;
        } else {
          _x += _x % _tabSpacing;
        }
#ifndef NOKIA1202_USE_FRAMEBUFFER
        setxy(_x * NOKIA1202_CHAR_WIDTH, _y);
#endif
        break;

      case '\b':
        if (_useCursor) {
          // Erase the cursor presently at _x,_y before moving it
#ifdef NOKIA1202_USE_FRAMEBUFFER
          _framebuffer[_y * NOKIA1202_COLUMNS + _x] = ' ';
          _dirtybits[_y] |= 1 << _x;
#else
          _writefont(' ');
#endif
        }
        if (_x > 0) {
          _x--;
#ifdef NOKIA1202_USE_FRAMEBUFFER
          _framebuffer[_y * NOKIA1202_COLUMNS + _x] = ' ';
          _dirtybits[_y] |= 1 << _x;
#else
          setxy(_x * NOKIA1202_CHAR_WIDTH, _y);
          _writefont(' ');
          setxy(_x * NOKIA1202_CHAR_WIDTH, _y);
#endif
        }
        break;
      // No default section; any other ctrl char is ignored
    }
                                
  }

  if (_x >= NOKIA1202_COLUMNS) {
    // Shift down 1 row
    _y++;
    _x = 0;
  }

  if (_y >= NOKIA1202_LINES) {
    // Ut oh, we must scroll (or roll back to the top in no-framebuffer mode)
#ifdef NOKIA1202_USE_FRAMEBUFFER
    for (i=1; i < NOKIA1202_LINES; i++) {
      // Copy line to line above
      memcpy(_framebuffer + (i-1) * NOKIA1202_COLUMNS,
             _framebuffer + i * NOKIA1202_COLUMNS,
             NOKIA1202_COLUMNS);
      _dirtybits[i-1] = 0xFFFF;
    }
    // Cursor re-set to the bottom line
    _y = NOKIA1202_LINES - 1;
    // Clear the bottom line
    memset(_framebuffer + _y * NOKIA1202_COLUMNS,
           ' ',
           NOKIA1202_COLUMNS);
    _dirtybits[_y] = 0xFFFF;
#else
    _y = 0;
#endif
  }

  // Plant the cursor at its new position.
  if (_useCursor) {
#ifdef NOKIA1202_USE_FRAMEBUFFER
    _framebuffer[_y * NOKIA1202_COLUMNS + _x] = 0x80;
    _dirtybits[_y] |= 1 << _x;
#else
    setxy(_x * NOKIA1202_CHAR_WIDTH, _y);
    _writefont(0x80);
#endif
  }

  // Commit data to screen (framebuffer mode) or set cursor position (non-framebuffer mode)
#ifdef NOKIA1202_USE_FRAMEBUFFER
  if (_doFlush)  // An optimization that makes puts() a lot faster...
    _flush();
#else
  setxy(_x * NOKIA1202_CHAR_WIDTH, _y);
#endif
	return 1;
}


/* _flush() processes dirtybits to commit framebuffer contents to the DDRAM.
 * Only applicable when this library is used in framebuffer-mode.
 */
#ifdef NOKIA1202_USE_FRAMEBUFFER
void Nokia1202::_flush()
{
  uint16_t i, j;

  for(i=0; i < NOKIA1202_LINES; i++) {
    if (_dirtybits[i]) {
      if (_dirtybits[i] == 0xFFFF) {
        setxy(0, i);
        digitalWrite(_csPin, LOW);
        for (j=0; j < NOKIA1202_COLUMNS; j++) {
          bulkwrite(font_5x7[_framebuffer[i * NOKIA1202_COLUMNS + j]-' '],
                    NOKIA1202_CHAR_WIDTH);
        }
        digitalWrite(_csPin, HIGH);
      } else {
        for (j=0; j < NOKIA1202_COLUMNS; j++) {
          if (_dirtybits[i] & 1 << j) {
            setxy(j * NOKIA1202_CHAR_WIDTH, i);
            _writefont(_framebuffer[i * NOKIA1202_COLUMNS + j]);
            _dirtybits[i] &= ~(1 << j);
          }
        }
      }
    }
  }
}
#endif


/* A .setCursor() UI function so the user can move the cursor around.
 * It has to manage the erasing/rewriting of the cursor too, if applicable.
 */
void Nokia1202::setCursor(uint8_t x, uint8_t y)
{
  if (x >= NOKIA1202_COLUMNS || y >= NOKIA1202_LINES)
    return;

  // Erase the cursor presently at _x,_y before moving it
  if (_useCursor) {
#ifdef NOKIA1202_USE_FRAMEBUFFER
    _framebuffer[_y * NOKIA1202_COLUMNS + _x] = ' ';
    _dirtybits[_y] |= 1 << _x;
#else
    _writefont(' ');
#endif
  }
  _x = x;
  _y = y;

  if (_useCursor) {
#ifdef NOKIA1202_USE_FRAMEBUFFER
    _framebuffer[_y * NOKIA1202_COLUMNS + _x] = 0x80;
    _dirtybits[_y] |= 1 << _x;
    _flush();
#else
    setxy(_x * NOKIA1202_CHAR_WIDTH, _y);
    _writefont(0x80);
#endif
  }

// Note the ifNdef here:
#ifndef NOKIA1202_USE_FRAMEBUFFER
  setxy(_x * NOKIA1202_CHAR_WIDTH, _y);
#endif
}

void Nokia1202::puts(const char *buf)
{
#ifdef NOKIA1202_USE_FRAMEBUFFER
  _doFlush = false;
#endif
  while (*buf != '\0') {
    write((uint8_t)(*buf++));
  }
#ifdef NOKIA1202_USE_FRAMEBUFFER
  _doFlush = true;
  _flush();
#endif
}
