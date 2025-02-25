#ifndef IRON_MAN_COUNTER_H
#define IRON_MAN_COUNTER_H

#include <stdint.h>

#define NEW_PISKEL_FRAME_COUNT 26
#define NEW_PISKEL_FRAME_WIDTH 5
#define NEW_PISKEL_FRAME_HEIGHT 5

/* Piskel data for "New Piskel" */

static const uint32_t iron_man[26][25] = {
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
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xffffffff, 0xffffffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xffffffff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xffffffff, 0xffffffff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xffffffff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xffffff00, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xffffff00, 0xff00ffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xffffff00, 0xff00ffff, 0xffffff00, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xffffff00, 0xff00ffff, 0xffffff00, 0xff00ffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xffffff00, 0xff00ffff, 0xffffff00, 0xff00ffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xffffff00, 0xff00ffff, 0xffffff00, 0xff00ffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff0000ff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xffffff00, 0xff00ffff, 0xffffff00, 0xff00ffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff0000ff, 0xff00ffff, 0xffffffff, 
0xff00ffff, 0xffffff00, 0xff00ffff, 0xffffff00, 0xff00ffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff
},
{
0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff0000ff, 0xff00ffff, 0xff00ffff, 
0xff00ffff, 0xffffff00, 0xff00ffff, 0xffffff00, 0xff00ffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff
},
{
0xff0000ff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff0000ff, 0xff00ffff, 0xff00ffff, 
0xff00ffff, 0xffffff00, 0xff00ffff, 0xffffff00, 0xff00ffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff
},
{
0xff0000ff, 0xff0000ff, 0xffffffff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff0000ff, 0xff00ffff, 0xff00ffff, 
0xff00ffff, 0xffffff00, 0xff00ffff, 0xffffff00, 0xff00ffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff
},
{
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xffffffff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff0000ff, 0xff00ffff, 0xff00ffff, 
0xff00ffff, 0xffffff00, 0xff00ffff, 0xffffff00, 0xff00ffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff
},
{
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xffffffff, 
0xff00ffff, 0xff00ffff, 0xff0000ff, 0xff00ffff, 0xff00ffff, 
0xff00ffff, 0xffffff00, 0xff00ffff, 0xffffff00, 0xff00ffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff
},
{
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 
0xff00ffff, 0xff00ffff, 0xff0000ff, 0xff00ffff, 0xff00ffff, 
0xff00ffff, 0xffffff00, 0xff00ffff, 0xffffff00, 0xff00ffff, 
0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 0xff00ffff, 
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff0000ff
}
};

#endif