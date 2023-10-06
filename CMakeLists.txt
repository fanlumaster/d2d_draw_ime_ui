cmake_minimum_required(VERSION 3.25.0)
project(castkey)

# add_library(D2DOverlay "./fany.cpp")
add_executable(castkey WIN32 "./fany.cpp" "./DPIAware.manifest")
