# Degenerate Bases
This algorithm generates a list of possible sequences derived from a sequence containing degenerate bases.

## 1. Setup

### 1.0 Prerequisites

Make sure you have CMake installed on your machine. For Windows users, make sure you have defined the appropriate environment path to it.

### 1.1 Cloning the Repository
Click the `Code` button then chose your preferred method of cloning.

If you want to clone it using the command line, please make sure you have Git installed and use the code bellow:
``` bash
> mkdir degenerate-bases & cd degenerate-bases
> git clone https://github.com/DatDarkAlpaca/Degenerate-Bases/
```

## 2. Building

### 2.1 Building for Windows

You can either use `CMakeGUI` or the command prompt to build the project.

Upon completion, open the generated *.sln* file under the build directory. After that, right click the `degenerate-bases` project and click `Build`. The executable files will be generated at `/build/src/'Configuration'`.


The following code is an example that you can use in the command prompt.
``` bash
> mkdir build
> cmake -S . -B build
```

### 2.2 Building for Linux

You can use the following code to build the project:
``` bash
> mkdir build & cd build
> cmake ..
> make
```
