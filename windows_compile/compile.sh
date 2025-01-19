# This compiles for windows using mingw32 on linux systems, dependencies: mingw32-gcc
# Script output is at 'windows_compile_out'

x86_64-w64-mingw32-gcc $(find src -name "*.c") -o out.exe -lopengl32 -lglu32 -lkernel32 -luser32 -lgdi32
