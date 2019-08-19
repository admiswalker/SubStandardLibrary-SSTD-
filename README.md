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

Note: Recently, sstd has not been tested on Windows (MSVC++), while codes locked on linux is not so many.

## Tips to use always latest versions of sstd.
### Linux
Below lines of makefile enable to update sstd by a command of ```$ make update```.
Adding a dependence of sstd to your makefile by using ```$(LIB_SSTD)```.
```
# when you need to check the change of files in lib, you need to change file name to a not-existing name like "FORCE_XXX".
#LIB_SSTD       = FORCE_SSTD
LIB_SSTD        = ./sstd/lib/libsstd.a

$(LIB_SSTD):
	@echo ""
	@unzip -n SubStandardLibrary-SSTD--master.zip
	@mv SubStandardLibrary-SSTD--master/sstd ./
	@rm -rf SubStandardLibrary-SSTD--master/
	@(cd ./sstd; make -j)

.PHONY: updateLib
updateLib:
	wget https://github.com/admiswalker/SubStandardLibrary-SSTD-/archive/master.zip -O SubStandardLibrary-SSTD--master.zip
	-rm -rf sstd # remove previous versions of sstd
```

## Documents
file | URL
---- | ---
./Makefile | [admiswalker.blogspot.com/2017/02/makefile.html](https://admiswalker.blogspot.com/2017/02/makefile.html)
./sstd/src/c2py.cpp-.hpp | [admiswalker.blogspot.com/2018/02/c-python.html](https://admiswalker.blogspot.com/2018/02/c-python.html)
./sstd/src/bmat/*.cpp-.hpp | [admiswalker.blogspot.com/2017/11/bit-xorshift.html](https://admiswalker.blogspot.com/2017/11/bit-xorshift.html), [admiswalker.blogspot.com/2017/11/bit-xorshift.html](https://admiswalker.blogspot.com/2017/11/bit-xorshift.html)
./sstd/src/stdVector_expansion/stdVector_expansion.hpp | [admiswalker.blogspot.com/2018/08/stdvectorexpansion.html](https://admiswalker.blogspot.com/2018/08/stdvectorexpansion.html)
./sstd/src/matrixContainer_colMajor/mat_c.hpp | [admiswalker.blogspot.com/2019/04/a-single-header-file-template-container.html](https://admiswalker.blogspot.com/2019/04/a-single-header-file-template-container.html)
./sstd/src/matrixContainer_rowMajor/mat_r.hpp | [admiswalker.blogspot.com/2019/04/a-single-header-file-template-container.html](https://admiswalker.blogspot.com/2019/04/a-single-header-file-template-container.html)
The others | https://sstd-lib.blogspot.com/p/index.html

## License
MIT licence or Public domain.
(This software is dual license, so you can choose whichever you want.)

## Below libraries are incorporated in sstd.

library name    | URL | used version | license | intended use
--------------------- | ---- | -------- | -------------------------------- | ----
md5 | [github.com/kalven/md5](https://github.com/kalven/md5) | committed on 1 Jan 2014 | Public domain | MD5 calculation
WjCryptLib | [github.com/WaterJuice/WjCryptLib](https://github.com/WaterJuice/WjCryptLib) | committed on 16 Mar 2018 | Public domain | SHA-1 calculation
SHA-2 | [github.com/kalven/sha-2](https://github.com/kalven/sha-2) | committed on 27 Aug 2012 | Public domain | SHA-2 calculation




