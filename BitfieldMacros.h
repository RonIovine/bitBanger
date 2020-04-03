#ifndef BITFIELD_MACROS_H
#define BITFIELD_MACROS_H

#include <stdio.h>
#include <arpa/inet.h>

////////////////////////////////////////////////////////////////////////////////
//
// This file includes macros that are designed to only work with the
// MemoryMappedHardware classes, they were just put in this separate file
// rather than that file for readability purposes
//
////////////////////////////////////////////////////////////////////////////////

#if defined(FORCE_BIG_ENDIAN)

// we force a big endian byte interpretation ourselves based on the compiler flag

#define HTONS(n) (n)
#define NTOHS(n) (n)
#define HTONL(n) (n)
#define NTOHL(n) (n)

// simple endianess checker
inline bool isBigEndian(void)
{
  return(true);
}

#elif defined(FORCE_LITTLE_ENDIAN)

// we force a little endian byte interpretation ourselves based on the compiler flag

#define HTONS(n) (((((uint16_t)(n) & 0xFF)) << 8) | (((uint16_t)(n) & 0xFF00) >> 8))
#define NTOHS(n) (((((uint16_t)(n) & 0xFF)) << 8) | (((uint16_t)(n) & 0xFF00) >> 8))

#define HTONL(n) (((((uint32_t)(n) & 0xFF)) << 24) | \
                  ((((uint32_t)(n) & 0xFF00)) << 8) | \
                  ((((uint32_t)(n) & 0xFF0000)) >> 8) | \
                  ((((uint32_t)(n) & 0xFF000000)) >> 24))

#define NTOHL(n) (((((uint32_t)(n) & 0xFF)) << 24) | \
                  ((((uint32_t)(n) & 0xFF00)) << 8) | \
                  ((((uint32_t)(n) & 0xFF0000)) >> 8) | \
                  ((((uint32_t)(n) & 0xFF000000)) >> 24))

// simple endianess checker
inline bool isBigEndian(void)
{
  return(false);
}

#else

// simple endianess checker
inline bool isBigEndian(void)
{
  static uint8_t endian[2] = {0,1};
  return(*(uint16_t *)endian == 1);
}

// no compiler flag for byte order, let the system decide

#define HTONS(n) htons(n)
#define NTOHS(n) ntohs(n)

#define HTONL(n) htonl(n)
#define NTOHL(n) ntohl(n)

#endif

// all these macros are designed to only work with the MemoryMappedHardware classes,
// they were just put in a separate file rather than that file for readability purposes

#define MAX_BITFIELD_VALUE(lowOrderBit, highOrderBit) (unsigned)((1<<(highOrderBit-lowOrderBit+1))-1)
#define BITMASK(lowOrderBit, highOrderBit) (MAX_BITFIELD_VALUE(lowOrderBit, highOrderBit)<<lowOrderBit)
#define SET_BITFIELD8(address, lowOrderBit, highOrderBit, value) (address = ((address & ~BITMASK(lowOrderBit, highOrderBit)) | (value << lowOrderBit)))
#define GET_BITFIELD8(address, lowOrderBit, highOrderBit) return(((address & BITMASK(lowOrderBit, highOrderBit)) >> lowOrderBit));
#define SET_BITFIELD16(address, lowOrderBit, highOrderBit, value) (address = NTOHS(((HTONS(address) & ~BITMASK(lowOrderBit, highOrderBit)) | (value << lowOrderBit))))
#define GET_BITFIELD16(address, lowOrderBit, highOrderBit) return(((HTONS(address) & BITMASK(lowOrderBit, highOrderBit)) >> lowOrderBit));
#define SET_BITFIELD32(address, lowOrderBit, highOrderBit, value) (address = NTOHL(((HTONL(address) & ~BITMASK(lowOrderBit, highOrderBit)) | (value << lowOrderBit))))
#define GET_BITFIELD32(address, lowOrderBit, highOrderBit) return(((HTONL(address) & BITMASK(lowOrderBit, highOrderBit)) >> lowOrderBit));

// undefine this for performance
#if defined(ERROR_CHECKING)

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
