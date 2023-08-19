#include <stdio.h>
#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <filesystem>
#include <fstream>
#include <boost/asio.hpp>
#include <boost/asio/deadline_timer.hpp>
using namespace std;


class commandExecutor {
public:
    int getCommand();
    int getTimeUnit();
    int getTime();
    int startTimer();
    int writeCommand2File();
    int runCommand();
    int printOutputOfCommand();
    int deleteCreatedFile();
private:
    char buffer1[51120];
    int fileSize;
    char enterCommandDesc[31] = "Enter command to be executed: ";
    char enterTimeUnitDesc[67] = "Enter time unit.\n" \
    "\"h\" for hour, \"m\" for minute and \"s\" for second: ";
    char timeDesc[45] = "Enter time ( no floats allowed [Ex. 34.5]): ";
    char inputSuccess[19] = "Input successful.\n";
    char inputError[22] = "Input throwed error.\n";
    char bashStart[22] = "#! /bin/bash\n\n";
    char feofReached[24] = "Reached end of output.\n";
    string command;
    char timeUnit[2];
    char second1[2] = "s";
    char minute1[2] = "m";
    char hour1[2] = "h";
    int time;
    FILE *bufFile;
    ofstream anotherBufFile;
    ifstream inputFileStream;
    size_t fileSizeInBytes;
    boost::asio::io_context ioContext;
};

int commandExecutor::getCommand() {
    printf(enterCommandDesc);
    getline(cin >> ws, command);
    if (command.empty() == 0) {
        printf("Input is %s. %s", command.c_str(), inputSuccess);
    } else if (command.empty() == 1) {
        fprintf(stderr, "%s", inputError);
    }
    return 0;
}

int commandExecutor::getTimeUnit() {
    printf(enterTimeUnitDesc);
    if (scanf("%s", timeUnit) >= 0) {
        printf("Input is %s. %s", timeUnit, inputSuccess);
    } else {
        fprintf(stderr, "%s", inputError);
    }
    return 0;
}

int commandExecutor::getTime() {
    printf(timeDesc);
    if (scanf("%i", &time) >= 0) {
        printf("Input is %i. %s", time, inputSuccess);
    } else {
        fprintf(stderr, "%s", inputError);
    }
    return 0;
}

int commandExecutor::startTimer() {
    boost::asio::deadline_timer timer(ioContext);
    printf("Time unit is %s.\n", timeUnit);
    if (strcmp(timeUnit, second1) == 0) {
        timer.expires_from_now(boost::posix_time::seconds(time));
    } else if (timeUnit == minute1) {
        timer.expires_from_now(boost::posix_time::minutes(time));
    } else if (timeUnit == hour1) {
        timer.expires_from_now(boost::posix_time::hours(time));
    } else {
        fprintf(stderr, "time unit entered uncorrectly.\n");
        exit(1);
    }
    timer.wait();
    
    return 0;
}

int commandExecutor::writeCommand2File() {
    anotherBufFile.open("./command2Exec.sh");
    anotherBufFile.write(bashStart, sizeof(bashStart));
    anotherBufFile.write(command.c_str(), command.size());
    anotherBufFile.close();
    return 0;
}

int commandExecutor::runCommand() {
    bufFile = popen("chmod +x ./command2Exec.sh", "r");
    pclose(bufFile);
    bufFile = popen("./command2Exec.sh", "r");
    return 0;
}

int commandExecutor::printOutputOfCommand() {
    while (fgets(buffer1, sizeof(buffer1), bufFile)) {
        printf("output per line: %s", buffer1);
    }
    if (feof(bufFile)) {
        printf(feofReached);
    }
    pclose(bufFile);
    return 0;
}

int commandExecutor::deleteCreatedFile() {
    printf("Waiting for signals of system...\n");
    boost::asio::deadline_timer timer(ioContext);
    timer.expires_from_now(boost::posix_time::seconds(2));
    timer.wait();
    remove("command2Exec.sh");
    return 0;
}
