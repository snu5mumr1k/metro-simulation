#pragma once

#include <array>

#include <lib/graphics/texture/texture.h>

void DrawRectangle(
    const std::array<float, 2> &top_left,
    const std::array<float, 2> &bottom_right,
    const Texture &texture,
    const std::array<float, 2> &texture_top_left,
    const std::array<float, 2> &texture_bottom_right
);
