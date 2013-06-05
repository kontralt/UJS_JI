#include "TLE_ACM.h"

TLE_ACM::TLE_ACM(const std::wstring &options) {
	swscanf(options.c_str(), L"%d", &timeLimit);
	timeActual = 0;
}

JudgeModule *TLE_ACM::create(const std::wstring &options) { 
	return new TLE_ACM(options); 
}

std::wstring TLE_ACM::id() {
	return L"TLE_ACM";
}

std::wstring TLE_ACM::info() {
	return L"Time Limit Exceed check module (ACM ICPC style) v1.0 [Limit = " + std::to_wstring((_Longlong)timeLimit) + L" ms]";
}

void TLE_ACM::beforeSolution(int testN, ShellCommands *shell) {
	shell->execData.time = timeLimit + 100;
}

void TLE_ACM::afterSolution(int testN, ShellCommands *shell) {
	timeActual = shell->execData.time;
}

std::pair<double, std::wstring> TLE_ACM::verdict() {
	if (timeActual > timeLimit)
		return std::make_pair(0, L"Time Limit Exceeded: " + std::to_wstring((_Longlong)timeActual) + L" ms.");
	return std::make_pair(1, L"OK: test passed (" + std::to_wstring((_Longlong)timeActual) + L" ms).");
}