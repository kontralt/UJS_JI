#ifndef UJS_JI_JUDGEMODULEBUILDER
#define UJS_JI_JUDGEMODULEBUILDER

#include "JudgeModule.h"
#include "RE_ACM.h"
#include "PE_ACM.h"
#include "TLE_ACM.h"
#include "MLE_ACM.h"
#include "WA_ACM.h"
#include "TLE_Asympt2.h"
#include <string>
#include <map>

class JudgeModuleBuilder {
	std::map<std::wstring, JudgeModule *(*)(const std::wstring &)> creationMethods;
public:

	JudgeModuleBuilder() {
		creationMethods.insert(make_pair(L"RE_ACM", &RE_ACM::create));		
		creationMethods.insert(make_pair(L"PE_ACM", &PE_ACM::create));		
		creationMethods.insert(make_pair(L"TLE_ACM", &TLE_ACM::create));
		creationMethods.insert(make_pair(L"MLE_ACM", &MLE_ACM::create));
		creationMethods.insert(make_pair(L"WA_ACM", &WA_ACM::create));
		creationMethods.insert(make_pair(L"TLE_Asympt2", &TLE_Asympt2::create));
	}

	bool canBuild(const std::wstring &judgeModuleId) {
		return creationMethods.find(judgeModuleId) != creationMethods.end();
	}

	JudgeModule *build(const std::wstring &judgeModuleId, const std::wstring &options) {
		std::map<std::wstring, JudgeModule *(*)(const std::wstring &)>::iterator i = creationMethods.find(judgeModuleId);
		if (i == creationMethods.end())
			return NULL;
		return i->second(options);
	}

};

#endif