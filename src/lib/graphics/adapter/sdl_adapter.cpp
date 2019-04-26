// XXX: Has to be included first
#include <lib/graphics/adapter/sdl_adapter.h>

#include <external/imgui/examples/imgui_impl_opengl3.h>
#include <external/imgui/examples/imgui_impl_sdl.h>

#include <lib/graphics/interface/config_editor.h>
#include <lib/graphics/interface/metro_editor.h>
#include <lib/graphics/interface/metro_representation.h>
#include <lib/graphics/primitives/rectangle.h>

#include <sstream>
#include <stdexcept>


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

  window_ = SDL_CreateWindow(
  "Metro simulation",
  0, 0,
  width_, height_,
  SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL);
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
    std::stringstream error_message;
    error_message << "SDL created OpenGL context version: ";
    error_message << context_major_version_ << "." << context_minor_version_;
    error_message << " instead of " << received_major_version << "." << received_minor_version;
    throw std::runtime_error(error_message.str());
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGui::StyleColorsLight();

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

void SDL::InitFrame() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(255, 255, 255, 255);
  SDL_GL_MakeCurrent(window_, gl_context_);

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame(window_);
  ImGui::NewFrame();
}

void SDL::FinishFrame() {
  ImGuiIO &io = ImGui::GetIO();
  ImGui::Render();
  glViewport(0, 0, static_cast<int>(io.DisplaySize.x), static_cast<int>(io.DisplaySize.y));
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  SDL_GL_SwapWindow(window_);
}

proto::Config SDL::EditConfig(const proto::Config &config) const {
  return graphics::EditConfig(config);
}

void SDL::EditMetro(proto::Metro *metro) const {
  graphics::EditMetro(metro);
}

SDL::Action SDL::DrawInterface() const {
  Action action = Action::Idle;
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::MenuItem("Quit", "Alt+F4")) {
      action = Action::Quit;
    }
    if (ImGui::MenuItem("Reset to defaults")) {
      action = Action::ResetToDefaults;
    }
    if (ImGui::MenuItem("Save metro")) {
      action = Action::ResetToBeginning;
    }
    ImGui::EndMainMenuBar();
  }

  SDL_Event sdl_event;
  while (SDL_PollEvent(&sdl_event) != 0) {
    ImGui_ImplSDL2_ProcessEvent(&sdl_event);
    switch (sdl_event.type) {
      case SDL_QUIT: {
        action = Action::Quit;
        break;
      }
    }
  }
  return action;
}

void SDL::Draw(const proto::Config &config, const proto::Metro &metro) const {
  graphics::GenerateTextMetroRepresentation(metro);
  static Texture station("textures/station.bmp");
  ImGui::Begin("Timers");
  ImGui::Text("Current timestamp: %f", config.current_simulation_timestamp());
  ImGui::Text("Simulation seconds per tick: %f", config.seconds_per_tick());
  ImGui::Text("Frames per second: %d", config.frames_per_second());
  ImGui::Text(
    "Simulation seconds per real second: %f",
    config.frames_per_second() * config.ticks_per_frame() * config.seconds_per_tick());
  ImGui::End();
}
}  // namespace graphics
