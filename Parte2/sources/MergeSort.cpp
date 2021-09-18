#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>

#include "Tracks.h"
#include "Artists.h"

using namespace std;

int movimentacoesMS= 0;
int comparacoesMS = 0;
void mergeArtists(Artists* vet, int p, int q, int r){
    /**
    *  @brief Algoritmo merge utilizado para o Merge Sort
    * 
    *  @param vet        Um ponteiro de um vetor de Artists
    *  @param p          Primeira posição do primeiro vetor
    *  @param r          Primeira posição do outro vetor
    *  @param q          Tamanho do vetor - 1
    * 
    *                    Exemplo de uso para um vetor artists de tamanho 100:
    * 
    *                       mergeArtists(vet, 0, (p+r)/2, 99)
    * 
    */
        
    

    //p1                 Primeiro indice do primeiro vetor
    //p2                 Primeiro indice do segundo vetor
    //r1                 Fim do primeiro vetor       
    //r2                 Fim do segundo vetor
    //i, j e k           Auxiliares
    
    int p1,p2, tamanho, i,j,k;
    int r1 = 0,r2 = 0;

    tamanho = r-p+1; p1 = p; p2 = q + 1;
    
    Artists *aux = new Artists[tamanho];//Alocando vetor de artistas dinâmicamente

    if(aux != NULL){
        for(i=0;i<tamanho;i++){

            if(!r1 && !r2){

                if(vet[p1].followers < vet[p2].followers)aux[i]=vet[p1++]; //Comparações
                else aux[i] = vet[p2++];

                comparacoesMS+=1;
                movimentacoesMS+=1;

                if(p1>q)r1=1;
                if(p2>r)r2=1;

            }else{
                if(!r1){aux[i]=vet[p1++];comparacoesMS+=1;movimentacoesMS+=1;}//Movimentando o vetor: vet para aux
                else aux[i]=vet[p2++];
                
            }
        }

        for(j=0,k=p;j<tamanho;j++,k++){ //Movimentando o vetor: aux para o vet

            vet[k] = aux[j];    
            movimentacoesMS+=1;
        }
        
    }
    //Liberando a memória
    delete[] aux;

}



void mergeSortArtists(Artists* vet, int p, int r){

    /**
    * @brief                    Função mergeSort: Usada para ordenar, de forma crescente, um vetor de Artista
    * @param vet                um ponteiro de um vetor de Artists
    * @param p                  primeira posição do primeiro vetor
    * @param r                  tamanho do vetor - 1
    * 
    *                           Exemplo de uso para um vetor artists de tamanho 100:
    *       
    *                               mergeSortArtists(vet, 0, 99)
    *
    * 
    */
        

    

    //q                         Representa o primeiro indice do segundo vetor, que é o meio do vetor principal
    
    int q;
    
    if(p < r){

        //Chamadas sucessivas
        q = floor((p+r)/2);
        mergeSortArtists(vet, p,q);
        mergeSortArtists(vet, q+1, r);
        mergeArtists(vet, p,q,r);
    }

}

void metricaMergeSort(string enderecoPastas, string nomeArquivo ,int repeticao){
    /**
     * @brief                                   Função que permite salvar as metricas após seu cálculo
     * 
     * @param enderecoPastas                    Endereço onde os arquivos se encontram
     * @param nomeArquivo                       Nome do arquivo em que será escrito os dados
     * @param repeticao                         Quantidade de vezes que será feita o mesmo processo  
     */

    //Abertura de todos os arquivos necessários
    ifstream arqBin(enderecoPastas + "artists.bin");
    ifstream arqSort(enderecoPastas + "sort.dat");
    ofstream arqOut(enderecoPastas + nomeArquivo, ios_base::app);

    int r = repeticao;

    arqOut << "REALIZANDO O TESTE DO MERGESORT\n";
    cout << "REALIZANDO O TESTE DO MERGESORT"<<endl;

    string aux;             // String auxiliar para primeira linha do arquivo sort.dat
    getline(arqSort, aux);

    //Variaveis para armazenar o valor de M e N
    string nAux, mAux;
    int n, m;
    int i = 0;

    //Usados para computar as metricas
    long long microseconds;
    long long mediaMicroseconds = 0;
    long long mediaComparacoes = 0;
    long long mediaMovimentacoes = 0;

    while (arqSort.good() && i<r){
        //Estrai os valores de M e N do Arquivo Sort.dat
        i++;
        getline(arqSort, nAux, ',');
        getline(arqSort, mAux);
        n = stoi(nAux);
        m = stoi(mAux);

        arqOut << "\nPARA N = " << n<<"\n";

        //Inicia o processo de escrita
        for(int j=0;j<m;j++){

            //Retornando o vetor com tamanho n, apartir do arquivo binário  
            Artists *vet = returnVetArtists(arqBin, n);
            auto inicio = chrono::high_resolution_clock::now();
            //Ordenando o vetor
            mergeSortArtists(vet, 0, n-1);
            auto final = chrono::high_resolution_clock::now() - inicio;
            microseconds = chrono::duration_cast<chrono::microseconds>(final).count();

            delete[] vet;//DESALOCANDO O VETOR

            //ESCREVENDO NO OUTFILE
            arqOut << "\nMOVIMENTAÇÕES: " << movimentacoesMS << " COMPARAÇÕES: " << comparacoesMS <<" TEMPO DE EXECUÇÃO(EM SEGUNDOS): "<< microseconds/1000000.0 << "\n";
            //INCREMENTO DAS MEDIAS
            mediaComparacoes += comparacoesMS; mediaMovimentacoes += movimentacoesMS; mediaMicroseconds += microseconds;
            
            //ZERANDO OS CONTADORES
            movimentacoesMS = 0;comparacoesMS = 0;
            
        }

        //CALCULO DAS MÉDIAS
        mediaComparacoes /=m;mediaMicroseconds /=m;mediaMovimentacoes /=m;

        //ESCREVENDO NO OUTFILE
        if(repeticao>1)arqOut << "\nMEDIAS: MOVIMENTAÇÕES: " << mediaMovimentacoes << " COMPARAÇÕES: " << mediaComparacoes <<" TEMPO DE EXECUÇÃO(EM SEGUNDOS): "<< mediaMicroseconds/1000000.0 <<"\n\n";
        arqOut << "__________________________________________________________________________________________________________________\n";

        //ZERANDO OS CONTADORES
        mediaComparacoes = 0;mediaMicroseconds = 0; mediaMovimentacoes = 0;

    }   
    //Fechando os arquivos abertos acima
    arqBin.close();arqOut.close();arqSort.close();  
}



