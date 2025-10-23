# Pic-g 3D Engine (Legacy OpenGL engine)
An simple 3D engine using OpenGL 1.1 and OS-native window management libraries.
Dependencies: X11, GLU, OpenGL. Currently only supports linux running X11. Windows compilation is possible, but all X11 things are not yet implemented. 

### Some graphics demos I made with this:

<p float="left">
<img src="dev/screenshots/flightsim.png" alt="drawing" width="700"/>
<img src="dev/screenshots/demo_4_6_25.png" alt="drawing" width="200"/>
<img src="dev/screenshots/teapot.png" alt="drawing" width="200"/>
<img src="dev/screenshots/cubespin.png" alt="drawing" width="200"/>
<img src="dev/screenshots/debug.png" alt="drawing" width="200"/>
</p>

# Installation (Linux)
1. Download the git repository and cd to it
```shell
git clone  https://github.com/Tammerodev/Pic-gEngine.git 
cd Pic-gEngine
 ```
2. Create and open build directory (executable will be found here)
```shell
mkir build && 
cd build
 ```

3. Run CMake
```shell
cmake ..
 ```

### Building the project
1. Make sure you created the program source file according to section "Scripting".

2. Build
```shell
cmake --build . 
 ```
3. Run the executable
```shell
./Pic-g 
 ```


# Windows cross-compiling
There is a script located at windows_compile/compile.sh, that compiles this using mingw32. 

# Scripting
Rename the "program.c-info" file into "program.c". Your code will be written here.

### Lighting

<img src="dev/screenshots/lighting_0v1.png" alt="drawing" width="500"/>

Lighting with vertex normals displayed (loaded from wavefront OBJ file

### Models
Format: wavefront .obj.

If using blender, please make sure export MTL texture path setting is to "absolute". 

![](dev/screenshots/export.png)

## Collaboration
Please read the syntax.md document for information on code syntax and collaboration rules.