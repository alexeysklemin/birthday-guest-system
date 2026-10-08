#Root CMakeLists.txt

cmake_minimum_required(VERSION 3.23)
project(
    birthday-guest-system
    VERSION 0.0.1
    LANGUAGES CXX
    DESCRIPTION "studing pet-project with protobuf and gRPC"
)

set(CMAKE_CXX_STANDARD 20)  
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 1. Ищем Protobuf и gRPC 
find_package(Protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED) # Подключаем модули gRPC для CMake
find_package(gRPC REQUIRED)
# Находим плагин для генерации gRPC кода
find_program(GRPC_CPP_PLUGIN grpc_cpp_plugin REQUIRED)

# 2. Находим все .proto файлы
file(GLOB PROTO_FILES "${CMAKE_CURRENT_SOURCE_DIR}/proto/*.proto")

# 3. Генерируем обычные .pb файлы (для данных)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

# 4. Генерируем .grpc.pb файлы (для сетевого сервиса)
set(GRPC_SRCS "")
set(GRPC_HDRS "")
foreach(PROTO_FILE ${PROTO_FILES})
    get_filename_component(PROTO_NAME ${PROTO_FILE} NAME_WE)
    
    add_custom_command(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${PROTO_NAME}.grpc.pb.cc"
               "${CMAKE_CURRENT_BINARY_DIR}/${PROTO_NAME}.grpc.pb.h"
        COMMAND protobuf::protoc
        ARGS --grpc_out="${CMAKE_CURRENT_BINARY_DIR}"
             --plugin=protoc-gen-grpc="${GRPC_CPP_PLUGIN}"
             -I "${CMAKE_CURRENT_SOURCE_DIR}/proto"
             "${PROTO_FILE}"
        DEPENDS "${PROTO_FILE}"
        COMMENT "Generating gRPC code for ${PROTO_NAME}.proto"
    )
    
    list(APPEND GRPC_SRCS "${CMAKE_CURRENT_BINARY_DIR}/${PROTO_NAME}.grpc.pb.cc")
    list(APPEND GRPC_HDRS "${CMAKE_CURRENT_BINARY_DIR}/${PROTO_NAME}.grpc.pb.h")
endforeach()

# 5. Находим исходники C++
file(GLOB FILE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# 6. Создаем исполняемый файл
add_executable(birthday-guest-system 
    ${FILE_SRC} 
    ${PROTO_SRCS} 
    ${PROTO_HDRS}
    ${GRPC_SRCS}   # <-- Добавляем сгенерированные gRPC файлы
    ${GRPC_HDRS}
)

# 7. Подключаем заголовочные файлы
target_include_directories(birthday-guest-system PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}        # Здесь лежат сгенерированные .h файлы
    ${Protobuf_INCLUDE_DIRS}
    ${gRPC_INCLUDE_DIRS}
)

# 8. Линкуем библиотеки
target_link_libraries(birthday-guest-system PRIVATE 
    protobuf::libprotobuf
    gRPC::grpc++
    gRPC::grpc
    pthread                            # В Linux gRPC требует потоки
)