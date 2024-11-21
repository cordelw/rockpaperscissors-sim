#include "../headers/sim.h"

Entity Sim_CreateEntity(EntityType entity_type, float pos_x, float pos_y, float width, float height)
{
    Entity ent = {
        entity_type,
        pos_x, pos_y,
        width, height
    };

    return ent;
}

void Sim_DrawEntity(Entity entity, SDL_Renderer *renderer, SDL_Texture *texture)
{
    // Define rect
    SDL_FRect entity_rect = {
        entity.pos_x,
        entity.pos_y,
        entity.width,
        entity.height,
    };

    // Draw
    //SDL_RenderFillRectF(renderer, &entity_rect);
    SDL_RenderCopyF(renderer, texture, NULL, &entity_rect);
}

bool Sim_EntityCollide(Entity entityA, Entity entityB)
{
    float l1 = entityA.pos_x;
    float r1 = entityA.pos_x+entityA.width;
    float l2 = entityB.pos_x;
    float r2 = entityB.pos_x+entityB.width;

    if (l1 < r2 && r1 > l2)
    {
        float t1 = entityA.pos_y;
        float b1 = entityA.pos_y+entityA.height;
        float t2 = entityB.pos_y;
        float b2 = entityB.pos_y+entityB.height;

        if (t1 < b2 && b1 > t2)
            return true;
    }

    return false;
}
