#ifndef MY_8_BIT_DEVICE_H
#define MY_8_BIT_DEVICE_H

#include <MemoryMappedHardware.h>

////////////////////////////////////////////////////////////////////////////////
//
// example derived class for a specific 8-bit memory mapped device, we
// need to know the memory mapped address and the size of the mapped space
// in 8-bit units
//
////////////////////////////////////////////////////////////////////////////////

class My8BitDevice : public MemoryMappedHardware8
{
  public:

    // setup memory mapped device base address and size in 8-bit units
    enum Device
    {
      ADDRESS = 0x08000000,
      SIZE    = 8   // in 8-bit units
    };

    My8BitDevice() : MemoryMappedHardware8("My8BitDevice", ADDRESS, SIZE){};
    ~My8BitDevice(){};

    // add any device specific functionality member functions here

};

// define all the registers and their offsets from the base address
// and any bitfields those registers might have here

// since these are just #define macros, we can't take advantage of
// the class namespace, so we do it the hard way with a unique prefix,
// we could define the registers in the class as an enum, but since
// the bitfield definitions are just #define pre-processor substitutions,
// we cannot set those up within the class namespace as an enum, so
// keep everything together for clarity and readability

// format for register macro is just <regOffset>
// format for single bit bitfield macro is <bitNum>, note: <lowOrderBit>,<highOrderBit> format would also work provided both values are the same
// format for multi-bit bitfield macro is <lowOrderBit>,<highOrderBit>

// register offsets
#define MY_8BIT_REG0  0
// single bit bitfields for parent register
#define MY_8BIT_REG0_BITFIELD1  0
//#define MY_8BIT_REG0_BITFIELD1  0,0   // alternate format for single bit bitfield
// multi-bit bitfields for parent register
#define MY_8BIT_REG0_BITFIELD2  1,2
#define MY_8BIT_REG0_BITFIELD3  3,5
#define MY_8BIT_REG0_BITFIELD4  6,7

// remaining regisgter offsets
#define MY_8BIT_REG1  1
#define MY_8BIT_REG2  2
#define MY_8BIT_REG3  3
#define MY_8BIT_REG4  4
#define MY_8BIT_REG5  5
#define MY_8BIT_REG6  6
#define MY_8BIT_REG7  7

#endif
