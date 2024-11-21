#ifndef SIM_H
#define SIM_H

#include <SDL2/SDL_render.h>
#include <stdbool.h>

typedef enum
{
    Sim_Rock,
    Sim_Paper,
    Sim_Scissor,
    Sim_ETLast
} EntityType;

typedef struct
{
    EntityType type;

    float pos_x;
    float pos_y;
    float width;
    float height;
} Entity;

Entity Sim_CreateEntity(EntityType entity_type, float pos_x, float pos_y, float width, float height);
void Sim_DrawEntity(Entity entity, SDL_Renderer *renderer, SDL_Texture *texture);
bool Sim_EntityCollide(Entity entityA, Entity entityB);

#endif
