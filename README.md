# cpp_rtype

### By Unarelith

- This game is a 3rd year Epitech project

![](screenshot.png?raw=true)

## Keys

- Shoot: <kbd>X</kbd>
- Move: <kbd>&larr;</kbd> <kbd>&uarr;</kbd> <kbd>&darr;</kbd> <kbd>&rarr;</kbd>

## How to compile

- Dependencies:
    - A compiler with C++14 support
    - [CMake](http://www.cmake.org/download/)
    - [GameKit](http://github.com/Unarelith/GameKit) (requires `SDL2` + `tinyxml2`, will switch to `SFML` starting from 2.6)
    - [SFML](https://www.sfml-dev.org/) (only used for network)
    - _Linux users: Check your distribution repositories for packages._
- Run `cmake . && make -j8`
- Run the server with `./server/rtype_server`
- Run the client with `./client/rtype_client`

