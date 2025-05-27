# kapinbteditor
This program is designed to:
- read and write NBT and `.litematic` files
- edit data in these files
- create renders of an object from `.litematic`
- create map arts in `.litematic` format from images
- maybe anything else

# Dependencies

- [zlib](https://www.zlib.net/) — for compression (licensed under the [zlib License](https://opensource.org/licenses/Zlib))
- [stb](https://github.com/nothings/stb) — public domain / MIT licensed single-file libraries:
  - `stb_image.h`
  - `stb_image_write.h`
- [kapilib.h](https://github.com/kapi3217/kapinbteditor/blob/main/source/lib/kapilib.h) - just a single header file that content some useful functions, maybe sometimes it will be in its own repository
  
These libraries are included in `source/lib`.
# Building an executable file using g++ compiler
The `zlib` library was built for x86-64 Windows and Linux, but if something went wrong or you use another architecture - you can build it yourself.

## Build zlib library
- Remove files from `source/your_architecture`
- Open `bash` in `source/lib/zlib`
- Execute next commands
  - `./configure`
  - `make`
- move `libz.a` and `zconf.h` to `source/your_architecture`
  
## Build executable file
- Download `VS Code`
- Download `C/C++` extension
- Open project folder
- Open `.vs/tasks.json` and change the task / create a new one if you want
- I used these flags:
  - `-Os` to reduce size
  - `-O2` optimisation, level 2
  - `-s` to remove all debug info from the binary
  - `-static` to link all libraries directly to the binary
- Choose a task and run it
