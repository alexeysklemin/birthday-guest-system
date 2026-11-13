// src/server/chat_service.cpp 
#include "server/chat_service.h"

#include <iostream>

// Реализация метода GetData
grpc::Status GuestServiceImpl::GetData(grpc::ServerContext* /*context*/,
                                       const chat::DataRequest* /*request*/,
                                       chat::DataResponse* response)
{
    std::cout << "[SERVER] Вызван метод GetData!\n";
    
    // Тут пока ничего не делаем, просто возвращаем ОК.
    // Если в DataResponse есть поля, можно их заполнить:
    // response->set_some_field("test");

    return grpc::Status::OK;
}