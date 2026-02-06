cmake_minimum_required(VERSION 3.11)
project(MyProject)

# Tell Cmake to use C++17
set(CMAKE_CXX_STANDARD 17)

# Find the FTXUI library
find_package(ftxui REQUIRED)

# Create executable
add_executable(main main.cpp util/file_io.cpp)

target_link_libraries(main
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
)
