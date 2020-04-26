# bitBanger
**A generic, endian agnostic, bit/register banger for memory mapped HW devices**

<a name="overview"></a>
### Overview
This package contians code and examples for creating simple device drivers
for memory mapped HW devices.  It provices for generic, endian agnostic bit
and register banging.  The base class APIs will support 8, 16, and 32 bit
memory mapped devices.  There are 3 example derived classes for each specific
memory mapped HW device, My8BitDevice.h, My16BitDevice.h, and My32BitDevice.h.
There is also a demo program that shows the bit/register banging into a RAM
based memory buffer.

This package also contains a basic BitBanger.h static class that provides bit
banging into passed in values, i.e. not accessed via a base memory mapped
HW address.  This is useful for generic banging of values without providing
the underlying memory access.

<a name="building"></a>
### Building
To build the demo program, from this directory run one of the following build
commands then run the executable 'driver' at the command line and follow the
prompts

Validate all register offsets, bitfield specifications, and value ranges,
and let system determine endianess, this is the recommended compile option,
remove ERROR_CHECKING option for max performance:

`g++ -I . -DERROR_CHECKING driver.cc -o driver`

Force big endian based bit banging, regardless of native system endianess:

`g++ -I . -DFORCE_BIG_ENDIAN driver.cc -o driver`

Force little endian based bit banging, regardless of native system endianess:

`g++ -I . -DFORCE_LITTLE_ENDIAN driver.cc -o driver`

No error checking, let system detect endianess, use for maximum performance:

`$ g++ -I . driver.cc -o driver`
