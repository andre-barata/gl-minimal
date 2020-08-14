# gl-minimal

Minimal modern OpenGL project in C, using mingw64/MSYS2 toolchains, SDL2, debug and standalone release makefiles, and VS Code configuration

How to build:
```
make [degub|release] [static=y] [console=y]
```

Project paths:
```
 project folder:
 |- src/
 |  |- *.c           -- c source files
 |  |- include/
 |     |- *.h        -- any local .h files would go here
 |- res/
 |  |- win/
 |  |  |- main.ico   -- application icon on windows
 |  |  |- winres.rc  -- when compiling on windows, resourse file defining the main icon and executable metadata
 |  |- *.*           -- any binary files to pack in the executable go here
 |- obj/             -- temporary object and resource files generated and used during compilation
 |- Makefile         -- this file
 |- *.exe            -- ouput executable goes here
```
