cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VESRION})


option(WITH_GOOGLE_TEST "Whether to build Google test" ON)

configure_file(version.h.in version.h)

add_executable(ip_filter ip_filter.cpp)
add_library(ip_address ip_address.cpp)

set_target_properties(ip_address ip_filter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(ip_filter
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(ip_filter PRIVATE
    ip_address
)

if(WITH_GOOGLE_TEST)
    find_package(GTest REQUIRED)
    add_executable(test_version test_version.cpp)
    add_executable(test_ip_filter test_ip_filter.cpp)
    
    set_target_properties(test_version test_ip_filter PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
    )

    set_target_properties(test_version test_ip_filter PROPERTIES
        INCLUDE_DIRECTORIES 
        ${GTEST_INCLUDE_DIRS}
    )


    # исполняемый файл тестов
    
    target_link_libraries(test_version
        ${GTEST_LIBRARIES} 
        ip_address
        pthread)

    target_link_libraries(test_ip_filter 
        ${GTEST_LIBRARIES} 
        ip_address
        pthread)
endif()


if (MSVC)
    target_compile_options(ip_address PRIVATE
        /W4
    )
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    if(WITH_GOOGLE_TEST)
        target_compile_options(test_version PRIVATE
            /W4
        )
        target_compile_options(test_ip_filter PRIVATE
            /W4
        )

    endif()
else ()
    target_compile_options(ip_address PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    if(WITH_GOOGLE_TEST)
        target_compile_options(test_version PRIVATE
            -Wall -Wextra -pedantic -Werror
        )

        target_compile_options(test_ip_filter PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)


if(WITH_GOOGLE_TEST)
    enable_testing()
    add_test(test_version test_version)
    add_test(test_ip_filter test_ip_filter)
endif()
