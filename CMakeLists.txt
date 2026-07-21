#CMakeLists.txt

cmake_minimum_required(3.23)
project(
    birthday-guest-system
    VERSION 0.0.1
    LANGUAGES CXX
    DESCRIPTION "studing pet-project with protobuf and gRPC"
)
set(CMAKE_CXX_STANDARD 20)  
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(protobuf CONFIG REQUIRED)

file(GLOB PROTO_FILES "${CMAKE_CURRENT_SOURCE_DIR}/proto/*.proto")
# set(PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/proto/*.proto) нужен либо file(GLOB  либо set. set не умеет в * ему нужны реальные имена файлов
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

file(GLOB FILE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(birthday-guest-system ${FILE_SRC} ${PROTO_SRCS} ${PROTO_HDRS})

target_include_directories(birthday-guest-system PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src    # исходники лежат здесь
    ${CMAKE_CURRENT_BINARY_DIR}        # Сгенерированные .pb.h лежат здесь
)

target_link_libraries(birthday-guest-system PRIVATE protobuf::libprotobuf)
