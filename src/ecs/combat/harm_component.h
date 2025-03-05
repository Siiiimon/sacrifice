#ifndef HARM_COMPONENT_H
#define HARM_COMPONENT_H

#include "defs.h"

#include <ecs.h>

struct HarmComponent {
    int damage;
};

struct HarmComponent* NewHarm(int damage);
void FreeHarm(struct HarmComponent* harm);

#endif //HARM_COMPONENT_H
