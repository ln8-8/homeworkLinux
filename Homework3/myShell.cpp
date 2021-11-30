#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <sys/wait.h>
#include <vector>
#include <sys/stat.h>
#include <fcntl.h>

// function to check if directory existd or nor
bool IsDirectoryExists(const std::string &s) {
	struct stat buffer;
  	return (stat (s.c_str(), &buffer) == 0);
}

int main() {
	
	
	std::string silentshellDir = "/opt/silentshell/";

	// check existing of silentshellDir
	if(!IsDirectoryExists(silentshellDir)) {

		// if doesn't exists make directrory
		int makeSilentshell = mkdir("/opt/silentshell", 0777);

		// check error when makeing
		if(makeSilentshell < 0) {
			std::cerr << "Something went wrong when makeing Silentshell" << std::endl;
		}
	}

	// start working of shell 
	while(true) {

		// create new process
		int pid = fork();
		
		// process couldn't be created because of error
		if(pid < 0) {
			std::cerr << "Error when forking" << std::endl;
			exit(errno);
	        }
		
		// child process
		if(pid == 0) {
			
			// make directory with pid name
			int PID = getpid();
			int makeDirPID = mkdir(((std::string)"/opt/silentshell/" + std::to_string(PID)).c_str(), 0777);
			
			//check error when makeing directory
			if(makeDirPID < 0) {
				std::cerr << "Error when makeing directory" << std::endl;
				exit(errno);
			}
	
			// create file for output
			std::string strOutput = "/opt/silentshell/" + std::to_string(PID) + "/out.std";
			const char* forOutput = strOutput.c_str();
			
			// open file
			int outputDiskr = open(forOutput, O_CREAT|O_WRONLY, S_IRWXU|S_IRWXG|S_IRWXO);
			
			// check error when openning file
			if(outputDiskr < 0) {
				std::cerr << "Something went wrong when openning file "  << std::endl;
				exit(errno);
			}
			
			// duplicate file
			int dupOutput = dup2(outputDiskr, 1);
			
			// check error when duplicating	
			if(dupOutput < 0) {
				std::cerr << "Something went wrong when duplicating file " << std::endl;
                                exit(errno);
			}
			
                        // create file for stderr
                        std::string strStderr = "/opt/silentshell/" + std::to_string(PID) + "/err.std";
                        const char* forStderr = strStderr.c_str();

                        // open file
                        int stderrDiskr = open(forStderr, O_CREAT|O_WRONLY, S_IRWXU|S_IRWXG|S_IRWXO);

                        // check error when openning file
                        if(stderrDiskr < 0) {
                                std::cerr << "Something went wrong when openning file "  << std::endl;
                                exit(errno);
                        }

                        // duplicate file
                        int dupStderr = dup2(stderrDiskr, 2);

                        // check error when duplicating 
                        if(dupStderr < 0) {
                                std::cerr << "Something went wrong when duplicating file " << std::endl;
                                exit(errno);
                        }


			char line[124];

			// input command and arguments 
			if(fgets(line, sizeof(line),stdin) != NULL) {
				
				// devide input into words
				char *args[64];
        			char **next = args;
        			char *temp = strtok(line, " \n");
        			while (temp != NULL)
        			{
            				*next++ = temp;
            				temp = strtok(NULL, " \n");
       				}
       				*next = NULL;
				
				// ecxecute the programm
	     			int executed = execvp(args[0], args);

				// check error when we use executed
				if(executed < 0) {
					std::cerr << "Error while executing" << std::endl;
					exit(errno);
				}

			}
			
			// close forOutput file
			close(dupOutput);

			// close forStderr file
			close(dupStderr);
		}

		int status = 0;
		
		// wait for child process in parent
		if(pid > 0) {
			int waited = waitpid(pid, &status, 0);

			// check error when waiting
			if (waited < 0) {
				std::cerr << "Error while waiting" << std::endl;
				exit(errno);
			}

		}


	}	

	return 0;
}
