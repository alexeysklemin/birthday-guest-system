// inc/server/chat_service.h
#pragma once

#include <grpcpp/grpcpp.h>
#include <google/protobuf/arena.h>
#include "Chat.grpc.pb.h"       

class GuestServiceImpl final : public chat::RegService::Service
{
public:
    // Конструктор
    GuestServiceImpl() {}

    // Метод строго по контракту: rpc GetData (DataRequest) returns (DataResponse)
    grpc::Status GetData(grpc::ServerContext* context,
                         const chat::DataRequest* request,
                         chat::DataResponse* response) override;

private:
    chat::GuestList* list_;   // данные пришли извне, сервер ими не владеет
};