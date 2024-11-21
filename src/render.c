#include "../headers/game.h"
#include <SDL2/SDL_render.h>

void Game_Draw(Game *game)
{
    // Clear draw buffah
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);

    // Draw entities
    int i;
    for (i = 0; i < ENTITY_COUNT; i++)
    {
        Sim_DrawEntity(game->entities[i], game->renderer, game->textures[game->entities[i].type]);
    }

    // Present renderer
    SDL_RenderPresent(game->renderer);
}
