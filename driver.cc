#include <stdio.h>
#include <string.h>
#include <BitBanger.h>
#include <MemoryMappedDevice.h>
#include <My8BitDevice.h>
#include <My16BitDevice.h>
#include <My32BitDevice.h>

////////////////////////////////////////////////////////////////////////////////
//
// this file is just an example test program that does the bit/register banging
// in a RAM based buffers, to build this program use one of the following build
// commands then run the executable 'driver' at the command line and follow
// the prompts
//
// Validate all register offsets, bitfield specifications, and value ranges,
// and let system determine endianess, this is the recommended compile option,
// remove ERROR_CHECKING option for max performance
//
// g++ -I . -DERROR_CHECKING driver.cc -o driver
//
// Force big endian based bit banging, regardless of native system endianess:
//
// g++ -I . -DFORCE_BIG_ENDIAN driver.cc -o driver
//
// Force little endian based bit banging, regardless of native system endianess:
//
// g++ -I . -DFORCE_LITTLE_ENDIAN driver.cc -o driver
//
// no error checking, let system detect endianess, use for maximum performance:
//
// g++ -I . driver.cc -o driver
//
////////////////////////////////////////////////////////////////////////////////

// simple 8-bit memory dumper
void dumpMemory8(uint8_t *address_, unsigned length_)
{
  printf("\n");
  printf("8-bit device raw hex dump:\n");
  printf("\n");
  for (unsigned i = 0; i < length_; i++)
  {
    if ((i%16) == 0)
    {
      if (i > 0)
      {
        printf("\n");
      }
      printf("%04x  ", i);
    }
    printf("%02x ", address_[i]);
  }
  printf("\n");
}

// simple 16-bit memory dumper
void dumpMemory16(uint16_t *address_, unsigned length_)
{
  printf("\n");
  printf("16-bit device raw hex dump:\n");
  printf("\n");
  for (unsigned i = 0; i < length_; i++)
  {
    if ((i%16) == 0)
    {
      if (i > 0)
      {
        printf("\n");
      }
      printf("%04x  ", i);
    }
    printf("%04x ", address_[i]);
  }
  printf("\n");
}

// simple 32-bit memory dumper
void dumpMemory32(uint32_t *address_, unsigned length_)
{
  printf("\n");
  printf("32-bit device raw hex dump:\n");
  printf("\n");
  for (unsigned i = 0; i < length_; i++)
  {
    if ((i%16) == 0)
    {
      if (i > 0)
      {
        printf("\n");
      }
      printf("%04x  ", i);
    }
    printf("%08x ", address_[i]);
  }
  printf("\n");
}


// check the endian
void showEndian(void)
{
  if (isBigEndian())
  {
    printf("\nBig endian detected\n");
  }
  else
  {
    printf("\nLittle endian detected\n");
  }
}

