#pragma once

#include <string>
#include <vector>

struct MemoryWriteContext {
  std::vector<unsigned char> data;
};

void memory_write_func(void* context, void* data, int size);

std::string base64_encode(const unsigned char* data, size_t length);
std::string base64_decode(const std::string& encoded_string);
