# SubStandardLibrary (SSTD)

Convenient functions for GCC(g++) and MSVC++.

List of functions: `sstd/sstd.hpp` 

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

## Documents
・./Makefile: https://admiswalker.blogspot.com/2017/02/makefile.html  
・./sstd/src/c2py.cpp-.hpp: https://admiswalker.blogspot.com/2018/02/c-python.html  
・./sstd/src/bmat/*.cpp-.hpp: https://admiswalker.blogspot.com/2017/11/bit-xorshift.html, https://admiswalker.blogspot.com/2017/11/bit-xorshift.html  
・The others: https://sstd-lib.blogspot.com/p/index.html  

## License
MIT licence or Public domain. (You can choose whichever you want.)

## Below libraries are incorporated in sstd.

library name    | URL | used version | license
--------------------- | ---- | -------- | --------------------------------
md5 | https://github.com/kalven/md5 | committed on 1 Jan 2014 | Public domain
WjCryptLib | https://github.com/WaterJuice/WjCryptLib | committed on 16 Mar 2018 | Public domain
SHA-2 | https://github.com/kalven/sha-2 | committed on 27 Aug 2012 | Public domain




