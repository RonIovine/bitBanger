#ifndef MY_16_BIT_DEVICE_H
#define MY_16_BIT_DEVICE_H

#include <MemoryMappedDevice.h>

////////////////////////////////////////////////////////////////////////////////
//
// Example derived class for a specific 16-bit memory mapped device, we
// need to know the memory mapped address and the size of the mapped space
// in 16-bit units
//
////////////////////////////////////////////////////////////////////////////////

class My16BitDevice : public MemoryMappedDevice16
{
  public:

    // setup memory mapped device base address and size in 16-bit units
    enum Device
    {
      ADDRESS = 0x08000000,
      SIZE    = 8   // in 16-bit units
    };

    My16BitDevice() : MemoryMappedDevice16("My16BitDevice", ADDRESS, SIZE){};

    // add any device specific higher functionality member functions here,
    // all the basic bit/register banging is provided by the base class

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
// format for bitfield macro is <lowOrderBit>,<highOrderBit>, use lob=hob for single bit bitfields

// register offsets
#define MY_16BIT_REG0  0
// single bit bitfields for parent register
#define MY_16BIT_REG0_BITFIELD1  0,0
// multi-bit bitfields for parent register
#define MY_16BIT_REG0_BITFIELD2  1,2
#define MY_16BIT_REG0_BITFIELD3  3,5
#define MY_16BIT_REG0_BITFIELD4  6,7

// remaining regisgter offsets
#define MY_16BIT_REG1  1
#define MY_16BIT_REG2  2
#define MY_16BIT_REG3  3
#define MY_16BIT_REG4  4
#define MY_16BIT_REG5  5
#define MY_16BIT_REG6  6
#define MY_16BIT_REG7  7

#endif
