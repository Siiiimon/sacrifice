#ifndef DEBUG_DATA_H
#define DEBUG_DATA_H

#include <ecs.h>
#include <stdbool.h>

struct DebugData {
  bool show_main_window;
  bool show_entities_window;
  bool show_entity_inspector_window;
  Entity currently_inspected_entity_id;
};

struct DebugData* NewDebugData(void);
void FreeDebugData(struct DebugData* d);

#endif //DEBUG_DATA_H
