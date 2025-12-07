# *********** Add C/ASM files,recursion mode, ***********
file(GLOB_RECURSE COMMON_SOURCES
    ${PROJECT_ROOT_DIR}/BSW_Config/*.c
    ${PROJECT_ROOT_DIR}/Mcal_config/*.c
    ${PROJECT_ROOT_DIR}/TC39XX/_00_ASW/*.c
    ${PROJECT_ROOT_DIR}/TC39XX/_01_BSW/*.c
    ${PROJECT_ROOT_DIR}/TC39XX/_02_CDD/*.c
    ${PROJECT_ROOT_DIR}/TC39XX/_03_MCAL/*.c
    ${PROJECT_ROOT_DIR}/TC39XX/_04_StartUp/*.c
    ${PROJECT_ROOT_DIR}/BSW_Config/*.asm
    ${PROJECT_ROOT_DIR}/Mcal_config/*.asm
    ${PROJECT_ROOT_DIR}/TC39XX/_00_ASW/*.asm
    ${PROJECT_ROOT_DIR}/TC39XX/_01_BSW/*.asm
    ${PROJECT_ROOT_DIR}/TC39XX/_02_CDD/*.asm
    ${PROJECT_ROOT_DIR}/TC39XX/_03_MCAL/*.asm
    ${PROJECT_ROOT_DIR}/TC39XX/_04_StartUp/*.asm
)
# *********** AddC/ASM fileS, NOT recursion mode. ***********
# file(GLOB LOCAL_COMMON_SOURCES
#     ${PROJECT_ROOT_DIR}/ASW/*.c
# )
# list(APPEND COMMON_SOURCES ${LOCAL_COMMON_SOURCES})

# ***********  define usercode ***********
# file(GLOB_RECURSE USER_SOURCES ${PROJECT_ROOT_DIR}/ASW/*.c ${PROJECT_ROOT_DIR}/CDD/*.c)
# set(EXCLUDED_DIR1 ${PROJECT_ROOT_DIR}/CDD/CDD_FpgaEfuse/Jtag)
# set(EXCLUDED_DIR2 ${PROJECT_ROOT_DIR}/CDD/CDD_HSM/CycurHsm)
# set(EXCLUDED_DIR3 ${PROJECT_ROOT_DIR}/CDD/CDD_HSM/third)
# list(FILTER USER_SOURCES EXCLUDE REGEX ${EXCLUDED_DIR1}|${EXCLUDED_DIR2}|${EXCLUDED_DIR3})

# *********** Copy H files to certain directory,recursion mode ***********
file(GLOB_RECURSE header_files "${PROJECT_ROOT_DIR}/BSW_Config/*.h")
file(COPY ${header_files} DESTINATION "${CMAKE_BINARY_DIR}/IncludeFiles")

file(GLOB_RECURSE header_files "${PROJECT_ROOT_DIR}/Mcal_config/*.h")
file(COPY ${header_files} DESTINATION "${CMAKE_BINARY_DIR}/IncludeFiles")

file(GLOB_RECURSE header_files "${PROJECT_ROOT_DIR}/TC39XX/_00_ASW/*.h")
file(COPY ${header_files} DESTINATION "${CMAKE_BINARY_DIR}/IncludeFiles")

file(GLOB_RECURSE header_files "${PROJECT_ROOT_DIR}/TC39XX/_01_BSW/*.h")
file(COPY ${header_files} DESTINATION "${CMAKE_BINARY_DIR}/IncludeFiles")

file(GLOB_RECURSE header_files "${PROJECT_ROOT_DIR}/TC39XX/_02_CDD/*.h")
file(COPY ${header_files} DESTINATION "${CMAKE_BINARY_DIR}/IncludeFiles")

file(GLOB_RECURSE header_files "${PROJECT_ROOT_DIR}/TC39XX/_03_MCAL/*.h")
file(COPY ${header_files} DESTINATION "${CMAKE_BINARY_DIR}/IncludeFiles")

file(GLOB_RECURSE header_files "${PROJECT_ROOT_DIR}/TC39XX/_04_StartUp/*.h")
file(COPY ${header_files} DESTINATION "${CMAKE_BINARY_DIR}/IncludeFiles")
# *********** Copy H files to certain directory,NOT recursion mode ***********
# file(GLOB header_files "${PROJECT_ROOT_DIR}/CustomerConfig/${CUSTOMER_DIRNAME}/BasicSoftware/*.h")
# file(COPY ${header_files} DESTINATION "${CMAKE_BINARY_DIR}/IncludeFiles")

# *********** Define Common Macro ***********
# target specific preprocessor definitions
add_compile_definitions(
    BUILD_BIP
)