#pragma once

#include <external/gl/gl_core_3_3.h>

#include <SDL.h>
#include <SDL_opengl.h>
#include <external/imgui/imgui.h>
#include <proto/config.pb.h>

#include <optional>
#include <string>

namespace graphics {
    class SDL {
    public:
        SDL();
        ~SDL();

        void ClearBuffer();
        std::optional<metro::Config> DrawInterface(const metro::Config& config);
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
}
