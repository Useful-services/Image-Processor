#include <stdint.h>

// can be scaled by increasing MY_BUFFER_SIZE in CMakeLists.txt
// TODO: add headers to handle data in multiple packages
// TODO: move it to Simple Logger
struct MQData {

  static MQData from_buffer(char buffer[MY_BUFFER_SIZE]) {
    static_assert(sizeof(MQData) <= MY_BUFFER_SIZE, "Require bigger buffer");

    MQData data;
    std::memcpy(&data, buffer, sizeof(MQData));

    return data;
  }

  void to_buffer(char buffer[MY_BUFFER_SIZE]) const {
    std::memset(buffer, 0, MY_BUFFER_SIZE);
    std::memcpy(buffer, this, sizeof(MQData));
  }

  struct MessageInfo {
    enum class msg_type {
      INFO, WARN, ERR
    } msg_type;
    enum class action_type {
      TEXT, IMG, NONE
    } action_type;
    uint32_t elapsed_time;
  } msg_info;
  
  char message_content[MY_BUFFER_SIZE - sizeof(MessageInfo)];
};