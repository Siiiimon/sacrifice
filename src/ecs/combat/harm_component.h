#ifndef HARM_COMPONENT_H
#define HARM_COMPONENT_H

#include "defs.h"

#include <ecs.h>

struct HarmComponentArray {
    struct HarmComponent* components[MAX_ENTITIES];
};

struct HarmComponent {
    int damage;
};

struct HarmComponentArray* NewHarmComponentArray(void);
void FreeHarmComponentArray(struct HarmComponentArray* harms);

void AddHarmToEntity(Entity entity, struct HarmComponentArray* harms, int damage);
struct HarmComponent* GetHarm(struct HarmComponentArray* harms, Entity entity);
void FreeHarm(struct HarmComponent* harm);

#endif //HARM_COMPONENT_H
