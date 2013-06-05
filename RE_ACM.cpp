#include "RE_ACM.h"

RE_ACM::RE_ACM(const std::wstring &options) { }

JudgeModule *RE_ACM::create(const std::wstring &options) { 
	return new RE_ACM(options); 
}

std::wstring RE_ACM::id() {
	return L"RE_ACM";
}

std::wstring RE_ACM::info() {
	return L"Runtime Error check module (ACM ICPC style) v1.0";
}

void RE_ACM::beforeSolution(int testN, ShellCommands *shell) {
	runtimeError = false;
}

void RE_ACM::afterSolution(int testN, ShellCommands *shell) {
	runtimeError = shell->execData.exitCode;
}

std::pair<double, std::wstring> RE_ACM::verdict() {
	if (runtimeError)
		return std::make_pair(0, L"Runtime Error.");
	return std::make_pair(1, L"OK: test passed.");
}