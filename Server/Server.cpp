#include "Server.h"

Server::Server()
{
}

void threadProgress(HANDLE hPipe)
{
	DWORD cbBytesRead = 0, cbReplyBytes = 0, cbWritten = 0; 
	BOOL fSuccess = FALSE;

	char buffer[BUFFER_SIZE];
	
		fSuccess = ReadFile(hPipe, 
			buffer,
			BUFFER_SIZE,
			&cbBytesRead,
			nullptr);

		printf("%s", buffer);

	if(std::strcmp(buffer, "Hello\n") == 0)
	{
		int prev_color = 0;
		while(true)
		{
			srand(time(nullptr));
			int color = rand() % 4 + 1;
			while(prev_color == color)
			{
				color = rand() % 4 + 1;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			std::string tmp = "lights up" + std::to_string(color);
			printf("%s", tmp.c_str());
			prev_color = color;
			fSuccess = WriteFile(hPipe,
				tmp.c_str(),
				11,
				&cbWritten,
				nullptr);

			if(!fSuccess || cbWritten != 11)
			{
				break;
			}
		}
	}

	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);
}

void Server::run()
{
	std::cout << "Waiting for new connections ... \n";
	HANDLE hPipe = INVALID_HANDLE_VALUE;

	while(true)
	{
		std::cout << "\n Connected ... \n";
		hPipe = CreateNamedPipe(PIPE_NAME, 
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE |
			PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES,
			BUFFER_SIZE,
			BUFFER_SIZE,
			0, 
			nullptr);

		if (hPipe == INVALID_HANDLE_VALUE) 
		{
			printf("CreateNamedPipe failed, GLE=%d.\n", GetLastError()); 
			return;
		}

		BOOL fConnected = ConnectNamedPipe(hPipe, nullptr) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);
		if(fConnected)
		{
			std::thread thread(threadProgress, hPipe);
			thread.detach();
		}
		else
			CloseHandle(hPipe);
	}

}

