cmake_minimum_required(VERSION 2.8.9)
project(Thread_Concepts)

#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_STANDARD 14)
 
#Bring the headers into the project
include_directories("headers")

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)


#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.c" "src/Advanced/Thread_Cooperation/*.c" "src/Advanced/Thread_Termination/*.c" "src/Condition_Variable/*.c" "src/Examples/*.c"
"src/Mutexes/*.c" "src/Semaphores/*.c" "src/Thread_Management/*.c")

file(GLOB INCLUDES "headers/*.h")

add_executable(Thread_Concepts_Executable ${SOURCES} ${INCLUDES})

target_link_libraries(Thread_Concepts_Executable Threads::Threads)