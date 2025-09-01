#include "Enemy.h"

#include <raymath.h>
#include <string>

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture, float enemySpeed) {
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    width = texture.width / maxFrame;
    height = texture.height;
    speed = enemySpeed;
}

Vector2 Enemy::getScreenPos() {
    return Vector2Subtract(worldPos, target->getWorldPos());
}

void Enemy::tick(float deltaTime) {
    if (!alive)
        return;

    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if (Vector2Length(velocity) < radius)
        velocity = {};
    BaseCharacter::tick(deltaTime);

    if (CheckCollisionRecs(getCollisionRec(), target->getCollisionRec())) {
        target->damage(damagePerSec * deltaTime);
    }

    // draw the health bar
    std::string healthText = "";
    healthText.append(std::to_string(health > 0 ? health : 0), 0, 5);

    Vector2 textSize = MeasureTextEx(GetFontDefault(), healthText.c_str(), 20, 1);

    Vector2 origin = {textSize.x, textSize.y};
    Vector2 position = {getScreenPos().x + textSize.x, getScreenPos().y + textSize.y /2.f};
    DrawTextPro(GetFontDefault(), healthText.c_str(), position, origin, 0.f, 20, 1, RED);
}

void Enemy::setTarget(Character *character) {
    target = character;
}
