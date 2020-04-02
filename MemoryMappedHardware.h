#ifndef MEMORY_MAPPED_HARDWARE_H
#define MEMORY_MAPPED_HARDWARE_H

#include <BitfieldMacros.h>

////////////////////////////////////////////////////////////////////////////////
//
// This module has the generic API for access  to memory mapped devices for
// 8, 16, and 32 bit memory mapped HW devices, create derived classes for a
// specific memory mapped HW device and add any functionality as needed, see
// the example My8BitDevice.h, My16BitDevice.h, My32BitDevice.h for
//
////////////////////////////////////////////////////////////////////////////////

// for 8-bit devices
class MemoryMappedHardware8
{
  public:

    enum {ADDRESS_WIDTH = sizeof(uint8_t)*8};

    MemoryMappedHardware8(const char *name_, void *address_, unsigned size_) : _address((uint8_t *)address_), _size(size_){strcpy(_name, name_);};
    MemoryMappedHardware8(const char *name_, unsigned long address_, unsigned size_) : _address((uint8_t *)address_), _size(size_){strcpy(_name, name_);};
    ~MemoryMappedHardware8(){};

    // get/set bitfield values
    void set(unsigned register_, unsigned lowOrderBit_, unsigned highOrderBit_, uint8_t value_){SET_REGISTER_BITFIELD8(register_, lowOrderBit_, highOrderBit_, value_);};
    uint8_t get(unsigned register_, unsigned lowOrderBit_, unsigned highOrderBit_){GET_REGISTER_BITFIELD8(register_, lowOrderBit_, highOrderBit_);};

    // get/set single bit values
    void set(unsigned register_, unsigned bit_, uint8_t value_){SET_REGISTER_BITFIELD8(register_, bit_, bit_, value_);};
    uint8_t get(unsigned register_, unsigned bit_){GET_REGISTER_BITFIELD8(register_, bit_, bit_);};

    // get/set whole register values
    void set(unsigned register_, uint8_t value_){SET_REGISTER_VALUE(register_, value_);};
    uint8_t get(unsigned register_){GET_REGISTER_VALUE(register_);};

  private:

    volatile uint8_t *_address;
    unsigned _size;
    char _name[80];

};

// for 16-bit devices
class MemoryMappedHardware16
{
  public:

    enum {ADDRESS_WIDTH = sizeof(uint16_t)*8};

    MemoryMappedHardware16(const char *name_, void *address_, unsigned size_) : _address((uint16_t *)address_), _size(size_){strcpy(_name, name_);};
    MemoryMappedHardware16(const char *name_, unsigned long address_, unsigned size_) : _address((uint16_t *)address_), _size(size_){strcpy(_name, name_);};
    ~MemoryMappedHardware16(){};

    // get/set bitfield values
    void set(unsigned register_, unsigned lowOrderBit_, unsigned highOrderBit_, uint16_t value_){SET_REGISTER_BITFIELD16(register_, lowOrderBit_, highOrderBit_, value_);};
    uint16_t get(unsigned register_, unsigned lowOrderBit_, unsigned highOrderBit_){GET_REGISTER_BITFIELD16(register_, lowOrderBit_, highOrderBit_);};

    // get/set single bit values
    void set(unsigned register_, unsigned bit_, uint16_t value_){SET_REGISTER_BITFIELD16(register_, bit_, bit_, value_);};
    uint16_t get(unsigned register_, unsigned bit_){GET_REGISTER_BITFIELD16(register_, bit_, bit_);};

    // get/set whole register values
    void set(unsigned register_, uint16_t value_){SET_REGISTER_VALUE(register_, value_);};
    uint16_t get(unsigned register_){GET_REGISTER_VALUE(register_);};

  private:

    volatile uint16_t *_address;
    unsigned _size;
    char _name[80];

};

// for 32-bit devices
class MemoryMappedHardware32
{
  public:

    enum {ADDRESS_WIDTH = sizeof(uint32_t)*8};

    MemoryMappedHardware32(const char *name_, void *address_, unsigned size_) : _address((uint32_t *)address_), _size(size_){strcpy(_name, name_);};
    MemoryMappedHardware32(const char *name_, unsigned long address_, unsigned size_) : _address((uint32_t *)address_), _size(size_){strcpy(_name, name_);};
    ~MemoryMappedHardware32(){};

    // get/set bitfield values
    void set(unsigned register_, unsigned lowOrderBit_, unsigned highOrderBit_, uint32_t value_){SET_REGISTER_BITFIELD32(register_, lowOrderBit_, highOrderBit_, value_);};
    uint32_t get(unsigned register_, unsigned lowOrderBit_, unsigned highOrderBit_){GET_REGISTER_BITFIELD32(register_, lowOrderBit_, highOrderBit_);};

    // get/set single bit values
    void set(unsigned register_, unsigned bit_, uint32_t value_){SET_REGISTER_BITFIELD32(register_, bit_, bit_, value_);};
    uint32_t get(unsigned register_, unsigned bit_){GET_REGISTER_BITFIELD32(register_, bit_, bit_);};

    // get/set whole register values
    void set(unsigned register_, uint32_t value_){SET_REGISTER_VALUE(register_, value_);};
    uint32_t get(unsigned register_){GET_REGISTER_VALUE(register_);};

  private:

    volatile uint32_t *_address;
    unsigned _size;
    char _name[80];

};

#endif
