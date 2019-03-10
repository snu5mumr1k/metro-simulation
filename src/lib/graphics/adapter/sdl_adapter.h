#pragma once

#include <external/gl/gl_core_3_3.h>

#include <SDL.h>
#include <SDL_opengl.h>
#include <external/imgui/imgui.h>

#include <string>

namespace graphics {
    class SDL {
    public:
        SDL();
        ~SDL();

        void ClearBuffer();
        void SwapBuffers();
        bool HandleEvents();

    private:
        int width_;
        int height_;

        SDL_Window *window_;
        SDL_GLContext gl_context_;

        int context_major_version_;
        int context_minor_version_;

        ImVec4 clear_color_;

        std::string glsl_version_;
    };
}
