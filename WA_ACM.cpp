#include "WA_ACM.h"

WA_ACM::WA_ACM(const std::wstring &options) { }

JudgeModule *WA_ACM::create(const std::wstring &options) { 
	return new WA_ACM(options); 
}

std::wstring WA_ACM::id() {
	return L"WA_ACM";
}

std::wstring WA_ACM::info() {
	return L"Basic (ACM ICPC style) checker execution v1.0";
}

void WA_ACM::beforeSolution(int testN, ShellCommands *shell) {
	wrongAnswer = false;
}

void WA_ACM::afterSolution(int testN, ShellCommands *shell) {
	shell->copy("tests/pattern" + std::to_string((_Longlong)testN) + ".txt", "checker/pattern.txt");
	shell->copy("solution/output.txt", "checker/output.txt");
	wrongAnswer = shell->exec("checker/", "run");
	shell->del("checker/pattern.txt");
	shell->del("checker/output.txt");
}

std::pair<double, std::wstring> WA_ACM::verdict() {
	if (wrongAnswer)
		return std::make_pair(0, L"Wrong Answer.");
	return std::make_pair(1, L"OK: test passed.");
}