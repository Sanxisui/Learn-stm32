# Find the kernel release
execute_process(COMMAND uname -r
                OUTPUT_VARIABLE KERNEL_RELEASE
                RESULT_VARIABLE RESULT
                OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(COMMAND uname -r
                OUTPUT_VARIABLE corename
                RESULT_VARIABLE result
                OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Find the headers
string(FIND ${CMAKE_C_COMPILER} "arm-linux-gnueabihf-gcc" res)
if (res GREATER 0)
    set(ARM_KERNEL_SOURCE_PATH ~/imx6ull-14x14-evk-kernel-5.4.2.1.x/ ~/work/imx6ull-14x14-evk-kernel-5.4.2.1.x/)
endif()

find_path(KERNELHEADERS_DIR
    include/linux/user.h
    PATHS ${ARM_KERNEL_SOURCE_PATH}
    PATHS /lib/modules/${KERNEL_RELEASE}/build 
)
message(STATUS "Kernel release: ${KERNEL_RELEASE}")
message(STATUS "Kernel headers: ${KERNELHEADERS_DIR}")

if (KERNELHEADERS_DIR)
    set(KERNELHEADERS_INCLUDE_DIRS
            ${KERNELHEADERS_DIR}/include
            ${KERNELHEADERS_DIR}/arch/x86/include
            CACHE PATH "Kernel headers include dirs"
            )
    set(KERNELHEADERS_FOUND 1 CACHE STRING "Set to 1 if kernel headers were found")
else (KERNELHEADERS_DIR)
    set(KERNELHEADERS_FOUND 0 CACHE STRING "Set to 1 if kernel headers were found")
endif (KERNELHEADERS_DIR)

mark_as_advanced(KERNELHEADERS_FOUND)
