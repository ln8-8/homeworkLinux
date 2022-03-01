#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <pwd.h>
#include <ucontext.h>
#include <cstring>
#include <cerrno>

// function to handle signal SIGUSR1
void handleSigusr1(int signum, siginfo_t* info, void* context) {

    // get pid of the sender
    std::cout << "PID - " << info->si_pid << std::endl;

    // get uid of the sender
    uid_t uid = info->si_uid;
    std::cout << "UID - " << uid << std::endl;
    
    // get username of the sender
    struct passwd *pws;
    pws = getpwuid(uid);
    std::cout << "UserName - " << pws->pw_name << std::endl;
     
    // get values of eip, eax and ebx registres
    ucontext_t* ucont = (ucontext_t*)context;
    std::cout << "EIP - " << ucont->uc_mcontext.gregs[REG_RIP] << std::endl;
    std::cout << "EAX - " << ucont->uc_mcontext.gregs[REG_RAX] << std::endl;
    std::cout << "EBX - " << ucont->uc_mcontext.gregs[REG_RBX] << std::endl;

    std::cout << std::endl;
}


int main() {

    // handle SIGUSR1
    struct sigaction sigAct;
    memset(&sigAct, 0, sizeof(struct sigaction));
    sigAct.sa_flags = SA_SIGINFO;
    sigAct.sa_sigaction = handleSigusr1;
    int action = sigaction(SIGUSR1, &sigAct, NULL);

    // check error while handleing signal
    if(action < 0) {
        std::cerr << "Error while handleing SIGUSR1 signal" << std::endl;
        exit(errno);
    }
    // infinite loop
    while(true) {
        sleep(10);
    }    
    return 0;
}