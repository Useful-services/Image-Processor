#include <Image.hpp>
#include <iostream>

int main() {

  Image img("input.jpg");

  if (img.get_channels() < 3) {
    std::cerr << "Required image with at least 3 channels" << std::endl;
    return 1;
  }

  img.gray_scale();
  
  if (!img.save("output.jpg")) {
    std::cerr << "Failed to save image!" << std::endl;
    return 1;
  }

  std::cout << "Image saved successfully!" << std::endl;
  return 0;
}