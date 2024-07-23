cmake_minimum_required(VERSION 3.22)
project(Ya-Yeet-alloc C)

set(CMAKE_C_STANDARD 17)

# Add the include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add the library source files
set(LIB_SOURCES
    src/yayeet_alloc.c
)

# Add the library header files
set(LIB_HEADERS
    include/yayeet_alloc.h
)

# Create the library
add_library(yayeet_alloc STATIC ${LIB_SOURCES} ${LIB_HEADERS})

# Add examples subdirectory
# add_subdirectory(examples)

# Enable testing
enable_testing()
# Add tests subdirectory
add_subdirectory(test)

install(TARGETS yayeet_alloc
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(FILES include/yayeet_alloc.h DESTINATION include)