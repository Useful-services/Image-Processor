#pragma once

#include <ZMQServer.hpp>
#include <Logger.hpp>
#include <map>
#include <functional>

class BackendRouter {
public:
  BackendRouter();

  void start();

private:

  inline void process_text_request();
  inline void process_image_request();
  inline void process_log_request();

  MQData data;
  ZMQServer server;
  Logger logger;
};