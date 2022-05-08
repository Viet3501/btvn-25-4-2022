#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)

int main(int argc, char* argv[])
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(8000);

    system("pause");

    int ret = connect(client, (SOCKADDR*)&addr, sizeof(addr));
    if (ret == SOCKET_ERROR)
    {
        ret = WSAGetLastError();
        printf("Ket noi khong thanh cong - %d\n", ret);
        return 1;
    }

    char c[1000];

    ret = recv(client, c, sizeof(c), 0);
    if (ret <= 0)
        printf("Lỗi");


    printf("Noi dung tu server: %s\n", c);

    while (1)
    {
        char msg[1000];
        printf("Nhap noi dung gui cho server: ");
        scanf("%s", &msg);
        send(client, msg, strlen(msg), 0);
    }

    closesocket(client);
    WSACleanup();
}