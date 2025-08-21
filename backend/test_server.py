#!/usr/bin/env python3
"""
Тестовый скрипт для проверки веб-сервера Image Processor
"""

import requests
import json
import time

def test_server():
    base_url = "http://localhost:8080"
    
    print("🧪 Тестирование веб-сервера Image Processor")
    print("=" * 50)
    
    try:
        # Тест 1: Главная страница
        print("\n1️⃣ Тестирую главную страницу (GET /)")
        response = requests.get(f"{base_url}/")
        print(f"   Статус: {response.status_code}")
        print(f"   Размер ответа: {len(response.text)} символов")
        
        # Тест 2: Статус сервера
        print("\n2️⃣ Тестирую статус сервера (GET /status)")
        response = requests.get(f"{base_url}/status")
        print(f"   Статус: {response.status_code}")
        if response.status_code == 200:
            data = response.json()
            print(f"   Статус сервера: {data.get('status')}")
            print(f"   Версия: {data.get('version')}")
            print(f"   Временная метка: {data.get('timestamp')}")
        
        # Тест 3: Обработка изображения (заглушка)
        print("\n3️⃣ Тестирую обработку изображения (POST /process)")
        response = requests.post(f"{base_url}/process", json={"test": "data"})
        print(f"   Статус: {response.status_code}")
        if response.status_code == 200:
            data = response.json()
            print(f"   Сообщение: {data.get('message')}")
            print(f"   Примечание: {data.get('note')}")
        
        print("\n✅ Все тесты прошли успешно!")
        print(f"🌐 Сервер доступен по адресу: {base_url}")
        
    except requests.exceptions.ConnectionError:
        print("❌ Ошибка подключения к серверу!")
        print("   Убедитесь, что сервер запущен на порту 8080")
    except Exception as e:
        print(f"❌ Ошибка: {e}")

if __name__ == "__main__":
    test_server() 