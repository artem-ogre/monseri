project(monseri)

# Collect .h sources from the include directories
file(GLOB files "include/*.h" "include/iostream_storage/*.h")
# Add a library
add_library(monseri INTERFACE)
# Add sources
target_sources(monseri INTERFACE ${files})
# Specify library's include directory
target_include_directories(monseri INTERFACE include)
