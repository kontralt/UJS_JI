#ifndef UJS_JI_TLE_Asympt2
#define UJS_JI_TLE_Asympt2

#include "JudgeModule.h"

class TLE_Asympt2 : public JudgeModule {
	int t[3];
	int x[3];
	int y[3];
	int collected;
	double coeff[3];
	double coeffLimit[3];
	TLE_Asympt2(const std::wstring &options);
public:		
	static JudgeModule *create(const std::wstring &options);
	virtual ~TLE_Asympt2() { }
	virtual std::wstring id();
	virtual std::wstring info();	
	virtual void afterSolution(int testN, ShellCommands *shell);
	virtual std::pair<double, std::wstring> verdict();
};

#endif