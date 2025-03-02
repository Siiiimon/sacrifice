#include "debug_entities.h"
#include <stdlib.h>

void DrawEntitiesDebugUI(struct GameContext* game_context) {
    igBegin("Entities", NULL, 0);
    if (igCollapsingHeader_TreeNodeFlags("Entity Manager", ImGuiTreeNodeFlags_DefaultOpen)) {
        igText("Next Entity Id: %u", game_context->world->entities->next_entity);
    }

    igSeparator();

    unsigned int active_entity_count;
    unsigned int* active_entities = GetActiveEntities(game_context->world->entities, &active_entity_count);
    if (active_entities != NULL) {
        for (unsigned int i = 0; i <= active_entity_count; ++i) {
            unsigned int entity = active_entities[i];
            igText("Entity ID: %u", entity);
            struct PositionComponent* position = GetPosition(game_context->world->positions, entity);
            if (position) {
                igText("Position: (%f, %f)", position->x, position->y);
            }
            struct VelocityComponent* velocity = GetVelocity(game_context->world->velocities, entity);
            if (velocity) {
                igText("Velocity: (%f, %f)", velocity->x, velocity->y);
            }
            // struct SpriteComponent* sprite = GetSprite(game_context->world->sprites, entity);
        }
    }
    free(active_entities);
    igEnd();

}
