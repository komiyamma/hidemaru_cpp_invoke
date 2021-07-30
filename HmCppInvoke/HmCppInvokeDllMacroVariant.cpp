/*
 * Copyright (c) 2021 Akitsugu Komiyama
 * under the MIT License
 */

#include "HmCppInvoke.h"
#include "HmCppInvokeDllExport.hpp"

using namespace std;
using namespace Hidemaru;

THm::TDllMacroVariant::PFNGetDllFuncCalledType THm::TDllMacroVariant::Hidemaru_GetDllFuncCalledType = NULL;

THmMacroVariable Hidemaru::TestDynamicVar = nullptr;

Hidemaru::THm::TDllMacroVariant::TDllMacroVariant()
{
	if (hHideExeHandle) {
		Hidemaru_GetDllFuncCalledType = (PFNGetDllFuncCalledType)GetProcAddress(hHideExeHandle, "Hidemaru_GetDllFuncCalledType");
	}
}

// �G�ۂ̕ϐ��������񂩐��l���̔���p
HM_DLLEXPORT THmNumber SetDynamicVar(const void* dynamic_value) {

	if (!THm::TDllMacroVariant::Hidemaru_GetDllFuncCalledType) {
		return 0;
	}

	auto param_type = (THm::TDllMacroVariant::DLLFUNCPARAM)THm::TDllMacroVariant::Hidemaru_GetDllFuncCalledType(1);
	if (param_type == THm::TDllMacroVariant::DLLFUNCPARAM::WCHAR_PTR) {
		Hidemaru::TestDynamicVar = wstring((wchar_t*)dynamic_value);
		return 1;
	}
	else {
		Hidemaru::TestDynamicVar = (THmNumber)(intptr_t)dynamic_value;
		return 1;
	}
}


static THmNumber popnumvar = 0;
// �X�^�b�N�����ϐ����G�ۃ}�N��������o���B���������p
HM_DLLEXPORT THmNumber PopNumVar() {
	return popnumvar;
}

// �ϐ����G�ۃ}�N��������o�����߂ɃX�^�b�N�B���������p
HM_DLLEXPORT THmNumber PushNumVar(THmNumber i_tmp_num) {
	popnumvar = i_tmp_num;
	return 1;
}

// �X�^�b�N�����ϐ����G�ۃ}�N��������o���B���������p
static wstring popstrvar;
HM_DLLEXPORT const wchar_t* PopStrVar() {
	return popstrvar.data();
}

// �ϐ����G�ۃ}�N��������o�����߂ɃX�^�b�N�B���������p
HM_DLLEXPORT THmNumber PushStrVar(const wchar_t* wsz_tmp_str) {
	popstrvar = wsz_tmp_str;
	return 1;
}

