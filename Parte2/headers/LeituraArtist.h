#ifndef DADAF9AD_6933_4AB9_BA02_D0DB79BD2AD1
#define DADAF9AD_6933_4AB9_BA02_D0DB79BD2AD1

#include <iostream>
#include <string.h>
#include <fstream>
#include <cstring>
#include <vector>
#include "Artists.h"
#include "Tools.h"

using namespace std;

void leituraDeLinhasArtists(string dirArq)
{
    string idAux = "";
    string followAux = "1.1";
    string genresAux = "";
    string nameAux = "";
    string popularityAux = "1.1";
    int popularityAuxInt = 0;
    float followersAuxFloat = 0;

    string dirArqArt = dirArq + "artists.csv";
    
    string auxGe="";
    string auxNo="";

    ifstream arq(dirArqArt, ios_base::in | ios_base::out | ios_base::app);
    ofstream arq1(dirArq+"artists.bin", ios_base:: out | ios_base::app | ios_base::binary);

    string temp;
    int v = 0;
    int n = 0;
    char auxAspa[500];
    while (arq.good() && v < 1104350) // MUDAR PARA TAM ARQUIVO DPS.
    {   
        if(v == 0){
            getline(arq, idAux, ',');
            getline(arq, followAux, ',');
            getline(arq, genresAux, ',');
            getline(arq, nameAux, ',');
            getline(arq, popularityAux, '\n');
        }else{

        getline(arq, idAux, ',');

        getline(arq, followAux, ',');
        
        getline(arq, genresAux, ']');
        
        strcpy(auxAspa,genresAux.c_str());

        if(auxAspa[0] == '"'){
            genresAux += ']';
            genresAux += '"';
        }   
        else
            genresAux += "]";

        getline(arq, temp, ',');

        getline(arq,nameAux,'\n');

        char name[nameAux.length()+1];
        strcpy(name, nameAux.c_str());

        string inversoPopu;
        int i = nameAux.length();

     

        while( name[i] != ','){

            inversoPopu += name[i];
            i -= 1;
            nameAux = nameAux.substr(0,  nameAux.length()-1);
            
        }

        string auxInver="";
        int aux = inversoPopu.length();


        while(aux != 0){

            auxInver += inversoPopu[aux];
            aux -= 1;
        }

        popularityAux = auxInver;
        popularityAux = popularityAux.substr(1, popularityAux.length());
        if (v > 0)
        {
            int n = idAux.length();
            char idAuxChar[n+1];
            strcpy(idAuxChar, idAux.c_str()); 

            n = genresAux.length();
            char genresAuxChar[n+1];
            strcpy(genresAuxChar, genresAux.c_str());         

            

            n = nameAux.length();
            char nameAuxChar[n+1];
            
            strcpy(nameAuxChar, nameAux.c_str());          
            
            try{
               followersAuxFloat = stof(followAux);
            }
            catch(const exception& e){
                followersAuxFloat = 0.0;
            }

            try{
               popularityAuxInt = stoi(popularityAux);
            }
            catch(const exception& e){
                popularityAuxInt = 0;
            }
            
            // popularityAuxInt = stoi(popularityAux);

            

            try
            {
                maiusculo(nameAuxChar);
                createArtist(arq1,idAuxChar, followersAuxFloat, genresAuxChar,nameAuxChar,popularityAuxInt);
            }
            catch(const exception& e)
            {
                cout << e.what() << '\n';
            }
            
            
        }}
        v += 1;
    }
    arq.close();
    arq1.close();
}

#endif /* DADAF9AD_6933_4AB9_BA02_D0DB79BD2AD1 */
