#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;

int main()
{
    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocket == -1)
    {
        cout << "Error creating socket" << endl;
        return 1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080); // Port number

    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
    {
        cout << "Error binding" << endl;
        return 1;
    }

    cout << "Server listening on port 8080..." << endl;

    while (true)
    {
        sockaddr_in clientAddress;
        socklen_t clientAddressSize = sizeof(clientAddress);

        char buffer[1024];
        int bytesRead = recvfrom(serverSocket, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientAddress, &clientAddressSize);

        if (bytesRead <= 0)
        {
            cout << "\nCONNECTION CLOSED / ERROR !" << endl;
            continue;
        }

        buffer[bytesRead] = '\0';
        cout << "\nReceived from client: " << buffer << endl;

        char response[1024];
        cout << "\nEnter a message to send to the client: ";
        cin.getline(response, sizeof(response));

        sendto(serverSocket, response, strlen(response), 0, (struct sockaddr *)&clientAddress, sizeof(clientAddress));
    }

    close(serverSocket);

    return 0;
}
