#include <lib/graphics/texture/texture.h>

#include <fstream>

#include <SDL.h>


Texture::Texture(const std::string &filename) : gl_id_(0) {
  SDL_Surface* image = SDL_LoadBMP(filename.c_str());
  if (!image) {
  const std::string error = SDL_GetError();
  throw std::runtime_error("cant load bmp texture from " + filename + " " + error);
  }

  const int width = image->w;
  const int height = image->h;
  uint8_t *buf = reinterpret_cast<uint8_t *>(image->pixels);

  glGenTextures(1, &gl_id_);
  glBindTexture(GL_TEXTURE_2D, gl_id_);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, buf);

  SDL_FreeSurface(image);
}

Texture::~Texture() {
  glDeleteTextures(1, &gl_id_);
}

void Texture::Activate() const {
  glBindTexture(GL_TEXTURE_2D, gl_id_);
}
