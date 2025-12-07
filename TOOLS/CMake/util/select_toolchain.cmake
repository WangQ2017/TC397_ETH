set(TOOLCHAIN_CMAKE_PATH "${CMAKE_ROOT_DIR}/toolchain")

set(TOOLCHAIN_LIST
    ADS
    Tasking
)

set(ADS_TOOLCHAIN_PATH "d:/Infineon/AURIX-Studio-1.10.24/tools/Compilers/Tasking_1.1r8/ctc")
set(TASKING_TOOLCHAIN_PATH "c:/Program Files/TASKING/TriCore v6.3r1/ctc")# or "c: /Program Files/TASKING/Tricore v6.3r1/ctc"

function(check_toolchain)
    message(CHECK_START "Check TOOLCHAIN")
 
    if(NOT DEFINED TOOLCHAIN)
        message(CHECK_FAIL "not defined.\n"
            "    Use -DTOOLCHAIN='<toolchain>'to specify a toolchain.\n"
            "    Supported: ${TOOLCHAIN_LIST}")
        set_property(GLOBAL APPEND PROPERTY CHECK_FAILURES "TOOLCHAIN")
    elseif(NOT TOOLCHAIN IN_LIST TOOLCHAIN_LIST)
        message(CHECK_FAIL "not supported.\n"
            "    '${TOOLCHAIN}' not found in ${TOOLCHAIN_LIST}\n"
            "    Supported:${TOOLCHAIN_LIST}")
        set_property(GLOBAL APPEND PROPERTY CHECK_FAILURES "TOOLCHAIN")
    else()
        message(CHECK_PASS "'${TOOLCHAIN}' is supported")

        if(${TOOLCHAIN} STREQUAL "ADS")
            set(ENV{TASKING_TRICORE_TOOLCHAIN_PATH} ${ADS_TOOLCHAIN_PATH})
            set(CMAKE_TOOLCHAIN_FILE "${TOOLCHAIN_CMAKE_PATH}/toolchain_ads.cmake" PARENT_SCOPE)
        elseif(${TOOLCHAIN} STREQUAL "Tasking")
            set(ENV{TASKING_TRICORE_TOOLCHAIN_PATH} ${TASKING_TOOLCHAIN_PATH})
            set(CMAKE_TOOLCHAIN_FILE "${TOOLCHAIN_CMAKE_PATH}/toolchain_tasking.cmake" PARENT_SCOPE)
        endif()
    endif(NOT DEFINED TOOLCHAIN)
endfunction()