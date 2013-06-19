#include "JudgeFormat.h"

void JudgeFormat::clear() {
	modules.clear();
	for (int i = 0; i < modulesForTest.size(); i++)
		modulesForTest[i].clear();
	modulesForTest.clear();
	testsCount = 0;
	maxTotalPoints = 0;
}

std::pair<bool, std::vector< std::pair<int, int> > > parseTestWeights(const std::wstring &str) {
	std::vector< std::pair<int, int> > res;
	int p = 0;
	while (p < str.length()) {
		while (p < str.length() && iswspace(str[p]))
			p++;
		if (p >= str.length() || !iswdigit(str[p])) {
			res.clear();
			return std::make_pair(false, res);
		}
		int test = 0;
		while (p < str.length() && iswdigit(str[p]))
			test = test * 10 + str[p++] - L'0';
		while (p < str.length() && iswspace(str[p]))
			p++;
		if (p >= str.length() || str[p] != L'-') {
			res.clear();
			return std::make_pair(false, res);
		}
		p++;
		while (p < str.length() && iswspace(str[p]))
			p++;
		if (p >= str.length() || !iswdigit(str[p])) {
			res.clear();
			return std::make_pair(false, res);
		}
		int weight = 0;
		while (p < str.length() && iswdigit(str[p]))
			weight = weight * 10 + str[p++] - L'0';
		if (test <= 0 || weight < 0) {
			res.clear();
			return std::make_pair(false, res);
		}
		res.push_back(std::make_pair(test, weight));
	}
	return std::make_pair(true, res);
}

JudgeFormat::JudgeFormat(const std::string &filename) {		
	JudgeModuleBuilder judgeModuleBuilder;
	maxTotalPoints = 0;
	Parser parser(filename);
	if (!parser.testCurChar(L"{"))
		return;
	for (int moduleIndex = 1; true; moduleIndex++) {
		if (!parser.testNextChar(L"\"")) {
			clear();
			return;
		}
		std::wstring moduleId = parser.nextString(L"\"");
		if (!parser.testNextChar(L":") || !parser.testNextChar(L"[") || !parser.testNextChar(L"\"")) {
			clear();
			return;
		}
		std::wstring options = parser.nextString(L"\"");
		if (!parser.testNextChar(L",") || !parser.testNextChar(L"\"")) {
			clear();
			return;
		}
		std::wstring judgeType = parser.nextString(L"\"");
		if (!parser.testNextChar(L",") || !parser.testNextChar(L"\"")) {
			clear();
			return;
		}
		std::wstring testWeights = parser.nextString(L"\"");
		if (!parser.testNextChar(L"]")) {
			clear();
			return;
		}
		if (!judgeModuleBuilder.canBuild(moduleId)) {
			fwprintf(stderr, L"Warning: judge module %d has unrecognizable ID. Module will be skipped.\n", moduleIndex);
		} else {
			JudgeModule *module = judgeModuleBuilder.build(moduleId, options);
			if (!module) {
				fwprintf(stderr, L"Warning: cannot build judge module %d. Module will be skipped.\n", moduleIndex);
			} else {
				TerminationType type = NONE;
				if (judgeType == L"test")
					type = TEST;
				if (judgeType == L"all")
					type = ALL;				
				modules.push_back(std::make_pair(module, type));
				int curModuleArrayPos = modules.size() - 1;
				std::pair<bool, std::vector< std::pair<int, int> > > resTestWeights = parseTestWeights(testWeights);
				if (!resTestWeights.first) {
					fwprintf(stderr, L"Warning: Judge module %d has unrecognizable test weights. Module will be skipped.\n", moduleIndex);
				} else {
					for (int i = 0; i < resTestWeights.second.size(); i++) {	
						int testN = resTestWeights.second[i].first;
						int weight = resTestWeights.second[i].second;
						testsCount = std::max(testsCount, testN);
						if (modulesForTest.size() < testsCount + 1)
							modulesForTest.resize(testsCount + 1);
						modulesForTest[testN].push_back(std::make_pair(curModuleArrayPos, weight));
						maxTotalPoints += weight;
					}
				}
			}
		}
		if (!parser.testNextChar(L",}")) {
			clear();
			return;
		}
		if (parser.curChar() == L'}')
			break;
	}
}

JudgeFormat::~JudgeFormat() {
	for (std::vector<std::pair<JudgeModule *, JudgeFormat::TerminationType> >::iterator i = modules.begin(); i != modules.end(); i++)
		delete i->first;
}

void JudgeFormat::runTests(const std::string &resultFileName, const std::string &logFileName, ShellCommands *shell) {	
	double totalPoints = 0;
	FILE *logFile = fopen(logFileName.c_str(), "w");	
	bool terminatingAll = false;
	fwprintf(logFile, L"Testing log\nRunning %d total tests.\n\n", testsCount);
	for (int test = 1; !terminatingAll && test <= testsCount; test++) {
		fwprintf(logFile, L"Test case #%d\n\n", test);		
		shell->copy("tests/input" + std::to_string((_Longlong)test) + ".txt", "solution/input.txt");
		for (int i = 0; i < modulesForTest[test].size(); i++)
			modules[modulesForTest[test][i].first].first->beforeSolution(test, shell);
		shell->execWithData("solution/", "run");		
		for (int i = 0; i < modulesForTest[test].size(); i++)
			modules[modulesForTest[test][i].first].first->afterSolution(test, shell);
		shell->del("solution/input.txt");
		shell->del("solution/output.txt");
		int maxTestPoints = 0;
		double testPoints = 0;	
		bool terminatingTest = false;	
		for (int i = 0; i < modulesForTest[test].size(); i++) {
			int maxPoints = modulesForTest[test][i].second;
			maxTestPoints += maxPoints;
			if (terminatingAll || terminatingTest)
				continue;
			JudgeModule *module = modules[modulesForTest[test][i].first].first;
			std::pair<double, std::wstring> verdict = module->verdict();				
			double points = verdict.first * maxPoints;
			terminatingTest |= !verdict.first && modules[modulesForTest[test][i].first].second == TEST;
			terminatingAll |= !verdict.first && modules[modulesForTest[test][i].first].second == ALL;			
			fwprintf(logFile, L"\tJudge module \"%ls\" (%ls) verdict: ", module->id().c_str(), module->info().c_str());
			fwprintf(logFile, L"%.4lf of %d\n", points, maxPoints);
			fwprintf(logFile, L"\t%ls\n\n", verdict.second.c_str());			
			testPoints += points;
		}						
		if (terminatingAll) {
			fwprintf(logFile, L"All-terminating check failed. Testing terminated. The solution does not achieve any score.\n\n");
			totalPoints = 0;
			break;
		} 
		if (terminatingTest) {
			fwprintf(logFile, L"\tTest-terminating check failed. The solution does not achieve score for current test.\n\n");
			testPoints = 0;
		}
		fwprintf(logFile, L"Points for test: %.4lf of %d\n\n", testPoints, maxTestPoints);
		totalPoints += testPoints;
	}
	fwprintf(logFile, L"Total result points: %.4lf of %d\n", totalPoints, maxTotalPoints);	
	fclose(logFile);
	FILE *resultFile = fopen(resultFileName.c_str(), "w");
	fwprintf(resultFile, L"[%.4lf]", totalPoints);
	fclose(resultFile);	
}