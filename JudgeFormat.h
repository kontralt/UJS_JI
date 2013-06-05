#ifndef UJS_JI_JUDGEFORMAT
#define UJS_JI_JUDGEFORMAT

#include "JudgeModule.h"
#include "JudgeModuleBuilder.h"
#include "ShellCommands.h"
#include "Parser.h"
#include <vector>
#include <set>

class JudgeFormat {
	enum TerminationType { NONE, TEST, ALL };
	int testsCount;
	int maxTotalPoints;
	std::vector< std::pair<JudgeModule *, TerminationType> > modules;
	std::vector< std::vector< std::pair<int, int> > > modulesForTest;
	void clear();
public:	
	JudgeFormat(const std::string &filename);
	void runTests(const std::string &resultFileName, const std::string &logFileName, ShellCommands *shell);
};

#endif