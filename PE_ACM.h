#ifndef UJS_JI_PE_ACM
#define UJS_JI_PE_ACM

#include "JudgeModule.h"

class PE_ACM : public JudgeModule {
	bool presentationError;
	PE_ACM(const std::wstring &options);
public:		
	static JudgeModule *create(const std::wstring &options);
	virtual ~PE_ACM() { }
	virtual std::wstring id();
	virtual std::wstring info();
	virtual void beforeSolution(int testN, ShellCommands *shell);
	virtual void afterSolution(int testN, ShellCommands *shell);
	virtual std::pair<double, std::wstring> verdict();
};

#endif