#ifndef F390D4CF_BEC2_43B0_A1A6_739D7B767359
#define F390D4CF_BEC2_43B0_A1A6_739D7B767359

#include <iostream>
#include <string.h>
#include <fstream>
#include <cstring>
#include <vector>
#include "Tracks.h"


using namespace std;

void leituraDeLinhasTrack(string dirArq) 
{   
    string dirArqTrack = dirArq + "tracks.csv";
    ifstream arq(dirArqTrack, ios_base::in| ios_base::app);
    ofstream arq1(dirArq+"tracks.bin", ios_base::app| ios_base::binary);

    string idAux;
    string nameAux;
    string popularityAux;
    float popularityAuxInt;
    
    string durationAux;
    int durationAuxInt;
    
    string explicitoAux;
    int explicitoAuxBool;
    
    string artistaAux;
    string idArtistAux;
    string realeseAux;
    
    string danceabilityAux;
    float danceabilityAuxFloat;
    
    string energyAux;
    float energyAuxFloat;
    
    string keyAux;
    int keyAuxInt;
    
    string loudnessAux;
    float loudnessAuxFloat;
    
    string modeAux;
    int modeAuxInt;
    
    string speechinessAux;
    float speechinessAuxFloat;
    
    string acousticnessAux;
    float acousticnessAuxFloat;
    
    string instrumentalnessAux;
    float instrumentalnessAuxFloat;
    
    string livenessAux;
    float livenessAuxFloat;
    
    string valenceAux;
    float valenceAuxFloat;
    
    string tempoAux;
    float tempoAuxFloat;
    
    string signatureAux;
    int signatureAuxInt;

     
    
    int j = 0;
    int g=-1;
    
    string temp;
    while (arq.good() && j < 586672)
    {   
        g=-1;
        string auxDoName;

        if(j == 0){

            getline(arq, idAux, ',');
            getline(arq, nameAux, ',');
            getline(arq, popularityAux, ',');
            getline(arq, durationAux, ',');
            getline(arq, explicitoAux, ',');
            getline(arq, artistaAux, ',');
            getline(arq, idArtistAux, ',');
            getline(arq, realeseAux, ',');
            getline(arq, danceabilityAux, ',');
            getline(arq, energyAux, ',');
            getline(arq, keyAux, ',');
            getline(arq, loudnessAux, ',');
            getline(arq, modeAux, ',');
            getline(arq, speechinessAux, ',');
            getline(arq, acousticnessAux, ',');
            getline(arq, instrumentalnessAux, ',');
            getline(arq, livenessAux, ',');
            getline(arq, valenceAux, ',');
            getline(arq, tempoAux, ',');
            getline(arq, signatureAux, '\n');
        }

        if (j > 0){   
//7u1Y763EnkRgtz5DbDqRR5,"Чебурашка (Из сказки ""Чебурашка"")",41,94480,0,"['Klara Rumyanova', 'Инструментальный ансамбль «Мелодия»']","['4lw4yhQJlm5xwpXUCxxiqo', '0dfQQdIIZHgAam7wcpi7NP']",1983-01-01,0.539,0.174,9,-18.556,0,0.081,0.867,1.53e-06,0.116,0.611,97.697,4
//3gJem1ky3SSSdBAkgHk5sA,"Cello Suite No. 5 in C Minor, BWV 1011: III. Courante",40,116027,0,"['Johann Sebastian Bach', 'Yo-Yo Ma']","['5aIqB5nVVvmFsvSdExz408', '5Dl3HXZjG6ZOWT5cV375lk']",1983,0.268,0.134,0,-20.43,0,0.039,0.965,0.862,0.11,0.76,83.099,3

            getline(arq, idAux, ',');
            getline(arq, nameAux, ',');

            if(nameAux[0] == '"'){
            while(g<0){
                getline(arq, auxDoName,',');
                try{
                    popularityAuxInt = stoi(auxDoName);
                    g=1;
                    }
                catch(const exception& e)
                {   
                    nameAux +=auxDoName;
                }
            }
        }else{getline(arq, auxDoName,',');}
            // cout << "\n-----------\n";
            // cout << "nameAux " << nameAux << endl;
            // cout << "popula " <<popularityAuxInt << endl;

            getline(arq, durationAux, ',');

            // cout << "Dura " << durationAux << endl;

            getline(arq, explicitoAux, ',');
            
            // cout << "explicitoAux " << explicitoAux << endl;


            getline(arq, artistaAux, ']');
            artistaAux +=']';

            getline(arq, temp, ',');

            // cout << "artistaAux " << artistaAux << endl;

            getline(arq, idArtistAux, ']');
            getline(arq, temp, ',');
            idArtistAux+= ']';

            // cout << "idArtistAux " << idArtistAux << endl;

            getline(arq, realeseAux, ',');

            // cout << "realeseAux " << realeseAux << endl;

            getline(arq, danceabilityAux, ',');
            getline(arq, energyAux, ',');
            getline(arq, keyAux, ',');
            getline(arq, loudnessAux, ',');
            getline(arq, modeAux, ',');
            getline(arq, speechinessAux, ',');
            getline(arq, acousticnessAux, ',');
            getline(arq, instrumentalnessAux, ',');
            getline(arq, livenessAux, ',');
            getline(arq, valenceAux, ',');
            getline(arq, tempoAux, ',');
            getline(arq, signatureAux, '\n');

            int n = idAux.length();
            char idAuxChar[n+1];
            strcpy(idAuxChar, idAux.c_str());
            
            n = nameAux.length();
            char nameAuxChar[n+1];
            strcpy(nameAuxChar, nameAux.c_str());

            try{
                durationAuxInt = stoi (durationAux);
            }
            catch(const exception& e)
            {
               durationAuxInt = 0;
            }
            
            try{
                explicitoAuxBool = stoi (explicitoAux);
            }
            catch(const exception& e)
            {
               explicitoAuxBool = 1;
            }
            
            
            n = artistaAux.length();
            char artistaAuxChar[n+1];
            strcpy(artistaAuxChar, artistaAux.c_str());

            n = idArtistAux.length();
            char idArtistAuxChar[n+1];
            strcpy(idArtistAuxChar, idArtistAux.c_str());

            n = realeseAux.length();
            char realeseAuxChar[n+1];
            strcpy(realeseAuxChar, realeseAux.c_str());
            
            try{
                danceabilityAuxFloat = stof (danceabilityAux);
            }
            catch(const exception& e)
            {
               danceabilityAuxFloat = 0;
            }
            
            try{
                energyAuxFloat = stof (energyAux);
            }
            catch(const exception& e)
            {
              energyAuxFloat = 0;
            }

            try{
                keyAuxInt = stoi (keyAux);
            }
            catch(const exception& e)
            {
              keyAuxInt = 0;
            }

            try{
                loudnessAuxFloat = stof (loudnessAux);
            }
            catch(const exception& e)
            {
                loudnessAuxFloat = 0;
            }

            try{
                modeAuxInt = stoi (modeAux);
            }
            catch(const exception& e)
            {
                modeAuxInt = 0;
            }

            try{
                speechinessAuxFloat = stof (speechinessAux);
            }
            catch(const exception& e)
            {
                speechinessAuxFloat = 0;
            }

            try{
                acousticnessAuxFloat = stof (acousticnessAux);
            }
            catch(const exception& e)
            {
                acousticnessAuxFloat = 0;
            }

            try{
                instrumentalnessAuxFloat = stof (instrumentalnessAux);
            }
            catch(const exception& e)
            {
                instrumentalnessAuxFloat = 0;
            }

            try{
                livenessAuxFloat = stof (livenessAux);
            }
            catch(const exception& e)
            {
                livenessAuxFloat = 0;
            }

            try{
                valenceAuxFloat = stof (valenceAux);
            }
            catch(const exception& e)
            {
                valenceAuxFloat = 0;
            }
        
            try{
                tempoAuxFloat = stof (tempoAux);
            }
            catch(const exception& e)
            {
                tempoAuxFloat = 0;
            }
            
            try{
                signatureAuxInt = stoi (signatureAux);
            }
            catch(const exception& e)
            {
                signatureAuxInt = 0;
            }
            
            try
            {
                createTrack(arq1,idAuxChar,nameAuxChar,popularityAuxInt,durationAuxInt,explicitoAuxBool,artistaAuxChar,idArtistAuxChar,
                    realeseAuxChar,danceabilityAuxFloat,energyAuxFloat,keyAuxInt,loudnessAuxFloat,modeAuxInt,speechinessAuxFloat,acousticnessAuxFloat,
                        instrumentalnessAuxFloat,livenessAuxFloat,valenceAuxFloat,tempoAuxFloat,signatureAuxInt);
            }
            catch(const exception& e)
            {
                cout << e.what() << '\n';
            }
            
            
        }
        j += 1;
    }
    arq.close();

}


#endif /* F390D4CF_BEC2_43B0_A1A6_739D7B767359 */
