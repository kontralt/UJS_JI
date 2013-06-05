#ifndef UJS_JI_JUDGEMODULE
#define UJS_JI_JUDGEMODULE

#include "ShellCommands.h"
#include <string>

class JudgeModule {
public:
	virtual ~JudgeModule();
	virtual std::wstring id() = 0;
	virtual std::wstring info() = 0;
	virtual void beforeSolution(int testN, ShellCommands *shell);
	virtual void afterSolution(int testN, ShellCommands *shell);
	virtual std::pair<double, std::wstring> verdict() = 0;
};

#endif