
:: Prompt the user for the file name
set /p fileName=Enter the name for the C++ and header files: 

:: Check if the file name is not empty
if "%fileName%"=="" (
    echo File name cannot be empty.
    exit /b
)

:: Create the .cpp file
echo // %fileName%.cpp >> "%fileName%.cpp"
echo #include "../Global.h" >> "%fileName%.cpp"
echo >> "%fileName%.cpp"
echo int main() { >> "%fileName%.cpp"
echo     return 0; >> "%fileName%.cpp"
echo } >> "%fileName%.cpp"

:: Create the .h file
echo // %fileName%.h >> "%fileName%.h"
echo #pragma once >> "%fileName%.h"
echo >> "%fileName%.h"
echo class %fileName%: public WindowBase { >> "%fileName%.h"
echo private: >> "%fileName%.h"
echo >> "%fileName%.h"
echo public: >> "%fileName%.h"
echo     void Render() override; >> "%fileName%.h"
echo }; >> "%fileName%.h"

echo Files "%fileName%.cpp" and "%fileName%.h" have been created in the current directory.
