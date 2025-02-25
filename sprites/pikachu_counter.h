#ifndef PIKACHU_COUNTER_H
#define PIKACHU_COUNTER_H

#include <stdint.h>

#define NEW_PISKEL_FRAME_COUNT 26
#define NEW_PISKEL_FRAME_WIDTH 5
#define NEW_PISKEL_FRAME_HEIGHT 5

/* Piskel data for "New Piskel" */

static const uint32_t pikachu[26][25] = {
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xffffffff, 0xffffffff, 0xffffffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xffffffff, 0xffffffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xffffffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff0000ff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff0000ff, 0xff00ffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff0000ff, 0xff00ffff, 0xff00ffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff0000ff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff0000ff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff0000ff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff0000ff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff0000ff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff0000ff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff0000ff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xffffffff, 0xffffffff, 
0xff0000ff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff0000ff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xffffffff, 
0xff0000ff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff0000ff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff0000ff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff0000ff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff0000ff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff0000ff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff0000ff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff0000ff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff
},
{
0xff00ffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff0000ff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff
},
{
0xff00ffff, 0xff00ffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff0000ff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff
},
{
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff0000ff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff
},
{
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff0000ff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff
},
{
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff0000ff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff
}
};

#endif