#ifndef FIRE_H
#define FIRE_H

#include <stdint.h>

#define FIRE_FRAME_COUNT 6
#define FIRE_FRAME_WIDTH 5
#define FIRE_FRAME_HEIGHT 5

/* Piskel data for "fire" */

const uint32_t fire_data[6][25] = {
{
0x00000000, 0x00000000, 0x00000000, 0xff0000ff, 0x00000000, 
0x00000000, 0xff0000ff, 0xff00ffff, 0xff0000ff, 0xff00ffff, 
0xff0000ff, 0xff00ffff, 0xff0000ff, 0xff00ffff, 0xff0000ff, 
0xff0000ff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff0000ff, 
0x00000000, 0xff0000ff, 0xff00ffff, 0xff0000ff, 0x00000000
},
{
0x00000000, 0x00000000, 0xff0000ff, 0x00000000, 0x00000000, 
0xff0000ff, 0x00000000, 0xff00ffff, 0xff0000ff, 0x00000000, 
0xff00ffff, 0xff0000ff, 0xff00ffff, 0xff00ffff, 0xff0000ff, 
0xff0000ff, 0xff00ffff, 0xff0000ff, 0xff00ffff, 0xff0000ff, 
0x00000000, 0xff0000ff, 0xff00ffff, 0xff0000ff, 0x00000000
},
{
0x00000000, 0xff0000ff, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0xff0000ff, 0xff00ffff, 0xff0000ff, 0x00000000, 
0xff0000ff, 0xff00ffff, 0xff0000ff, 0xff00ffff, 0xff0000ff, 
0xff0000ff, 0xff00ffff, 0xff00ffff, 0xff0000ff, 0xff00ffff, 
0x00000000, 0xff0000ff, 0xff00ffff, 0xff0000ff, 0x00000000
},
{
0x00000000, 0xff0000ff, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0xff0000ff, 0xff00ffff, 0xff0000ff, 0x00000000, 
0xff0000ff, 0xff00ffff, 0xff0000ff, 0xff00ffff, 0xff0000ff, 
0xff00ffff, 0xff0000ff, 0xff0000ff, 0xff00ffff, 0xff00ffff, 
0x00000000, 0xff0000ff, 0xff00ffff, 0xff0000ff, 0x00000000
},
{
0x00000000, 0x00000000, 0x00000000, 0xff0000ff, 0x00000000, 
0x00000000, 0xff00ffff, 0xff0000ff, 0xff00ffff, 0x00000000, 
0xff0000ff, 0xff0000ff, 0xff00ffff, 0xff0000ff, 0xff0000ff, 
0xff0000ff, 0xff00ffff, 0xff0000ff, 0xff00ffff, 0xff0000ff, 
0x00000000, 0xff0000ff, 0xff00ffff, 0xff0000ff, 0x00000000
},
{
0x00000000, 0x00000000, 0xff0000ff, 0x00000000, 0x00000000, 
0x00000000, 0xff0000ff, 0xff00ffff, 0xff0000ff, 0x00000000, 
0xff0000ff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff0000ff, 
0xff0000ff, 0xff00ffff, 0xff0000ff, 0xff00ffff, 0xff0000ff, 
0x00000000, 0xff0000ff, 0xff00ffff, 0xff0000ff, 0x00000000
}
};

#endif