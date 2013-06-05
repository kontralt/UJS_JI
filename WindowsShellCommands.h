#ifndef UJS_JI_WINDOWSSHELLCOMMANDS
#define UJS_JI_WINDOWSSHELLCOMMANDS

#include "ShellCommands.h"
#include <windows.h>
#include <psapi.h>
#pragma comment (lib, "psapi.lib") 
#include <string>

class WindowsShellCommands : public ShellCommands {
	std::string workarea;
public:
	WindowsShellCommands(const std::string &workareaPath);
	virtual bool exists(const std::string &source);
	virtual void copy(const std::string &source, const std::string &dest);
	virtual int exec(const std::string &dir, const std::string &source);
	virtual int execWithData(const std::string &dir, const std::string &source);
	virtual void del(const std::string &source);
};

#endif