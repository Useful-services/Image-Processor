#include <ApiListener.hpp>

ApiListener::ApiListener() {
  auto& cors = app.get_middleware<crow::CORSHandler>();

  cors
    .global()
      .headers("X-Custom-Header", "Upgrade-Insecure-Requests")
      .methods("POST"_method, "GET"_method)
    .prefix("/process-text")
      .origin("http://127.0.0.1:5500")
    .prefix("/process-image")
      .origin("http://127.0.0.1:5500")
    .prefix("/nocors")
      .ignore();

  CROW_ROUTE(app, "/")
    ([]() {
      return "Hello world!";
    });

  CROW_ROUTE(app, "/process-text")
    .methods("POST"_method)([](const crow::request& req) {
      CROW_LOG_INFO << "Processing POST request with body " + req.body;
      try {
        auto body = crow::json::load(req.body);
        if (!body || !body.has("text")) {
          crow::response res(400);
          res.body = "{\"error\":\"Invalid JSON: expected {\\\"text\\\": \\\"...\\\"}\"}";
          return res;
        }
        std::string input = body["text"].s();
        std::string reversed_input = input;
        std::reverse(reversed_input.begin(), reversed_input.end());

        crow::json::wvalue json;
        json["original"] = input;
        json["reversed"] = reversed_input;
        json["length"]   = static_cast<int>(input.size());

        crow::response res(json);
        res.set_header("Content-Type", "application/json");

        return res;
      } catch (const std::exception& e) {
        CROW_LOG_ERROR << "Text processing error: " << e.what();
        crow::response res(500);
        res.set_header("Content-Type", "application/json");
        res.body = "{\"error\":\"Internal server error\"}";
        return res;
      }
        
    });


  CROW_ROUTE(app, "/process-image")
    .methods("POST"_method)([](const crow::request& req){
      CROW_LOG_INFO << "Processing image POST request";

      try {

        auto body = crow::json::load(req.body);
        if (!body || !body.has("image")) {
          CROW_LOG_ERROR << "Image processing started without image";
          crow::response res(400);
          res.set_header("Content-Type", "application/json");
          res.body = "{\"error\":\"Invalid JSON: expected {\\\"image\\\": \\\"base64_data...\\\"}\"}";
          return res;
        }

        Image img;
        img.from_base64(body["image"].s());
        img.gray_scale();
        
        auto processedBase64 = img.to_base64();

        crow::json::wvalue json;
        json["width"] = img.get_width();
        json["height"] = img.get_height();
        json["channels"] = img.get_channels();
        json["processed_image"] = processedBase64;

        crow::response res(json);
        res.set_header("Content-Type", "application/json");
        return res;

      } catch(const std::exception& e) {
        CROW_LOG_ERROR << "Image processing error: " << e.what();
        crow::response res(500);
        res.set_header("Content-Type", "application/json");
        res.body = "{\"error\":\"Internal server error during image processing.\"}";
        return res;
      }
    });
}

void ApiListener::run(int port) {
  app.port(port).run();
}

void ApiListener::run_multithreaded(int port) {
  app.port(port).multithreaded().run();
}