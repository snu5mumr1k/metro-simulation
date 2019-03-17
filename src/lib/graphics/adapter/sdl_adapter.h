#pragma once

#include <external/gl/gl_core_3_3.h>

#include <SDL.h>
#include <SDL_opengl.h>
#include <external/imgui/imgui.h>

#include <optional>
#include <string>

namespace metro_simulation {
class Metro;
class Config;
}  // namespace metro_simulation

namespace graphics {
class SDL {
public:
    SDL();
    ~SDL();

    std::optional<metro_simulation::Config> DrawInterface(const metro_simulation::Config& config);
    void Draw(const metro_simulation::Config& config, const metro_simulation::Metro& metro);

    void ClearBuffer();
    void SwapBuffers();

private:
    int width_;
    int height_;

    SDL_Window *window_;
    SDL_GLContext gl_context_;

    int context_major_version_;
    int context_minor_version_;

    std::string glsl_version_;
};
}  // namespace graphics
