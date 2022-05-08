#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)

int main(int argc, char* argv[])
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);


    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(8000);

    bind(listener, (SOCKADDR*)&addr, sizeof(addr));

    listen(listener, 5);
    SOCKET client = accept(listener, NULL, NULL);

    FILE* chaoTXT;
    FILE* clientTXT;
    char c[256];

    chaoTXT = fopen("C:\\Users\\nguye\\chao.txt", "r");
    clientTXT = fopen("C:\\Users\\nguye\\client.txt", "a");

    fgets(c, sizeof(c), chaoTXT);
    send(client, c, sizeof(c), 0);


    while (1)
    {
        char msg[1000];
        int ret = recv(client, msg, sizeof(msg), 0);
        if (ret <= 0)
        {
            system("pause");
            return 1;
        }
        if (ret < 1000)
            msg[ret] = 0;
        fprintf(clientTXT, "%s\n", msg);
    }

    fclose(chaoTXT);
    fclose(clientTXT);

    closesocket(client);
    closesocket(listener);
    WSACleanup();
}