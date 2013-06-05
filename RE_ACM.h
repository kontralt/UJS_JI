#ifndef UJS_JI_RE_ACM
#define UJS_JI_RE_ACM

#include "JudgeModule.h"

class RE_ACM : public JudgeModule {
	bool runtimeError;
	RE_ACM(const std::wstring &options);
public:		
	static JudgeModule *create(const std::wstring &options);
	virtual ~RE_ACM() { }
	virtual std::wstring id();
	virtual std::wstring info();
	virtual void beforeSolution(int testN, ShellCommands *shell);
	virtual void afterSolution(int testN, ShellCommands *shell);
	virtual std::pair<double, std::wstring> verdict();
};

#endif