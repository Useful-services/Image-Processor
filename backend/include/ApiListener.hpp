#pragma once

#include <crow.h>
#include <crow/middlewares/cors.h>
#include <Image.hpp>
#include <iostream>
#include <string>
#include <algorithm>

class ApiListener {
public:
  ApiListener();

  void run(int port);
  void run_multithreaded(int port);

private:
  crow::App<crow::CORSHandler> app;
};