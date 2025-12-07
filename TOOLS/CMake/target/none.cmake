# *********** Add C/ASM files,recursion mode ***********
# file(GLOB_RECURSE TARGET_SOURCES
#     ${PROJECT_ROOT_DIR}/CustomerConfig/${CUSTOMER_DIRNAME}/*.c
#     ${PROJECT_ROOT_DIR}/customerconfig/${CUSTOMER_DIRNAME}/*.asm
# )
# *********** Add C/ASM files,NOT recursion mode ***********
# file(GLOB LOCAL_COMMON_SOURCES
#     ${PROJECT_ROOT_DIR}/CustomerConfig/${CUSTOMER_DIRNAME}/Basicsoftware/*.c
#     ${PROJECT_ROOT_DIR}/customerconfig/${CUSTOMER_DIRNAME}/Basicsoftware/*.asm
# )
# liSt(APPEND COMMON_SOURCES ${LOCAL_COMMON_SOURCES})

# *********** Copy H files to certain directory,recursion mode ***********
# file(GLOB_RECURSE header_files "${PROJECT_ROOT_DIR}/CustomerConfig/${CUSTOMER_DIRNAME}/*.h")
# file(COPY ${header_files} DESTINATION "${CMAKE_BINARY_DIR}/IncludeFiles")

# file(GLOB_RECURSE header_files "${PROJECT_ROOT_DIR}/ASW/*.inc")
# file(COPY ${header_files} DESTINATION "${CMAKE_BINARY_DIR}/IncludeFiles")

# *********** Copy H files to certain directory, NoT recurvion mode. ***********
# file(GLOB header_files. "${PROJECT_ROOT_DIR}/CustomerConfig/${CUSTOMER_DIRNAME}/Basicsoftware/*.h")
# file(COPY ${header_files} DESTINATION "${CMAKE_BINARY_DIR}/IncludeFiles")
# target specific preprocessor definitions
set(TARGET_DEFINITIONS
    "HT_CUSTOMER_PLATFORM"
)
# *********** Define OmmOn MaCro ***********
# target specific preprocessor definitions
# set(TARGET_DEFINITIONS
#     "MACRO_TEST"
# )
