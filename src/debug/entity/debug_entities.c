#include "debug_entities.h"
#include "../../ecs/tag_component.h"
#include "../cimgui_include.h"
#include "debug_entity.h"

#include "../debug_data.h"
#include <stdlib.h>

void DrawEntitiesDebugUI(struct GameContext* game_context) {
    if (game_context->debug_data->show_entities_window && igBegin("Entities", &game_context->debug_data->show_entities_window, 0)) {
        if (igCollapsingHeader_TreeNodeFlags("Entity Manager", ImGuiTreeNodeFlags_DefaultOpen)) {
            igText("Next Entity Id: %u", game_context->world->ecs->next_entity);
        }

        igSpacing();
        igSeparator();
        igSpacing();

        Entity active_entity_count;
        Entity* active_entities = GetActiveEntities(game_context->world->ecs, &active_entity_count);
        if (active_entities != NULL) {
            ImGuiTableFlags table_flags =
                ImGuiTableFlags_SizingFixedFit |
                ImGuiTableFlags_Resizable |
                ImGuiTableFlags_RowBg |
                ImGuiTableFlags_BordersOuter |
                ImGuiTableFlags_BordersV;
            if (igBeginTable("entities_table", 3, table_flags, (ImVec2){.x = 300.0f, .y = 100.0f}, 0.0f)) {
                igTableSetupColumn("ID", ImGuiTableColumnFlags_None, 5.0f, 0);
                igTableSetupColumn("Tag", ImGuiTableColumnFlags_None, 15.0f, 1);
                igTableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 0.0f, 2);

                igTableHeadersRow();
                for (Entity i = 0; i < active_entity_count; ++i) {
                    Entity entity = active_entities[i];
                    igTableNextRow(0, 0.0f);
                    igTableNextColumn();
                    igText("%u", entity);
                    igTableNextColumn();
                    struct TagComponent* tag = GetTag(game_context->world->tags, entity);
                    if (!tag) {
                        igText("None");
                    } else {
                        igText("%s", GetTagName(tag->tag));
                    }
                    igTableNextColumn();
                    igPushID_Int(i);
                    if (igSmallButton("i")) {
                        game_context->debug_data->currently_inspected_entity_id = entity;
                    }
                    igPopID();
                }
                igEndTable();
            }
        }
        free(active_entities);
        igEnd();
    }

    DrawEntityInspector(game_context);

}
