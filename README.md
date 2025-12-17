<div align="center">
    <h1>Akari</h1>
</div>

This is an implementation of the puzzle Akari in C++.

In an Akari Puzzle, the goal is to place light bulbs on a grid so all purple squares are lit.
* A light bulb lights up all the purple squares in its row and column until blocked by a wall.
* No light bulb may light up another light bulb.

# Screenshots 
<div align="center">
    <img src="./screenshots/level_in_progress.png">
</div>

# Features
* Automatic win detection
* X-out cells
* Support for custom levels with JSON

# How To Build

```shell
cmake -DCMAKE_OSX_SYSROOT=$(xcrun --show-sdk-path) \
      -DCMAKE_C_COMPILER=$(xcrun --find clang) \
      -DCMAKE_CXX_COMPILER=$(xcrun --find clang++) \
      -DCMAKE_CXX_FLAGS="-I$(xcrun --show-sdk-path)/usr/include/c++/v1" \
      -B build
cmake --build build --parallel
```
