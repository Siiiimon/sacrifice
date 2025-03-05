#ifndef CHASE_BEHAVIOUR_COMPONENT_H
#define CHASE_BEHAVIOUR_COMPONENT_H

#include "defs.h"

#include <ecs.h>

struct ChaseBehaviourComponent {
    Entity target;
};

struct ChaseBehaviourComponent* NewChaseBehaviour(Entity target);
void FreeChaseBehaviour(struct ChaseBehaviourComponent* chase_behaviour);

#endif
