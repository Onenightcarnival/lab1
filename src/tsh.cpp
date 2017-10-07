#include "tsh.h"
#include <sys/wait.h>
#include <string>
#include <sstream>

using namespace std;

void simple_shell::parse_command(char* cmd, char** cmdTokens) {
  // TODO: tokenize the command string into arguments
	stringstream strStream(cmd);
	char letter;
	string word;
	int i = 0;

	while(strStream.get(letter)){
		if(letter == ' ' || letter == '\n' || letter == EOF){
			char *cstr = new char[word.length() + 1];
			strcpy(cstr, word.c_str());
			cmdTokens[i++] = cstr;
			word.clear();
			continue;
		}
		else{
			word += letter;
			if(strStream.peek() == EOF){
				char *cstr = new char[word.length() + 1];
				strcpy(cstr, word.c_str());
				cmdTokens[i++] = cstr;
				word.clear();
			}
		}
	}
	cmdTokens[i++] = NULL;
	//cout << i << endl;
}

void simple_shell::exec_command(char **argv){
  // TODO: fork a child process to execute the command.
  // parent process should wait for the child process to complete and reap it
	int rc = fork();
	if(rc < 0){
		exit(1);//fork failed
	}
	else if(rc == 0){//child
		execvp(argv[0], argv[1] ? argv : &argv[0]);
	}
	else {//parent
		wait(NULL);
	}
}

bool simple_shell::isQuit(char *cmd){
  // TODO: check for the command "quit" that terminates the shell
	if(strcmp(cmd, "quit") == 0){
		return true;
	}
	else{
		return false;
	}

}
