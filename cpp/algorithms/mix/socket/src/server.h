#ifndef SERVER_H
#define SERVER_H

#include <WinSock2.h>
#include <cstring>
#include <string>
#include <iostream>
#include "./client.h"
#ifndef PORT
#define PORT 8080
#endif


#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib, "ws2_32.lib")

class Server
{
    public:
    Server();
    int Send(int & tmp);
    Point * recv();
    ~Server();

    private:

    Point ptr;
    void StartChatting();
    SOCKET serv;
    sockaddr_in serv_data;


};



Server::Server()
{
    WORD version = MAKEWORD(2,2);
    WSADATA wsa;
    if (WSAStartup(version, &wsa) != 0)
    {
        std::cerr<<"Init winsock failed\n";
        std::exit(1);
    }

    serv = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in server_info;
    server_info.sin_family = AF_INET;
    server_info.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    server_info.sin_port = htons(PORT);

    if (bind(serv, (sockaddr*)&server_info, sizeof(server_info)) == SOCKET_ERROR)
    {
        std::cerr<<"Error bind to IP address...\n";
        std::exit(1);
    }

    StartChatting();

}

int Server::Send(int & tmp)
{
    int size = sizeof(serv_data);
    int res = sendto(serv, reinterpret_cast<const char*>(tmp), sizeof(int), 0, (sockaddr*)&serv_data, size);
    return res;
}

Point * Server::recv()
{
    int size = sizeof(serv_data);
    Point * new_point = new Point;
    int res = recvfrom(serv, reinterpret_cast<char*>(new_point), sizeof(new_point), 0, (sockaddr*)&serv_data, &size);
    if (res != SOCKET_ERROR)
    {
        return new_point;
    }
    else
    {
        return NULL;
    }
}




void Server::StartChatting()
{
    Point *x = new Point;
    char buff[10];
    int size = sizeof(serv_data);
    recvfrom(serv, buff, 10, 0, (sockaddr*)&serv_data, &size);
    while (true)
    {
        x = recv();
        std::cout<<"Received numbers are: "<< x->x << " and "<<x->y<<'\n';
        int tmp = x->x + x->y;
        std::cout<<"Summ is: "<<tmp<<'\n';
    }
    delete x;
}

Server::~Server()
{
    std::cout<<"Session closed...\n";
    closesocket(serv);
    WSACleanup();
}


#endif