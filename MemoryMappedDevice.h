#ifndef MEMORY_MAPPED_DEVICE_H
#define MEMORY_MAPPED_DEVICE_H

#include <BitfieldMacros.h>

////////////////////////////////////////////////////////////////////////////////
//
// This module has the generic API for access to memory mapped devices for
// 8, 16, and 32 bit memory mapped HW devices, create derived classes for a
// specific memory mapped HW device and add any functionality as needed, see
// the examples My8BitDevice.h, My16BitDevice.h, and My32BitDevice.h for
// examples of derived classes.
//
// All the basic bit/register banging is provided by these base classes, the
// derived classes should implement any higher level functionality as required
// by the specific device.
//
////////////////////////////////////////////////////////////////////////////////

// for 8-bit devices
class MemoryMappedDevice8
{
  public:

    // constructor for a RAM based buffer address pointer
    MemoryMappedDevice8(const char *name_, void *address_, unsigned size_) : _address((uint8_t *)address_), _size(size_){strcpy(_name, name_);};

    // constructor for a mapped HW address via a hardcoded address value
    MemoryMappedDevice8(const char *name_, unsigned long address_, unsigned size_) : _address((uint8_t *)address_), _size(size_){strcpy(_name, name_);};

    // get/set whole register values
    void setRegister(unsigned register_, uint8_t value_){SET_REGISTER_VALUE(register_, value_);};
    uint8_t getRegister(unsigned register_){GET_REGISTER_VALUE(register_);};

    // get/set bitfield values
    void setBitfield(unsigned register_, unsigned lowOrderBit_, unsigned highOrderBit_, uint8_t value_){SET_REGISTER_BITFIELD8(register_, lowOrderBit_, highOrderBit_, value_);};
    uint8_t getBitfield(unsigned register_, unsigned lowOrderBit_, unsigned highOrderBit_){GET_REGISTER_BITFIELD8(register_, lowOrderBit_, highOrderBit_);};

  private:

    volatile uint8_t *_address;
    unsigned _size;
    char _name[80];

};

// for 16-bit devices
class MemoryMappedDevice16
{
  public:

    // constructor for a RAM based buffer address pointer
    MemoryMappedDevice16(const char *name_, void *address_, unsigned size_) : _address((uint16_t *)address_), _size(size_){strcpy(_name, name_);};

    // constructor for a mapped HW address via a hardcoded address value
    MemoryMappedDevice16(const char *name_, unsigned long address_, unsigned size_) : _address((uint16_t *)address_), _size(size_){strcpy(_name, name_);};

    // get/set whole register values
    void setRegister(unsigned register_, uint16_t value_){SET_REGISTER_VALUE(register_, value_);};
    uint16_t getRegister(unsigned register_){GET_REGISTER_VALUE(register_);};

    // get/set bitfield values
    void setBitfield(unsigned register_, unsigned lowOrderBit_, unsigned highOrderBit_, uint16_t value_){SET_REGISTER_BITFIELD16(register_, lowOrderBit_, highOrderBit_, value_);};
    uint16_t getBitfield(unsigned register_, unsigned lowOrderBit_, unsigned highOrderBit_){GET_REGISTER_BITFIELD16(register_, lowOrderBit_, highOrderBit_);};

  private:

    volatile uint16_t *_address;
    unsigned _size;
    char _name[80];

};

// for 32-bit devices
class MemoryMappedDevice32
{
  public:

    // constructor for a RAM based buffer address pointer
    MemoryMappedDevice32(const char *name_, void *address_, unsigned size_) : _address((uint32_t *)address_), _size(size_){strcpy(_name, name_);};

    // constructor for a mapped HW address via a hardcoded address value
    MemoryMappedDevice32(const char *name_, unsigned long address_, unsigned size_) : _address((uint32_t *)address_), _size(size_){strcpy(_name, name_);};

    // get/set whole register values
    void setRegister(unsigned register_, uint32_t value_){SET_REGISTER_VALUE(register_, value_);};
    uint32_t getRegister(unsigned register_){GET_REGISTER_VALUE(register_);};

    // get/set bitfield values
    void setBitfield(unsigned register_, unsigned lowOrderBit_, unsigned highOrderBit_, uint32_t value_){SET_REGISTER_BITFIELD32(register_, lowOrderBit_, highOrderBit_, value_);};
    uint32_t getBitfield(unsigned register_, unsigned lowOrderBit_, unsigned highOrderBit_){GET_REGISTER_BITFIELD32(register_, lowOrderBit_, highOrderBit_);};

  private:

    volatile uint32_t *_address;
    unsigned _size;
    char _name[80];

};

#endif
