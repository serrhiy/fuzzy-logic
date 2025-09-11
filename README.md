### How to build

1. Install dependecies for matplotplusplus. In Debian or Ubuntu:

`sudo apt install gnuplot libglfw3-dev`

2. Add `CMakeUserPresets.json` to source directory:

```json
{
  "version": 2,
  "configurePresets": [
    {
      "name": "release",
      "inherits": "vcpkg",
      "environment": {
        "VCPKG_ROOT": "<path to vcpkg>"
      },
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Release"
      }
    },
    {
      "name": "debug",
      "inherits": "vcpkg",
      "environment": {
        "VCPKG_ROOT": "<path to vcpkg>"
      },
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Debug",
        "CMAKE_CXX_INCLUDE_WHAT_YOU_USE": "include-what-you-use"
      }
    }
  ]
}
```

3. Run CMake in source directory:

```shell
cmake --preset=release # or debug
cmake --build build
```