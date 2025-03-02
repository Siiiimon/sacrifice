#include "texture_io.h"
#include "raylib.h"

Texture LoadTextureFromFile(const char* path) {
    Texture texture = LoadTexture(path);
    if (!IsTextureValid(texture)) {
        TraceLog(LOG_ERROR, "Texture %s is not valid", path);
        return texture; // returns error texture
    }
    return texture;
}
