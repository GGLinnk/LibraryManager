cmake_minimum_required(VERSION 3.12...3.12)

project(LibraryManager
  LANGUAGES CXX
  VERSION 0.1.0
)

set(CMAKE_CXX_STANDARD 11)

# add dependencies
include(cmake/CPM.cmake)

CPMAddPackage("gh:ArthurSonzogni/ftxui#v5.0.0")
CPMAddPackage("gh:SRombauts/SQLiteCpp#3.3.1")
##CPMAddPackage("gh:gabime/spdlog#v1.12.0")

# Set source files
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
  PRIVATE SQLiteCpp
  #PRIVATE spdlog
)