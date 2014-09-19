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
#include <Print.h>
#include <SPI.h>
#include <stdint.h>


#define NOKIA1202_VERSION 0.5

/* Stellaris support--from Enrf24 */
#if defined(__LM4F120H5QR__)
#include <inc/hw_types.h>
#include <inc/hw_memmap.h>
#include <driverlib/sysctl.h>
#include <driverlib/pin_map.h>
#include <driverlib/gpio.h>
#endif

#ifndef BITF
  #define BIT0                (0x0001)
  #define BIT1                (0x0002)
  #define BIT2                (0x0004)
  #define BIT3                (0x0008)
  #define BIT4                (0x0010)
  #define BIT5                (0x0020)
  #define BIT6                (0x0040)
  #define BIT7                (0x0080)
  #define BIT8                (0x0100)
  #define BIT9                (0x0200)
  #define BITA                (0x0400)
  #define BITB                (0x0800)
  #define BITC                (0x1000)
  #define BITD                (0x2000)
  #define BITE                (0x4000)
  #define BITF                (0x8000)
#endif


/* Nokia 1202 LCD constants */
#define NOKIA1202_LINES 8
#define NOKIA1202_CHAR_WIDTH 6
#define NOKIA1202_COLUMNS 16

/* Use framebuffer? */
#define NOKIA1202_USE_FRAMEBUFFER 1

/* Class definition--inherits from Print so we have .print() functions */
class Nokia1202 : public Print {
  public:
    Nokia1202(uint8_t _csPin);
    void begin(boolean useCursor=true, uint8_t contrast=15, uint8_t tabSpacing = 4);
    void end();

    /* Command I/O -- normally used internally but exposed for tinkering */
    void issuecmd(uint8_t cmd, uint8_t arg, uint8_t argmask);
    void issue_compoundcmd(uint8_t cmd, uint8_t arg, uint8_t argmask);

    /* Data I/O */
    void bulkwrite(const void *buf, uint16_t len);

    /* Screen operations */
    void setCursor(uint8_t x, uint8_t y);
    void clear();

    /* Attribute operations */
    void invert(boolean onoff);
    void powersave(boolean onoff);
    void contrast(uint8_t val);
    void refreshrate(uint8_t val);

    /* Print::write et al */
    virtual size_t write(uint8_t);
    using Print::write;
    void puts(const char *buf);


    uint8_t _x, _y;
    uint8_t _framebuffer[NOKIA1202_LINES * NOKIA1202_COLUMNS];
  private:
    uint8_t _contrast;
    uint8_t _csPin;
    uint8_t _tabSpacing;
    boolean _useCursor;
    boolean _doFlush;  // Optimization flag making puts() a lot faster than print() or println()

    void setxy(uint8_t x, uint8_t y);  // Set X,Y position of LCD cursor; this is bit-level
    void _writefont(uint8_t c);  // Dumb write to the display (resolves char into font_5x7 array)
#ifdef NOKIA1202_USE_FRAMEBUFFER
    void _flush();  // Used in framebuffer mode only, performs mass update of display
    uint16_t _dirtybits[NOKIA1202_LINES];
#endif
};
