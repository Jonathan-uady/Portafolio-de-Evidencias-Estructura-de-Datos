# PowerShell build script — compila todos los .c en output\main.exe
$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition
$outputDir = Join-Path $scriptDir 'output'
if (-not (Test-Path $outputDir)) {
    New-Item -ItemType Directory -Path $outputDir | Out-Null
}

Write-Host "Compilando fuentes..."
& gcc -Wall -Wextra -g3 "${scriptDir}\*.c" -o "${outputDir}\main.exe"
if ($LASTEXITCODE -ne 0) {
    Write-Error "Error de compilacion. Codigo: $LASTEXITCODE"
    exit $LASTEXITCODE
}

Write-Host "Compilacion exitosa: $outputDir\main.exe"
exit 0
