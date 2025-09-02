#include "Button.h"

#include <string>

Button::Button(const char *btn_texture, const char *btn_sound, float winWidth, float winHeight)
    : windowWidth(winWidth),
      windowHeight(winHeight) {
    texture = LoadTexture(btn_texture);
    fxButton = LoadSound(btn_sound);
}

void Button::render() {
    // Define frame rectangle for drawing
    Rectangle sourceRec = {0, 0, (float) texture.width, (float) texture.height};
    btnBounds = {
        windowWidth / 2.0f - texture.width / 2.0f, windowHeight / 2.0f - texture.height / 2.0f,
        (float) texture.width, (float) texture.height
    };
    DrawTextureRec(texture, sourceRec, (Vector2){btnBounds.x, btnBounds.y}, WHITE);

    std::string text = "Restart";
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text.c_str(), 30, 1);

    Vector2 origin = {textSize.x, textSize.y};
    Vector2 position = {windowWidth / 2.0f + 55.f, windowHeight / 2.0f + 15.f};
    DrawTextPro(GetFontDefault(), text.c_str(), position, origin, 0.f, 30, 1, WHITE);
}
