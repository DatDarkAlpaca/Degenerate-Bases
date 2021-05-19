# Degenerate-Bases
This algorithm generates a list of possible sequences derived from a sequence containing degenerate bases.

## Setup

### Cloning the Repository
Click the `Code` button then chose your preferred method of cloning.

If you want to clone it using the command line, please make sure you have Git installed and use the code bellow:
``` bash
> mkdir degenerate-bases & cd degenerate-bases
> git clone https://github.com/DatDarkAlpaca/Degenerate-Bases/
```
## Building

Build using `make release` in the project directory, then run the executable under `build/bin`.

Example:

``` bash
> make release
> ./build/bin/degenerate
```

There are also a few other options when using the make command:

``` bash
# Compiles the code in debug mode:
> make debug

# Compile using the build:
> make all

# Cleans the objects, dependencies and executables:
> make clean

# Displays some directory and file information:
> make info
```
