#ifndef FIELDSOFFURY_BUTTON_H
#define FIELDSOFFURY_BUTTON_H
#include <raylib.h>

class Button {
public:
    Button(const char *btn_texture, const char *btn_sound, float winWidth, float winHeight);

    void render();

    Rectangle getBtnBounds() const { return btnBounds; }

    Sound getFxButton() const { return fxButton; }

private:
    Texture2D texture;
    Sound fxButton;
    Vector2 screenPos;
    float windowWidth{};
    float windowHeight{};
    Rectangle btnBounds = {0.f, 0.f};
};
#endif
