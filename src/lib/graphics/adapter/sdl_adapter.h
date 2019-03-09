#pragma once

#include <external/gl/gl_core_3_3.h>

#include <SDL.h>
#include <SDL_opengl.h>
#include <external/imgui/imgui.h>

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

        bool show_demo_window_ = true;
        bool show_another_window_ = false;
        ImVec4 clear_color_ = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    };
}
