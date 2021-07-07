#include "HmCppInvoke.h"

#include <shlwapi.h>

using namespace std;
using namespace Hidemaru;

// �A�E�g�v�b�g�p�l��
THm::TOutputPane::PFNHmOutputPane_Output THm::TOutputPane::HmOutputPane_Output = NULL;
THm::TOutputPane::PFNHmOutputPane_OutputW THm::TOutputPane::HmOutputPane_OutputW = NULL;
THm::TOutputPane::PFNHmOutputPane_Push THm::TOutputPane::HmOutputPane_Push = NULL;
THm::TOutputPane::PFNHmOutputPane_Pop THm::TOutputPane::HmOutputPane_Pop = NULL;
THm::TOutputPane::PFNHmOutputPane_GetWindowHandle THm::TOutputPane::HmOutputPane_GetWindowHandle = NULL;
THm::TOutputPane::PFNHmOutputPane_SetBaseDir THm::TOutputPane::HmOutputPane_SetBaseDir = NULL;



THm::TOutputPane::TOutputPane()
{
	// ���Ȃ��Ƃ�GetWindowsCurrentHandle�������ƁA���ɗ����Ȃ�
	if (Hidemaru_GetCurrentWindowHandle) {
		// hidemaru.exe�̃f�B���N�g�������߂�
		wchar_t hidemarudir[512] = L"";
		wcscpy_s(hidemarudir, szHidemaruFullPath);
		PathRemoveFileSpec(hidemarudir);

		// �f�B���N�g������H �i�܂������ˁj
		if (PathFileExists(hidemarudir)) {
			// HmOutputPane.dll�����邩�ǂ����B
			wstring hmoutputpane_fullpath = wstring(hidemarudir) + wstring(L"\\HmOutputPane.dll");
			hHmOutputPaneDLL = LoadLibrary(hmoutputpane_fullpath.data());

			// ����΁AOutput�֐����Z�b�e�B���O���Ă���
			if (hHmOutputPaneDLL) {
				HmOutputPane_Output = (PFNHmOutputPane_Output)GetProcAddress(hHmOutputPaneDLL, "Output");
				HmOutputPane_Push = (PFNHmOutputPane_Push)GetProcAddress(hHmOutputPaneDLL, "Push");
				HmOutputPane_Pop = (PFNHmOutputPane_Pop)GetProcAddress(hHmOutputPaneDLL, "Pop");
				HmOutputPane_GetWindowHandle = (PFNHmOutputPane_GetWindowHandle)GetProcAddress(hHmOutputPaneDLL, "GetWindowHandle");
				if (hm_version > 877) {
					HmOutputPane_SetBaseDir = (PFNHmOutputPane_SetBaseDir)GetProcAddress(hHmOutputPaneDLL, "SetBaseDir");
				}
				if (hm_version > 898) {
					HmOutputPane_OutputW = (PFNHmOutputPane_OutputW)GetProcAddress(hHmOutputPaneDLL, "OutputW");
				}
			}
		}
	}
}

bool THm::TOutputPane::output(std::wstring message)
{
	// ��
	return 0;
}

bool THm::TOutputPane::push()
{
	// ��
	return 0;
}

bool THm::TOutputPane::pop()
{
	return 0;
}

bool THm::TOutputPane::clear()
{
	return 0;
}

long THm::TOutputPane::sendMessage(int command_id)
{
	return long();
}

bool THm::TOutputPane::setBaseDir(std::wstring dirpath)
{
	return false;
}

HWND THm::TOutputPane::getWindowHandle()
{
	return HWND();
}


// �t�@�C���}�l�[�W���p�l��
THm::TExplorerPane::PFNHmExplorerPane_SetMode THm::TExplorerPane::HmExplorerPane_SetMode = NULL;
THm::TExplorerPane::PFNHmExplorerPane_GetMode THm::TExplorerPane::HmExplorerPane_GetMode = NULL;
THm::TExplorerPane::PFNHmExplorerPane_LoadProject THm::TExplorerPane::HmExplorerPane_LoadProject = NULL;
THm::TExplorerPane::PFNHmExplorerPane_SaveProject THm::TExplorerPane::HmExplorerPane_SaveProject = NULL;
THm::TExplorerPane::PFNHmExplorerPane_GetProject THm::TExplorerPane::HmExplorerPane_GetProject = NULL;
THm::TExplorerPane::PFNHmExplorerPane_GetWindowHandle THm::TExplorerPane::HmExplorerPane_GetWindowHandle = NULL;
THm::TExplorerPane::PFNHmExplorerPane_GetUpdated THm::TExplorerPane::HmExplorerPane_GetUpdated = NULL;
THm::TExplorerPane::PFNHmExplorerPane_GetCurrentDir THm::TExplorerPane::HmExplorerPane_GetCurrentDir = NULL;

