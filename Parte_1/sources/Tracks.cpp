#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime> // para usar na semente do rand

#include "Tracks.h"

using namespace std;

/*
recebe uma track e a salva no arquivo ofstream passado no parametro arq

*/
void salvarTrackBin(ofstream &arq,Tracks track){
    if(arq.is_open())
        arq.write((char *) &track, sizeof(Tracks));
    else{
        cout << "Arquivo não aberto duranta o salvamento da Track" << endl;
        return;
    }
};



/*
Cria uma track, apartir dos paramêtro passados, e salva no arquivo ofstream passado no parametro 'arq', isso usando a função 'salvarTracksBin'

*/
void createTrack(ofstream &arq, char id[], char name[], int popularity, int duration_ms, bool is_explicit,char artists[],char id_artists[],
                    char release_date[],float danceability,float energy,int key,float loudness,bool mode,float speechiness,float acousticness,
                    float instrumentalness,float liveness,float valence,float tempo,int time_signature){

    if(!arq.is_open()){

        cout << "Arquivo não aberto duranta a criação da Track" << endl;
        return;
    }

    try{
    
        Tracks track;

        strcpy( track.id, id);
        strcpy( track.name, name);
        track.popularity = popularity;
        track.duration_ms = duration_ms;
        track.is_explicit = is_explicit;
        strcpy( track.artists, artists);
        strcpy( track.id_artists, id_artists);
        strcpy( track.release_date, release_date);
        track.danceability = danceability;
        track.energy = energy;
        track.key = key;
        track.loudness = loudness;
        track.mode = mode;
        track.speechiness = speechiness;
        track.acousticness = acousticness;
        track.instrumentalness = instrumentalness;
        track.liveness = liveness;
        track.valence = valence;
        track.tempo = tempo;
        track.time_signature = time_signature;
        
        salvarTrackBin(arq, track);

    }catch(const exception& e){

        cout << "Erros ao criar a Track" << endl;
        cout << e.what() << '\n';
    }
    

};

/*
retorna, para onde chamado, uma track que se encontra n posições do inicio do arquivo ifstream passado no parametro arq

*/
Tracks returnTrack(ifstream &arq,int n){

    Tracks track;
    if(!arq.is_open()){

        cout << "Arquivo não aberto durante o retorno da track" << endl;
        return track;

    }

    //move o ponteiro para n posições do inicio do arquivo aberto em arq
    arq.seekg(n*sizeof(Tracks), ios_base::beg);

    //lê a linha atual em que o ponteiro se encontra
    arq.read((char *) &track,sizeof(Tracks));
    
    return track;
};

/*
Retorna, para onde chamado, a quantidade de registros tracks no arquivo ifstream passado em '&arq'

*/
int nRegistrosTracks(ifstream &arq){ 

    if(arq.is_open()){

        arq.seekg(0, ios_base::end);
        int nReg = int(arq.tellg()/sizeof(Tracks)); 
        return nReg; 

    }else{

        cout << "Erro no retorno da quantidades de elementos salvos" << endl;
        return -1; 

    }
   
}

/*
Lê do arquivo ifstream passado em '&arq' e retorna 'nQuantidade' de tracks em um 
vetor de track 
Deve-se desalocar o vetor apos o uso

*/
Tracks *returnVetTracks(ifstream &arq, int nQuantidade){

    Tracks *vetTrack = new Tracks[nQuantidade];

    if(!arq.is_open()){
        cout << "Arquivo não aberto durante o retorno do vetor" << endl;
        return vetTrack;
    }

    srand(time(0));//mudar os numeros sorteados
    int randN;

    if(nQuantidade > nRegistrosTracks(arq)){cout << "Requisição maior do que os já salvos" << endl; return vetTrack;}

    try{

        for(int i = 0; i < nQuantidade ;i++){

            randN = rand()%nRegistrosTracks(arq);//soteia de 0 ao numero de Tracks - 1
            vetTrack[i] = returnTrack(arq, randN);
        }

    }catch(const exception& e){

        cout << "Erro ao ler nQuantidade de Track do arquivo";
        cout << e.what() << endl;

    }
    
    return vetTrack;

}