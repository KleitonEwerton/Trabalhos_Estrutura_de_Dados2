#include <iostream>
#include <fstream>
#include <string.h>
#include "Artists.h"
#include "Tracks.h"
#include "LeituraArtist.h"
#include "LeituraTrack.h"

using namespace std;

//Retornar numero aleatorio
int numAleatorio(int a, int b)
{   
    
    return a + rand() % (b - a + 1);
}

void verificaArquivosBin(string dirArq){

    string dirArqArt = dirArq + "artists.bin";
    string dirArqTra = dirArq + "tracks.bin";
    ifstream artBin(dirArqArt,ios::in);
    ifstream trackBin(dirArqTra,ios::in);
    
    if ((artBin.is_open()) && (trackBin.is_open())){
        cout << "Todos arquivos binarios ja existem." << endl;
    }
    else if ((artBin.is_open()) && (!trackBin.is_open())){
        cout << "O arquivo artist.bin existe, porem o arquivo tracks.bin nao. Sera feita sua construcao" << endl;
        leituraDeLinhasTrack(dirArq);

    }
    else if ((!artBin.is_open()) && (trackBin.is_open())){
        cout << "O arquivo tracks.bin existe, porem o arquivo artists.bin nao. Sera feita sua construcao" << endl;
        leituraDeLinhasArtists(dirArq);
    }
    else{
        cout << "Nenhum arquivo binario existe. Ambos serao construidos" << endl;
        cout << "Iniciando leitura de artistas" << endl;
        leituraDeLinhasArtists(dirArq);
        cout << "Iniciando leitura de tracks" << endl;
        leituraDeLinhasTrack(dirArq);
    }
}




int main(int arqc, char *arqv[]){

    //Verifica os argumentos 
    if(!arqv[1]){
        cout << "Não foi passado o endereço da pasta" << endl; return -1;}
    else{
        if(strlen(arqv[1]) < 10){//Verifica o tamanho do argumento
            cout << "Endereço muito curto, tente novamente" << endl; return -1;}
        }

    string dirArq(arqv[1]);
    verificaArquivosBin(dirArq);

    

    ifstream arq(dirArq+"tracks.bin", ios_base ::in| ios_base ::app);
    ifstream arq2(dirArq+"artists.bin", ios_base ::in | ios_base ::app);

    // Artists *teste = new Artists[100];
    // teste = returnVetArtists(arq2, 100);

    // for(int k = 0; k<100;k++)
    //     cout << teste[k].followers << " " << endl;

    // delete [] teste;
    int tam = nRegistrosTracks(arq);
    int aux1, aux2, aux3;
    char resposta;
    cout << "Como voce gostaria de visualizar os dados? \n C para console\n F para arquivo" << endl;
    cin >> resposta;

    //verificar qual opcao foi escolhida
    if (resposta == 'C' || resposta == 'c')
    {
        for (int i = 0; i < 10; i++)
        {

            //tamanho do arquivo artista
            aux1 = numAleatorio(0, tam);
            aux2 = nRegistrosArtists(arq2);
            aux3 = numAleatorio(0, aux2);

            Tracks tracks;
            tracks = returnTrack(arq, aux1);
            Artists artists;
            //arquivo posição
            artists = returnArtist(arq2, aux3);
                cout << "Artista = [Id: " << artists.id << " Seguidores: " << artists.followers << " Genero: " << artists.genres << " Nome: " << artists.name << " Popularidade: " << artists.popularity
                        << "] \nMusica = [Id :" << tracks.id << " Nome: " << tracks.name << " Popularidade: " << tracks.popularity << " Duracao: " << tracks.duration_ms << " Explicito: " << tracks.is_explicit << " Data de Lancamento: " << tracks.release_date << " Dancabilidade: " << tracks.danceability << " Energia: " << tracks.energy << " Chave: " << tracks.key << " Volume: " << tracks.loudness << " Modo: " << tracks.mode << " Discurso: " << tracks.speechiness << " Acustico: " << tracks.acousticness << " Instrumental: " << tracks.instrumentalness << " Vivacidade: " << tracks.liveness << " Valencia: " << tracks.valence << " Tempo: " << tracks.tempo << " Assinatura de tempo: " << tracks.time_signature << "]\n";
                        cout<<"\n-------------------------------------"<<endl;
            }
    }
    else if (resposta == 'F' || resposta == 'f')
    {
        ofstream outFile;
        outFile.open(dirArq+"Texto.txt", ios::out);
        if (!outFile)
            return 0;
        
        for (int i = 0; i < 100; i++)
        {
            Tracks tracks;
            aux1 = numAleatorio(0, tam);
            tracks = returnTrack(arq, aux1);
            //tamanho do arquivo artista
            aux2 = nRegistrosArtists(arq2);
            aux3 = numAleatorio(0, aux2);

            Artists artists;
            //arquivo posição
            artists = returnArtist(arq2, aux3);

            outFile << "Artista = [Id: " << artists.id << " Seguidores: " << artists.followers << " Genero: " << artists.genres << " Nome: " << artists.name << " Popularidade: " << artists.popularity
                    << "]\nMusica = [Id :" << tracks.id << " Nome: " << tracks.name << " Popularidade: " << tracks.popularity << " Duracao: " << tracks.duration_ms << " Explicito: " << tracks.is_explicit << " Data de Lancamento: " << tracks.release_date << " Dancabilidade: " << tracks.danceability << " Energia: " << tracks.energy << " Chave: " << tracks.key << " Volume: " << tracks.loudness << " Modo: " << tracks.mode << " Discurso: " << tracks.speechiness << " Acustico: " << tracks.acousticness << " Instrumental: " << tracks.instrumentalness << " Vivacidade: " << tracks.liveness << " Valencia: " << tracks.valence << " Tempo: " << tracks.tempo << " Assinatura de tempo: " << tracks.time_signature << "]\n";
                    
        }
        cout<<"Escrita feita no arquivo texto.txt. Ele estara na mesma pasta que os arquivos de entrada."<<endl;
        outFile.close();
    }
    else
    {
        cout << "Opcao Invalida" << endl;
    }
    arq.close();
    arq2.close();
	
    return 0;
}