THm::TExplorerPane::TExplorerPane()
{
	// ���Ȃ��Ƃ�GetWindowsCurrentHandle�������ƁA���ɗ����Ȃ�
	if (Hidemaru_GetCurrentWindowHandle) {
		// hidemaru.exe�̃f�B���N�g�������߂�
		wchar_t hidemarudir[512] = L"";
		wcscpy_s(hidemarudir, szHidemaruFullPath);
		PathRemoveFileSpec(hidemarudir);

		// �f�B���N�g������H �i�܂������ˁj
		if (PathFileExists(hidemarudir)) {
			// HmOutputPane.dll�����邩�ǂ����B
			wstring hmoutputpane_fullpath = wstring(hidemarudir) + wstring(L"\\HmOutputPane.dll");
			hHmExplorerPaneDLL = LoadLibrary(hmoutputpane_fullpath.data());

			// ����΁AExplorerPane�֐����Z�b�e�B���O���Ă���
			if (hHmExplorerPaneDLL) {
				HmExplorerPane_SetMode = (PFNHmExplorerPane_SetMode)GetProcAddress(hHmExplorerPaneDLL, "SetMode");
				HmExplorerPane_GetMode = (PFNHmExplorerPane_GetMode)GetProcAddress(hHmExplorerPaneDLL, "GetMode");
				HmExplorerPane_LoadProject = (PFNHmExplorerPane_LoadProject)GetProcAddress(hHmExplorerPaneDLL, "LoadProject");
				HmExplorerPane_SaveProject = (PFNHmExplorerPane_SaveProject)GetProcAddress(hHmExplorerPaneDLL, "SaveProject");
				HmExplorerPane_GetProject = (PFNHmExplorerPane_GetProject)GetProcAddress(hHmExplorerPaneDLL, "GetProject");
				HmExplorerPane_GetWindowHandle = (PFNHmExplorerPane_GetWindowHandle)GetProcAddress(hHmExplorerPaneDLL, "GetWindowHandle");
				HmExplorerPane_GetUpdated = (PFNHmExplorerPane_GetUpdated)GetProcAddress(hHmExplorerPaneDLL, "GetUpdated");
				if (hm_version > 885) {
					HmExplorerPane_GetCurrentDir = (PFNHmExplorerPane_GetCurrentDir)GetProcAddress(hHmExplorerPaneDLL, "GetCurrentDir");
				}
			}
		}
	}

}

bool THm::TExplorerPane::setMode(int mode)
{
	return false;
}

int THm::TExplorerPane::getMode()
{
	return 0;
}

bool THm::TExplorerPane::loadProject(std::wstring filepath)
{
	return false;
}

bool THm::TExplorerPane::saveProject(std::wstring filepath)
{
	return false;
}

std::wstring THm::TExplorerPane::getProject()
{
	return std::wstring();
}

long THm::TExplorerPane::sendMessage(int command_id)
{
	return long();
}

HWND THm::TExplorerPane::getWindowHandle()
{
	return HWND();
}

bool THm::TExplorerPane::getUpdated()
{
	return false;
}



extern unsigned int hidemaru_encode_map[];
std::vector<BYTE> THm::EncodeWStringToOriginalEncodeVector(std::wstring original_string)
{

	// ���̌��ʂ̃o�C�g��(vector.data())�� HmOutputPane.dll��Output�֐��ɂȂ���΁AUnicode�ł��Č��ł���
	vector<BYTE> r;
	for (wchar_t ch : original_string) {
		int ix = ch;

		// �ϊ���̃R�[�h�̐��l���A255�ȉ��Ȃ�
		unsigned int encode_code = hidemaru_encode_map[ix];
		if (encode_code <= 0xFF) { // �P�����Ŏ��܂�
			r.push_back(encode_code);
		}
		else {
			union EncodeCodeUnion {
				unsigned int code;
				BYTE ch[4];
			};

			EncodeCodeUnion ecu;
			ecu.code = encode_code;
			for (BYTE b : ecu.ch) {
				if (b == 0) {
					break;
				}
				r.push_back(b);
			}
		}
	}

	r.push_back(0);
	return r;
}

