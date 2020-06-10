/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Process.h
 * Author: marioandre
 *
 * Created on 28 de Março de 2017, 11:31
 */

#ifndef PROCESS_H
#define PROCESS_H

#include <sys/types.h>
#include <string>
#include <vector>

using namespace std;

class Process {
public:
    Process();
    Process(string & program, vector<string> & params, bool block);
    Process(const Process& orig);
    virtual ~Process();
    
    int wait2();
    pid_t pid();
    int status();
    
private:
    void exec(string & program, vector<string> & params);
    static char * string_to_c_convert(const string & s);
    
    pid_t  _my_pid;
    pid_t  _parent;
    int _status;
};

#endif /* PROCESS_H */

