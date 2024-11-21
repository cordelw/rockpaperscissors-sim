#include "../headers/game.h"

void Game_Update(Game *game)
{
    /*
        For every entity in the game,
        move towards the closest killable
        entity.
    */

    for (int i = 0; i < ENTITY_COUNT; i++)
    {
        Entity *entity = &game->entities[i];
        Entity *t_entity;

        EntityType target;
        if (entity->type == Sim_Rock)
            target = Sim_Scissor;
        else if (entity->type == Sim_Paper)
            target = Sim_Rock;
        else
            target = Sim_Paper;

        // Find nearest killable entity
        float n_dist = 999999999.9;
        for (int j = 0; j < ENTITY_COUNT; j++)
        {
            // Only check target entities
            if (game->entities[j].type != target)
                continue;

            // Find distance
            float distX = (entity->pos_x - game->entities[j].pos_x);
            float distY = (entity->pos_y - game->entities[j].pos_y);
            float dist = sqrt((distX * distX) + (distY * distY));

            // Run checks
            if (dist < n_dist)
            {
                n_dist = dist;
                t_entity = &game->entities[j];
            }
        }

        // Skip if no target is found
        if (t_entity == NULL)
            continue;

        // Move X position
        if (entity->pos_x < t_entity->pos_x)
            entity->pos_x += ENTITY_SPEED * game->clock.delta_time;
        else if (entity->pos_x > t_entity->pos_x)
            entity->pos_x -= ENTITY_SPEED * game->clock.delta_time;

        // Move Y position
        if (entity->pos_y < t_entity->pos_y)
            entity->pos_y += ENTITY_SPEED * game->clock.delta_time;
        if (entity->pos_y > t_entity->pos_y)
            entity->pos_y -= ENTITY_SPEED * game->clock.delta_time;

        // Check collisions
        if (Sim_EntityCollide(*entity, *t_entity))
            t_entity->type = entity->type;
    }
}
