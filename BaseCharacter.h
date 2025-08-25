#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include <raylib.h>

class BaseCharacter {
public:
    BaseCharacter();

    Vector2 getWorldPos() { return worldPos; }

    void undoMovement();

    Rectangle getCollisionRec();

    virtual void tick(float deltaTime);

    virtual Vector2 getScreenPos() = 0;

    bool getAlive() { return alive; }
    void setAlive(bool isAlive) {
        alive = isAlive;
    }

protected:
    Texture2D texture{LoadTexture("assets/characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("assets/characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("assets/characters/knight_run_spritesheet.png")};

    float width{};
    float height{};

    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    Vector2 velocity{};

    // Animation frames
    float runningTime{0};
    int frame{0};
    int maxFrame{6};
    float updateTime{1.f / 12.f};
    float speed{4.f};
    float scale{4.f};
    float rightLeft{1.f};
    bool alive{true};
};

#endif
