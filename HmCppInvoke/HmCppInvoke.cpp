#include "HmCppInvoke.h"

#include <shlwapi.h>

#pragma comment(lib, "version.lib")
#pragma comment(lib, "shlwapi.lib")

using namespace std;
using namespace Hidemaru;


THm Hm = THm();


double THm::hm_version = 0;
THm::PFNGetCurrentWindowHandle THm::Hidemaru_GetCurrentWindowHandle = NULL;

HMODULE THm::hHideExeHandle = NULL;
wchar_t THm::szHidemaruFullPath[MAX_PATH] = L"";

HMODULE THm::TOutputPane::hHmOutputPaneDLL = NULL;
HMODULE THm::TExplorerPane::hHmExplorerPaneDLL = NULL;


THm::THm()
{
	// �������g��dll�̏��́A��Ԑ�ɐݒ肵�Ă���
	this->SelfDllInfo = TSelfDllAttribute();

	GetModuleFileName(NULL, szHidemaruFullPath, _countof(szHidemaruFullPath));

	bool success = setVersion();
	if (success)
	{
		if (hm_version >= 866) {

			// �G�ۖ{�̂Ɋ֐�������̂� 8.66�ȏ�
			hHideExeHandle = LoadLibrary(szHidemaruFullPath);
			if (hHideExeHandle) {
				Hidemaru_GetDllFuncCalledType = (PFNGetDllFuncCalledType)GetProcAddress(hHideExeHandle, "Hidemaru_GetDllFuncCalledType");
				Hidemaru_GetCurrentWindowHandle = (PFNGetCurrentWindowHandle)GetProcAddress(hHideExeHandle, "Hidemaru_GetCurrentWindowHandle");
			}

			this->Edit = TEdit();
			this->File = TFile();
			this->Macro = TMacro();
			this->OutputPane = TOutputPane();
			this->ExplorerPane = TExplorerPane();
		}
		else {
			throw std::runtime_error("HidemaruMissionVersionException:" + to_string( this->getVersion() ) + "<866");
		}
	}
}

double THm::QueryFileVersion(wchar_t* path)
{
	VS_FIXEDFILEINFO* v;
	UINT len;
	DWORD sz = GetFileVersionInfoSize(path, NULL);
	if (sz) {
		unique_ptr<char[]> mngBuf = make_unique<char[]>(sz);
		void* buf = (void *)mngBuf.get();
		GetFileVersionInfo(path, 0, sz, buf);

		if (VerQueryValue(buf, L"\\", (LPVOID*)&v, &len)) {
			double ret = 0;
			ret = double(HIWORD(v->dwFileVersionMS)) * 100 +
				double(LOWORD(v->dwFileVersionMS)) * 10 +
				double(HIWORD(v->dwFileVersionLS)) +
				double(LOWORD(v->dwFileVersionLS)) * 0.01;
			return ret;
		}
	}

	return 0;
}

double THm::getVersion()
{
	// ��
	return hm_version;
}

HWND THm::getWindowHandle()
{
	return Hidemaru_GetCurrentWindowHandle();
}

bool THm::setVersion()
{
	hm_version = QueryFileVersion(szHidemaruFullPath);
	if (hm_version > 0.0) {
		return true;
	}
	return false;
}










