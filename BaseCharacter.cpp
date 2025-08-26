#include "BaseCharacter.h"

#include <raymath.h>

BaseCharacter::BaseCharacter(){
}

void BaseCharacter::undoMovement() {
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec() {
    Vector2 screenPos = getScreenPos();
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * scale,
        height * scale
    };
}


void BaseCharacter::damage(float damage){
    health -= damage;

    if (health <= 0)
        alive = false;
}

void BaseCharacter::tick(float deltaTime) {
    worldPosLastFrame = worldPos;

    if (Vector2Length(velocity) != 0.0) {
        velocity = Vector2Normalize(velocity);
        //set worldPos = worldPos + direction
        worldPos = Vector2Add(worldPos, Vector2Scale(velocity, speed));
        rightLeft = velocity.x < 0 ? -1.f : 1.f;
        texture = run;
    } else {
        texture = idle;
    }

    // update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime) {
        runningTime = 0.0;

        frame++;
        if (frame > maxFrame)
            frame = 0;
    }

    // draw the character
    Vector2 screenPos = getScreenPos();
    Rectangle source{
        frame * width, 0.f, rightLeft * width, height
    };
    Rectangle dest{screenPos.x, screenPos.y, scale * width, scale * height};

    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

