#include "Character.h"
#include "Enemy.h"
#include "Prop.h"
#include "raylib.h"
#include "raymath.h"


int main() {
    const int windowWidth{1280};
    const int windowHeight{720};

    InitWindow(windowWidth, windowHeight, "Fields of Fury");
    Texture2D map = LoadTexture("assets/nature_tileset/WorldMapLevel1.png");
    Vector2 mapPos{0.0, 0.0};
    float mapScale{4.f};

    Character knight{windowWidth, windowHeight};

    // Props
    float propScale{4.f};
    Prop props[11]{
        Prop{Vector2{380.f * propScale, 129.f * propScale}, LoadTexture("assets/nature_tileset/Log.png")},
        Prop{Vector2{412.f * propScale, 129.f * propScale}, LoadTexture("assets/nature_tileset/Log.png")},
        Prop{Vector2{444.f * propScale, 129.f * propScale}, LoadTexture("assets/nature_tileset/Log.png")},
        Prop{Vector2{640.f * propScale, 290.f * propScale}, LoadTexture("assets/nature_tileset/Rock.png")},
        Prop{Vector2{100.f * propScale, 425.f * propScale}, LoadTexture("assets/nature_tileset/Rock.png")},
        Prop{Vector2{130.f * propScale, 640.f * propScale}, LoadTexture("assets/nature_tileset/Rock.png")},
        Prop{Vector2{420.f * propScale, 620.f * propScale}, LoadTexture("assets/nature_tileset/Rock.png")},
        Prop{Vector2{420.f * propScale, 330.f * propScale}, LoadTexture("assets/nature_tileset/Bush.png")},
        Prop{Vector2{452.f * propScale, 330.f * propScale}, LoadTexture("assets/nature_tileset/Bush.png")},
        Prop{Vector2{360.f * propScale, 390.f * propScale}, LoadTexture("assets/nature_tileset/Bush.png")},
        Prop{Vector2{360.f * propScale, 450.f * propScale}, LoadTexture("assets/nature_tileset/Bush.png")}
    };

    Enemy goblin{
        Vector2{0.f, 0.f},
        LoadTexture("assets/characters/goblin_idle_spritesheet.png"),
        LoadTexture("assets/characters/goblin_run_spritesheet.png")
    };

    goblin .setTarget(&knight);

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        float deltaTime = GetFrameTime();

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        // draw the prop
        for (Prop prop: props) {
            prop.Render(knight.getWorldPos());
        }

        knight.tick(deltaTime);

        // check map bounds
        if (knight.getWorldPos().x < 0 ||
            knight.getWorldPos().y < 0 ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale) {
            knight.undoMovement();
        }

        for (auto prop: props) {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec())) {
                knight.undoMovement();
            }
        }

        goblin.tick(deltaTime);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
