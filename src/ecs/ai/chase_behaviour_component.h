#ifndef CHASE_BEHAVIOUR_COMPONENT_H
#define CHASE_BEHAVIOUR_COMPONENT_H

#include "defs.h"

#include <ecs.h>

struct ChaseBehaviourComponentArray {
    struct ChaseBehaviourComponent* components[MAX_ENTITIES];
};

struct ChaseBehaviourComponent {
    Entity target;
};

struct ChaseBehaviourComponentArray* NewChaseBehaviourComponentArray(void);
void FreeChaseBehaviourComponentArray(struct ChaseBehaviourComponentArray* chase_behaviours);

void AddChaseBehaviourToEntity(Entity entity, struct ChaseBehaviourComponentArray* chase_behaviours, Entity target);
struct ChaseBehaviourComponent* GetChaseBehaviour(struct ChaseBehaviourComponentArray* chase_behaviours, Entity entity);
void FreeChaseBehaviour(struct ChaseBehaviourComponent* chase_behaviour);

#endif
