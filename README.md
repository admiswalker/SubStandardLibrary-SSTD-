# SubStandardLibrary

Convenient functions for GCC(g++) and MSVC++.

Functions: `sstd/sstd.hpp` 

Usages of functions: `main.cpp` 

## Installation
### Linux 
1. Copy all of under `./sstd/*`. 
2. Compile sstd.
```
$ cd ./sstd
$ make
```
3. Add flags in your makefile.
```
CFLAGS += -I./sstd/include -L./sstd/lib -lsstd
CFLAGS += -std=gnu++0x
```
4. Include a header (`#include <sstd/sstd.hpp>`) in your code.

### Windows 
1. Copy all of under `./sstd/*`. 
2. Include a header (`#include "./sstd/sstd.hpp"`) in your code.

## License
MIT licence.
