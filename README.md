# Overview

This package allows to load, parameterize, run and analyze OpenFLUID simulations 
from the GNU R environment 

The ROpenFLUID license is available in the package/LICENSE file

This package uses the following R packages:
- Runit (for tests only)
- roxygen2 (during package development only, not for installation or usage) 


# Source code

Package heavily relies on binding facilities provided by the OpenFLUID Framework. See `openfluid/utils/Binding.hpp` and related headers in the [OpenFLUID sourec code](https://github.com/OpenFLUID/openfluid).


The R part of the code is written following the [Tidyverse coding style](https://style.tidyverse.org/), with the following exceptions:

* line length is not stricly limited to 80 characters and can be extended to 120 characters if needed
* case style of functions names is not restricted to the recommended snake case 



# Development and Build

The ROpenFLUID package requires for building process:
- The OpenFLUID framework
- The R development framework
- The CMake build tools family
- The GCC compiler suite 4.8 or higher (for C++11 compatibility) 

On Windows platforms, the MinGW compiler provided by Qt have to be used from an MSYS terminal.


The build/doc commands are launched using the CMake tool in script mode. In this mode, 
configuration variables passed on the command line must be placed before the `-P <script>` argument.


Each following command produces results in a build directory. 
The default name for this directory is `_build` and is located at the root of the ROpenFLUID sources.
To override this default build directory, you can set a custom absolute path through the `BUILD_PATH` variable of the CMake command (e.g. `cmake -DBUILD_PATH=/path/to/build/dir -P check.cmake`)


## Checking ROpenFLUID package

This will run the R checking process for the package:
```
cmake -P check.cmake
```

The CRAN mode can be enabled to apply the CRAN submission requirements for package submissions:
```
cmake -DAS_CRAN_MODE=ON -P check.cmake
```


## Building ROpenFLUID package

This will create the package. 

On Linux/Unix platforms, run the following command in a terminal:
```
cmake -P build.cmake
```

On Windows platforms, run the following command in an MSYS terminal:
```
cmake -P build-win32.cmake
```
Before running this command on Windows platform, you may have to configure the run environment.
See the `win32-env.sh.tpl` file for an example.


## Generating HTML doc for ROpenFLUID package

```
cmake -P htmldoc.cmake
```

