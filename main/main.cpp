#include "../includes/includes.hpp"

int main(int argc, char *argv[]) {
    commandExecutor cExecutor;
    cExecutor.getCommand();
    cExecutor.getTimeUnit();
    cExecutor.getTime();
    cExecutor.startTimer();
    cExecutor.writeCommand2File();
    cExecutor.runCommand();
    cExecutor.printOutputOfCommand();
    cExecutor.deleteCreatedFile();
    return 0;
}