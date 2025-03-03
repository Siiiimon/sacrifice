#include "debug_entities.h"
#include "cimgui_include.h"
#include "debug_entity.h"
#include "tag_component.h"
#include <stdlib.h>

void DrawEntitiesDebugUI(struct GameContext* game_context) {
    igBegin("Entities", NULL, 0);
    if (igCollapsingHeader_TreeNodeFlags("Entity Manager", ImGuiTreeNodeFlags_DefaultOpen)) {
        igText("Next Entity Id: %u", game_context->world->entities->next_entity);
    }

    igSpacing();
    igSeparator();
    igSpacing();

    unsigned int active_entity_count;
    unsigned int* active_entities = GetActiveEntities(game_context->world->entities, &active_entity_count);
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
            for (unsigned int i = 0; i <= active_entity_count; ++i) {
                unsigned int entity = active_entities[i];
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
                    game_context->currently_inspected_entity_id = entity;
                }
                igPopID();
            }
            igEndTable();
        }
    }
    free(active_entities);
    igEnd();

    DrawEntityInspector(game_context);

}
