/*
 * Copyright (c) 2021 Akitsugu Komiyama
 * under the MIT License
 */


#include "HmCppInvoke.h"

using namespace std;
using namespace Hidemaru;

THm::PFNGetDllFuncCalledType THmDllExport::Hidemaru_GetDllFuncCalledType = NULL;

BOOL THm::DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: {
		//-------------------------------------------------------------------------
		// �������g��dll�̃n���h����t���p�X��ۑ����Ă���
		//-------------------------------------------------------------------------
		SelfDllInfo::initHandle(hModule);

		break;
	}
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

bool THm::rebindParameters() {
	// ����d�v�Bloadll�̌`�Ԃ�ێ�����B�֐����Ă΂��x�ɍX�V���Ă����B
	return SelfDllInfo::setBindDllType();
}
