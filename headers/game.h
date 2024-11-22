#ifndef GAME_H
#define GAME_H

#define ENTITY_SPEED 0.015

#include "../headers/sim.h"
#include "../headers/clock.h"

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct
{
    bool running;
    int window_width;
    int window_height;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *textures[Sim_ETLast];

    // Sim
    Clock clock;
    float target_delta_time;
    int unit_s;
    int entity_count;
    Entity *entities;
} Game;

void Game_LoadTextures(Game *game);
void Game_DestroyTextures(Game *game);
void Game_InitEntities(Game *game);
void Game_HandleEvents(Game *game);
void Game_Update(Game *game);
void Game_Draw(Game *game);

void Game_Init(Game *game, int window_width, int window_height, int entity_count, int fps_max);
void Game_Stop(Game *game);

#endif
