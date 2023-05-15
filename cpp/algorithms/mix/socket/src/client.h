#ifndef CLIENT_H
#define CLIENT_H
#ifndef PORT
#define PORT 8080 // to connect server
#endif

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#include <cstring>
#include <string>

#pragma comment(lib, "ws2_32.lib")

struct Point
{
    int x;
    int y;
    Point(const Point & point)
    {
        this->x = point.x;
        this->y = point.y; 
    }
    Point() = default;
    Point & operator=(const Point& point)
    {
        x = point.x;
        y = point.y;
        return *this;
    }
};

class Client
{
    public:
    Client();
    ~Client();
    int recv();
    int Send(Point * ptr);
    void StartChatting();
    private:
    SOCKET sock;
    sockaddr_in server;
};


Client::Client()
{
    WORD ver = MAKEWORD(2,2);
    WSADATA wsa;
    if (WSAStartup(ver, &wsa) == SOCKET_ERROR)
    {
        std::cerr<<"Error init. winsock...\n";
        return;
    }

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock == INVALID_SOCKET)
    {
        std::cerr<<"Error creating socket...\n";
        Client::~Client();
    }

    // server info
    server.sin_family = AF_INET;
    server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(PORT);

    int result = connect(sock, (sockaddr*)&server, sizeof(server));
    if (result == SOCKET_ERROR)
    {
        std::cerr<<"Could't connect to server...\n";
        Client::~Client();
    }

    StartChatting();
    
}

Client::~Client()
{
    closesocket(sock);
    WSACleanup();
}



void Client::StartChatting()
{
    Point * point = new Point;
    char buffer[10];
    sendto(sock, buffer, 10, 0, (sockaddr*)&server, sizeof(server));
    while (1)
    {
        std::cout<<"Enter X: ";
        std::cin >> point->x;
        std::cout<<"Enter Y: ";
        std::cin >> point->y;
        Send(point);
        
    }
    delete point;
    
}


int Client::Send(Point * ptr)
{
    int ptr_size = sizeof(ptr);
    int server_size = sizeof(server);
    int res = sendto(sock, reinterpret_cast<const char*>(ptr), ptr_size, 0, (sockaddr*)&server, sizeof(server));
    return res;
}

int Client::recv()
{
    int sum;
    int size = sizeof(server);
    int res = recvfrom(sock, reinterpret_cast<char*>(sum), sizeof(sum), 0, (sockaddr*)&server, &size);
    if (res != -1)
    {
        return sum;
    }
    else 
    {
        return 0;
    }
}



#endif