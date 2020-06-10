/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Terminal.cpp
 * Author: marioandre
 * 
 * Created on 28 de Março de 2017, 11:31
 */

#include "Terminal.h"
#include <string>
#include <iostream>

Terminal::Terminal() {
    //adicionando o nome de usuario e nome da maquina na string cabeçalhoTerminal
    cabecalhoTerminal += pegarNomeUsuario();
    cabecalhoTerminal += "@";
    cabecalhoTerminal += pegarHostName();
    cabecalhoTerminal += ":~$";
}

Terminal::Terminal(const Terminal& orig) {
}

Terminal::~Terminal() {
}

string Terminal::pegarNomeUsuario(){
    //pegando o nome de usuario
    struct passwd *p;
    uid_t uid;
    uid = getuid();

    if ((p = getpwuid(uid)) == NULL)
        cerr << "getpwuid() error" << endl;
    else {
        return p->pw_name; //Retorna o nome de usuario da sessão
    }
}

string Terminal::pegarHostName(){
    //pegando o nome da maquina
    char hostname[1024];
    gethostname(hostname, 1024);
    
    return hostname; //Retorna o nome da maquina
}

vector<string> Terminal::coletorString(string s){
    //Separando comandos da string e colocando-os separadamentes no vector v1
    vector<string> v1;
    string palavra;
    int numeroDeCaracter;
    numeroDeCaracter = s.size();
   
    
    for (int j=0; j <= numeroDeCaracter; j++){
       if(s[j] == ' '){
          if (palavra != ""){
            v1.push_back(palavra);
          }
          palavra = "";
       }else if(s[j] == '\0'){
         if (palavra != ""){
            v1.push_back(palavra); 
         }  
       }else{
           palavra += s[j];
       }
    }
    return v1;
}

string Terminal::nomePrograma(vector<string> &ve){
    string np;
    np = ve.front();
    return np;
}

bool Terminal::tem_E(vector<string> &ve){
    //Verificando se algum comando coletado é o & (E comercial) 
    bool te; 
    te = false;
    
    for ( int k = 0 ; k < ve.size() ; k++ ){
        if(ve[k] == "&"){
            te = true;
            ve.erase(ve.begin()+k); //apagando a posição com valor & (E comercial) 
        }
    }
    
    return te;
}


int Terminal::run()
{
    string comandoSair;
   
    while(comandoSair != "exit"){
        cout << cabecalhoTerminal;
        getline(cin,comando);
        comandoSair = comando;
        
        if(comandoSair != "exit"){
            vector<string> parametros = coletorString(comandoSair);
            
            if(parametros.size() != 0){ //verifica se foi digitado algum caracter
                string nomeDoPrograma = nomePrograma(parametros);
                bool tem_e = tem_E(parametros);
            
                if (nomeDoPrograma == "jobs"){
                    // mostra conteudo de _processes
                    for (map<pid_t,Process*>::iterator it=_processes.begin(); it != _processes.end(); ++it){
                        cout << "PID:" << it->first << " => " << "Status:" << it->second->status() << '\n';
                    }
                
                }else{
                
                    Process p(nomeDoPrograma, parametros, tem_e);
                    
                    _processes.insert (pair<pid_t,Process*>(p.pid(),&p)); //mapa para colocar pid e status
                
                }
            }   
        }   
    }   
}

// HERE IS HOW TO TRIM SPACES FROM THE BORDERS OF A STRING
// AQUI É COMO TRIM ESPAÇOS DAS FRONTEIRAS DE UM STRING
/*string Terminal::trim(string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
}*/