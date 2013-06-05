#include "PE_ACM.h"

PE_ACM::PE_ACM(const std::wstring &options) { }

JudgeModule *PE_ACM::create(const std::wstring &options) { 
	return new PE_ACM(options); 
}

std::wstring PE_ACM::id() {
	return L"PE_ACM";
}

std::wstring PE_ACM::info() {
	return L"Presentation Error check module (ACM ICPC style) v1.0";
}

void PE_ACM::beforeSolution(int testN, ShellCommands *shell) {
	presentationError = false;
}

void PE_ACM::afterSolution(int testN, ShellCommands *shell) {
	presentationError = !shell->exists("solution/output.txt");
}

std::pair<double, std::wstring> PE_ACM::verdict() {
	if (presentationError)
		return std::make_pair(0, L"Presentation Error: no output file detected.");
	return std::make_pair(1, L"OK: test passed.");
}