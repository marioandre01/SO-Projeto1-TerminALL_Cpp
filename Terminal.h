/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Terminal.h
 * Author: marioandre
 *
 * Created on 28 de Março de 2017, 11:31
 */

#ifndef TERMINAL_H
#define TERMINAL_H

#include "Process.h"
#include <map>
#include <string>
#include <vector>
#include <sys/types.h> //biblioteca para usar getpwuid() e getuid()
#include <pwd.h> //biblioteca para usar getpwuid()
#include <unistd.h> //biblioteca para usar gethostname() e getuid()

using namespace std;

class Terminal {
public:
    Terminal();
    Terminal(const Terminal& orig);
    virtual ~Terminal();
    
    int run();
    pid_t pid();
    
private:
    //std::string trim(std::string& str);
    //bool extract_cmd(std::string cmd, std::vector<std::string> * tokens);
    
    string cabecalhoTerminal; 
    string comando;
    pid_t _my_pid;
    pid_t _parent;
    typedef map<pid_t,Process*> ProcessMap;
    ProcessMap _processes;
    string pegarNomeUsuario();
    string pegarHostName();
    vector<string> coletorString(string s);
    bool tem_E(vector<string> &ve);
    string nomePrograma(vector<string> &ve);
    
};

#endif /* TERMINAL_H */

