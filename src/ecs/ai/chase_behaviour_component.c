#include "chase_behaviour_component.h"
#include "raylib.h"

#include <ecs.h>
#include <stdlib.h>

struct ChaseBehaviourComponent* NewChaseBehaviour(Entity target) {
    struct ChaseBehaviourComponent* chase_behaviour = malloc(sizeof(struct ChaseBehaviourComponent));
    if (!chase_behaviour) {
        TraceLog(LOG_ERROR, "failed to allocate memory for ChaseBehaviourComponent");
        return NULL;
    }
    chase_behaviour->target = target;

    return chase_behaviour;
}

void FreeChaseBehaviour(struct ChaseBehaviourComponent* chase_behaviour) {
    free(chase_behaviour);
}
