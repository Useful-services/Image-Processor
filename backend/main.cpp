#include <Image.hpp>
#include <iostream>

int main() {

  Image img("ngga.jpg");

  if (img.getChannels() < 3) {
    std::cerr << "Required image with at least 3 channels" << std::endl;
    return 1;
  }

  img.grayScale();
  
  if (!img.save("nigger.jpg")) {
    std::cerr << "Failed to save image!" << std::endl;
    return 1;
  }

  std::cout << "Image saved successfully!" << std::endl;
  return 0;
}