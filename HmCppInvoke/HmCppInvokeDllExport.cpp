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
	return SelfDllInfo::setBindDllType();
}
