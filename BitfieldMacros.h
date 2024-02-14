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

// big endian, no need to do any byte swapping
#define HTONS(n) (n)
#define NTOHS(n) (n)
#define HTONL(n) (n)
#define NTOHL(n) (n)

// simple endianess checker, were forcing big endian at compile time, hardcode to return true
inline bool isBigEndian(void)
{
  return(true);
}

#elif defined(FORCE_LITTLE_ENDIAN)

// we force a little endian byte interpretation ourselves based on the compiler flag

// little endian, swap bytes to put in bit endian order
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

// simple endianess checker, were forcing little endian at compile time, hardcode to return false
inline bool isBigEndian(void)
{
  return(false);
}

#else

// no compiler flag for byte order, let the system decide

#define HTONS(n) htons(n)
#define NTOHS(n) ntohs(n)

#define HTONL(n) htonl(n)
#define NTOHL(n) ntohl(n)

// simple endianess checker, we auto detect the endianess
inline bool isBigEndian(void)
{
  static uint8_t endian[2] = {0,1};
  return(*(uint16_t *)endian == 1);
}

#endif

// all these macros are designed to only work with the MemoryMappedHardware classes,
// they were just put in a separate file rather than that file for readability purposes

#define MAX_BITFIELD_VALUE(lowOrderBit, highOrderBit) (unsigned)((1<<(highOrderBit-lowOrderBit+1))-1)
#define BITMASK(lowOrderBit, highOrderBit) (MAX_BITFIELD_VALUE(lowOrderBit, highOrderBit)<<lowOrderBit)
#define SET_BITFIELD8(fullValue, lowOrderBit, highOrderBit, bitfieldValue) (fullValue = ((fullValue & ~BITMASK(lowOrderBit, highOrderBit)) | (bitfieldValue << lowOrderBit)))
#define GET_BITFIELD8(fullValue, lowOrderBit, highOrderBit) return(((fullValue & BITMASK(lowOrderBit, highOrderBit)) >> lowOrderBit));
#define SET_BITFIELD16(fullValue, lowOrderBit, highOrderBit, bitfieldValue) (fullValue = NTOHS(((HTONS(fullValue) & ~BITMASK(lowOrderBit, highOrderBit)) | (bitfieldValue << lowOrderBit))))
#define GET_BITFIELD16(fullValue, lowOrderBit, highOrderBit) return(((HTONS(fullValue) & BITMASK(lowOrderBit, highOrderBit)) >> lowOrderBit));
#define SET_BITFIELD32(fullValue, lowOrderBit, highOrderBit, bitfieldValue) (fullValue = NTOHL(((HTONL(fullValue) & ~BITMASK(lowOrderBit, highOrderBit)) | (bitfieldValue << lowOrderBit))))
#define GET_BITFIELD32(fullValue, lowOrderBit, highOrderBit) return(((HTONL(fullValue) & BITMASK(lowOrderBit, highOrderBit)) >> lowOrderBit));

// undefine this for performance
#if defined(ERROR_CHECKING)

// real error checking macros for debug/diagnostics
#define SET_REGISTER_ERROR_CHECKING(register_) \
  if (_address == NULL) \
  { \
    printf("ERROR: device: %s, REGISTER: address is NULL\n", getName()); \
    return; \
  } \
  else if (register_ > _size) \
  { \
    printf("ERROR: device: %s, REGISTER: requested register: %d, exceeds memory mapped size: %d\n", getName(), register_, _size); \
    return; \
  }

#define GET_REGISTER_ERROR_CHECKING(register_) \
  if (_address == NULL) \
  { \
    printf("ERROR: device: %s, REGISTER: address is NULL\n", getName()); \
    return (0); \
  } \
  else if (register_ > _size) \
  { \
    printf("ERROR: device: %s, REGISTER: requested register: %d, exceeds memory mapped size: %d\n", getName(), register_, _size); \
    return (0); \
  }

#define SET_BITFIELD_ERROR_CHECKING(lowOrderBit_, highOrderBit_, numBits_, value_) \
  if (value_ > MAX_BITFIELD_VALUE(lowOrderBit_, highOrderBit_)) \
  { \
    printf("ERROR: BITFIELD: value: %d, exceeds max bitfield value: %d\n", value_, MAX_BITFIELD_VALUE(lowOrderBit_, highOrderBit_)); \
    return; \
  } \
  else if (lowOrderBit_ > highOrderBit_) \
  { \
    printf("ERROR: BITFIELD: lowOrderBit: %d, is greater than highOrderBit: %d\n", lowOrderBit_, highOrderBit_); \
    return; \
  } \
  else if (highOrderBit_ > (numBits_-1)) \
  { \
    printf("ERROR: BITFIELD: highOrderBit: %d, exceeds range: 0-%d, for %d-bit value\n", highOrderBit_, (numBits_-1), numBits_); \
    return; \
  }

#define GET_BITFIELD_ERROR_CHECKING(lowOrderBit_, highOrderBit_, numBits_) \
  if (lowOrderBit_ > highOrderBit_) \
  { \
    printf("ERROR: BITFIELD: lowOrderBit: %d, is greater than highOrderBit: %d\n", lowOrderBit_, highOrderBit_); \
    return (0); \
  } \
  else if (highOrderBit_ > (numBits_-1)) \
  { \
    printf("ERROR: BITFIELD: highOrderBit: %d, exceeds range: 0-%d, for %d-bit value\n", highOrderBit_, (numBits_-1), numBits_); \
    return (0); \
  }

