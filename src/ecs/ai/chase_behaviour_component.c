#include "chase_behaviour_component.h"
#include "raylib.h"
#include <stdlib.h>

struct ChaseBehaviourComponentArray* NewChaseBehaviourComponentArray(void) {
    struct ChaseBehaviourComponentArray* chase_behaviours = malloc(sizeof(struct ChaseBehaviourComponentArray));
    if (!chase_behaviours) {
        TraceLog(LOG_ERROR, "failed to allocate memory for ChaseBehaviourComponentArray");
        return NULL;
    }

    for (unsigned int i = 0; i < MAX_ENTITIES; i++) {
        chase_behaviours->components[i] = NULL;
    }

    return chase_behaviours;
}

void FreeChaseBehaviourComponentArray(struct ChaseBehaviourComponentArray* chase_behaviours) {
    if (!chase_behaviours) return;
    for (int i = 0; i < MAX_ENTITIES; i++) {
        FreeChaseBehaviour(chase_behaviours->components[i]);
    }
    free(chase_behaviours);
}

void AddChaseBehaviourToEntity(unsigned int entity, struct ChaseBehaviourComponentArray* chase_behaviours, unsigned int target) {
    if (!chase_behaviours) return;
    if (entity >= MAX_ENTITIES) {
        TraceLog(LOG_ERROR, "entity index out of bounds");
        return;
    }

    struct ChaseBehaviourComponent* component = malloc(sizeof(struct ChaseBehaviourComponent));
    if (!component) {
        TraceLog(LOG_ERROR, "failed to allocate memory for ChaseBehaviourComponent");
        return;
    }
    component->target = target;

    if (chase_behaviours->components[entity] != NULL) {
        TraceLog(LOG_ERROR, "entity %u already has a ChaseBehaviourComponent", entity);
        FreeChaseBehaviour(chase_behaviours->components[entity]);
    }
    chase_behaviours->components[entity] = component;
}

struct ChaseBehaviourComponent* GetChaseBehaviour(struct ChaseBehaviourComponentArray* chase_behaviours, unsigned int entity) {
    if (!chase_behaviours) return NULL;
    if (entity >= MAX_ENTITIES) {
        TraceLog(LOG_ERROR, "entity index out of bounds");
        return NULL;
    }
    return chase_behaviours->components[entity];
}

void FreeChaseBehaviour(struct ChaseBehaviourComponent* chase_behaviour) {
    free(chase_behaviour);
}
