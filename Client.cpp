
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <chrono>
#include <ctime>
#include<arpa/inet.h>
using namespace std;

// Function to get the current timestamp as a string
string getCurrentTimestamp() {
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    return ctime(&currentTime);
}

int main()
{
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1)
    {
        cerr << "Error creating socket" << endl;
        return 1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET; //
    serverAddress.sin_port = htons(8080); // Port number
    //on running multiclietn, comment this
    //serverAddress.sin_addr.s_addr = INADDR_ANY; // replace with server's IP address will come here
    

    //we get ip address from the wifi/hotspot and make changes to this "127..."
    if(inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr)<=0)
    {
        perror("Invalid IP Address");
    }

    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
    {
        cerr << "Connection failed" << endl;
        return 1;
    }

    while (true)
    {
        char message[1024];
        cout << "\nEnter a message to send to the server ('exit' to quit): ";
        cin.getline(message, sizeof(message));

        if (strcmp(message, "exit") == 0)
        {
            break;
        }

        // Get the current timestamp
        string timestamp = getCurrentTimestamp();
        timestamp = timestamp.substr(0, timestamp.length() - 1); // Remove newline

        // Append the timestamp to the message
        string messageWithTimestamp = "Time sent from client: " + timestamp + "\n with message:  " + message;
        
        

        send(clientSocket, messageWithTimestamp.c_str(), messageWithTimestamp.length(), 0);

        char buffer[1024];
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead > 0)
        {
            buffer[bytesRead] = '\0';
            cout << "\nReceived at client at: " << getCurrentTimestamp() << "\n" << buffer << endl;
        }
        else{
            cout << "\nSERVER IS DOWN / ERROR !" << endl;
            break;
        }
    }
    close(clientSocket);

    return 0;
}