// main
#define MAX_MEMORY_MAPPED_SIZE 32
int main(int argc, char *argv[])
{
  unsigned reg = 0;
  unsigned lowOrderBit = 0;
  unsigned highOrderBit = 0;
  unsigned bit = 0;
  unsigned value = 0;
  uint8_t value8 = 0;
  uint16_t value16 = 0;
  uint32_t value32 = 0;
  uint8_t buffer8[MAX_MEMORY_MAPPED_SIZE] = {0};
  uint16_t buffer16[MAX_MEMORY_MAPPED_SIZE] = {0};
  uint32_t buffer32[MAX_MEMORY_MAPPED_SIZE] = {0};
  printf("value8: 0x%02x, value16: 0x%04x, 0x%08x\n", value8, value16, value32);
  BitBanger::setBitfield(value8, 0, 1, 3);
  BitBanger::setBitfield(value16, 0, 1, 3);
  BitBanger::setBitfield(value32, 0, 1, 3);
  printf("value8: 0x%02x, value16: 0x%04x, value32: 0x%08x\n", value8, value16, value32);
  printf("getValue8: %d, getValue16: %d, getValue32: %d\n", BitBanger::getBitfield(value8, 0, 1),
                                                            BitBanger::getBitfield(value16, 0, 1),
                                                            BitBanger::getBitfield(value32, 0, 1));
  showEndian();
  // test our derived class examples instantiations
  My8BitDevice my8BitDevice;
  My16BitDevice my16BitDevice;
  My32BitDevice my32BitDevice;
  // the following are examples of calling the API, there is no actually memory HW at the
  // addresses in the derived classes, so if these lines are commented out a segment fault
  // will result, these are just for example only
  //my8BitDevice.setRegister(MY_8BIT_REG2, 4);
  //my8BitDevice.setBitfield(MY_8BIT_REG0, MY_8BIT_REG0_BITFIELD1, 2);
  //my16BitDevice.setRegister(MY_16BIT_REG2, 4);
  //my16BitDevice.setBitfield(MY_16BIT_REG0, MY_16BIT_REG0_BITFIELD1, 2);
  //my32BitDevice.setRegister(MY_32BIT_REG2, 4);
  //my32BitDevice.setBitfield(MY_32BIT_REG0, MY_32BIT_REG0_BITFIELD1, 2);
  // instantiate our base classes using RAM based buffers for our address space
  MemoryMappedDevice8 device8("device8", buffer8, MAX_MEMORY_MAPPED_SIZE);
  MemoryMappedDevice16 device16("device16", buffer16, MAX_MEMORY_MAPPED_SIZE);
  MemoryMappedDevice32 device32("device32", buffer32, MAX_MEMORY_MAPPED_SIZE);
  for (;;)
  {

    // do a hex dump of our raw RAM bases memory buffers
    dumpMemory8(buffer8, MAX_MEMORY_MAPPED_SIZE);
    dumpMemory16(buffer16, MAX_MEMORY_MAPPED_SIZE);
    dumpMemory32(buffer32, MAX_MEMORY_MAPPED_SIZE);

    // start with a clean slate for every loop interation
    memset(buffer8, 0, sizeof(buffer8));
    memset(buffer16, 0, sizeof(buffer16));
    memset(buffer32, 0, sizeof(buffer32));

    // test full register set/get
    printf("\nenter register: ");
    scanf("%d", &reg);
    printf("enter value: ");
    scanf("%d", &value);

    // set register value and read it back for all 3 devices
    device8.setRegister(reg, (uint8_t)value);
    printf("device8 register: %d, value: %d\n", reg, device8.getRegister(reg));

    device16.setRegister(reg, (uint16_t)value);
    printf("device16 register: %d, value: %d\n", reg, device16.getRegister(reg));

    device32.setRegister(reg, (uint32_t)value);
    printf("device32 register: %d, value: %d\n", reg, device32.getRegister(reg));

    // test multi-bit bitfield set/get
    printf("\nenter register: ");
    scanf("%d", &reg);
    printf("enter lowOrderBit: ");
    scanf("%d", &lowOrderBit);
    printf("enter highOrderBit: ");
    scanf("%d", &highOrderBit);
    printf("enter value: ");
    scanf("%d", &value);

    // set bitfield value and read it back for all 3 devices
    device8.setBitfield(reg, lowOrderBit, highOrderBit, (uint8_t)value);
    printf("device8 register: %d, bitfield: %d-%d, value: %d\n", reg, lowOrderBit, highOrderBit, device8.getBitfield(reg, lowOrderBit, highOrderBit));

    device16.setBitfield(reg, lowOrderBit, highOrderBit, (uint16_t)value);
    printf("device16 register: %d, bitfield: %d-%d, value: %d\n", reg, lowOrderBit, highOrderBit, device16.getBitfield(reg, lowOrderBit, highOrderBit));

    device32.setBitfield(reg, lowOrderBit, highOrderBit, (uint32_t)value);
    printf("device32 register: %d, bitfield: %d-%d, value: %d\n", reg, lowOrderBit, highOrderBit, device32.getBitfield(reg, lowOrderBit, highOrderBit));

  }
}
