#include "MLE_ACM.h"

MLE_ACM::MLE_ACM(const std::wstring &options) {
	swscanf(options.c_str(), L"%d", &memoryLimit);
	memoryActual = 0;
}

JudgeModule *MLE_ACM::create(const std::wstring &options) { 
	return new MLE_ACM(options); 
}

std::wstring MLE_ACM::id() {
	return L"MLE_ACM";
}

std::wstring MLE_ACM::info() {
	return L"Memory Limit Exceed check module (ACM ICPC style) v1.0 [Limit = " + std::to_wstring((_Longlong)memoryLimit) + L" bytes]";
}

void MLE_ACM::afterSolution(int testN, ShellCommands *shell) {
	memoryActual = shell->execData.memory;
}

std::pair<double, std::wstring> MLE_ACM::verdict() {
	if (memoryActual > memoryLimit)
		return std::make_pair(0, L"Memory Limit Exceeded: " + std::to_wstring((_Longlong)memoryActual) + L" bytes.");
	return std::make_pair(1, L"OK: test passed (" + std::to_wstring((_Longlong)memoryActual) + L" bytes).");
}