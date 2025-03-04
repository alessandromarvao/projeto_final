#ifndef KIRBY_COUNTER_H
#define KIRBY_COUNTER_H

#include <stdint.h>

#define NEW_PISKEL_FRAME_COUNT 26
#define NEW_PISKEL_FRAME_WIDTH 5
#define NEW_PISKEL_FRAME_HEIGHT 5

/* Piskel data for "New Piskel" */

static const uint32_t kirby[26][25] = {
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
0xff0000ff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff0000ff, 0xff0000ff, 0xffffffff, 0xffffffff, 0xffffffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff0000ff, 0xff0000ff, 0xffff00ff, 0xffffffff, 0xffffffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff0000ff, 0xff0000ff, 0xffff00ff, 0xff0000ff, 0xffffffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff0000ff, 0xff0000ff, 0xffff00ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffff00ff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff0000ff, 0xff0000ff, 0xffff00ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffff00ff, 0xffff00ff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff0000ff, 0xff0000ff, 0xffff00ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffffffff, 0xffffffff, 
0xff0000ff, 0xff0000ff, 0xffff00ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffffffff, 
0xff0000ff, 0xff0000ff, 0xffff00ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 
0xff0000ff, 0xff0000ff, 0xffff00ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffff00ff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 
0xff0000ff, 0xff0000ff, 0xffff00ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffff00ff, 0xffff0000, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 
0xff0000ff, 0xff0000ff, 0xffff00ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffff00ff, 0xffff0000, 0xffff00ff, 0xffffffff, 0xffffffff, 
0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 
0xff0000ff, 0xff0000ff, 0xffff00ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffff00ff, 0xffff0000, 0xffff00ff, 0xffff0000, 0xffffffff, 
0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 
0xff0000ff, 0xff0000ff, 0xffff00ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffff00ff, 0xffff0000, 0xffff00ff, 0xffff0000, 0xffff00ff, 
0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 
0xff0000ff, 0xff0000ff, 0xffff00ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffff00ff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffff00ff, 0xffff0000, 0xffff00ff, 0xffff0000, 0xffff00ff, 
0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 
0xff0000ff, 0xff0000ff, 0xffff00ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffff00ff, 0xffff0000, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffff00ff, 0xffff0000, 0xffff00ff, 0xffff0000, 0xffff00ff, 
0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 
0xff0000ff, 0xff0000ff, 0xffff00ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffff00ff, 0xffff0000, 0xffff00ff, 0xffffffff, 0xffffffff, 
0xffff00ff, 0xffff0000, 0xffff00ff, 0xffff0000, 0xffff00ff, 
0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 
0xff0000ff, 0xff0000ff, 0xffff00ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffff00ff, 0xffff0000, 0xffff00ff, 0xffff0000, 0xffffffff, 
0xffff00ff, 0xffff0000, 0xffff00ff, 0xffff0000, 0xffff00ff, 
0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 
0xff0000ff, 0xff0000ff, 0xffff00ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffff00ff, 0xffff0000, 0xffff00ff, 0xffff0000, 0xffff00ff, 
0xffff00ff, 0xffff0000, 0xffff00ff, 0xffff0000, 0xffff00ff, 
0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 
0xff0000ff, 0xff0000ff, 0xffff00ff, 0xff0000ff, 0xff0000ff
},
{
0xffff00ff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffff00ff, 0xffff0000, 0xffff00ff, 0xffff0000, 0xffff00ff, 
0xffff00ff, 0xffff0000, 0xffff00ff, 0xffff0000, 0xffff00ff, 
0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 
0xff0000ff, 0xff0000ff, 0xffff00ff, 0xff0000ff, 0xff0000ff
},
{
0xffff00ff, 0xffff00ff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffff00ff, 0xffff0000, 0xffff00ff, 0xffff0000, 0xffff00ff, 
0xffff00ff, 0xffff0000, 0xffff00ff, 0xffff0000, 0xffff00ff, 
0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 
0xff0000ff, 0xff0000ff, 0xffff00ff, 0xff0000ff, 0xff0000ff
},
{
0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffffffff, 0xffffffff, 
0xffff00ff, 0xffff0000, 0xffff00ff, 0xffff0000, 0xffff00ff, 
0xffff00ff, 0xffff0000, 0xffff00ff, 0xffff0000, 0xffff00ff, 
0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 
0xff0000ff, 0xff0000ff, 0xffff00ff, 0xff0000ff, 0xff0000ff
},
{
0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffffffff, 
0xffff00ff, 0xffff0000, 0xffff00ff, 0xffff0000, 0xffff00ff, 
0xffff00ff, 0xffff0000, 0xffff00ff, 0xffff0000, 0xffff00ff, 
0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 
0xff0000ff, 0xff0000ff, 0xffff00ff, 0xff0000ff, 0xff0000ff
},
{
0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 
0xffff00ff, 0xffff0000, 0xffff00ff, 0xffff0000, 0xffff00ff, 
0xffff00ff, 0xffff0000, 0xffff00ff, 0xffff0000, 0xffff00ff, 
0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 0xffff00ff, 
0xff0000ff, 0xff0000ff, 0xffff00ff, 0xff0000ff, 0xff0000ff
}
};

#endif