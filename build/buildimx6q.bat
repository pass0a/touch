set TOOLCHAIN="-DCMAKE_TOOLCHAIN_FILE=../../cmake/imx6qwin.cmake"
set GENERATOR=Unix Makefiles

if not exist imx6q mkdir imx6q
cd imx6q

cmake ../../generate -G "%GENERATOR%" %TOOLCHAIN% -DCMAKE_INSTALL_PREFIX=../../output -DCMAKE_EXPORT_COMPILE_COMMANDS=YES
cmake --build ./ --target install
cd ..
pause