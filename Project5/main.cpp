#include <iostream>
#include <WS2tcpip.h>


#pragma comment (lib, "ws2_32.lib")

using namespace std;



void main()
{

	//Initialize winsock
	WSADATA wsData;

	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);

	if (wsOk != 0)
	{
		cerr << "Can't initialize winsock! Quiting" << endl;
		return;

	}

	//create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << "Cant create a socket! Quitting" << endl;
		return;
	}

	//Bind the ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	//Tell Winsock the socket is for listening
	listen(listening, SOMAXCONN);
	//Wait for connection
	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST];			//client's remost name
	char service[NI_MAXHOST];		//Service (i.e. port) the client is connect on

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXHOST);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		cout << host << "connected on port" << service << endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << " connected on port" << ntohs(client.sin_port) << endl;
	}
	//Close listening socket
	closesocket(listening);
	//While loop: accept and echo message back to client 

	char buf[4096];

	while (true)
	{
		ZeroMemory(buf, 4096);
		//Wait for client to send data

		int bytesReceived = recv(clientSocket, buf, 4096, 0);
		if (bytesReceived == SOCKET_ERROR)
		{
			cerr << "Error in recv(). Quitting" << endl;
			break;
		}

		if (bytesReceived == 0)
		{
			cout << "Client Disconnected" << endl;
			break;
		}

		send(clientSocket, buf, bytesReceived + 1, 0);

		// Echo message back to client
	}
	//close the socket
	closesocket(clientSocket);



	//CleanUp winsock
	WSACleanup();
}