#else

// dummy macros when compiling for performance
#define SET_REGISTER_ERROR_CHECKING(register_)
#define GET_REGISTER_ERROR_CHECKING(register_)
#define SET_BITFIELD_ERROR_CHECKING(lowOrderBit_, highOrderBit_, numBits_, value_)
#define GET_BITFIELD_ERROR_CHECKING(lowOrderBit_, highOrderBit_, numBits_)

#endif

// thes macros are used by the MemoryMappedHardware classes and
// assume a base memory mapped address of a given HW device
#define SET_REGISTER_BITFIELD8(register_, lowOrderBit_, highOrderBit_, value_) \
  SET_REGISTER_ERROR_CHECKING(register_) \
  SET_BITFIELD_ERROR_CHECKING(lowOrderBit_, highOrderBit_, 8, value_) \
  SET_BITFIELD8(_address[register_], lowOrderBit_, highOrderBit_, value_)

#define GET_REGISTER_BITFIELD8(register_, lowOrderBit_, highOrderBit_) \
  GET_REGISTER_ERROR_CHECKING(register_) \
  GET_BITFIELD_ERROR_CHECKING(lowOrderBit_, highOrderBit_, 8) \
  GET_BITFIELD8(_address[register_], lowOrderBit_, highOrderBit_)

#define SET_REGISTER_BITFIELD16(register_, lowOrderBit_, highOrderBit_, value_) \
  SET_REGISTER_ERROR_CHECKING(register_) \
  SET_BITFIELD_ERROR_CHECKING(lowOrderBit_, highOrderBit_, 16, value_) \
  SET_BITFIELD16(_address[register_], lowOrderBit_, highOrderBit_, value_)

#define GET_REGISTER_BITFIELD16(register_, lowOrderBit_, highOrderBit_) \
  GET_REGISTER_ERROR_CHECKING(register_) \
  GET_BITFIELD_ERROR_CHECKING(lowOrderBit_, highOrderBit_, 16) \
  GET_BITFIELD16(_address[register_], lowOrderBit_, highOrderBit_)

#define SET_REGISTER_BITFIELD32(register_, lowOrderBit_, highOrderBit_, value_) \
  SET_REGISTER_ERROR_CHECKING(register_) \
  SET_BITFIELD_ERROR_CHECKING(lowOrderBit_, highOrderBit_, 32, value_) \
  SET_BITFIELD32(_address[register_], lowOrderBit_, highOrderBit_, value_)

#define GET_REGISTER_BITFIELD32(register_, lowOrderBit_, highOrderBit_) \
  GET_REGISTER_ERROR_CHECKING(register_) \
  GET_BITFIELD_ERROR_CHECKING(lowOrderBit_, highOrderBit_, 32) \
  GET_BITFIELD32(_address[register_], lowOrderBit_, highOrderBit_)

#define SET_REGISTER_VALUE(register_, value_) \
  SET_REGISTER_ERROR_CHECKING(register_) \
  _address[register_] = value_;

#define GET_REGISTER_VALUE(register_) \
  GET_REGISTER_ERROR_CHECKING(register_) \
  return(_address[register_]);

// thes macros are used by the BitBanger classes and use the passed in values as-is,
// without assuming a base memory mapped address of a given HW device
#define SET_VALUE_BITFIELD8(fullValue_, lowOrderBit_, highOrderBit_, bitfieldValue_) \
  SET_BITFIELD_ERROR_CHECKING(lowOrderBit_, highOrderBit_, 8, bitfieldValue_) \
  SET_BITFIELD8(fullValue_, lowOrderBit_, highOrderBit_, bitfieldValue_)

#define GET_VALUE_BITFIELD8(fullValue_, lowOrderBit_, highOrderBit_) \
  GET_BITFIELD_ERROR_CHECKING(lowOrderBit_, highOrderBit_, 8) \
  GET_BITFIELD8(fullValue_, lowOrderBit_, highOrderBit_)

#define SET_VALUE_BITFIELD16(fullValue_, lowOrderBit_, highOrderBit_, bitfieldValue_) \
  SET_BITFIELD_ERROR_CHECKING(lowOrderBit_, highOrderBit_, 16, bitfieldValue_) \
  SET_BITFIELD16(fullValue_, lowOrderBit_, highOrderBit_, bitfieldValue_)

#define GET_VALUE_BITFIELD16(fullValue_, lowOrderBit_, highOrderBit_) \
  GET_BITFIELD_ERROR_CHECKING(lowOrderBit_, highOrderBit_, 16) \
  GET_BITFIELD16(fullValue_, lowOrderBit_, highOrderBit_)

#define SET_VALUE_BITFIELD32(fullValue_, lowOrderBit_, highOrderBit_, bitfieldValue_) \
  SET_BITFIELD_ERROR_CHECKING(lowOrderBit_, highOrderBit_, 32, bitfieldValue_) \
  SET_BITFIELD32(fullValue_, lowOrderBit_, highOrderBit_, bitfieldValue_)

#define GET_VALUE_BITFIELD32(fullValue_, lowOrderBit_, highOrderBit_) \
  GET_BITFIELD_ERROR_CHECKING(lowOrderBit_, highOrderBit_, 32) \
  GET_BITFIELD32(fullValue_, lowOrderBit_, highOrderBit_)

#endif
