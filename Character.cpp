#include "Character.h"
#include <raymath.h>

Character::Character(int winWidth, int winHeight) {
    width = texture.width / maxFrame;
    height = texture.height;
    screenPos = {
        static_cast<float>(winWidth) / 2.0f - scale * (0.5f * width),
        static_cast<float>(winHeight) / 2.0f - scale * (0.5f * height)
    };
}

void Character::tick(float deltaTime) {
    worldPosLastFrame = worldPos;
    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;

    float rightLeft{1.f};
    if (Vector2Length(direction) != 0.0) {
        direction = Vector2Normalize(direction);
        //set worldPos = worldPos + direction
        worldPos = Vector2Add(worldPos, Vector2Scale(direction, speed));
        rightLeft = direction.x < 0 ? -1.f : 1.f;
        texture = run;
    } else {
        texture = idle;
    }

    runningTime += deltaTime;
    if (runningTime >= updateTime) {
        runningTime = 0.0;

        frame++;
        if (frame > maxFrame)
            frame = 0;
    }

    // draw the character
    Rectangle source{
        frame * width, 0.f, rightLeft * width, height
    };
    Rectangle dest{screenPos.x, screenPos.y, scale * width, scale * height};

    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

void Character::undoMovement() {
    worldPos = worldPosLastFrame;
}

Rectangle Character::getCollisionRec() {
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * scale,
        height * scale
    };
}