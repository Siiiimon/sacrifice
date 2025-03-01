#ifndef ECS_PHYSICS_POSITION_COMPONENT_H
#define ECS_PHYSICS_POSITION_COMPONENT_H

struct PositionComponentArray {
    struct PositionComponent* components[256];
    unsigned int entities[256];
    unsigned int count;
};

struct PositionComponent {
    float x;
    float y;
};

struct PositionComponentArray* NewPositionComponentArray(void);
void FreePositionComponentArray(struct PositionComponentArray* position_components);

void AddPositionToEntity(unsigned int entity, struct PositionComponentArray* position_components, float x, float y);
struct PositionComponent* GetPosition(struct PositionComponentArray* position_components, unsigned int entity);
void FreePosition(struct PositionComponent* component);

#endif
