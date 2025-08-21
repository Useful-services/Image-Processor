Write-Host "Starting Image Processor Web Server..." -ForegroundColor Green
Write-Host ""

if (-not (Test-Path "build\Release\WEB_SERVER.exe")) {
    Write-Host "Error: WEB_SERVER.exe not found!" -ForegroundColor Red
    Write-Host "Please build the project first using: .\build.ps1" -ForegroundColor Yellow
    Read-Host "Press Enter to continue"
    exit 1
}

Write-Host "Server will be available at: http://localhost:8080" -ForegroundColor Cyan
Write-Host "Press Ctrl+C to stop the server" -ForegroundColor Yellow
Write-Host ""

Set-Location "build\Release"
.\WEB_SERVER.exe 