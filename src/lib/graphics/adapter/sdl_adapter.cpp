#include "sdl_adapter.h"

#include <stdexcept>
#include <string>

#include <external/imgui/examples/imgui_impl_opengl3.h>
#include <external/imgui/examples/imgui_impl_sdl.h>

namespace graphics {
    SDL::SDL() :
        width_(0),
        height_(0),
        window_(nullptr),
        gl_context_(nullptr),
        context_major_version_(3),
        context_minor_version_(3)
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            throw std::runtime_error("SDL couldn't be initialized! SDL_Error: " + std::string(SDL_GetError()));
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, context_major_version_);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, context_minor_version_);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        window_ = SDL_CreateWindow("Metro simulation", 0, 0, width_, height_, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL);
        if (window_ == nullptr) {
            throw std::runtime_error("Window couldn't be created! SDL_Error: " + std::string(SDL_GetError()));
        }
        SDL_GetWindowSize(window_, &width_, &height_);

        gl_context_ = SDL_GL_CreateContext(window_);
        if (gl_context_ == nullptr) {
            throw std::runtime_error("OpenGL context could not be created! SDL_Error: " + std::string(SDL_GetError()));
        }

        if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
            throw std::runtime_error("OpenGL functions couldn't be loaded");
        }

        int received_major_version;
        int received_minor_version;
        SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &received_major_version);
        SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &received_minor_version);
        if (received_major_version != context_major_version_ || received_minor_version != context_minor_version_) {
            const std::string requested = std::to_string(context_major_version_) + "." + std::to_string(context_minor_version_);
            const std::string received = std::to_string(received_major_version) + "." + std::to_string(received_minor_version);
            throw std::runtime_error("SDL created OpenGL context version " + received + " instead of " + requested);
        }

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);


        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsDark();
    };

    SDL::~SDL() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        SDL_GL_DeleteContext(gl_context_);
        SDL_DestroyWindow(window_);
        SDL_Quit();
    }

    void SDL::ClearBuffer() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void SDL::SwapBuffers() {
        SDL_GL_SwapWindow(window_);
    }

    bool SDL::HandleEvents() {
        SDL_Event sdl_event;
        while (SDL_PollEvent(&sdl_event) != 0) {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame(window_);
            ImGui::NewFrame();

            ImGuiIO& io = ImGui::GetIO();
            // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
            if (show_demo_window_) {
                ImGui::ShowDemoWindow(&show_demo_window_);
            }

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

                ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                ImGui::Checkbox("Demo Window", &show_demo_window_);      // Edit bools storing our window open/close state
                ImGui::Checkbox("Another Window", &show_another_window_);

                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::ColorEdit3("clear color", (float*)&clear_color_); // Edit 3 floats representing a color

                if (ImGui::Button("Button")) {                           // Buttons return true when clicked (most widgets return true when edited/activated) 
                    counter++;
                }
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }

            // 3. Show another simple window.
            if (show_another_window_)
            {
                ImGui::Begin("Another Window", &show_another_window_);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                ImGui::Text("Hello from another window!");
                if (ImGui::Button("Close Me")) {
                    show_another_window_ = false;
                }
                ImGui::End();
            }
            ImGui::Render();
            SDL_GL_MakeCurrent(window_, gl_context_);
            glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
            glClearColor(clear_color_.x, clear_color_.y, clear_color_.z, clear_color_.w);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            SDL_GL_SwapWindow(window_);

            switch (sdl_event.type) {
                case SDL_QUIT:
                    return true;
                default:
                    break;
            }
        }
        return false;
    }
}
