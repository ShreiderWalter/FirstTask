#include "Server.h"

/*int main()
{
	std::thread thread(&Server::run, Server());
	thread.detach();

	return 0;
}*/

/** Win Service API */
SERVICE_STATUS_HANDLE g_ServiceStatusHandle;
HANDLE g_StopEvent;
DWORD g_CurrentState = 0;
bool g_SystemShutdown = false;

void ReportStatus(DWORD state)
{
	g_CurrentState = state;
	SERVICE_STATUS serviceStatus = 
	{
		SERVICE_WIN32_OWN_PROCESS,
		g_CurrentState,
		state == SERVICE_START_PENDING ? 0 : SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN,
		NO_ERROR,
		0,
		0,
		0,
	};
	SetServiceStatus(g_ServiceStatusHandle, &serviceStatus);
}

void ReportProgressStatus(DWORD state, DWORD checkPoint, DWORD waitHint)
{
	g_CurrentState = state;
	SERVICE_STATUS serviceStatus = 
	{
		SERVICE_WIN32_OWN_PROCESS,
		g_CurrentState,
		state == SERVICE_START_PENDING ? 0 : SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN,
		NO_ERROR,
		0,
		checkPoint,
		waitHint,
	};
	SetServiceStatus(g_ServiceStatusHandle, &serviceStatus);
}

void ReportErrorStatus(DWORD errorCode)
{
	g_CurrentState = SERVICE_STOPPED;
	SERVICE_STATUS serviceStatus = 
	{
		SERVICE_WIN32_OWN_PROCESS,
		g_CurrentState,
		0,
		ERROR_SERVICE_SPECIFIC_ERROR,
		errorCode,
		0,
		0,
	};
	SetServiceStatus(g_ServiceStatusHandle, &serviceStatus);
}

DWORD WINAPI HandlerEx(DWORD control, DWORD eventType, void *eventData, void *context)
{
	switch (control)
	{
		// Entrie system is shutting down.
	case SERVICE_CONTROL_SHUTDOWN:
		g_SystemShutdown = true;

	case SERVICE_CONTROL_STOP:
		ReportStatus(SERVICE_STOP_PENDING);
		SetEvent(g_StopEvent);
		break;
		// Ignoring all other events, but we must always report service status.
	default:
		ReportStatus(g_CurrentState);
		break;
	}
	return NO_ERROR;
}

void WINAPI ServiceMain(DWORD argc, LPTSTR * argv)
{
	g_ServiceStatusHandle = RegisterServiceCtrlHandlerEx(_T("NewYearGarland"), &HandlerEx, NULL);
	ReportStatus(SERVICE_START_PENDING);
	g_StopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	Server server;
	HANDLE hPipe = CreateNamedPipe(PIPE_NAME, 
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE |
		PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		BUFFER_SIZE,
		BUFFER_SIZE,
		0, 
		nullptr);

	ReportStatus(SERVICE_RUNNING);

	DWORD cbBytesRead = 0, cbReplyBytes = 0, cbWritten = 0; 
	BOOL fSuccess = FALSE;
	char buffer[BUFFER_SIZE];
	while(!fSuccess)
	{
		fSuccess = ReadFile(hPipe, 
			buffer,
			BUFFER_SIZE,
			&cbBytesRead,
			nullptr);
	}

	ReportStatus(SERVICE_STOP_PENDING);

	CloseHandle(g_StopEvent);

	ReportStatus(SERVICE_STOPPED);	
}

int main(int argc, char* argv[])
{

	SERVICE_TABLE_ENTRY serviceTable[] =
	{
		{ _T(""), &ServiceMain },
		{ nullptr, nullptr }
	};

	if (StartServiceCtrlDispatcher(serviceTable))
	{
		return 0;
	}
	else if (GetLastError() == ERROR_FAILED_SERVICE_CONTROLLER_CONNECT)
	{
		return -1;
	}
	else
	{
		return -2;
	}
}
