# bitBanger
A generic, endian agnostic, bit/register banger for memory mapped HW devices

<a name="overview"></a>
### Overview
This package contians code and examples for creating simple device drivers
for memory mapped HW devices.  It provices for generic, and endian agnostic
bit banging and register banging.  The base class APIs will support 8, 16,
and 32 bit memory mapped devices.  There are 3 example derived classes for
each specific memory mapped HW device, My8BitDevice.h, My16BitDevice.h, and
My32BitDevice.h.  There is also a demo program that shows the bit/register
banging into a RAM based memory buffer.

<a name="building"></a>
### Building
To build the demo program, from this directory run:

`$ g++ -I . driver.cc -o driver`

and then run the executable 'driver' at the command line and follow the prompts


