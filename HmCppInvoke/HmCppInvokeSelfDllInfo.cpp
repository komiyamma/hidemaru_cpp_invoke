/*
 * Copyright (c) 2021 Akitsugu Komiyama
 * under the MIT License
 */

#include "HmCppInvoke.h"

#include <shlwapi.h>

using namespace std;
using namespace Hidemaru;



HMODULE THm::SelfDllInfo::hModule = NULL;

wchar_t THm::SelfDllInfo::szSelfModuleFullPath[MAX_PATH] = L"";
wchar_t THm::SelfDllInfo::szSelfModuleDirPath[MAX_PATH] = L"";

int THm::SelfDllInfo::iSelfBindedType = 0;


HMODULE THm::SelfDllInfo::getCurrentModule()
{
	DWORD flags = GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT;
	HMODULE hm = 0;
	::GetModuleHandleEx(flags, reinterpret_cast<LPCTSTR>(THm::SelfDllInfo::getCurrentModule), &hm);
	return hm;
}



void THm::SelfDllInfo::initHandle() {
	HMODULE hCurrentModule = getCurrentModule();
	SelfDllInfo::hModule = hCurrentModule;
	GetModuleFileName(hModule, SelfDllInfo::szSelfModuleFullPath, _countof(SelfDllInfo::szSelfModuleFullPath));
	wcscpy_s(SelfDllInfo::szSelfModuleDirPath, SelfDllInfo::szSelfModuleFullPath);
	PathRemoveFileSpec(SelfDllInfo::szSelfModuleDirPath);
}

int THm::SelfDllInfo::getBindDllType() {
	return iSelfBindedType;
}

BOOL THm::SelfDllInfo::setBindDllType() {

	// �G��8.66�ȏ�
	if (Hm.Hidemaru_GetDllFuncCalledType) {
		int dll = Hm.Hidemaru_GetDllFuncCalledType(-1); // ������dll�̌Ă΂�����`�F�b�N
		SelfDllInfo::iSelfBindedType = dll;
		return TRUE;
	}
	else {
		MessageBox(NULL, L"loadll�̃p�^�[�����F���o���܂���ł����B", L"loadll�̃p�^�[�����F���o���܂���ł����B", MB_ICONERROR);
	}

	return FALSE;
}

wstring THm::SelfDllInfo::getInvocantString() {
	if (iSelfBindedType == -1) {
		return L"";
	}
	else {
		return to_wstring(iSelfBindedType) + L",";
	}
}

wstring THm::SelfDllInfo::getSelfModuleFullPath() {
	return szSelfModuleFullPath;
}

wstring THm::SelfDllInfo::getSelfModuleDir() {
	return szSelfModuleDirPath;
}



