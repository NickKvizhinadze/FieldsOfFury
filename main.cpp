#include "Character.h"
#include "Enemy.h"
#include "Prop.h"
#include "raylib.h"
#include "raymath.h"
#include <string>
#include <vector>

const int windowWidth{1280};
const int windowHeight{720};
Texture2D map{};
Vector2 mapPos{};
float mapScale{4.f};
std::vector<Prop> props{};
std::vector<Enemy*> enemies = {};

void setupLevelOne() {
    map = LoadTexture("assets/nature_tileset/WorldMapLevel1.png");
    //Props
    float propScale{4.f};
    props = {
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


    enemies = {
        new Enemy{
            Vector2{800.f, 300.f},
            LoadTexture("assets/characters/goblin_idle_spritesheet.png"),
            LoadTexture("assets/characters/goblin_run_spritesheet.png")
        },
        new Enemy{
            Vector2{500.f, 700.f},
            LoadTexture("assets/characters/slime_idle_spritesheet.png"),
            LoadTexture("assets/characters/slime_run_spritesheet.png")
        }
    };
}

void cleanUpLevel() {
    // At the end of main(), before return:
    for (Enemy* enemy : enemies) {
        delete enemy;
    }
}


int main() {
    InitWindow(windowWidth, windowHeight, "Fields of Fury");

    setupLevelOne();
Character knight{windowWidth, windowHeight};

    for (Enemy *enemy: enemies) {
        enemy->setTarget(&knight);
    }


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

        if (!knight.getAlive()) {
            DrawText("GAME OVER !!!", (windowWidth / 2) - 20, (windowHeight / 2) - 20.f, 40, RED);
            EndDrawing();
            continue;
        }

        std::string health = "Health: ";
        health.append(std::to_string(knight.getHealth() > 0 ? knight.getHealth() : 0), 0, 5);
        DrawText(health.c_str(), windowWidth - 270.f, 45.f, 40, RED);

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

        for (Enemy *enemy: enemies) {
            enemy->tick(deltaTime);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionRecs(
                    enemy->getCollisionRec(), knight.getWeaponCollisionRec())) {
                enemy->damage(knight.getWeaponDamage());
            }
        }

        EndDrawing();
    }

    //TODO: use it when level changed too
    cleanUpLevel();

    CloseWindow();

    return 0;
}
