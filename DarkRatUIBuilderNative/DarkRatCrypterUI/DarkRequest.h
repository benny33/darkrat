#include <iostream>
#include <shlwapi.h>
#include <wininet.h>
#include <string>
#include "HTTPURL.h"
#include<QDebug>

using namespace std;

#pragma comment (lib, "WinInet.lib")




std::string postRequest(std::string url, std::string param, LPCSTR method = "POST")
{

	char* host;
	char* path;
	HTTPURL u(url);


	host = (char*)u.domain.c_str();
	path = (char*)u.path.c_str();

	TCHAR hdrs[] = TEXT("Content-Type: application/x-www-form-urlencoded");
	LPVOID frmdata = (LPVOID)param.c_str();
	LPCSTR accept[1] = { "text/plain" };
	HINTERNET hSession = InternetOpen(L"MyAgent", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	HINTERNET hConnect = InternetConnect(hSession, (LPCWSTR)host, INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
	HINTERNET hRequest = HttpOpenRequest(hConnect, (LPCWSTR)method, (LPCWSTR)path, NULL, NULL, (LPCWSTR*)accept, NULL, 1);



	HttpSendRequest(hRequest,
		hdrs,
		strlen((const char*)hdrs),
		frmdata, //lpOptional <--Your POST data...not really optional for you.
		strlen(param.c_str()));

		//DWORD errorCode = GetLastError();
		//qInfo() << errorCode;
	


	//HttpSendRequest(hRequest, hdrs, strlen(hdrs), frmdata, strlen(param.c_str()));
	DWORD rSize;
	char tmp[1024 + 1];
	string szBuffer;

	while (InternetReadFile(hRequest, tmp, 1024, &rSize) && rSize > 0)
	{
		tmp[rSize] = '\0';
		szBuffer += (string)tmp;
	}
	InternetCloseHandle(hSession);
	InternetCloseHandle(hConnect);
	InternetCloseHandle(hRequest);
	//std::cout << szBuffer;
	return szBuffer;

}