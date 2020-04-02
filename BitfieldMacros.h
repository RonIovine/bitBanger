#ifndef BITFIELD_MACROS_H
#define BITFIELD_MACROS_H

#include <stdio.h>
#include <arpa/inet.h>

inline bool isBigEndian(void)
{
  static uint8_t endian[2] = {0,1};
  return(*(uint16_t *)endian == 1);
}

// all these macros are designed to only work with the MemoryMappedHardware classes,
// they were just put in a separate file rather than that file for readability purposes

#define MAX_BITFIELD_VALUE(lowOrderBit, highOrderBit) (unsigned)((1<<(highOrderBit-lowOrderBit+1))-1)
#define BITMASK(lowOrderBit, highOrderBit) (MAX_BITFIELD_VALUE(lowOrderBit, highOrderBit)<<lowOrderBit)
#define SET_BITFIELD8(address, lowOrderBit, highOrderBit, value) (address = ((address & ~BITMASK(lowOrderBit, highOrderBit)) | (value << lowOrderBit)))
#define GET_BITFIELD8(address, lowOrderBit, highOrderBit) return(((address & BITMASK(lowOrderBit, highOrderBit)) >> lowOrderBit));
#define SET_BITFIELD16(address, lowOrderBit, highOrderBit, value) (address = ntohs(((htons(address) & ~BITMASK(lowOrderBit, highOrderBit)) | (value << lowOrderBit))))
#define GET_BITFIELD16(address, lowOrderBit, highOrderBit) return(((htons(address) & BITMASK(lowOrderBit, highOrderBit)) >> lowOrderBit));
#define SET_BITFIELD32(address, lowOrderBit, highOrderBit, value) (address = ntohl(((htonl(address) & ~BITMASK(lowOrderBit, highOrderBit)) | (value << lowOrderBit))))
#define GET_BITFIELD32(address, lowOrderBit, highOrderBit) return(((htonl(address) & BITMASK(lowOrderBit, highOrderBit)) >> lowOrderBit));

#define ERROR_CHECKING 1
#ifdef ERROR_CHECKING

// real error checking macros for debug/diagnostics
#define SET_REGISTER_ERROR_CHECKING(register_) \
  if (_address == NULL) \
  { \
    printf("ERROR: device: %s, SET_REGISTER: address is NULL\n", _name); \
    return; \
  } \
  else if (register_ > _size) \
  { \
    printf("ERROR: device: %s, SET_REGISTER: requested register: %d, exceeds memory mapped size: %d\n", _name, register_, _size); \
    return; \
  }

#define GET_REGISTER_ERROR_CHECKING(register_) \
  if (_address == NULL) \
  { \
    printf("ERROR: device: %s, GET_REGISTER: address is NULL\n", _name); \
    return (0); \
  } \
  else if (register_ > _size) \
  { \
    printf("ERROR: device: %s, GET_REGISTER: requested register: %d, exceeds memory mapped size: %d\n", _name, register_, _size); \
    return (0); \
  }

#define SET_BITFIELD_ERROR_CHECKING(register_, lowOrderBit_, highOrderBit_, value_) \
  if (value_ > MAX_BITFIELD_VALUE(lowOrderBit_, highOrderBit_)) \
  { \
    printf("ERROR: device: %s, SET_BITFIELD: value: %d, exceeds max bitfield value: %d\n", _name, value_, MAX_BITFIELD_VALUE(lowOrderBit_, highOrderBit_)); \
    return; \
  } \
  else if (lowOrderBit_ > highOrderBit_) \
  { \
    printf("ERROR: device: %s, SET_BITFIELD: lowOrderBit: %d, is greater than highOrderBit: %d\n", _name, lowOrderBit_, highOrderBit_); \
    return; \
  } \
  else if (highOrderBit_ > (ADDRESS_WIDTH-1)) \
  { \
    printf("ERROR: device: %s, SET_BITFIELD: highOrderBit: %d, exceeds max: %d, for %d-bit device\n", _name, highOrderBit_, (ADDRESS_WIDTH-1), ADDRESS_WIDTH); \
    return; \
  }

