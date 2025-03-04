//
// Created by Simon Cornelius on 04.03.25.
//

#include "debug_data.h"

#include <stdlib.h>

struct DebugData* NewDebugData(void) {
    struct DebugData* data = malloc(sizeof(struct DebugData));
    data->show_main_window = false;
    data->show_entities_window = true;
    data->show_entity_inspector_window = true;
    data->currently_inspected_entity_id = 0;
    return data;
}
