#include "CoreModLoader.h"
#include <process.h>
#include <windows.h>
#include <filesystem>
#include "Utilities/Logger.h"
namespace fs = std::filesystem;
namespace CoreModLoader
{
	void InjectDLL(std::string path)
	{
		HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, _getpid());
		if (hProc && hProc != INVALID_HANDLE_VALUE)
		{
			void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			WriteProcessMemory(hProc, loc, path.c_str(), strlen(path.c_str()) + 1, 0);
			HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);
			if (hThread)
			{
				CloseHandle(hThread);
			}
		}
		if (hProc)
		{
			CloseHandle(hProc);
		}
	}

	void LoadCoreMods()
	{
		char path_c[MAX_PATH];
		GetModuleFileNameA(NULL, path_c, MAX_PATH);
		std::string path = std::string(path_c);
		path = path.substr(0, path.find_last_of("/\\"));
		path = path.substr(0, path.find_last_of("/\\"));
		path = path.substr(0, path.find_last_of("/\\"));
		path = path + "\\Content\\CoreMods\\";
		if (!std::filesystem::exists(path))
		{
			std::filesystem::create_directory(path);
		}
		for (const auto& entry : fs::directory_iterator(path))
		{
			if (entry.path().extension().string() == ".dll")
			{
				std::wstring path = entry.path();
				std::string str(path.begin(), path.end());
				InjectDLL(str);
			}
		}
	}
};