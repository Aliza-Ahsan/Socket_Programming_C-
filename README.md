# C++ Socket Program with Multithreading

## Overview

This is a simple C++ socket program that demonstrates a basic server-client communication model using sockets. The server is capable of handling multiple client connections concurrently through multithreading.

## Features

- **Server-Client Communication**: The server listens for incoming connections and exchanges messages with connected clients.

- **Multithreading**: The server uses multithreading to handle multiple client connections simultaneously.

## Prerequisites

- C++ compiler with C++11 support
- [Optional] Virtual Machine (e.g., VMware Workstation) for hosting the server

## How to Run

### Server

1. **Compile the Server Code**:
   ```bash
   g++ server.cpp -o server -pthread
   ```

2. **Run the Server**:
   ```bash
   ./server
   ```
   The server will start listening for incoming connections.

### Client
1. **Compile the Client Code**:
   ```bash
   g++ client.cpp -o server -pthread
   ```

2. **Run the Server**:
   ```bash
   ./client
   ```
  You can split more terminals and run multiple clients. 

## Configuration

- **Server Configuration**: You can configure the server settings, such as the port number and the number of threads, in the `server.cpp` file.

## Example Usage

1. Compile and run the server on your virtual host.

2. Compile and run the client on your local machine.

3. Connect to the server using the client and exchange messages.

## Troubleshooting

- **Port Availability**: Ensure that the specified port is not blocked by a firewall, and it's available for use.

- **Network Configuration**: Verify the network settings on your virtual machine to allow incoming connections.


## Contributing

Feel free to contribute to the project. Create a fork, make your changes, and submit a pull request.

## Author

Aliza Ahsan

## Contact

Alizaaliza253@Gmail.com

---
