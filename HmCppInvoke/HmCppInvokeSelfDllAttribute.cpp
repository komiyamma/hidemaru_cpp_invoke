/*
 * Copyright (c) 2021 Akitsugu Komiyama
 * under the MIT License
 */

#include "HmCppInvoke.h"

#include <shlwapi.h>

using namespace std;
using namespace Hidemaru;



HMODULE THm::TSelfDllAttribute::hModule = NULL;

wchar_t THm::TSelfDllAttribute::szSelfModuleFullPath[MAX_PATH] = L"";
wchar_t THm::TSelfDllAttribute::szSelfModuleDirPath[MAX_PATH] = L"";

int THm::TSelfDllAttribute::iSelfBindedType = 0;


HMODULE THm::TSelfDllAttribute::getCurrentModule()
{
	DWORD flags = GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT;
	HMODULE hm = 0;
	::GetModuleHandleEx(flags, reinterpret_cast<LPCTSTR>(THm::TSelfDllAttribute::getCurrentModule), &hm);
	return hm;
}



Hidemaru::THm::TSelfDllAttribute::TSelfDllAttribute()
{
	this->initHandle();
}

void THm::TSelfDllAttribute::initHandle() {
	HMODULE hCurrentModule = getCurrentModule();
	TSelfDllAttribute::hModule = hCurrentModule;
	GetModuleFileName(hModule, TSelfDllAttribute::szSelfModuleFullPath, _countof(TSelfDllAttribute::szSelfModuleFullPath));
	wcscpy_s(TSelfDllAttribute::szSelfModuleDirPath, TSelfDllAttribute::szSelfModuleFullPath);
	PathRemoveFileSpec(TSelfDllAttribute::szSelfModuleDirPath);
}

int THm::TSelfDllAttribute::getBindDllType() {
	return iSelfBindedType;
}

BOOL THm::TSelfDllAttribute::setBindDllType() {

	// �G��8.66�ȏ�
	if (Hm.Hidemaru_GetDllFuncCalledType) {
		int dll = Hm.Hidemaru_GetDllFuncCalledType(-1); // ������dll�̌Ă΂�����`�F�b�N
		TSelfDllAttribute::iSelfBindedType = dll;
		return TRUE;
	}
	else {
		MessageBox(NULL, L"loadll�̃p�^�[�����F���o���܂���ł����B", L"loadll�̃p�^�[�����F���o���܂���ł����B", MB_ICONERROR);
	}

	return FALSE;
}

wstring THm::TSelfDllAttribute::getInvocantString() {
	if (iSelfBindedType == -1) {
		return L"";
	}
	else {
		return to_wstring(iSelfBindedType) + L",";
	}
}

wstring THm::TSelfDllAttribute::getSelfModuleFullPath() {
	return szSelfModuleFullPath;
}

wstring THm::TSelfDllAttribute::getSelfModuleDir() {
	return szSelfModuleDirPath;
}



