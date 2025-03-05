#include <greatest.h>
#include "ecs/entity_manager.h"
#include "defs.h"
#include <stdlib.h>

TEST test_new_entity_manager(void) {
    struct EntityManager* manager = NewEntityManager();
    ASSERT(manager != NULL);

    ASSERT_EQ(1, manager->next_entity);

    for (Entity i = 0; i < MAX_ENTITIES; i++) {
        ASSERT_FALSE(manager->active_entities[i]);
    }

    FreeEntityManager(manager);
    PASS();
}

TEST test_new_entity(void) {
    struct EntityManager* manager = NewEntityManager();

    Entity entity1 = NewEntity(manager);
    ASSERT_EQ(1, entity1);
    ASSERT_EQ(2, manager->next_entity);
    ASSERT(manager->active_entities[entity1]);

    Entity entity2 = NewEntity(manager);
    ASSERT_EQ(2, entity2);
    ASSERT_EQ(3, manager->next_entity);
    ASSERT(manager->active_entities[entity2]);

    FreeEntityManager(manager);
    PASS();
}

TEST test_get_active_entities(void) {
    struct EntityManager* manager = NewEntityManager();

    Entity entity1 = NewEntity(manager);
    Entity entity2 = NewEntity(manager);
    Entity entity3 = NewEntity(manager);

    RemoveEntity(manager, entity2);
    Entity count = 0;
    Entity* active = GetActiveEntities(manager, &count);
    ASSERT_EQ(2, count);

    if (active[0] == entity1) {
        ASSERT_EQ(entity3, active[1]);
    } else {
        ASSERT_EQ(entity3, active[0]);
        ASSERT_EQ(entity1, active[1]);
    }

    free(active);
    FreeEntityManager(manager);
    PASS();
}

TEST test_remove_entity(void) {
    struct EntityManager* manager = NewEntityManager();

    Entity entity = NewEntity(manager);
    ASSERT(manager->active_entities[entity]);

    RemoveEntity(manager, entity);
    ASSERT_FALSE(manager->active_entities[entity]);
    ASSERT_EQ(0, manager->entities[entity]);

    FreeEntityManager(manager);
    PASS();
}

SUITE(entity_manager_suite) {
    RUN_TEST(test_new_entity_manager);
    RUN_TEST(test_new_entity);
    RUN_TEST(test_get_active_entities);
    RUN_TEST(test_remove_entity);
}
