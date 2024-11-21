#include "../headers/clock.h"
#include <SDL2/SDL_timer.h>

void Clock_Init(Clock *clock)
{
    clock->tick_time = SDL_GetPerformanceCounter();
    clock->delta_time = 0.00001;
}

void Clock_Tick(Clock *clock)
{
    clock->last_tick_time = clock->tick_time;
    clock->tick_time = SDL_GetPerformanceCounter();

    clock->delta_time = (float)((clock->tick_time - clock->last_tick_time)*1000 / (float)SDL_GetPerformanceFrequency());
}
