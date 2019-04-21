#pragma once

namespace Detours {
	extern "C" {
		// LONG WINAPI DetourTransactionBegin(VOID);
		void __stdcall DetourTransactionBegin();

		// PVOID WINAPI DetourFindFunction(_In_ LPCSTR pszModule,
		//                                 _In_ LPCSTR pszFunction);
		void* __stdcall DetourFindFunction(const char* pszModule, const char* pszFunction);

		// LONG WINAPI DetourAttach(_Inout_ PVOID *ppPointer,
		//                          _In_ PVOID pDetour);
		long __stdcall DetourAttach(void** ppPointer, void* pDetour);

		// LONG WINAPI DetourUpdateThread(_In_ HANDLE hThread);
		long __stdcall DetourUpdateThread(void* hThread);

		// LONG WINAPI DetourTransactionCommit(VOID);
		void __stdcall DetourTransactionCommit();
	}
}