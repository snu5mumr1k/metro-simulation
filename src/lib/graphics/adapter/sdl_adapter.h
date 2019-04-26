#pragma once

#include <proto/config.pb.h>
#include <proto/metro.pb.h>

#include <external/gl/gl_core_3_3.h>
#include <external/imgui/imgui.h>

#include <string>

#include <SDL.h>
#include <SDL_opengl.h>

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

  proto::Config EditConfig(const proto::Config &config) const;
  void EditMetro(proto::Metro *metro) const;

  Action DrawInterface() const;
  void Draw(const proto::Config &config, const proto::Metro &metro) const;

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
