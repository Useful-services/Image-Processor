# Image Processor

Веб-приложение для обработки изображений с бэкендом на C++ и фронтендом на TypeScript/React.

## Функционал

- Загрузка изображений через drag & drop или выбор файла
- Конвертация изображений в черно-белые
- Сохранение статистики обработки в базу данных SQLite
- Современный и отзывчивый пользовательский интерфейс

## Архитектура

### Бэкенд (C++)
- **HTTP сервер**: Использует библиотеку httplib
- **Обработка изображений**: OpenCV для конвертации в ЧБ
- **База данных**: SQLite для хранения статистики
- **Время обработки**: Точное измерение времени выполнения

### Фронтенд (TypeScript/React)
- **React 18** с TypeScript
- **Vite** для быстрой разработки и сборки
- **Современный UI** с drag & drop
- **Адаптивный дизайн** для мобильных устройств

## Требования

### Системные требования
- C++17 компилятор (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.16+
- Node.js 16+ и npm

### Зависимости C++
- OpenCV 4.x
- SQLite3
- httplib (включена в проект)

### Зависимости JavaScript
- React 18
- TypeScript 5
- Vite 4

## Установка и запуск

### 1. Клонирование репозитория
```bash
git clone <repository-url>
cd Image-Processor
```

### 2. Установка зависимостей C++

#### Ubuntu/Debian:
```bash
sudo apt update
sudo apt install build-essential cmake libopencv-dev libsqlite3-dev
```

#### Windows (с vcpkg):
```bash
vcpkg install opencv sqlite3
```

#### macOS:
```bash
brew install opencv sqlite3 cmake
```

### 3. Установка зависимостей фронтенда
```bash
cd frontend
npm install
```

### 4. Сборка бэкенда

#### Linux/macOS:
```bash
chmod +x build.sh
./build.sh
```

#### Windows:
```bash
build.bat
```

### 5. Сборка фронтенда
```bash
cd frontend
npm run build
```

### 6. Запуск приложения

#### Запуск бэкенда:
```bash
# Linux/macOS
./build/image_processor_backend

# Windows
build\Release\image_processor_backend.exe
```

#### Запуск фронтенда (для разработки):
```bash
cd frontend
npm run dev
```

## Использование

1. Откройте браузер и перейдите по адресу `http://localhost:8080`
2. Загрузите изображение, перетащив файл в зону загрузки или нажав на неё
3. Нажмите кнопку "Превратить в ЧБ"
4. Дождитесь завершения обработки
5. Скачайте обработанное изображение

## API Endpoints

### POST /api/convert-to-bw
Конвертирует изображение в черно-белое.

**Request Body**: Бинарные данные изображения
**Response**: Обработанное изображение в формате JPEG

**Headers**:
- Content-Type: image/jpeg
- Access-Control-Allow-Origin: *

### GET /api/health
Проверка состояния сервера.

**Response**: "OK"

## Структура базы данных

```sql
CREATE TABLE processing_records (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    image_size INTEGER NOT NULL,
    processing_time_ms REAL NOT NULL,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
);
```

## Структура проекта

```
Image-Processor/
├── src/                    # C++ исходный код
│   ├── main.cpp           # Основной файл сервера
│   ├── image_processor.h  # Заголовок обработчика изображений
│   ├── image_processor.cpp # Реализация обработчика изображений
│   ├── database_manager.h # Заголовок менеджера БД
│   └── database_manager.cpp # Реализация менеджера БД
├── frontend/              # TypeScript/React фронтенд
│   ├── src/
│   │   ├── App.tsx       # Основной компонент
│   │   ├── main.tsx      # Точка входа
│   │   └── index.css     # Стили
│   ├── package.json      # Зависимости
│   └── vite.config.ts    # Конфигурация Vite
├── CMakeLists.txt         # CMake конфигурация
├── build.sh              # Скрипт сборки (Linux/macOS)
├── build.bat             # Скрипт сборки (Windows)
└── README.md             # Документация
```

## Разработка

### Запуск в режиме разработки
```bash
# Терминал 1: Бэкенд
./build/image_processor_backend

# Терминал 2: Фронтенд
cd frontend
npm run dev
```

### Сборка для продакшена
```bash
# Фронтенд
cd frontend
npm run build

# Бэкенд
./build.sh
```

## Производительность

- **Время обработки**: Измеряется с точностью до миллисекунд
- **Размер изображений**: Поддерживаются изображения любого размера
- **Форматы**: JPG, PNG, GIF, BMP
- **Параллельная обработка**: Возможность обработки нескольких изображений одновременно

## Безопасность

- Валидация типов файлов
- Ограничение размера загружаемых файлов
- CORS настройки для веб-интерфейса
- Защита от SQL-инъекций

## Лицензия

MIT License - см. файл LICENSE для деталей.

## Поддержка

При возникновении проблем:
1. Проверьте, что все зависимости установлены
2. Убедитесь, что порт 8080 свободен
3. Проверьте логи сервера в консоли
4. Создайте issue в репозитории проекта 