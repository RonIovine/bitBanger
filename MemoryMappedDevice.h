#ifndef MEMORY_MAPPED_DEVICE_H
#define MEMORY_MAPPED_DEVICE_H

#include <sys/mman.h>
#include <fcntl.h>
#include <string>

#include "TraceLog.h"
#include <BitfieldMacros.h>

using namespace std;

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

////////////////////////////////////////////////////////////////////////////////
//
// class definition for 8-bit devices
//
////////////////////////////////////////////////////////////////////////////////
class MemoryMappedDevice8
{
  public:

    // constructor for a RAM based buffer address pointer
    MemoryMappedDevice8(const char *name_, void *address_, unsigned size_) : _address((uint8_t *)address_), _memFd(0), _size(size_), _name(name_), _isMapped(true) {};

    // constructor for a mapped HW address via a hardcoded address value, if device == NULL, it will just assume the
    // address passed in is already mapped and will be used as-is, if device != NULL, it will do an mmap to map the
    // device and set the address accordingly
    MemoryMappedDevice8(const char *name_, unsigned long address_, unsigned size_, const char *device_ = NULL);

    ~MemoryMappedDevice8();

    // get/set whole register values
    void setRegister(unsigned register_, uint8_t value_){SET_REGISTER_VALUE(register_, value_);};
    uint8_t getRegister(unsigned register_){GET_REGISTER_VALUE(register_);};

    // get/set bitfield values
    void setBitfield(unsigned register_, unsigned lowOrderBit_, unsigned highOrderBit_, uint8_t value_){SET_REGISTER_BITFIELD8(register_, lowOrderBit_, highOrderBit_, value_);};
    uint8_t getBitfield(unsigned register_, unsigned lowOrderBit_, unsigned highOrderBit_){GET_REGISTER_BITFIELD8(register_, lowOrderBit_, highOrderBit_);};

    // set an address that is already memory mapped via another method
    void setAddress(void *address_){_address = (uint8_t *)address_;};

    // return memory mapped device, name, and size
    const char *getName(void){return (_name.data());};
    const char *getDevice(void){return (_device.data());};
    unsigned getSize(void){return (_size);};

    // return if memory has been successfully mapped via mmap
    bool isMemoryMapped(void){return (_isMapped);};

  protected:

    // return the memory mapped address at the specified 8-bit offset
    volatile uint8_t *getAddress(unsigned offset_ = 0){return (&_address[offset_]);};

  private:

