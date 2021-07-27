/*
 * Copyright (c) 2021 Akitsugu Komiyama
 * under the MIT License
 */

#include "HmCppInvoke.h"

#include <shlwapi.h>

using namespace std;
using namespace Hidemaru;



HMODULE THm::TDllBindAttribute::hModule = NULL;

wchar_t THm::TDllBindAttribute::wszSelfModuleFullPath[MAX_PATH] = L"";
wchar_t THm::TDllBindAttribute::wszSelfModuleDirPath[MAX_PATH] = L"";

int THm::TDllBindAttribute::iSelfBindedType = 0;


HMODULE THm::TDllBindAttribute::getCurrentModule()
{
	DWORD flags = GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT;
	HMODULE hm = 0;
	::GetModuleHandleEx(flags, reinterpret_cast<LPCTSTR>(THm::TDllBindAttribute::getCurrentModule), &hm);
	return hm;
}



Hidemaru::THm::TDllBindAttribute::TDllBindAttribute()
{
	this->initHandle();
}

void THm::TDllBindAttribute::initHandle() {
	HMODULE hCurrentModule = getCurrentModule();
	TDllBindAttribute::hModule = hCurrentModule;
	GetModuleFileName(hModule, TDllBindAttribute::wszSelfModuleFullPath, _countof(TDllBindAttribute::wszSelfModuleFullPath));
	wcscpy_s(TDllBindAttribute::wszSelfModuleDirPath, TDllBindAttribute::wszSelfModuleFullPath);
	PathRemoveFileSpec(TDllBindAttribute::wszSelfModuleDirPath);
}

int THm::TDllBindAttribute::getBindDllType() {
	return iSelfBindedType;
}

BOOL THm::TDllBindAttribute::setBindDllType() {

	// �G��8.66�ȏ�
	if (Hm.DllMacroVariant.Hidemaru_GetDllFuncCalledType) {
		int dll = Hm.DllMacroVariant.Hidemaru_GetDllFuncCalledType(-1); // ������dll�̌Ă΂�����`�F�b�N
		TDllBindAttribute::iSelfBindedType = dll;
		return TRUE;
	}
	else {
		MessageBox(NULL, L"loadll�̃p�^�[�����F���o���܂���ł����B", L"loadll�̃p�^�[�����F���o���܂���ł����B", MB_ICONERROR);
	}

	return FALSE;
}

wstring THm::TDllBindAttribute::getInvocantString() {
	if (iSelfBindedType == -1) {
		return L"";
	}
	else {
		return to_wstring(iSelfBindedType) + L",";
	}
}

wstring THm::TDllBindAttribute::getSelfModuleFullPath() {
	return wszSelfModuleFullPath;
}

wstring THm::TDllBindAttribute::getSelfModuleDir() {
	return wszSelfModuleDirPath;
}



