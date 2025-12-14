cmake_minimum_required(VERSION 3.25)

#gloabl definitions
set(PROJECT_NAME "app")
set(APP_MARK "WQ")
set(PLATFORM_CODE "00")
set(PROJECT_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../..")
set(CMAKE_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

define_property(GLOBAL PROPERTY BUILD_TARGET)
define_property(GLOBAL PROPERTY CMAKE_INCLUDES)
define_property(GLOBAL PROPERTY CHECK_FAILURES)

# select toolchain
include(util/select_toolchain.cmake)
check_toolchain()

# select target
include(util/select_target.cmake)
check_target()

get_property(check_failure_list GLOBAL PROPERTY CHECK_FAILURES)

if(check_failure_list)
    message(FATAL_ERROR "Check failures: ${check_failure_list}")
endif()

get_property(cmake_include_list GLOBAL PROPERTY CMAKE_INCLUDES)
foreach(cmake_file IN LISTS cmake_include_list)
    include(${cmake_file})
endforeach()

#project commom include paths
include_directories(
    "${CMAKE_BINARY_DIR}/IncludeFiles"
)

#project common compiler options
set(C_CXX_COMPILER_OPTIONS
    -Ctc39xb
    --lsl-core=vtc
    -t
    -Wa-Hsfr/regtc39xb.def
    -Wa-gAHLs
    --emit-locals=-equs,-symbols
    -Wa-Ogs
    -Wa--error-limit=42
    -DBRS_COMP_TASKING
    --iso=11
    --language=-gcc,-volatile,+strings,-kanji
    --fp-model=clfznrST
    --switch=auto
    --align=0
    --default-near-size=0
    --default-a0-size=0
    --default-a1-size=0
    -O0
    --tradeoff=4
    -g
    --error-limit=42
    --source
)

#project common ssembler options
set(ASSEMBLER_OPTIONS
    -Ctc39xb
    --lsl-core=vtc 
    -Wa-Ogs
    -Wa-Hsfr/regtc39xb.def
    -Wa-gAHLs
    -t
    --emit-locals=-equs,-symbols
    --error-limit=42
)

add_compile_options(
    "$<$<COMPILE_LANGUAGE:C>:${C_CXX_COMPILER_OPTIONS}>"
    "$<$<COMPILE_LANGUAGE:ASM>:${ASSEMBLER_OPTIONS}>"
)

set(LINKER_OPTIONS
    -t
    -lrt
    -lc_fpu
    --hex-format=s
    --lsl-file=${PROJECT_ROOT_DIR}/TC39XX/_01_BSW/GEN/Source/vLinkGen_Template.lsl
    --user-provided-initialization-code
)

add_link_options(${LINKER_OPTIONS})

# Tasking run stamp setup
add_custom_target(
    TASKING_RUN_STAMP ALL
)

add_custom_target(
    copy-compile-commands ALL
    ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${PROJECT_ROOT_DIR}
    COMMENT "Update compile commands.json"
)

# project
project(${PROJECT_NAME} LANGUAGES C ASM CXX)

setup_toolchain()

get_property(target GLOBAL PROPERTY BUILD_TARGET)

if(NOT DEFINED TARGET_NAME)
    set(TARGET_NAME ${target})
endif()

if(DEFINED BUILD_FORMAL_VERSION)
    set(BUILD_FORMAL_VERSION "BUILD_FORMAL_VERSION")
endif()

if(DEFINED BUILD_PREBURN_VERSION_V2)
    set(BUILD_PREBURN_VERSION_V2 "BUILD_PREBURN_VERSION_V2")
endif()

string(REGEX MATCH ".*BUILD_FUNCTEST_VERSION.*" ENABLE_FACTORY_AND_PREBURN_MACRO "${PRESET_DEFINITIONS}")
if(ENABLE_FACTORY_AND_PREBURN_MACRO)
    set(BUILD_FACTORY_VERSION "BUILD_FACTORY_VERSION")
    set(BUILD_PREBURN_VERSION_V2 "BUILD_PREBURN_VERSION_V2")
endif()

if(DEFINED ETHTRCV_ENABLE_AUTO_POLARITY)
    set(ETHTRCV_ENABLE_AUTO_POLARITY "ETHTRCV_ENABLE_AUTO_POLARITY")
endif()

add_executable(${TARGET_NAME} ${COMMON_SOURCES} ${TARGET_SOURCES})
add_dependencies(${TARGET_NAME} TASKING_RUN_STAMP copy-compile-commands)
target_include_directories(${TARGET_NAME} PUBLIC ${TARGET_INCLUDES})
target_compile_definitions(${TARGET_NAME} PUBLIC ${TARGET_DEFINITIONS} ${PRESET_DEFINITIONS}
    ${BUILD_FORMAL_VERSION}
    ${BUILD_PREBURN_VERSION_V2}
    ${BUILD_FACTORY_VERSION}
    ${ETHTRCV_ENABLE_AUTO_POLARITY}
)

add_extra_outputs(${TARGET_NAME})
#Used for queck access.

string(REPLACE "/" "\\" CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR})
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "${CMAKE_BINARY_DIR}\\${TARGET_NAME}.elf"
    # COMMAND python ${CMAKE_SOURCE_DIR}/../scripts/os_Task_StacKUsage.py ${CMAKE_BINARY_DIR} ${CUSTOMER_DIRNAME} ${TARGET_NAME}
    # COMMAND python ${CMAKE_SOURCE_DIR}/../scripts/BinProcess.py ${CMAKE_BINARY_DIR}/${TARGET_NAME}.hex ${PROJECT_NAME} ${PLATFORM_CODE} ${CUSTOMER_ID} ${APP_MARK} ${BUILD_PREBURN_VERSION_V2}
)