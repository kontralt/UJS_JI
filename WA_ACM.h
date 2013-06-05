#ifndef UJS_JI_WA_ACM
#define UJS_JI_WA_ACM

#include "JudgeModule.h"

class WA_ACM : public JudgeModule {
	bool wrongAnswer;
	WA_ACM(const std::wstring &options);
public:		
	static JudgeModule *create(const std::wstring &options);
	virtual ~WA_ACM() { }
	virtual std::wstring id();
	virtual std::wstring info();	
	virtual void beforeSolution(int testN, ShellCommands *shell);
	virtual void afterSolution(int testN, ShellCommands *shell);
	virtual std::pair<double, std::wstring> verdict();
};

#endif