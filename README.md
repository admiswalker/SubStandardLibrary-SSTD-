# SubStandardLibrary (SSTD)

SubStandardLibrary (SSTD) is a convenient functions set for C++, works on GCC (g++).


## Installation
1. Download this repository
2. Copy all of under `./sstd/*`
3. Compile sstd
   ```
   cd ./sstd
   make
   ```
4. Add flags in your makefile
   ```
   CFLAGS += -I./sstd/include -L./sstd/lib -lsstd
   CFLAGS += -std=gnu++0x
   ```
5. Include a header (`#include <sstd/sstd.hpp>`) in your code


## Tips to use always latest versions of sstd.
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

## Development
1. Clone this repository
   ```
   git clone git@github.com:admiswalker/SubStandardLibrary-SSTD-.git
   ```
2. Edite under `sstd/src/` and `test/`
3. Compile
   ```
   make
   ```
4. Run tests
   ```
   ./exe
   ```

## File and Directory descriptions

| File or directory name        | Description Origin |
| ----------------------------- | ------------------ |
| sstd/                         | Body of SSTD       |
| sstd/src/                     | Source files of SSTD |
| sstd/Makefile                 | Makefile to build SSTD |
| sstd/compileOption.hpp        | Define compilation options of SSTD |
| sstd/sstd.hpp                 | Header file that collects all the header files of SSTD |
| test/                         | Test files for SSTD. This directory has a same structure with under `sstd/src/`. |
| .git/                         | Git configulation and data files |
| .github/                      | Files for GitHub Actions |
| Makefile                      | Makefile to build `main.cpp` for running tests of sstd |
| README.md                     | This file          |
| googletest-master.zip         | Zip archive of googletest to build test code (`main.cpp` and files under `test/`) |
| main.cpp                      | Entrypoint to run tests under `test/` |
| test_c2py.py                  | Test file for `sstd::c2py()` to test `sstd::c2py()` calling python file on current directory. |
| .gitignore                    | Git configulation file to ignore and not to track files |

## Dependent libraries
Below libraries are incorporated in sstd.

| Library name | URL | Used version | License | Intended use |
| ------------ | --- | ------------ | ------- | ------------ |
| md5          | [github.com/kalven/md5](https://github.com/kalven/md5) | committed on 1 Jan 2014 | Public domain | MD5 calculation |
| WjCryptLib   | [github.com/WaterJuice/WjCryptLib](https://github.com/WaterJuice/WjCryptLib) | committed on 16 Mar 2018 | Public domain | SHA-1 calculation |
| SHA-2        | [github.com/kalven/sha-2](https://github.com/kalven/sha-2) | committed on 27 Aug 2012 | Public domain | SHA-2 calculation |

## Documents
[admiswalker.github.io/sstdref/](https://admiswalker.github.io/sstdref/) ([Repository](https://github.com/admiswalker/sstdref)).

## License
MIT licence or Public domain.
(This software is dual license, so you can choose whichever you want.)

