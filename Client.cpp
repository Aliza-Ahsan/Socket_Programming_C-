#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;

int main()
{
    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket == -1)
    {
        cerr << "Error creating socket" << endl;
        return 1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080); // Port number
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    while (true)
    {
        char message[1024];
        cout << "\nEnter a message to send to the server ('exit' to quit): ";
        cin.getline(message, sizeof(message));

        if (strcmp(message, "exit") == 0)
        {
            break;
        }

        sendto(clientSocket, message, strlen(message), 0, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

        char buffer[1024];
        socklen_t serverAddrLen = sizeof(serverAddress);
        int bytesRead = recvfrom(clientSocket, buffer, sizeof(buffer), 0, (struct sockaddr *)&serverAddress, &serverAddrLen);
        if (bytesRead > 0)
        {
            buffer[bytesRead] = '\0';
            cout << "\nReceived from server: " << buffer << endl;
        }
        else
        {
            cout << "\nSERVER IS DOWN / ERROR !" << endl;
            break;
        }
    }

    close(clientSocket);

    return 0;
}
