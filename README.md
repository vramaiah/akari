<div align="center">
    <h1>Akari</h1>
</div>
![forthebadge](https://forthebadge.com/badges/made-with-c-plus-plus.svg)
![forthebadge](https://forthebadge.com/api/badges/generate?panels=2&primaryLabel=Made+for&secondaryLabel=Mac+OS&primaryBGColor=%2331C4F3&primaryTextColor=%23FFFFFF&secondaryBGColor=%23389AD5&secondaryTextColor=%23FFFFFF&primaryFontSize=12&primaryFontWeight=600&primaryLetterSpacing=2&primaryFontFamily=Roboto&primaryTextTransform=uppercase&secondaryFontSize=12&secondaryFontWeight=900&secondaryLetterSpacing=2&secondaryFontFamily=Montserrat&secondaryTextTransform=uppercase&secondaryIcon=apple&secondaryIconColor=%23FFFFFF&secondaryIconSize=16&secondaryIconPosition=left)

This is an implementation of the puzzle [Akari](https://en.wikipedia.org/wiki/Light_Up_(puzzle)) in C++.

In an Akari Puzzle, the goal is to place light bulbs on a grid so all purple squares are lit.
* A light bulb lights up asll the purple squares in its row and column until blocked by a wall.
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
