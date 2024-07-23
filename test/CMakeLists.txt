# Add the test executable
add_executable(test_yayeet_alloc test_yayeet_alloc.c)

# Link the test executable with the library
target_link_libraries(test_yayeet_alloc yayeet_alloc)

# Add the include directory
target_include_directories(test_yayeet_alloc PRIVATE ${PROJECT_SOURCE_DIR}/include)


# Add a test
add_test(NAME YaYeetAllocTest COMMAND test_yayeet_alloc)