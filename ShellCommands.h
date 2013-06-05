#ifndef UJS_JI_SHELLCOMMANDS
#define UJS_JI_SHELLCOMMANDS

#include <string>

class ShellCommands {
public:
	struct ExecData {
		int exitCode;
		int time;
		int memory;
	} execData;
	virtual ~ShellCommands();
	virtual bool exists(const std::string &source) = 0;
	virtual void copy(const std::string &source, const std::string &dest) = 0;
	virtual int exec(const std::string &dir, const std::string &source) = 0;
	virtual int execWithData(const std::string &dir, const std::string &source) = 0;
	virtual void del(const std::string &source) = 0;	
};

#endif