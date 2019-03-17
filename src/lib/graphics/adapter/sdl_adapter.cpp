#include "sdl_adapter.h"

#include <proto/config.pb.h>
#include <proto/metro.pb.h>

#include <external/imgui/examples/imgui_impl_opengl3.h>
#include <external/imgui/examples/imgui_impl_sdl.h>

#include <optional>
#include <stdexcept>
#include <string>

namespace graphics {
    SDL::SDL()
        : width_(0),
          height_(0),
          window_(nullptr),
          gl_context_(nullptr),
          context_major_version_(3),
          context_minor_version_(3),
          glsl_version_("#version 150") {
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

        ImGui::StyleColorsDark();

        ImGui_ImplSDL2_InitForOpenGL(window_, gl_context_);
        ImGui_ImplOpenGL3_Init(glsl_version_.c_str());
    }

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
        ImGuiIO& io = ImGui::GetIO();
        ImGui::Render();
        SDL_GL_MakeCurrent(window_, gl_context_);
        glViewport(0, 0, static_cast<int>(io.DisplaySize.x), static_cast<int>(io.DisplaySize.y));
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window_);
    }

    std::optional<metro_simulation::Config> SDL::DrawInterface(const metro_simulation::Config& config) {
        std::optional<metro_simulation::Config> result = config;
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window_);
        ImGui::NewFrame();


        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::MenuItem("Quit", "Alt+F4")) {
                result = {};
            }
            ImGui::EndMainMenuBar();
        }

        SDL_Event sdl_event;
        while (SDL_PollEvent(&sdl_event) != 0) {
            switch (sdl_event.type) {
                case SDL_QUIT: {
                    result = {};
                    break;
                }
            }
        }
        return result;
    }

    void SDL::Draw(const metro_simulation::Config& config, const metro_simulation::Metro& metro) {
        ImGui::Begin("Train positions");
        for (const auto& line : metro.lines()) {
            ImGui::Text("Line %lld", line.id());
            for (const auto& section : line.sections()) {
                ImGui::Text("Section %lld", section.id());
                for (const auto& train : section.trains()) {
                    ImGui::Text("Train %lld at %.2lf part of section", train.id(), train.path_completed_part());
                }
            }
        }
        ImGui::End();
    }
}  // namespace graphics
