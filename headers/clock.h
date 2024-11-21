#ifndef CLOCK_H
#define CLOCK_H

#include <SDL2/SDL_timer.h>

typedef struct
{
    Uint64 tick_time;
    Uint64 last_tick_time;
    float delta_time;
} Clock;

void Clock_Init(Clock *clock);
void Clock_Tick(Clock *clock);

#endif
