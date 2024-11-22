#include "../headers/game.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_surface.h>
#include <stdlib.h>
#include <time.h>

void Game_LoadTextures(Game *game)
{
    SDL_Surface *texture_surface;

    // Rock
    texture_surface = SDL_LoadBMP("res/rock.bmp");
    game->textures[Sim_Rock] = SDL_CreateTextureFromSurface(game->renderer, texture_surface);
    SDL_FreeSurface(texture_surface);

    // Paper
    texture_surface = SDL_LoadBMP("res/paper.bmp");
    game->textures[Sim_Paper] = SDL_CreateTextureFromSurface(game->renderer, texture_surface);
    SDL_FreeSurface(texture_surface);

    // Scissors
    texture_surface = SDL_LoadBMP("res/scissors.bmp");
    game->textures[Sim_Scissor] = SDL_CreateTextureFromSurface(game->renderer, texture_surface);
    SDL_FreeSurface(texture_surface);
}

void Game_DestroyTextures(Game *game)
{
    for (int i = 0; i < Sim_ETLast; i++)
    {
        SDL_DestroyTexture(game->textures[i]);
    }
}

int rangeRand(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

void Game_InitEntities(Game *game)
{
    srand(time(NULL));

    for (int i = 0; i < game->entity_count; i++)
    {
        game->entities[i] = Sim_CreateEntity(
            i % Sim_ETLast,
            (float)rangeRand(0, game->window_width - game->unit_s),
            (float)rangeRand(0, game->window_height - game->unit_s),
            game->unit_s, game->unit_s
        );
    }
}

void Game_Init(Game *game, int window_width, int window_height, int entity_count, int fps_max)
{
    game->window_width = window_width;
    game->window_height = window_height;

    // Initialize SDL2
    //

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Could not initialize SDL2.\n");
        return;
    }

    // Create window
    game->window = SDL_CreateWindow(
        "Rock Paper Scissors",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        window_width, window_height,
        SDL_WINDOW_SHOWN
    );
    if (game->window == NULL)
    {
        printf("SDL2 could not create window. Exiting.\n");
        SDL_Quit();
    }

    // Create renderer
    game->renderer = SDL_CreateRenderer(
        game->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (game->renderer == NULL)
    {
        printf("SDL2 could not create renderer. Exiting.\n");
        SDL_DestroyWindow(game->window);
        SDL_Quit();
    }

    // Load textures
    Game_LoadTextures(game);

    // Simulation stuff
    //

    game->running = true;
    game->unit_s = window_height/32;

    // Simulation framerate
    Clock_Init(&game->clock);
    game->target_delta_time = 0.03333;

    // Allocate memory for entities
    game->entity_count = entity_count;
    game->entities = (Entity *)malloc(game->entity_count * sizeof(Entity));
    Game_InitEntities(game);
}

void Game_Stop(Game *game)
{
    // Clean Resources
    //

    free(game->entities);
    Game_DestroyTextures(game);

    // SDL2 cleanup
    //

    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
}

void Game_HandleEvents(Game *game)
{
    // Window Events
    //

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                game->running = false;
                break;
            case SDL_KEYUP:
                if (event.key.keysym.scancode == SDL_SCANCODE_R)
                    Game_InitEntities(game);
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                    game->running = false;
                break;
            default:
                break;
        }
    }
}