    volatile uint8_t *_address;
    int _memFd;
    unsigned _size;
    string _name;
    string _device;
    bool _isMapped;

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
inline MemoryMappedDevice8::MemoryMappedDevice8(const char *name_, unsigned long address_, unsigned size_, const char *device_)
{
  _memFd = 0;
  _size = size_;
  _name = name_;
  _device = device_;
  if (device_ != NULL)
  {
    // setup our base memory mapped address
    _memFd = open(device_, O_RDWR | O_SYNC);
    _address = (uint8_t *) mmap(NULL,
                                size_*sizeof(uint8_t),
                                PROT_READ | PROT_WRITE,
                                MAP_SHARED,
                                _memFd,
                                address_);

    if (_address == MAP_FAILED)
    {
      printf("ERROR: %s failed to map address: 0x%x, size: %d, on device: %s\n", getName(), (uint32_t)address_, size_, device_);
      _isMapped = false;
    }
    else
    {
      printf("INFO: %s successfully mapped address: 0x%x, size: %d, on device: %s\n", getName(), (uint32_t)address_, size_, device_);
      _isMapped = true;
    }
  }
  else
  {
    _address = (uint8_t *)address_;
    _isMapped = true;
  }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
inline MemoryMappedDevice8::~MemoryMappedDevice8()
{
  if ((_memFd != 0) && (_address != MAP_FAILED))
  {
    if (munmap((void *)_address, _size) == 0)
    {
      printf("INFO: %s successfully unmapped memory on device: %s\n", getName(), getDevice());
    }
    else
    {
      printf("ERROR: %s failed to unmap memory on device: %s\n", getName(), getDevice());
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
//
// class definition for 16-bit devices
//
////////////////////////////////////////////////////////////////////////////////
class MemoryMappedDevice16
{
  public:

    // constructor for a RAM based buffer address pointer
    MemoryMappedDevice16(const char *name_, void *address_, unsigned size_) : _address((uint16_t *)address_), _memFd(0), _size(size_), _name(name_), _isMapped(true) {};

    // constructor for a mapped HW address via a hardcoded address value, if device == NULL, it will just assume the
    // address passed in is already mapped and will be used as-is, if device != NULL, it will do an mmap to map the
    // device and set the address accordingly
    MemoryMappedDevice16(const char *name_, unsigned long address_, unsigned size_, const char *device_ = NULL);

    ~MemoryMappedDevice16();

    // get/set whole register values
    void setRegister(unsigned register_, uint16_t value_){SET_REGISTER_VALUE(register_, value_);};
    uint16_t getRegister(unsigned register_){GET_REGISTER_VALUE(register_);};

    // get/set bitfield values
    void setBitfield(unsigned register_, unsigned lowOrderBit_, unsigned highOrderBit_, uint16_t value_){SET_REGISTER_BITFIELD16(register_, lowOrderBit_, highOrderBit_, value_);};
    uint16_t getBitfield(unsigned register_, unsigned lowOrderBit_, unsigned highOrderBit_){GET_REGISTER_BITFIELD16(register_, lowOrderBit_, highOrderBit_);};

    // set an address that is already memory mapped via another method
    void setAddress(void *address_){_address = (uint16_t *)address_;};

    // return memory mapped device, name, and size
    const char *getName(void){return (_name.data());};
    const char *getDevice(void){return (_device.data());};
    unsigned getSize(void){return (_size);};

    // return if memory has been successfully mapped via mmap
    bool isMemoryMapped(void){return (_isMapped);};

  protected:

    // return the memory mapped address at the specified 16-bit offset
    volatile uint16_t *getAddress(unsigned offset_ = 0){return (&_address[offset_]);};

  private:

    volatile uint16_t *_address;
    int _memFd;
    unsigned _size;
    string _name;
    string _device;
    bool _isMapped;

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
inline MemoryMappedDevice16::MemoryMappedDevice16(const char *name_, unsigned long address_, unsigned size_, const char *device_)
{
  _memFd = 0;
  _size = size_;
  _name = name_;
  _device = device_;
  if (device_ != NULL)
  {
    // setup our base memory mapped address
    _memFd = open(device_, O_RDWR | O_SYNC);
    _address = (uint16_t *) mmap(NULL,
                                 size_*sizeof(uint16_t),
                                 PROT_READ | PROT_WRITE,
                                 MAP_SHARED,
                                 _memFd,
                                 address_);

    if (_address == MAP_FAILED)
    {
      printf("ERROR: %s failed to map address: 0x%x, size: %d, on device: %s\n", getName(), (uint32_t)address_, size_, device_);
      _isMapped = false;
    }
    else
    {
      printf("INFO: %s successfully mapped address: 0x%x, size: %d, on device: %s\n", getName(), (uint32_t)address_, size_, device_);
      _isMapped = true;
    }
  }
  else
  {
    _address = (uint16_t *)address_;
    _isMapped = true;
  }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
inline MemoryMappedDevice16::~MemoryMappedDevice16()
{
  if ((_memFd != 0) && (_address != MAP_FAILED))
  {
    if (munmap((void *)_address, _size) == 0)
    {
      printf("INFO: %s successfully unmapped memory on device: %s\n", getName(), getDevice());
    }
    else
    {
      printf("ERROR: %s failed to unmap memory on device: %s\n", getName(), getDevice());
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
//
// class definition for 32-bit devices
//
////////////////////////////////////////////////////////////////////////////////
class MemoryMappedDevice32
{
  public:

    // constructor for a RAM based buffer address pointer
    MemoryMappedDevice32(const char *name_, void *address_, unsigned size_) : _address((uint32_t *)address_), _memFd(0), _size(size_), _name(name_), _isMapped(true) {};

    // constructor for a mapped HW address via a hardcoded address value, if device == NULL, it will just assume the
    // address passed in is already mapped and will be used as-is, if device != NULL, it will do an mmap to map the
    // device and set the address accordingly
    MemoryMappedDevice32(const char *name_, unsigned long address_, unsigned size_, const char *device_ = NULL);

    ~MemoryMappedDevice32();

    // get/set whole register values
    void setRegister(unsigned register_, uint32_t value_){SET_REGISTER_VALUE(register_, value_);};
    uint32_t getRegister(unsigned register_){GET_REGISTER_VALUE(register_);};

    // get/set bitfield values
    void setBitfield(unsigned register_, unsigned lowOrderBit_, unsigned highOrderBit_, uint32_t value_){SET_REGISTER_BITFIELD32(register_, lowOrderBit_, highOrderBit_, value_);};
    uint32_t getBitfield(unsigned register_, unsigned lowOrderBit_, unsigned highOrderBit_){GET_REGISTER_BITFIELD32(register_, lowOrderBit_, highOrderBit_);};

    // set an address that is already memory mapped via another method
    void setAddress(void *address_){_address = (uint32_t *)address_;};

    // return memory mapped device, name, and size
    const char *getName(void){return (_name.data());};
    const char *getDevice(void){return (_device.data());};
    unsigned getSize(void){return (_size);};

    // return if memory has been successfully mapped via mmap
    bool isMemoryMapped(void){return (_isMapped);};

  protected:

    // return the memory mapped address at the specified 32-bit offset
    volatile uint32_t *getAddress(unsigned offset_ = 0){return (&_address[offset_]);};

  private:

    volatile uint32_t *_address;
    int _memFd;
    unsigned _size;
    string _name;
    string _device;
    bool _isMapped;

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
inline MemoryMappedDevice32::MemoryMappedDevice32(const char *name_, unsigned long address_, unsigned size_, const char *device_)
{
  _memFd = 0;
  _size = size_;
  _name = name_;
  _device = device_;
  if (device_ != NULL)
  {
    // setup our base memory mapped address
    _memFd = open(device_, O_RDWR | O_SYNC);
    _address = (uint32_t *) mmap(NULL,
                                 size_*sizeof(uint32_t),
                                 PROT_READ | PROT_WRITE,
                                 MAP_SHARED,
                                 _memFd,
                                 address_);

    if (_address == MAP_FAILED)
    {
      printf("ERROR: %s failed to map address: 0x%x, size: %d, on device: %s\n", getName(), (uint32_t)address_, size_, device_);
      _isMapped = false;
    }
    else
    {
      printf("INFO: %s successfully mapped address: 0x%x, size: %d, on device: %s\n", getName(), (uint32_t)address_, size_, device_);
      _isMapped = true;
    }
  }
  else
  {
    _address = (uint32_t *)address_;
    _isMapped = true;
  }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
inline MemoryMappedDevice32::~MemoryMappedDevice32()
{
  if ((_memFd != 0) && (_address != MAP_FAILED))
  {
    if (munmap((void *)_address, _size) == 0)
    {
      printf("INFO: %s successfully unmapped memory on device: %s\n", getName(), getDevice());
    }
    else
    {
      printf("ERROR: %s failed to unmap memory on device: %s\n", getName(), getDevice());
    }
  }
}

#endif
