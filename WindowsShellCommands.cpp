#include "WindowsShellCommands.h"

std::string slash(const std::string &s) {
	std::string res = "";
	for (int i = 0; i < s.length(); i++) 
		res += (s[i] != '/' ? s[i] : '\\');
	return res;
}

WindowsShellCommands::WindowsShellCommands(const std::string &workareaPath) {
	workarea = slash(workareaPath);
}

bool WindowsShellCommands::exists(const std::string &source) {
	return system(("if exist \"" + workarea + slash(source) + "\" (exit /b 1) else (exit /b 0)").c_str());
}

void WindowsShellCommands::copy(const std::string &source, const std::string &dest) {
	system(("copy \"" + workarea + slash(source) + "\" \"" + workarea + slash(dest) + "\"").c_str());
}

int WindowsShellCommands::exec(const std::string &dir, const std::string &source) {
	std::string fullDirPath = workarea + slash(dir);
	std::string fullSourcePath = fullDirPath + slash(source);
	system(("copy \"" + fullSourcePath + "\" \"" + fullSourcePath + ".bat\"").c_str());
	int exitCode = system(("cd " + fullDirPath + " && \"" + fullSourcePath + ".bat\"").c_str());
	system(("del \"" + fullSourcePath + ".bat\"").c_str());
	return exitCode;
}

int WindowsShellCommands::execWithData(const std::string &dir, const std::string &source) {
	std::string fullDirPath = workarea + slash(dir);
	std::string fullSourcePath = fullDirPath + slash(source);
	system(("copy \"" + fullSourcePath + "\" \"" + fullSourcePath + ".bat\"").c_str());

	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	GetStartupInfo(&si);
	LARGE_INTEGER startTime, finishTime, counterFrequency;
	QueryPerformanceFrequency(&counterFrequency);
	QueryPerformanceCounter(&startTime);
	CreateProcess((fullSourcePath + ".bat").c_str(), NULL, NULL, NULL, FALSE, 0, NULL, fullDirPath.c_str(), &si, &pi);
	WaitForSingleObject(pi.hProcess, execData.time ? execData.time : INFINITE);
	TerminateProcess(pi.hProcess, 0);  
	QueryPerformanceCounter(&finishTime);
	execData.time = (finishTime.QuadPart - startTime.QuadPart) / (counterFrequency.QuadPart / 1000);
	
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(pi.hProcess, &pmc, sizeof(pmc));
	execData.memory = pmc.QuotaPeakNonPagedPoolUsage + pmc.QuotaPeakPagedPoolUsage;
	
	system(("del \"" + fullSourcePath + ".bat\"").c_str());
	GetExitCodeProcess(pi.hProcess, (LPDWORD)&execData.exitCode);
	return execData.exitCode;
}

void WindowsShellCommands::del(const std::string &source) {
	system(("del \"" + workarea + slash(source) + "\"").c_str());
}



