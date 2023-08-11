if(WITH_GOOGLE_TEST)
    find_package(GTest REQUIRED)
    add_executable(test_ip_filter test_ip_filter.cpp)
    
    set_target_properties(test_ip_filter PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
    )

    set_target_properties(test_ip_filter PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/tests
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/tests
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
        INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS}

    )

    # исполняемый файл тестов
    target_link_libraries(test_ip_filter 
        ip_address
        pthread
        CONAN_PKG::gtest)
endif()

if (MSVC)
    if(WITH_GOOGLE_TEST)
        target_compile_options(test_ip_filter PRIVATE
            /W4
        )
    endif() 
else ()
    if(WITH_GOOGLE_TEST)
        target_compile_options(test_ip_filter PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)

if(WITH_GOOGLE_TEST)
    add_test(test_ip_filter ${CMAKE_BINARY_DIR}/tests/test_ip_filter )
endif()