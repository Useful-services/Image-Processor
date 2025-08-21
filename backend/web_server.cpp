#include <crow.h>
#include <Image.hpp>
#include <iostream>
#include <string>

int main() {
    crow::SimpleApp app;

    // Маршрут для главной страницы
    CROW_ROUTE(app, "/")([]() {
        return crow::response(R"(
<!DOCTYPE html>
<html>
<head>
    <title>Image Processor API</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 40px; }
        .endpoint { background: #f5f5f5; padding: 15px; margin: 10px 0; border-radius: 5px; }
        .method { color: #007acc; font-weight: bold; }
        .url { color: #28a745; font-family: monospace; }
    </style>
</head>
<body>
    <h1>Image Processor API</h1>
    <p>Available endpoints:</p>
    
    <div class="endpoint">
        <span class="method">GET</span> <span class="url">/</span> - Main page
    </div>
    
    <div class="endpoint">
        <span class="method">GET</span> <span class="url">/status</span> - Server status
    </div>
    
    <div class="endpoint">
        <span class="method">POST</span> <span class="url">/process</span> - Image processing
    </div>
    
    <h2>Usage example:</h2>
    <p>Send POST request on /process with image to grayscale.</p>
</body>
</html>
        )");
    });

    // Маршрут для проверки статуса
    CROW_ROUTE(app, "/status")([]() {
        crow::json::wvalue response;
        response["status"] = "running";
        response["timestamp"] = std::time(nullptr);
        response["version"] = "1.0.0";
        return crow::response(response);
    });

    // Маршрут для обработки изображения (заглушка)
    CROW_ROUTE(app, "/process")
        .methods("POST"_method)
        ([](const crow::request& req) {
            crow::json::wvalue response;
            response["message"] = "Image processing endpoint ready";
            response["note"] = "This is a placeholder. Implement actual image processing here.";
            return crow::response(response);    
        });

    std::cout << "Starting web server on http://localhost:8080" << std::endl;
    std::cout << "Press Ctrl+C to stop" << std::endl;
    
    app.port(8080).run();
    
    return 0;
} 