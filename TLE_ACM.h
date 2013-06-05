#ifndef UJS_JI_TLE_ACM
#define UJS_JI_TLE_ACM

#include "JudgeModule.h"

class TLE_ACM : public JudgeModule {
	int timeLimit;
	int timeActual;
	TLE_ACM(const std::wstring &options);
public:		
	static JudgeModule *create(const std::wstring &options);
	virtual ~TLE_ACM() { }
	virtual std::wstring id();
	virtual std::wstring info();	
	virtual void beforeSolution(int testN, ShellCommands *shell);
	virtual void afterSolution(int testN, ShellCommands *shell);
	virtual std::pair<double, std::wstring> verdict();
};

#endif