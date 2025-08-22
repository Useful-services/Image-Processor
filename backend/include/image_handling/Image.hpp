#pragma once

#include <memory>
#include <cstdint>
#include <string>
#include <stb_image.h>
#include <stb_image_write.h>
#include <vector>
#include <stdexcept>
#include <ImageEncoder.hpp>

class Image {
public:

  Image() : width(0), height(0), channels(0) {}
  Image(const std::string& path);

  Image(Image&& other) noexcept;
  Image& operator=(Image&& other) noexcept;

  uint8_t* pixel(int32_t x, int32_t y);

  bool save(const std::string& filename);
  
  bool is_loaded() const { return data != nullptr && width > 0 && height > 0 && channels > 0; }
  
  // Getters for image dimensions
  int32_t get_width() const { return width; }
  int32_t get_height() const { return height; }
  int32_t get_channels() const { return channels; }

  void gray_scale();
  void from_base64(const std::string& data_base64);
  std::string to_base64();

private:
  int32_t width, height, channels;
  std::unique_ptr<uint8_t[]> data;
};