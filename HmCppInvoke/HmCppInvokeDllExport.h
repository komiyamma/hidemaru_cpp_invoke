#pragma once

#define HM_DLLEXPORT extern "C" __declspec(dllexport)

namespace Hidemaru {
	extern THmMacroVariable TestDynamicVar;
}

// �G�ۃ}�N����̕ϐ��ƁAC++�����Ƃ̎������Ƃ�Ɏg�p�����B
HM_DLLEXPORT long SetDynamicVar(const void* dynamic_value);
HM_DLLEXPORT long PopNumVar();
HM_DLLEXPORT long PushNumVar(long i_tmp_num);
HM_DLLEXPORT const wchar_t* PopStrVar();
HM_DLLEXPORT long PushStrVar(const wchar_t* wsz_tmp_str);
