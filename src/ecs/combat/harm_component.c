#include "harm_component.h"
#include "raylib.h"

#include <stdlib.h>

struct HarmComponent* NewHarm(int damage) {
    struct HarmComponent* harm = malloc(sizeof(struct HarmComponent));
    if (!harm) {
        TraceLog(LOG_ERROR, "failed to allocate memory for HarmComponent");
        return NULL;
    }
    harm->damage = damage;

    return harm;
}

void FreeHarm(struct HarmComponent* harm) {
    free(harm);
}
