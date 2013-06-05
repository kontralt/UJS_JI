#ifndef UJS_JI_MLE_ACM
#define UJS_JI_MLE_ACM

#include "JudgeModule.h"

class MLE_ACM : public JudgeModule {
	int memoryLimit;
	int memoryActual;
	MLE_ACM(const std::wstring &options);
public:		
	static JudgeModule *create(const std::wstring &options);
	virtual ~MLE_ACM() { }
	virtual std::wstring id();
	virtual std::wstring info();	
	virtual void afterSolution(int testN, ShellCommands *shell);
	virtual std::pair<double, std::wstring> verdict();
};

#endif