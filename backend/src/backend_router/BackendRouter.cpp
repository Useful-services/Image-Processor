#include <BackendRouter.hpp>

BackendRouter::BackendRouter():
  server(ZMQServer("tcp://*:" + std::to_string(MQ_PORT))),
  logger() {}

void BackendRouter::start() {
  server.start([&]{
    for(;;) {
      char buffer[MY_BUFFER_SIZE] = {};
      server.receive(buffer, MY_BUFFER_SIZE);
      data = MQData::from_buffer(buffer);
      switch (data.msg_info.action_type) {
        case MQData::MessageInfo::action_type::IMG: {
          process_image_request();
          break;
        }
        case MQData::MessageInfo::action_type::TEXT: {
          process_text_request();
          break;
        }
        case MQData::MessageInfo::action_type::NONE: {
          process_log_request();
          break;
        }
      }

      server.send("");
    }
  });
}

inline void BackendRouter::process_text_request() {
  logger.print_info_ln("Sending text request to DB.");
  // TODO: Add DB query here
}

inline void BackendRouter::process_image_request() {
  logger.print_info_ln("Sending image request to DB.");
  // TODO: Add DB query here
}

inline void BackendRouter::process_log_request() {
  switch (data.msg_info.msg_type) {
    case (MQData::MessageInfo::msg_type::INFO): {
      logger.print_info_ln(data.message_content);
      break;
    }
    case (MQData::MessageInfo::msg_type::WARN): {
      logger.print_warning_ln(data.message_content);
      break;
    }
    case (MQData::MessageInfo::msg_type::ERR): {
      logger.print_error_ln(data.message_content);
      break;
    }
  }
}