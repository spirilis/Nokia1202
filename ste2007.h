/* STMicroelectronics STE2007 LCD driver chip support
 * Used by the Nokia 1202 LCD display
 */

#ifndef STE2007_H
#define STE2007_H

#include <stdint.h>

// These commands are standard CMD | DATA operations.
// The byte sent is CMD_* OR'd by (DATA & MASK_*) with
//   the 9th bit set to 0 indicating Command.

#define STE2007_CMD_ONOFF 0xAE
#define STE2007_MASK_ONOFF 0x01

#define STE2007_CMD_DPYREV 0xA6
#define STE2007_MASK_DPYREV 0x01 

#define STE2007_CMD_DPYALLPTS 0xA4
#define STE2007_MASK_DPYALLPTS 0x01

#define STE2007_CMD_LINE 0xB0
#define STE2007_MASK_LINE 0x0F

#define STE2007_CMD_COLMSB 0x10
#define STE2007_MASK_COLMSB 0x07

#define STE2007_CMD_COLLSB 0x00
#define STE2007_MASK_COLLSB 0x0F

#define STE2007_CMD_DPYSTARTLINE 0x40
#define STE2007_MASK_DPYSTARTLINE 0x3F

#define STE2007_CMD_SEGMENTDIR 0xA0
#define STE2007_MASK_SEGMENTDIR 0x01

#define STE2007_CMD_COMDIR 0xC0
#define STE2007_MASK_COMDIR 0x08

#define STE2007_CMD_PWRCTL 0x28
#define STE2007_MASK_PWRCTL 0x07

#define STE2007_CMD_VORANGE 0x40
#define STE2007_MASK_VORANGE 0x07

#define STE2007_CMD_ELECTVOL 0x80
#define STE2007_MASK_ELECTVOL 0x1F

#define STE2007_CMD_RESET 0xE2
#define STE2007_MASK_RESET 0x00

#define STE2007_CMD_NOP 0xE3
#define STE2007_MASK_NOP 0x00

/* Compound commands--sent by sending the command first, then value as a 2nd 9-bit byte. */
// VOP is set by submitting CMD_VOP, then the value as the next 9-bit byte.
#define STE2007_CMD_VOP 0xE1
#define STE2007_MASK_VOP 0xFF

// VLCD Slope is similar; submit CMD_VLCDSLOPE, then the value in the next 9-bit byte.
#define STE2007_CMD_VLCDSLOPE 0x38
#define STE2007_MASK_VLCDSLOPE 0x07

// Charge Pump similar.
#define STE2007_CMD_CHARGEPUMP 0x3D
#define STE2007_MASK_CHARGEPUMP 0x03

// Refresh Rate similar.
#define STE2007_CMD_REFRESHRATE 0xEF
#define STE2007_MASK_REFRESHRATE 0x03

// Bias ratio is a normal CMD|DATA operation. (not a compound command)
#define STE2007_CMD_SETBIAS 0x30
#define STE2007_MASK_SETBIAS 0x07

// N-Line inversion is a compound command (send CMD_NLINEINV, then value)
#define STE2007_CMD_NLINEINV 0xAD
#define STE2007_MASK_NLINEINV 0x1F

// Number of Lines is a normal CMD|DATA operation. (not a compound command)
#define STE2007_CMD_NUMLINES 0xD0
#define STE2007_MASK_NUMLINES 0x07

// Image Location is a compound command (send CMD_IMAGELOC, then value)
#define STE2007_CMD_IMAGELOC 0xAC
#define STE2007_MASK_IMAGELOC 0x07

// Icon Mode is a normal CMD|DATA operation. (not a compound command)
#define STE2007_CMD_ICONMODE 0xF8
#define STE2007_MASK_ICONMODE 0x01


#endif
