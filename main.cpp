#include "WindowsShellCommands.h"
#include "JudgeFormat.h"

int main(int argc, char **argv) {
	if (argc != 5) {
		fwprintf(stdout, 
		     L"USAGE:\n"
			 L"  ujs_ji <workarea_path> <options_file> <result_file> <log_file>             \n\n"
			 L"  <workarea_path>  Path to the testing directory.                              \n"
			 L"  <options_file>   Path to the JSON file containing information about judge mo-\n"
			 L"                   dules to use and their options.                             \n"
			 L"  <result_file>    Path to the plain-text file to save result points in.       \n"
			 L"  <log_file>       Path to the plain-text file to save testing log in.         \n");
		return 0;		
	}
	WindowsShellCommands shell(argv[1]);
	JudgeFormat format(argv[2]); 
	format.runTests(argv[3], argv[4], &shell);	
	return 0;
}