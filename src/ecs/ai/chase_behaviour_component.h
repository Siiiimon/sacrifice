#ifndef CHASE_BEHAVIOUR_COMPONENT_H
#define CHASE_BEHAVIOUR_COMPONENT_H

#include "defs.h"

struct ChaseBehaviourComponentArray {
    struct ChaseBehaviourComponent* components[MAX_ENTITIES];
};

struct ChaseBehaviourComponent {
    unsigned int target;
};

struct ChaseBehaviourComponentArray* NewChaseBehaviourComponentArray(void);
void FreeChaseBehaviourComponentArray(struct ChaseBehaviourComponentArray* chase_behaviours);

void AddChaseBehaviourToEntity(unsigned int entity, struct ChaseBehaviourComponentArray* chase_behaviours, unsigned int target);
struct ChaseBehaviourComponent* GetChaseBehaviour(struct ChaseBehaviourComponentArray* chase_behaviours, unsigned int entity);
void FreeChaseBehaviour(struct ChaseBehaviourComponent* chase_behaviour);

#endif
