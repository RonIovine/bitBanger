#include <stdio.h>
#include <string.h>
#include <MemoryMappedHardware.h>
#include <My8BitDevice.h>
#include <My16BitDevice.h>
#include <My32BitDevice.h>

////////////////////////////////////////////////////////////////////////////////
//
// this file is just an example test program that does the bit/register banging
// in a RAM based buffers, to build this program use the following command line
// command:
//
// g++ -I . driver.cc -o driver
//
// then run the executable 'driver' at the command line and follow the prompts
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
  uint8_t buffer8[MAX_MEMORY_MAPPED_SIZE];
  uint16_t buffer16[MAX_MEMORY_MAPPED_SIZE];
  uint32_t buffer32[MAX_MEMORY_MAPPED_SIZE];
  showEndian();
  // test our derived class examples instantiations
  My8BitDevice my8BitDevice;
  My16BitDevice my16BitDevice;
  My32BitDevice my32BitDevice;
  // the following are examples of calling the API, there is no actually memory HW at the
  // addresses in the derived classes, so if these lines are commented out a segment fault
  // will result, these are just for example only
  //my8BitDevice.set(MY_8BIT_REG2, 4);
  //my8BitDevice.set(MY_8BIT_REG0, MY_8BIT_REG0_BITFIELD1, 2);
  //my16BitDevice.set(MY_16BIT_REG2, 4);
  //my16BitDevice.set(MY_16BIT_REG0, MY_16BIT_REG0_BITFIELD1, 2);
  //my32BitDevice.set(MY_32BIT_REG2, 4);
  //my32BitDevice.set(MY_32BIT_REG0, MY_32BIT_REG0_BITFIELD1, 2);
  // instantiate our base classes using RAM based buffers for our address space
  memset(buffer8, 0, sizeof(buffer8));
  memset(buffer16, 0, sizeof(buffer16));
  memset(buffer32, 0, sizeof(buffer32));
  MemoryMappedHardware8 device8("buffer8", buffer8, MAX_MEMORY_MAPPED_SIZE);
  MemoryMappedHardware16 device16("buffer16", buffer16, MAX_MEMORY_MAPPED_SIZE);
  MemoryMappedHardware32 device32("buffer32", buffer32, MAX_MEMORY_MAPPED_SIZE);
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
    device8.set(reg, (uint8_t)value);
    printf("device8 register: %d, value: %d\n", reg, device8.get(reg));

    device16.set(reg, (uint16_t)value);
    printf("device16 register: %d, value: %d\n", reg, device16.get(reg));

    device32.set(reg, (uint32_t)value);
    printf("device32 register: %d, value: %d\n", reg, device32.get(reg));

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
    device8.set(reg, lowOrderBit, highOrderBit, (uint8_t)value);
    printf("device8 register: %d, bitfield: %d-%d, value: %d\n", reg, lowOrderBit, highOrderBit, device8.get(reg, lowOrderBit, highOrderBit));

    device16.set(reg, lowOrderBit, highOrderBit, (uint16_t)value);
    printf("device16 register: %d, bitfield: %d-%d, value: %d\n", reg, lowOrderBit, highOrderBit, device16.get(reg, lowOrderBit, highOrderBit));

    device32.set(reg, lowOrderBit, highOrderBit, (uint32_t)value);
    printf("device32 register: %d, bitfield: %d-%d, value: %d\n", reg, lowOrderBit, highOrderBit, device32.get(reg, lowOrderBit, highOrderBit));

    // test single bit bitfield set/get
    printf("\nenter register: ");
    scanf("%d", &reg);
    printf("enter bit: ");
    scanf("%d", &bit);
    printf("enter value: ");
    scanf("%d", &value);

    // set bit value and read it back for all 3 devices
    device8.set(reg, bit, (uint8_t)value);
    printf("device8 register: %d, bit: %d, value: %d\n", reg, bit, device8.get(reg, bit));

    device16.set(reg, bit, (uint16_t)value);
    printf("device16 register: %d, bit: %d, value: %d\n", reg, bit, device16.get(reg, bit));

    device32.set(reg, bit, (uint32_t)value);
    printf("device32 register: %d, bit: %d, value: %d\n", reg, bit, device32.get(reg, bit));

  }
}
