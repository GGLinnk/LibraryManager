cmake_minimum_required(VERSION 3.12...3.28)

project(LibraryManager
  LANGUAGES CXX
  VERSION 0.1.0
)

if(MSVC AND (MSVC_VERSION LESS 1910))
    message(FATAL_ERROR "MSVC version 2017 or newer is required.")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/CPM.cmake)

message("Adding FTXUI 5.0.0")
set(FTXUI_QUIET on)
CPMAddPackage("gh:ArthurSonzogni/ftxui#v5.0.0")
#add_subdirectory(${CMAKE_SOURCE_DIR}/lib/FTXUI-5.0.0)

message("Adding SQLiteCpp 3.3.1")
CPMAddPackage("gh:SRombauts/SQLiteCpp#3.3.1")
#add_subdirectory(${CMAKE_SOURCE_DIR}/lib/SQLiteCpp-3.3.1)

message("Adding CLI11 2.3.2")
CPMAddPackage("gh:CLIUtils/CLI11#v2.3.2")

configure_file(
    ${CMAKE_SOURCE_DIR}/config.h.in
    ${CMAKE_SOURCE_DIR}/include/config.h
)

include_directories(include)
file(GLOB
  SOURCES "src/*.cpp"
  SOURCES "src/ui/*.cpp"
  SOURCES "src/database/*.cpp"
)

# Create executable
add_executable(LibraryManager ${SOURCES})
link_directories(${${sqlite3_SOURCE_DIR}})
target_link_libraries(LibraryManager
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
  PRIVATE CLI11::CLI11
  PRIVATE SQLiteCpp
)