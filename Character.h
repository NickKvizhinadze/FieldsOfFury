
#include <raylib.h>

class Character {
public:
    Character(int winWidth, int winHeight);
    Vector2 getWorldPos() { return worldPos; }
    void tick(float deltaTime);
    void undoMovement();
    Rectangle getCollisionRec();

private:
    Texture2D texture{LoadTexture("assets/characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("assets/characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("assets/characters/knight_run_spritesheet.png")};

    float width{};
    float height{};

    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};

    // Animation frames
    float runningTime{0};
    int frame{0};
    int maxFrame{6};
    float updateTime{1.f / 12.f};
    float speed{4.f};
    float scale{4.f};
};
