<p align="center">

  <a href="https://www.vtil.org/">
    <img width="256" heigth="256" src="https://vtil.org/logo.png">
  </a>  

  <h1 align="center">VTIL-Python</h1>

  <p align="center">
    <a href="https://ci.appveyor.com/project/can1357/vtil-python">
      <img src="https://img.shields.io/appveyor/build/can1357/VTIL-Python?logo=appveyor&style=flat-square" alt="appveyor-ci"/>
    </a>
    <a href="https://github.com/vtil-project/vtil-core/blob/master/LICENSE.md">
      <img src="https://img.shields.io/github/license/vtil-project/vtil-core.svg?style=flat-square" alt="license"/>
    </a>
    <a href="https://discord.gg/VdMdkze">
      <img alt="discord" src="https://img.shields.io/discord/724300992023232533?label=chat&logo=Discord&style=flat-square">
    </a>
  </p>

  <p align="center">
    Virtual-machine Translation Intermediate Language - Python Bindings
  </p>
</p>

# Introduction
// TODO..

## Building (CMake)

Dependencies:

- Python >=3.5 (x64)
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