#define GET_BITFIELD_ERROR_CHECKING(register_, lowOrderBit_, highOrderBit_) \
  if (lowOrderBit_ > highOrderBit_) \
  { \
    printf("ERROR: device: %s, GET_BITFIELD: lowOrderBit: %d, is greater than highOrderBit: %d\n", _name, lowOrderBit_, highOrderBit_); \
    return (0); \
  } \
  else if (highOrderBit_ > (ADDRESS_WIDTH-1)) \
  { \
    printf("ERROR: device: %s, GET_BITFIELD: highOrderBit: %d, exceeds max: %d, for %d-bit device\n", _name, highOrderBit_, (ADDRESS_WIDTH-1), ADDRESS_WIDTH); \
    return (0); \
  }

#else

// dummy macros when compiling for performance
#define SET_REGISTER_ERROR_CHECKING(register_)
#define GET_REGISTER_ERROR_CHECKING(register_)
#define SET_BITFIELD_ERROR_CHECKING(register_, lowOrderBit_, highOrderBit_, value_)
#define GET_BITFIELD_ERROR_CHECKING(register_, lowOrderBit_, highOrderBit_)

#endif

#define SET_REGISTER_BITFIELD8(register_, lowOrderBit_, highOrderBit_, value_) \
  SET_REGISTER_ERROR_CHECKING(register_) \
  SET_BITFIELD_ERROR_CHECKING(register_, lowOrderBit_, highOrderBit_, value_); \
  SET_BITFIELD8(_address[register_], lowOrderBit_, highOrderBit_, value_);

#define GET_REGISTER_BITFIELD8(register_, lowOrderBit_, highOrderBit_) \
  GET_REGISTER_ERROR_CHECKING(register_) \
  GET_BITFIELD_ERROR_CHECKING(register_, lowOrderBit_, highOrderBit_); \
  GET_BITFIELD8(_address[register_], lowOrderBit_, highOrderBit_);

#define SET_REGISTER_BITFIELD16(register_, lowOrderBit_, highOrderBit_, value_) \
  SET_REGISTER_ERROR_CHECKING(register_) \
  SET_BITFIELD_ERROR_CHECKING(register_, lowOrderBit_, highOrderBit_, value_); \
  SET_BITFIELD16(_address[register_], lowOrderBit_, highOrderBit_, value_);

#define GET_REGISTER_BITFIELD16(register_, lowOrderBit_, highOrderBit_) \
  GET_REGISTER_ERROR_CHECKING(register_) \
  GET_BITFIELD_ERROR_CHECKING(register_, lowOrderBit_, highOrderBit_); \
  GET_BITFIELD16(_address[register_], lowOrderBit_, highOrderBit_);

#define SET_REGISTER_BITFIELD32(register_, lowOrderBit_, highOrderBit_, value_) \
  SET_REGISTER_ERROR_CHECKING(register_) \
  SET_BITFIELD_ERROR_CHECKING(register_, lowOrderBit_, highOrderBit_, value_); \
  SET_BITFIELD32(_address[register_], lowOrderBit_, highOrderBit_, value_);

#define GET_REGISTER_BITFIELD32(register_, lowOrderBit_, highOrderBit_) \
  GET_REGISTER_ERROR_CHECKING(register_) \
  GET_BITFIELD_ERROR_CHECKING(register_, lowOrderBit_, highOrderBit_); \
  GET_BITFIELD32(_address[register_], lowOrderBit_, highOrderBit_);

#define SET_REGISTER_VALUE(register_, value_) \
  SET_REGISTER_ERROR_CHECKING(register_); \
  _address[register_] = value_;

#define GET_REGISTER_VALUE(register_) \
  GET_REGISTER_ERROR_CHECKING(register_); \
  return(_address[register_]);

#endif
