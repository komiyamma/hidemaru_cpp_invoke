/*
 * Copyright (c) 2021 Akitsugu Komiyama
 * under the MIT License
 */

#include "HmCppInvoke.h"
#include "HmCppInvokeDllExport.h"
#include "HmCppInvokeDllFuncCalledType.h"

using namespace std;
using namespace Hidemaru;

THm::TDllFuncCalledType::PFNGetDllFuncCalledType THm::TDllFuncCalledType::Hidemaru_GetDllFuncCalledType = NULL;

THmMacroVariable Hidemaru::TestDynamicVar = nullptr;

Hidemaru::THm::TDllFuncCalledType::TDllFuncCalledType()
{
	if (hHideExeHandle) {
		Hidemaru_GetDllFuncCalledType = (PFNGetDllFuncCalledType)GetProcAddress(hHideExeHandle, "Hidemaru_GetDllFuncCalledType");
	}
}

bool THm::TDllFuncCalledType::isMissingMethod()
{
	if (!Hidemaru_GetDllFuncCalledType) {
		return true;
	}
	return false;
}

int THm::TDllFuncCalledType::getDllBindType()
{
	if (!Hidemaru_GetDllFuncCalledType) {
		return 0;
	}

	int dll = Hidemaru_GetDllFuncCalledType(-1); // ������dll�̌Ă΂�����`�F�b�N
	return dll;
}

THm::TDllFuncCalledType::DLLFUNCPARAM THm::TDllFuncCalledType::getFuncParamType(int arg_n)
{
	if (!Hidemaru_GetDllFuncCalledType) {
		return DLLFUNCPARAM::NOPARAM;
	}

	auto param_type = Hidemaru_GetDllFuncCalledType(arg_n);

	return (DLLFUNCPARAM)param_type;
}

THm::TDllFuncCalledType::DLLFUNCRETURN THm::TDllFuncCalledType::getFuncReturnType()
{
	auto return_type = Hidemaru_GetDllFuncCalledType(0);

	return (DLLFUNCRETURN)return_type;
}

// �G�ۂ̕ϐ��������񂩐��l���̔���p
HM_DLLEXPORT THmNumber SetDynamicVar(const void* dynamic_value) {

	if (Hm.DllFuncCalledType.isMissingMethod()) {
		return 0;
	}
	auto param_type = Hm.DllFuncCalledType.getFuncParamType(1);
	if (param_type == THm::TDllFuncCalledType::DLLFUNCPARAM::WCHAR_PTR) {
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

