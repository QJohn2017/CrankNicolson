project(CrankNicolson)

cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
add_definitions(-DAS_USE_STLNAMES=1)
add_definitions(-DAS_CAN_USE_CPP11)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)


set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost REQUIRED COMPONENTS system filesystem python program_options)
find_package(PythonLibs REQUIRED)


include_directories(${Boost_INCLUDE_DIR})
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES} ${Boost_LIBRARIES})
