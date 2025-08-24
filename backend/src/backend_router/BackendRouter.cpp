#include <BackendRouter.hpp>

BackendRouter::BackendRouter():
  server(ZMQServer("tcp://*:" + std::to_string(MQ_PORT))),
  logger() {
  
  
  if (!postgres.connect(connection_info)) {
    on_failed_db_connection();
  } else {
    on_successful_db_connection();
  }
}

// supposed to start in its own thread
inline void BackendRouter::on_failed_db_connection() {
  logger.print_warning_ln("Connection to Postgres with info {" + connection_info + "} has failed.");
  // try to connect again after some time
}

inline void BackendRouter::on_successful_db_connection() {
  logger.print_info_ln("Successfully connected to Postgres");
    std::string create_table = R"(
      CREATE TABLE IF NOT EXISTS request_info (
        id SERIAL PRIMARY KEY,
        type VARCHAR(3),
        elapsed_time INTEGER
      )
    )";

    if (!postgres.execute(create_table)) {
      logger.print_error_ln("Error occured while creating table: " + postgres.getLastError());
    }
}

void BackendRouter::start() {
  server.start([&]{
    for(;;) {
      char buffer[MY_BUFFER_SIZE] = {};
      server.receive(buffer, MY_BUFFER_SIZE);
      server.send_string("");
      data = MQData::from_buffer(buffer);
      switch (data.msg_info.action_type) {
        case MQData::MessageInfo::action_type::IMG: {
          process_image_request(data.msg_info.elapsed_time);
          break;
        }
        case MQData::MessageInfo::action_type::TEXT: {
          process_text_request(data.msg_info.elapsed_time);
          break;
        }
        case MQData::MessageInfo::action_type::NONE: {
          process_log_request();
          break;
        }
      }

    }
  });
}

inline void BackendRouter::process_text_request(uint32_t elapsed_time) {
  if (insert_data({"TXT", std::to_string(elapsed_time)})) {
    logger.print_info_ln("Text request successfuly stored in database.");  
  } else {
    logger.print_error_ln("Failed to send text request to database.");
  }
}

inline void BackendRouter::process_image_request(uint32_t elapsed_time) {
  if (insert_data({"IMG", std::to_string(elapsed_time)})) {
    logger.print_info_ln("Image request successfuly stored in database.");  
  } else {
    logger.print_error_ln("Failed to send image request to database.");
  }
}

inline bool BackendRouter::insert_data(const std::vector<std::string>& data) {
  std::string insert_query = "INSERT INTO request_info (type, elapsed_time) VALUES ($1, $2)";
  return postgres.execute(insert_query, data);
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