#pragma once

#include <ZMQServer.hpp>
#include <Logger.hpp>
#include <map>
#include <functional>
#include <PSQL.hpp>

// need threadpool here to manage queries while db is offline
class BackendRouter {
public:
  BackendRouter();

  void start();

private:

  inline void process_text_request(uint32_t elapsed_time);
  inline void process_image_request(uint32_t elapsed_time);
  inline void process_log_request();

  inline void on_failed_db_connection();
  inline void on_successful_db_connection();
  inline bool insert_data(const std::vector<std::string>& data);

  const std::string connection_info = "host=localhost port=5432 dbname=postgres user=postgres password=12345";
  MQData data;
  ZMQServer server;
  PSQL postgres;
  Logger logger;
};