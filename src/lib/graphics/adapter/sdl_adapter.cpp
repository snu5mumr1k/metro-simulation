#include "sdl_adapter.h"

#include <proto/config.pb.h>
#include <proto/metro.pb.h>

#include <external/imgui/examples/imgui_impl_opengl3.h>
#include <external/imgui/examples/imgui_impl_sdl.h>

#include <optional>
#include <stdexcept>
#include <string>

namespace {
void GenerateTextMetroRepresentation(const metro_simulation::Metro &metro) {
    ImGui::Begin("Train positions");
    std::unordered_map<int64_t, std::vector<const metro_simulation::Train *>> sectionsTrains;
    std::unordered_map<int64_t, std::vector<const metro_simulation::Train *>> platformsTrains;
    for (const auto &line : metro.lines()) {
        for (const auto &train : line.trains()) {
            switch (train.state()) {
                case metro_simulation::Train::SECTION: {
                    sectionsTrains[train.section_id()].push_back(&train);
                    break;
                }
                case metro_simulation::Train::PLATFORM: {
                    platformsTrains[train.section_id()].push_back(&train);
                    break;
                }
                default:
                    break;
            }
        }
    }
    for (const auto &line : metro.lines()) {
        ImGui::Text("Line %lld", line.id());
        for (const auto &section : line.sections()) {
            ImGui::Text("Section %lld", section.id());
            for (const auto *train : sectionsTrains[section.id()]) {
                ImGui::Text("Train %lld completed %lld/%lld", train->id(), train->section_completed_meters(), section.length());
            }
        }
        for (const auto &station : line.stations()) {
            ImGui::Text("Station %lld", station.id());
            for (const auto &platform : station.platforms()) {
                for (const auto *train : platformsTrains[platform.id()]) {
                    ImGui::Text("Train %lld is at the platform %lld", train->id(), platform.id());
                }
            }
        }
        for (const auto &train : line.trains()) {
            if (train.state() == metro_simulation::Train::IDLE) {
                ImGui::Text("Train %lld is idle at %lld", train.id(), train.platform_id());
            }
        }
    }
    ImGui::End();
}

metro_simulation::Config GenerateConfigMenu(metro_simulation::Config result) {
    return result;
}
}  // namespace

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
        SDL_GL_MakeCurrent(window_, gl_context_);
    }

    void SDL::SwapBuffers() {
        SDL_GL_SwapWindow(window_);
    }

    std::optional<metro_simulation::Config> SDL::DrawInterface(const metro_simulation::Config &config, const metro_simulation::Metro &metro) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window_);
        ImGui::NewFrame();

        std::optional<metro_simulation::Config> result = GenerateConfigMenu(config);

        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::MenuItem("Quit", "Alt+F4")) {
                result = {};
            }
            if (ImGui::MenuItem("Reset to defaults")) {
                result->set_reset_to_defaults(true);
            }
            if (ImGui::MenuItem("Reset to beginning")) {
                result->set_reset_to_beginning(true);
            }
            ImGui::EndMainMenuBar();
        }

        GenerateTextMetroRepresentation(metro);

        SDL_Event sdl_event;
        while (SDL_PollEvent(&sdl_event) != 0) {
            switch (sdl_event.type) {
                case SDL_QUIT: {
                    result = {};
                    break;
                }
            }
        }
        ImGuiIO& io = ImGui::GetIO();
        ImGui::Render();
        glViewport(0, 0, static_cast<int>(io.DisplaySize.x), static_cast<int>(io.DisplaySize.y));
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        return result;
    }

    void SDL::Draw(const metro_simulation::Config& config, const metro_simulation::Metro& metro) {
    }
}  // namespace graphics
