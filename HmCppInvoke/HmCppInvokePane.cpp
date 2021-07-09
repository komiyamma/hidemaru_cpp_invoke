/*
 * Copyright (c) 2021 Akitsugu Komiyama
 * under the MIT License
 */

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

	// �����Ɗ֐������鎞����
	if (Hidemaru_GetCurrentWindowHandle) {
		HWND hHidemaruWindow = Hidemaru_GetCurrentWindowHandle();
		if (HmOutputPane_Output) {
			auto encode_byte_data = EncodeWStringToOriginalEncodeVector(message);
			BOOL result = HmOutputPane_Output(hHidemaruWindow, encode_byte_data.data());
			return result;
		}
	}

	return false;
}

bool THm::TOutputPane::push()
{
	// �����Ɗ֐������鎞����
	if (Hidemaru_GetCurrentWindowHandle) {
		HWND hHidemaruWindow = THm::Hidemaru_GetCurrentWindowHandle();
		if (HmOutputPane_Push) {
			bool result = HmOutputPane_Push(hHidemaruWindow);
			return result;
		}
	}

	return false;
}

bool THm::TOutputPane::pop()
{
	// �����Ɗ֐������鎞����
	if (Hidemaru_GetCurrentWindowHandle) {
		HWND hHidemaruWindow = Hidemaru_GetCurrentWindowHandle();
		if (HmOutputPane_Pop) {
			bool result = HmOutputPane_Pop(hHidemaruWindow);
			return result;
		}
	}

	return false;
}

bool THm::TOutputPane::clear()
{
	long ret = this->sendMessage(1009);
	return (bool)ret;
}

long THm::TOutputPane::sendMessage(int command_id)
{
	HWND OutputWindowHandle = this->getWindowHandle();
	if (OutputWindowHandle) {
		// (#h,0x111/*WM_COMMAND*/,1009,0);//1009=�N���A
		// 0x111 = WM_COMMAND
		LRESULT r = SendMessageW(OutputWindowHandle, 0x111, command_id, 0);
		return (long)r;

	}
	return FALSE;
}

bool THm::TOutputPane::setBaseDir(std::wstring dirpath)
{
	auto encode_byte_data = EncodeWStringToOriginalEncodeVector(dirpath);

	// �����Ɗ֐������鎞����
	if (Hidemaru_GetCurrentWindowHandle) {
		HWND hHidemaruWindow = Hidemaru_GetCurrentWindowHandle();
		if (HmOutputPane_SetBaseDir) {
			bool result = HmOutputPane_SetBaseDir(hHidemaruWindow, encode_byte_data.data());
			return result;
		}
	}

	return false;
}

HWND THm::TOutputPane::getWindowHandle()
{
	// �����Ɗ֐������鎞����
	if (Hidemaru_GetCurrentWindowHandle) {
		HWND hHidemaruWindow =Hidemaru_GetCurrentWindowHandle();
		if (HmOutputPane_GetWindowHandle) {
			return HmOutputPane_GetWindowHandle(hHidemaruWindow);
		}
	}

	return NULL;
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
	// �����Ɗ֐������鎞����
	if (Hidemaru_GetCurrentWindowHandle) {
		HWND hHidemaruWindow = Hidemaru_GetCurrentWindowHandle();
		if (HmExplorerPane_SetMode) {
			bool result = HmExplorerPane_SetMode(hHidemaruWindow, mode);
			return result;
		}
	}

	return false;
}

int THm::TExplorerPane::getMode()
{
	// �����Ɗ֐������鎞����
	if (Hidemaru_GetCurrentWindowHandle) {
		HWND hHidemaruWindow = Hidemaru_GetCurrentWindowHandle();
		if (HmExplorerPane_GetMode) {
			bool result = HmExplorerPane_GetMode(hHidemaruWindow);
			return result;
		}
	}

	return false;
}

bool THm::TExplorerPane::loadProject(std::wstring filepath)
{
	// �����Ɗ֐������鎞����
	if (Hidemaru_GetCurrentWindowHandle) {
		HWND hHidemaruWindow = Hidemaru_GetCurrentWindowHandle();
		if (HmExplorerPane_LoadProject) {
			auto encode_byte_data = EncodeWStringToOriginalEncodeVector(filepath);
			bool result = HmExplorerPane_LoadProject(hHidemaruWindow, encode_byte_data.data());
			return result;
		}
	}

	return false;
}

bool THm::TExplorerPane::saveProject(std::wstring filepath)
{
	// �����Ɗ֐������鎞����
	if (Hidemaru_GetCurrentWindowHandle) {
		HWND hHidemaruWindow = Hidemaru_GetCurrentWindowHandle();
		if (HmExplorerPane_SaveProject) {
			auto encode_byte_data = EncodeWStringToOriginalEncodeVector(filepath);
			bool result = HmExplorerPane_SaveProject(hHidemaruWindow, encode_byte_data.data());
			return result;
		}
	}

	return false;
}

std::wstring THm::TExplorerPane::getProject()
{
	if (HmExplorerPane_GetProject) {
		if (Hm.Macro.isExecuting()) {
			auto ret = Hm.Macro.getVar(LR"RAW(dllfuncstr(loaddll("HmExplorerPane"), "GetProject", hidemaruhandle(0)))RAW");
			wstring project_name = std::get<wstring>(ret);
			return project_name;
		}
		else {
			auto ret = Hm.Macro.Exec.doEval(LR"RAW(endmacro dllfuncstr(loaddll("HmExplorerPane"), "GetProject", hidemaruhandle(0));)RAW");
			return ret.getMessage();
		}
	}
}

long THm::TExplorerPane::sendMessage(int command_id)
{
	HWND ExplorerWindowHandle = this->getWindowHandle();
	if (ExplorerWindowHandle) {
		//251=�P��̃t�H���_
		// 0x111 = WM_COMMAND
		LRESULT r = SendMessageW(ExplorerWindowHandle, 0x111, command_id, 0);
		return (long)r;

	}
	return FALSE;
}

HWND THm::TExplorerPane::getWindowHandle()
{
	// �����Ɗ֐������鎞����
	if (Hidemaru_GetCurrentWindowHandle) {
		HWND hHidemaruWindow = Hidemaru_GetCurrentWindowHandle();
		if (HmExplorerPane_GetWindowHandle) {
			return HmExplorerPane_GetWindowHandle(hHidemaruWindow);
		}
	}

	return NULL;
}

bool THm::TExplorerPane::getUpdated()
{
	// �����Ɗ֐������鎞����
	if (Hidemaru_GetCurrentWindowHandle) {
		HWND hHidemaruWindow = Hidemaru_GetCurrentWindowHandle();
		if (HmExplorerPane_GetUpdated) {
			bool result = HmExplorerPane_GetUpdated(hHidemaruWindow);
			return result;
		}
	}

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

