REM Should create legit pipeline instead of using batch files
@ECHO OFF
mkdir Build
cd Build
cmake ..
cmake --build . --target Engine