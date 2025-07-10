cmake_minimum_required(VERSION 3.16)

set(CMAKE_ASM_NASM_COMPILER "E:/comp/usr/bin/nasm.exe")
set(CMAKE_C_COMPILER "E:/comp/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "E:/comp/mingw64/bin/g++.exe")

project(AthenaOS ASM_NASM C CXX)

# Флаги 
set(CMAKE_C_FLAGS "-m32 -ffreestanding -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fno-exceptions -fno-rtti -fno-use-cxa-atexit")
set(CMAKE_EXE_LINKER_FLAGS "-m32 -nostdlib -T ${CMAKE_SOURCE_DIR}/link.ld -Wl,--build-id=none")
set(CMAKE_C_FLAGS_DEBUG "")
set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_C_FLAGS_RELEASE "")
set(CMAKE_CXX_FLAGS_RELEASE "")

include_directories(${CMAKE_SOURCE_DIR}/sys/kernel/include)




set(BOOTLOADER_ASM ${CMAKE_SOURCE_DIR}/sys/boot/simple_boot.asm)
add_custom_command(
    OUTPUT boot.bin
    COMMAND ${CMAKE_ASM_NASM_COMPILER} -f bin ${BOOTLOADER_ASM} -o ${CMAKE_BINARY_DIR}/boot.bin
    DEPENDS ${BOOTLOADER_ASM}
    COMMENT "Building bootloader"
)

if(EXISTS ${CMAKE_SOURCE_DIR}/sys/kernel/src/entry.asm)
    set(KERNEL_ENTRY_ASM ${CMAKE_SOURCE_DIR}/sys/kernel/src/entry.asm)
    add_custom_command(
        OUTPUT entry.o
        COMMAND ${CMAKE_ASM_NASM_COMPILER} -f elf32 ${KERNEL_ENTRY_ASM} -o ${CMAKE_BINARY_DIR}/entry.o
        DEPENDS ${KERNEL_ENTRY_ASM}
        COMMENT "Building kernel entry"
    )
    set(ENTRY_OBJECT ${CMAKE_BINARY_DIR}/entry.o)
endif()

set(KERNEL_SOURCES
    ${CMAKE_SOURCE_DIR}/kernel/src/main.cpp
    ${CMAKE_SOURCE_DIR}/kernel/src/commands.cpp
    ${CMAKE_SOURCE_DIR}/kernel/src/video.cpp
    ${CMAKE_SOURCE_DIR}/kernel/src/shell.cpp
    ${CMAKE_SOURCE_DIR}/kernel/src/ports.cpp
    ${CMAKE_SOURCE_DIR}/kernel/src/keyboard.cpp
)



add_executable(kernel.elf ${KERNEL_SOURCES})


# Запуск в QEMU
add_custom_target(run
    COMMAND qemu-system-i386 -fda ${CMAKE_BINARY_DIR}/athena.img
    DEPENDS athena.img
    COMMENT "Running Athena OS in QEMU"
)

# Отладка
add_custom_target(debug
    COMMAND qemu-system-i386 -fda ${CMAKE_BINARY_DIR}/athena.img -s -S
    DEPENDS athena.img
    COMMENT "Running Athena OS in QEMU with GDB server"
)