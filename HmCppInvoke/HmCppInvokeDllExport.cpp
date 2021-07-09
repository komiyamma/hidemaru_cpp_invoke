/*
 * Copyright (c) 2021 Akitsugu Komiyama
 * under the MIT License
 */


#include "HmCppInvoke.h"

using namespace std;
using namespace Hidemaru;

THm::PFNGetDllFuncCalledType THmDllExport::Hidemaru_GetDllFuncCalledType = NULL;

bool THm::rebindParameters() {
	// ����d�v�Bloadll�̌`�Ԃ�ێ�����B�֐����Ă΂��x�ɍX�V���Ă����B
	return TSelfDllAttribute::setBindDllType();
}




THmMacroVariable Hidemaru::TestDynamicVar = nullptr;


// �G�ۂ̕ϐ��������񂩐��l���̔���p
HM_DLLEXPORT long SetDynamicVar(const void* dynamic_value) {

	auto param_type = (THm::DLLFUNCPARAM)THm::Hidemaru_GetDllFuncCalledType(1);
	if (param_type == THm::DLLFUNCPARAM::WCHAR_PTR) {
		Hidemaru::TestDynamicVar = wstring((wchar_t*)dynamic_value);
		return 1;
	}
	else {
		Hidemaru::TestDynamicVar = (long)(intptr_t)dynamic_value;
		return 1;
	}
}


long popnumvar = 0;
// �X�^�b�N�����ϐ����G�ۃ}�N��������o���B���������p
HM_DLLEXPORT long PopNumVar() {
	return popnumvar;
}

// �ϐ����G�ۃ}�N��������o�����߂ɃX�^�b�N�B���������p
HM_DLLEXPORT long PushNumVar(long i_tmp_num) {
	popnumvar = i_tmp_num;
	return 1;
}

// �X�^�b�N�����ϐ����G�ۃ}�N��������o���B���������p
static wstring popstrvar;
HM_DLLEXPORT const wchar_t* PopStrVar() {
	return popstrvar.data();
}

// �ϐ����G�ۃ}�N��������o�����߂ɃX�^�b�N�B���������p
HM_DLLEXPORT long PushStrVar(const wchar_t* sz_tmp_str) {
	popstrvar = sz_tmp_str;
	return 1;
}

