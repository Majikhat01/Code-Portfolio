cmake_minimum_required(VERSION 3.10)
project(OSHW3)

# Add source files
set(SOURCES
        Command.c
        Command.h
        deq.h
        error.h
        Interpreter.c
        Interpreter.h
        Jobs.c
        Jobs.h
        Parser.c
        Parser.h
        Pipeline.c
        Pipeline.h
        Scanner.c
        Scanner.h
        Sequence.c
        Sequence.h
        Shell.c
        Shell.h
        Tree.c
        Tree.h
)

# Set C standard to C99
set(CMAKE_C_STANDARD 99)

# Add an executable for your main project
add_executable(OSHW3 ${SOURCES})

# Specify the location of the library
target_link_directories(OSHW3 PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Link the executable with the library
target_link_libraries(OSHW3 ${CMAKE_SOURCE_DIR}/libdeq.so)