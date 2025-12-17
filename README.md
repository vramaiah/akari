<div align="center">
    <h1>Akari</h1>
</div>

In an Akari Puzzle, the goal is to place light bulbs on a grid so all purple squares are lit.
* A light bulb lights up all the purple squares in its row and column until blocked by a wall.
* No light bulb may light up another light bulb.

# How To Build

```
cmake -DCMAKE_OSX_SYSROOT=$(xcrun --show-sdk-path) \
      -DCMAKE_C_COMPILER=$(xcrun --find clang) \
      -DCMAKE_CXX_COMPILER=$(xcrun --find clang++) \
      -DCMAKE_CXX_FLAGS="-I$(xcrun --show-sdk-path)/usr/include/c++/v1" \
      -B build
cmake --build build --parallel
```
