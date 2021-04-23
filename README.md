# 3D-Cube-Render
## Running
I'm not exactly certain *why* you would want to install this, but if that's something you want to do, here are the instructions for Windows :

- Have make installed
  - For that, install [chocolatey](https://chocolatey.org/install) if you don't have it, then run `choco install make`
- Have [MinGW](https://sourceforge.net/projects/mingw/) installed and in your PATH
- Download the MinGW version of [SFML](https://www.sfml-dev.org/download/sfml/2.5.1/) and extract it somewhere on your computer
  - Note that the paths in the Makefile need to be adjusted accordingly, simply link `INCLUDE_DIRECTORIES` and `LIB_DIRECTORIES` to your SFML installation
- Add the SFML debug dlls (in the SFML `bin/` folder, they finish by `-d-2.dll`) to the `bin/` folder in the directory
- Run `make` and you should be golden !
