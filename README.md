# VTIL-Python
// TODO: ..

## Building (CMake)

Dependencies:

- Python 2.7 (x64), Python 3.x (x64)
- Visual Studio 2019
- CMake 3.15 or higher

From a Visual Studio 2019 command prompt:

```
mkdir build && cd build
cmake -DPYTHON_EXECUTABLE=%PYTHON_PATH%\python.exe ..  ; e.g. c:\Python37-64\python.exe
cmake --build . --config Release
cmake --install . --component pyd --prefix .
```

This will give you `vtil.pyd` in the `build` directory.
