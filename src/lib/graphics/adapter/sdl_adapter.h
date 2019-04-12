#pragma once

#include <external/gl/gl_core_3_3.h>

#include <string>

#include <SDL.h>
#include <SDL_opengl.h>

#include <external/imgui/imgui.h>

#include <proto/config.pb.h>
#include <proto/metro.pb.h>

namespace graphics {
class SDL {
public:
    enum class Action {
        Quit,
        ResetToDefaults,
        ResetToBeginning,
        Idle
    };

    SDL();
    ~SDL();

    metro_simulation::Config EditConfig(const metro_simulation::Config& config) const;
    metro_simulation::Metro EditMetro(const metro_simulation::Metro& metro) const;

    Action DrawInterface() const;
    void Draw(const metro_simulation::Config& config, const metro_simulation::Metro& metro) const ;

    void InitFrame();
    void FinishFrame();

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
