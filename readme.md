Hello! This is a simple bash command executor tool ( for linux of course ).
You may compile the tool with the code below: ``g++ main.cpp -o main -lboost_system -lboost_thread -lpthread``.
The "why we compile tool in that way?" regards to the code i used in the project, i used the libboost header for the timer part of the project so you must link boost libraries that the compiler may do its job ( compile the code ).
