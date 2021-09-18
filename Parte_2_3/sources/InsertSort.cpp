#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>

#include "Artists.h"
#include "InsertSort.h"
using namespace std;

int comparacaoInterna =0;
int movimentosInternos =0;
int comparacoesMedias=0;
int movimentosMedias=0;
long long tempoInterno = 0;
long long tempoMedio=0;

/**
 * @brief ordena o vetor comparando o followers de cada artista
 * 
 * @param vet Vetor de artista
 * @param tam Tamanho do vetor
 */

void ordenaVetor(Artists vet[] , int tam){
    for(int k = 1; k < tam ; k++){
        int ch = vet[k].followers;
        int j = k-1;
        comparacaoInterna+=1;
        int followers = vet[j].followers;
        while( ch < followers && j >=0){
            vet[j+1] = vet[j];
            movimentosInternos+=1;
            j--;
        }
        vet[j+1] = vet[k];
        movimentosInternos+=1;
    }   
}

/**
 * @brief Faz as metricas do insersort a partir de parametros lidos em arquivo e salva os dados no arquivo de texto
 * 
 * @param enderecoPastas endereço onde serão salvos os dados
 * @param nomeArquivo nome do arquivo que serão salvos os dados
 * @param repeticao numero de vezes que será feito a ordenação. (Usado no caso de testes).
 */

void metricaInsertSort(string enderecoPastas, string nomeArquivo, int repeticao){

    ifstream arqBin(enderecoPastas + "artists.bin");
    ifstream arqSort(enderecoPastas + "sort.dat");
    ofstream arqOut(enderecoPastas + nomeArquivo, ios_base::app);
    int r = repeticao;
    arqOut << "REALIZANDO O TESTE DO INSERTSORT\n";
    cout << "REALIZANDO O TESTE DO INSERTSORT"<<endl;

    string aux;             // String auxiliar para primeira linha do arquivo sort.dat

    getline(arqSort, aux);
    string nAux, mAux;
    int n, m;
    int i = 0;


    while (arqSort.good() && i<r){

        i++;
        getline(arqSort, nAux, ',');
        getline(arqSort, mAux);
        n = stoi(nAux);
        m = stoi(mAux);

        arqOut << "\nPARA N = " << n<<"\n";

        for(int j=0;j<m;j++){

            Artists *vet = returnVetArtists(arqBin, n);

            auto inicio = chrono::high_resolution_clock::now();
            ordenaVetor(vet,n);
            auto final = chrono::high_resolution_clock::now() - inicio;
            tempoInterno = chrono::duration_cast<chrono::microseconds>(final).count();
            delete[] vet;//DESALOCANDO O VETOR

            arqOut << "\nMOVIMENTAÇÕES: " << movimentosInternos << " COMPARAÇÕES: " << comparacaoInterna <<" TEMPO DE EXECUÇÃO(EM SEGUNDOS): "<<tempoInterno/1000000.0 << "\n";
            //INCREMENTO DAS MEDIAS
            comparacoesMedias += comparacaoInterna; movimentosMedias += movimentosInternos; tempoMedio += tempoInterno;
            
            //ZERANDO OS CONTADORES
            comparacaoInterna = 0; 
            movimentosInternos = 0;
        }
        
        comparacoesMedias /=3;movimentosMedias /=3;tempoMedio /=3;

        //ESCREVENDO NO OUTFILE
        if(m>1)arqOut << "\nMEDIAS: MOVIMENTAÇÕES: " << movimentosMedias << " COMPARAÇÕES: " << comparacoesMedias <<" TEMPO DE EXECUÇÃO(EM SEGUNDOS): "<< tempoMedio/1000000.0 <<"\n\n";
        arqOut << "__________________________________________________________________________________________________________________\n";
        //ZERANDO OS CONTADORES
        comparacoesMedias = 0;tempoMedio = 0; movimentosMedias = 0;
        }
    
    arqBin.close();arqOut.close();arqSort.close();
}