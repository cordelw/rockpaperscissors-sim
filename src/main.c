#include "../headers/game.h"
#include <SDL2/SDL_render.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

/*
    TODO: Use command line args for
    defining screen size and simulation
    entity count.
*/

int main() {
    Game gctx;
    Game_Init(&gctx, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Game loop
    while (gctx.running)
    {
        Game_HandleEvents(&gctx);
        Game_Update(&gctx);
        Game_Draw(&gctx);

        Clock_Tick(&gctx.clock);
    }

    // Cleanup
    Game_Stop(&gctx);
}
