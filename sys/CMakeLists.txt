cmake_minimum_required(VERSION 3.16)
project(AthenaOS)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR i386)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(CMAKE_C_FLAGS "-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -ffreestanding")
set(CMAKE_CXX_FLAGS "-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -fno-exceptions -fno-rtti -ffreestanding")
set(CMAKE_EXE_LINKER_FLAGS "-m32 -nostdlib -nostartfiles -nodefaultlibs -T${CMAKE_SOURCE_DIR}/multiboot.ld")

set(CMAKE_C_STANDARD_LIBRARIES "")
set(CMAKE_CXX_STANDARD_LIBRARIES "")

# Исходные файлы C++
set(KERNEL_SOURCES
    kernel/src/main.cpp
    kernel/src/video.cpp
    kernel/src/shell.cpp
    kernel/src/ports.cpp
    kernel/src/keyboard.cpp
)

# Компиляция ASM
add_custom_command(
    OUTPUT boot.o
    COMMAND nasm -f elf32 -o boot.o ${CMAKE_SOURCE_DIR}/boot/boot.asm
    DEPENDS ${CMAKE_SOURCE_DIR}/boot/boot.asm
    COMMENT "Compiling multiboot boot.asm"
)

# Создание ядра
add_executable(kernel.elf ${KERNEL_SOURCES})
target_include_directories(kernel.elf PRIVATE kernel/include)
target_link_libraries(kernel.elf ${CMAKE_CURRENT_BINARY_DIR}/boot.o)
set_target_properties(kernel.elf PROPERTIES SUFFIX "")

add_custom_target(boot_asm DEPENDS boot.o)
add_dependencies(kernel.elf boot_asm)

add_custom_target(run
    COMMAND qemu-system-i386 -kernel kernel.elf
    DEPENDS kernel.elf
    COMMENT "Running AthenaOS in QEMU"
)

message(STATUS "Building multiboot kernel")
