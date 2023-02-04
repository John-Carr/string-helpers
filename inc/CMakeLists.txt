add_library(addr-helpers INTERFACE)
target_include_directories(addr-helpers INTERFACE .)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU AND CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    target_compile_options(addr-helpers
        INTERFACE
            "--coverage"
    )
    target_link_options(addr-helpers
        INTERFACE
        "--coverage"
    )
endif()
