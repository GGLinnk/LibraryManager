# Library Manager

This is a library item manager.
<!--It's designed using FTXUI and SQLite3 but other database or (G)UI can be easily implemented.-->


## Compile


### Requirements


#### Windows

- Visual Studio Build Tools or Visual Studio.
- CMake 3.12 and up.


#### Linux / UNIX

- g++ compiler or any supported c++ compiler should work.
- CMake 3.12 and up.


### Build withCMake on all supported platform

```bash
mkdir build
cd build
cmake ..
cmake --build .
```


## Requirements

To run this software once compiled you will need to install Microsoft VC Redistribuables:
- https://aka.ms/vs/17/release/vc_redist.x86.exe
- https://aka.ms/vs/17/release/vc_redist.x64.exe


## Usage

<!-- ### GUI Mode
This is the default mode when implemented. -->

<!-- ### TUI Mode
This mode allow for terminal user interface. It uses FTXUI by default.
It could be forced with tui argument ``LibraryManager(.exe) tui`` -->


### CLI Mode

This allow for direct cli commands

Run the program to show the helper
```bash
./LibraryManager(.exe) -h
```
> Under windows LibraryManager executable is in the ``Debug`` subfolder.


## Note for future versions

- Use [SOCI](https://github.com/SOCI/soci)
- Use [SPDLOG](https://github.com/gabime/spdlog)