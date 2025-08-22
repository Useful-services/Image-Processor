#include <ApiListener.hpp>

int main() {
  ApiListener obj;
  obj.run_multithreaded(8080);
    
  return 0;
} 