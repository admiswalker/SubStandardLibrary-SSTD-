# SubStandardLibrary (SSTD)

Convenient functions for GCC(g++) <s>and MSVC++</s>.

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

<s>
### Windows 
1. Copy all of under `./sstd/*`. 
2. Include a header (`#include "./sstd/sstd.hpp"`) in your code.
</s>

Note: Recently, sstd has not been tested on Windows (MSVC++).

## Tips to use always latest versions of sstd.
### Linux
Below lines of makefile enable to update sstd by a ```$ make update``` command.
Adding ```$(LIB_SSTD)```　as a depending lib to your makefile.
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
[admiswalker.github.io/sstdref/](https://admiswalker.github.io/sstdref/) ([Repository](https://github.com/admiswalker/sstdref)).

## License
MIT licence or Public domain.
(This software is dual license, so you can choose whichever you want.)

## Below libraries are incorporated in sstd.

library name    | URL | used version | license | intended use
--------------------- | ---- | -------- | -------------------------------- | ----
md5 | [github.com/kalven/md5](https://github.com/kalven/md5) | committed on 1 Jan 2014 | Public domain | MD5 calculation
WjCryptLib | [github.com/WaterJuice/WjCryptLib](https://github.com/WaterJuice/WjCryptLib) | committed on 16 Mar 2018 | Public domain | SHA-1 calculation
SHA-2 | [github.com/kalven/sha-2](https://github.com/kalven/sha-2) | committed on 27 Aug 2012 | Public domain | SHA-2 calculation




