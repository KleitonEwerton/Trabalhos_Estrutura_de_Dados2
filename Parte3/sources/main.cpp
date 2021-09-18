#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>

#include "Tools.h"
#include "BoyerMoore.h"
#include "ForcaBruta.h"
#include "KMP.h"

using namespace std;


int main(int arqc, char *arqv[]){

    //Verifica os argumentos 

    if(!arqv[1]){
        cout << "Não foi passado o endereço da pasta" << endl; return -1;}
    else{
        if(strlen(arqv[1]) < 10){//Verifica o tamanho do argumento
            cout << "Endereço muito curto, tente novamente" << endl; return -1;}
    }
    string dirArq(arqv[1]);

    if(verificaInputFile(dirArq))
        main_menu(dirArq);
       
    return 0;
}
