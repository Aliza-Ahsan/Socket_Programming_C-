
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <chrono>
#include <ctime>
#include <thread>
using namespace std;

// Function to get the current timestamp as a string
string getCurrentTimestamp() {
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    return ctime(&currentTime);
}

// func for handling individal client
void handleClient(int clientSocket){
    while (true)
        {   char buffer[1024];
            int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesRead <= 0)
            {
                cout << "\nCONNECTION CLOSED / ERROR !" << endl;
                break;
            }

            buffer[bytesRead] = '\0';
            //cout << "\nReceived from client: " << buffer << endl;
            cout << "\nReceived at server at "<< getCurrentTimestamp()<<"\n"<<buffer << endl;
            
            char response[1024];
            cout << "\nEnter a message to send to the client:  ";
            cin.getline(response, sizeof(response));

            //Get current time
            string timestamp= getCurrentTimestamp();
            timestamp = timestamp.substr(0, timestamp.length()-1);

            //append
            string responseWithTimestamp = "Time sent from Server: " + timestamp + "\n with message : " + response;

            send(clientSocket, responseWithTimestamp.c_str(), responseWithTimestamp.length(), 0);
        }
        close(clientSocket);
}

int main()
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        cout << "Error creating socket" << endl;
        return 1;
    }

    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
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

    if (listen(serverSocket, 5) == -1)
    {
        cout << "Error listening" << endl;
        return 1;
    }

    cout << "Server listening on port 8080..." << endl;
    
    while (true)
    {
        sockaddr_in clientAddress;
        socklen_t clientAddressSize = sizeof(clientAddress);

        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressSize);
        if (clientSocket == -1)
        {
            cout << "Error accepting connection" << endl;
            continue;
        }

        cout << "Connection established with client" << endl;
        thread multiClient(handleClient,clientSocket);
        multiClient.detach();
        

        
    }

    close(serverSocket);

    return 0;
}
