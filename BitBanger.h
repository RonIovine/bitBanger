#ifndef BIT_BANGER_H
#define BIT_BANGER_H

#include <BitfieldMacros.h>

////////////////////////////////////////////////////////////////////////////////
//
// This module has the generic API for access for basic bit banging from
// passed in values, there is no memory mapping of hardware devices, it
// assumed the values are accessed by other means.  This is a completly
// static class with the accessor functions overloaded based on the data
// with od the values passed into the functions.
//
////////////////////////////////////////////////////////////////////////////////

class BitBanger
{
  public:

    // get/set bitfield for 8-bit values
    static void setBitfield(uint8_t &fullValue_, unsigned lowOrderBit_, unsigned highOrderBit_, uint8_t bitfieldValue_){SET_VALUE_BITFIELD8(fullValue_, lowOrderBit_, highOrderBit_, bitfieldValue_);};
    static uint8_t getBitfield(uint8_t fullValue_, unsigned lowOrderBit_, unsigned highOrderBit_){GET_VALUE_BITFIELD8(fullValue_, lowOrderBit_, highOrderBit_);};

    // get/set bitfield for 16-bit values
    static void setBitfield(uint16_t &fullValue_, unsigned lowOrderBit_, unsigned highOrderBit_, uint16_t bitfieldValue_){SET_VALUE_BITFIELD16(fullValue_, lowOrderBit_, highOrderBit_, bitfieldValue_);};
    static uint16_t getBitfield(uint16_t fullValue_, unsigned lowOrderBit_, unsigned highOrderBit_){GET_VALUE_BITFIELD16(fullValue_, lowOrderBit_, highOrderBit_);};

    // get/set bitfield for 32-bit values
    static void setBitfield(uint32_t &fullValue_, unsigned lowOrderBit_, unsigned highOrderBit_, uint32_t bitfieldValue_){SET_VALUE_BITFIELD32(fullValue_, lowOrderBit_, highOrderBit_, bitfieldValue_);};
    static uint32_t getBitfield(uint32_t fullValue_, unsigned lowOrderBit_, unsigned highOrderBit_){GET_VALUE_BITFIELD32(fullValue_, lowOrderBit_, highOrderBit_);};

};
#endif
