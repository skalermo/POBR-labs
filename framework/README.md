# Framework - intro to POBR labs
Aim of this subproject was to test Rust bindings of OpenCV library.  
Provided C++ source code was ported to Rust: [main.rs](https://github.com/skalermo/POBR-labs/blob/main/framework/src/main.rs).

## Install
Packages to install on Arch Linux for OpenCV 4.5.1.  
Aside from OpenCV I had to install:
- base-devel (equivalent of build-essential on Ubuntu)
- hdf5
- vtk
- glew

## Build
To build run `cargo build` from the directory with Cargo.toml file.
  
## Results
Program compiles and runs without errors.
The console output:
```
Start...
false true
```

Image results:  
![Lena](https://github.com/skalermo/POBR-labs/blob/main/framework/Lena_new.png)|![Max](https://github.com/skalermo/POBR-labs/blob/main/framework/Max.png)
---|---
