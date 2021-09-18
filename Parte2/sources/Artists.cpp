#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>            //Para usar na semente do rand

#include "Artists.h"

using namespace std;

/*
recebe um artist e o salva no arquivo ofstream pasado no parametro arq

*/
void salvarArtistBin(ofstream &arq, Artists artist){
    
    if(arq.is_open())
        arq.write((char *) &artist, sizeof(Artists));
    else{
        cout << "Arquivo não aberto duranta o salvamento do Artist" << endl;
        return;
    }

};

/*
Cria um artist apartir dos paramêtro passados e salva no arquivo passado no parametro 'arq', isso usando a função 'salvarArtistsBin'

*/
void createArtist(ofstream &arq, char id[], float followers, char genres[], char name[], int popularity){

    if(!arq.is_open()){

        cout << "Arquivo não aberto durante a criação do Artist" << endl;
        return;
    }
    try{
        Artists artist;

        strcpy( artist.id, id);
        artist.followers = followers;
        strcpy( artist.genres,genres);
        strcpy( artist.name, name);
        artist.popularity = popularity;
        
        salvarArtistBin(arq, artist);
    }
    catch(const exception& e){
        cout << "Erro ao criar o Artist" << endl;
        cout << e.what() << '\n';
    }
    
    

};

/*
Retorna, para onde chamado, um artist que se encontra n posições do inicio do arquivo ifstream passado no parametro arq

*/
Artists returnArtist(ifstream &arq, int n){
 
    Artists artist;
    if(!arq.is_open()){

        cout << "Arquivo não aberto durante o retorno da track" << endl;
        return artist;
        
    }

    //Move o ponteiro para n posições do inicio do arquivo 'artists.bin'
    arq.seekg(n*sizeof(Artists), ios_base::beg);
    //Lê a linha atual em que o ponteiro se encontra
    arq.read((char *) &artist,sizeof(Artists));

    return artist;
};

int nRegistrosArtists(ifstream &arq){ 
    /**
     * @brief                   Retorna a quantidade de registro armazenados no arquivo binário
     * @param arq               Endereço de um arquivo binário ifstream, onde deve está armazenados os artistas
     */

    
    if(arq.is_open()){

        arq.seekg(0, ios_base::end);
        int tam = int(arq.tellg()/sizeof(Artists)); 
        return tam; 

    }else{

        cout << "Erro no retorno da quantidades de elementos salvos" << endl;
        return -1; 

    }
    
}

/*
Lê do arquivo ifstream passado em '&arq' e retorna 'nQuantidade' de artist em um 
vetor de artist
Deve-se desalocar o vetor apos o uso

*/
Artists *returnVetArtists(ifstream &arq, int nQuantidade){

    Artists *vetArtist = new Artists[nQuantidade];

    if(!arq.is_open()){
        cout << "Arquivo não aberto durante o retorno do vetor" << endl;
        return vetArtist;
    }

    srand(time(NULL));//mudar os numeros sorteados
    int randN;

    if(nQuantidade > nRegistrosArtists(arq)){cout << "Requisição maior do que os já salvos" << endl; return vetArtist;}

    try{

        for(int i = 0; i < nQuantidade ;i++){
            randN = rand()%nRegistrosArtists(arq);//soteia de 0 ao numero de Artists - 1
            vetArtist[i] = returnArtist(arq, randN);
        }

    }catch(const exception& e){

        cout << "Erro ao ler nQuantidade de Artist do arquivo";
        cout << e.what() << endl;

    }
    return vetArtist;

}


Artists buscaArtist(ifstream &arq,string idArtist){
    /**
     * @brief               Função utilizada para retornar o artista com determinado ID
     * 
     * @param arq           Endereço de um arquivo ifstream
     * @param idArtist      Uma string contendo o ID de uma artista
     */

       
    
    Artists artist;//Criando artista

    int max = nRegistrosArtists(arq);//Valor máximo para busca

    //Busca no arquivo Binário
    for(int i = 0;i<max;i++){

        artist = returnArtist(arq, i);

        if(artist.id == idArtist)return artist;//Verifica se pe igual, caso sim retorna o artista

}

    //Usado para retornar um valor "nao encontrado" caso ocorra algum erro na localização do artista 
    Artists aux;
    strcpy(aux.id,"nao encontrado");
    strcpy(aux.name,"nao encontrado");
    
    return aux;
}

int localizarArtist(ifstream &arq,string idArtist){

    Artists artist;//Criando artista

    int max = nRegistrosArtists(arq);//Valor máximo para busca

    //Busca no arquivo Binário
    for(int i = 0;i<max;i++){

        artist = returnArtist(arq, i);

        if(artist.id == idArtist) return i;
}    
    return -1;
}

