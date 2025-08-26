#ifndef CHARACTER_H
#define CHARACTER_H
#include <raylib.h>
#include "BaseCharacter.h"

class Character : public BaseCharacter {
public:
    Character(int winWidth, int winHeight);

    Rectangle getWeaponCollisionRec() { return weaponCollisionRec; }

    virtual void tick(float deltaTime) override;

    virtual Vector2 getScreenPos() override;

    float getWeaponDamage() const { return weaponDamage; }
    float getHealth() const { return health; }

private:
    int windowWidth;
    int windowHeight;
    Texture2D weapon{LoadTexture("assets/characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
    float weaponDamage{23};
};
#endif
