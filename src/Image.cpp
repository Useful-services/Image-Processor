#include <Image.hpp>

Image::Image(const std::string& path) {
  uint8_t* raw = stbi_load(path.c_str(), &width, &height, &channels, 0);
  if (raw) {
    data = std::make_unique<uint8_t[]>(width * height * channels);
    std::copy(raw, raw + width * height * channels, data.get());
    stbi_image_free(raw);
  } else {
    // Initialize with default values if loading fails
    width = 0;
    height = 0;
    channels = 0;
  }
  if (!isLoaded()) {
    throw std::runtime_error("Failed to load image " + path);
  }
}

Image::Image(Image&& other) noexcept = default;

Image& Image::operator=(Image&& other) noexcept = default;

uint8_t* Image::pixel(int32_t x, int32_t y) {
  return &data[(y * width + x) * channels];
}

bool Image::save(const std::string& filename) {
  if (!data || width <= 0 || height <= 0 || channels <= 0) {
    return false;
  }
  return stbi_write_jpg(filename.c_str(), width, height, channels, data.get(), 90);
}

void Image::grayScale() {
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      uint8_t* pxl = pixel(x, y);
      uint8_t gray = (pxl[0] + pxl[1] + pxl[2]) / 3;
      pxl[0] = pxl[1] = pxl[2] = gray;
    }
  }
}