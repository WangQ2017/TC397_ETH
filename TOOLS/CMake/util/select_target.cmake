set(TARGET_DIR ${CMAKE_ROOT_DIR}/target)

function(check_target)
    file(GLOB TARGET_LIST LIST_DIRECTORIES false RELATIVE ${TARGET_DIR}
        ${TARGET_DIR}/*.cmake
    )
    list(TRANSFORM TARGET_LIST REPLACE ".cmake" "")
    list(REMOVE_ITEM TARGET_LIST "common")

    message(CHECK_START "Check TARGET")

    if(NOT DEFINED TARGET)
        message(CHECK_FAIL "not defined.\n"
            "    Use `cmake -B build -S Toolsl\cmake -GNinja -DTARGET='<target>' to specify a build target.\n"
            "    Supported:${TARGET_LIST}")
        set(APPEND check_failures "TARGET")
        set_property(GLOBAL APPEND PROPERTY CHECK_FAILURES "TARGET")

    elseif(NOT ${TARGET} IN_LIST TARGET_LIST)
        message(CHECK_FAIL "not supported.\n"
            "    '${TARGET}' not found in ${TARGET_DIR}\n"
            "    Supported:${TARGET_LIST}")
    else()
        message(CHECK_PASS "'${TARGET}' is supported")
        set_property(GLOBAL PROPERTY BUILD_TARGET ${TARGET})
        set_property(GLOBAL APPEND PROPERTY CMAKE_INCLUDES ${TARGET_DIR}/common.cmake)
        set_property(GLOBAL APPEND PROPERTY CMAKE_INCLUDES ${TARGET_DIR}/${TARGET}.cmake)
    endif(NOT DEFINED TARGET)
endfunction()