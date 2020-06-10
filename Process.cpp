/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Process.cpp
 * Author: marioandre
 * 
 * Created on 28 de Março de 2017, 11:31
 */

#include "Process.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <signal.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

Process::Process() {
}

Process::Process(string & program, vector<string> & params, bool block)
{
    _my_pid = fork();  //Criando um processo filho
    
    if(_my_pid == -1) // fork falhou
    {
        cerr << "fork falhou!" << endl;
        exit(-1);
    }else if(_my_pid == 0) // Este é o processo filho
    {
        
        exec(program, params);
        exit(0);   
    }
    else // Este é o processo pai
    {
        
        if(block == false){
           
            wait(&_status);
            
        }
        //usleep(10000);    
    }    
}

Process::Process(const Process& orig) {
}

void Process::exec(string & program, vector<std::string> & params){
    
    vector<char *> argv;
    
    //pegando o conteudo do vetor params do tipo string e convertendo-o para o vetor argv do tipo char *
    //Em resumo se copiou o conteudo do vetor params e se colocou no vetor argv, só agora o conteudo é do tipo char *
    transform(params.begin(), params.end(), back_inserter(argv), string_to_c_convert);
    
    //Adicionando no vector argv o valor NULL na ultima posição
    argv.push_back(NULL); 
    
    //Criando array parametros 
    char *parametros[argv.size()];
    
    //Pegando conteudo do vetor argv e colocando no array parametros
    for ( int i = 0 ; i < argv.size() ; i++ ){
        parametros[i] = argv[i];
    }
    
    //Executando o programa junto com seus parametros
    execvp(argv.front(), parametros);
       
}

pid_t Process::pid(){
   return getpid(); 
}

int Process::status(){
    return _status;
}

Process::~Process() {
}

char * Process::string_to_c_convert(const string & s)
{
    char *pc = new char[s.size()+1];
    strcpy(pc, s.c_str());
    return pc;
}

//Observaçẽs:
// HERE IS HOW TO TRANSFORM A vector<string> TO A char * const []
// C++ STD provides a series of algorithms. We will use one of them: transform.
// transform will take a element series from a container (ex. vector) and call
// the function pointer passed as argument to transform each member of the series.
// The result of the transformation is stored in another container.
//
// For instance, to transform all strings in a vector<string> to c-like strings in
// a vector<char*>, use transform like this:
// vector<string> input;
// vector<char *> argv;
// transform(input.begin(), input.end(), back_inserter(argv), string_to_c_convert);
//
// If you need, you can cast the vector<char*> argv to a c-like array of char*:
// char * const args[] = (char*const*)&argv;
