#include "HmCppInvoke.h"

using namespace std;
using namespace Hidemaru;

THm::PFNGetDllFuncCalledType THmDllExport::Hidemaru_GetDllFuncCalledType = NULL;

void THm::initDllHandle(HMODULE handle) {
	SelfDllInfo::initHandle(handle);
}

bool THm::rebindParameters() {
	// ����d�v�Bloadll�̌`�Ԃ�ێ�����B�֐����Ă΂��x�ɍX�V���Ă����B
	return SelfDllInfo::setBindDllType();
}
