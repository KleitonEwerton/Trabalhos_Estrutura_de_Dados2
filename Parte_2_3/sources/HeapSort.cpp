#include <iostream>
#include "Artists.h"
#include "Heapsort.h"
#include <fstream>
#include <math.h>
#include <chrono>

using namespace std;

int troca = 0, comparacao = 0;

/**
 * @brief Construi a heap, troca a posicao e a reconstroi
 * 
 * @param vet Vetor de artista
 * @param n Tamanho do vetor
 */
void heapsortFollowers(Artists *vet, int n)
{
    //tempo de inicio
    //clock_t inicioHeap = clock();
    //construir a heap
    build_max_heap(vet, n); //Complexidade: O(n)

    //trocar e reconstruir o heap
    int tam = n - 1;
    for (int i = tam; i >= 1; i--) //Complexidade: O(n)
    {
        swap(vet[0], vet[i]); //Complexidade: O(1)
        troca++;              //Complexidade: O(1)
        tam--;                //Complexidade: O(1)
        heapify(vet, 0, tam); //Complexidade: O(log n)
    }
    //Complexidade total: O (n log n)

    //tempo final
    //clock_t fimHeap = clock() - inicioHeap;
    //tempoHeap = (double)fimHeap / CLOCKS_PER_SEC;
}
/**
 * @brief Percorre o vetor a partir da metade ate a 1 posicao inserindo os elementos na heap
 * 
 * @param vet Vetor de artista
 * @param n Tamanho do vetor
 */
void build_max_heap(Artists *vet, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(vet, i, n - 1);
    }
}

/**
 * @brief Verifica se a propriedade de heap nao e violada
 * 
 * @param vet Vetor de artista
 * @param i Posicao no vetor
 * @param n Tamanho do vetor
 */
void heapify(Artists *vet, int i, int tam)
{
    int fEsquerdo = 2 * i + 1; //filho esquerdo do indice
    int fDireito = 2 * i + 2;  //filho direito do indice
    int maior = i;

    //estrutras para verificar quem e o menor
    if ((fEsquerdo <= tam) && (vet[fEsquerdo].followers > vet[maior].followers))
    {
        maior = fEsquerdo;
        comparacao++;
    }

    if ((fDireito < tam) && (vet[fDireito].followers > vet[maior].followers))
    {
        maior = fDireito;
        comparacao++;
    }

    //troca da posicao
    if (maior != i)
    {
        swap(vet[i], vet[maior]);
        troca++;
        comparacao++;
        heapify(vet, maior, tam); //recursividade
    }
}

/**
 * @brief Imprimir na tela o vetor ordenado e salvar no arquivo .txt as comparacoes, movimentacoes e tempo
 * 
 * @param heap Diretório
 * @param nomeArq Arquivo de texto teste.txt
 */
void metricaHeapsort(string heap, string nomeArq)
{
    ifstream arqBin(heap + "artists.bin");
    ifstream arqSort(heap + "sort.dat");
    ofstream arqOut(heap + nomeArq, ios_base::app); //heap + "saida.txt" ou heap + "teste.txt"

    arqOut << "REALIZANDO O TESTE DO HEAPSORT\n";
    cout << "REALIZANDO O TESTE DO HEAPSORT" << endl;

    string linha1;

    //pular linha 1
    getline(arqSort, linha1);
    long long microseconds;
    long long mediaMicroseconds = 0;
    long long mediaComparacoes = 0;
    long long mediaMovimentacoes = 0;

    string n, m;
    if (arqSort.good())
    {
        while (getline(arqSort, n, ',') && getline(arqSort, m))
        {
            int parN, parM;
            parN = stoi(n);
            parM = stoi(m);

            arqOut << "\nPARA N = " << parN << "\n";

            for (int j = 0; j < parM; j++)
            {
                Artists *vet = returnVetArtists(arqBin, parN);

                auto inicio = chrono::high_resolution_clock::now();

                heapsortFollowers(vet, parN);

                auto final = chrono::high_resolution_clock::now() - inicio;
                microseconds = chrono::duration_cast<chrono::microseconds>(final).count();

                delete[] vet;

                arqOut << "\nMOVIMENTAÇÕES: " << troca << " COMPARAÇÕES: " << comparacao << " TEMPO DE EXECUÇÃO(EM SEGUNDOS): " << microseconds / 1000000.0 << "\n";

                mediaComparacoes += comparacao;
                mediaMovimentacoes += troca;
                mediaMicroseconds += microseconds;

                troca = 0;
                comparacao = 0;
            }
            mediaComparacoes /= parM;
            mediaMicroseconds /= parM;
            mediaMovimentacoes /= parM;

            if(parM>1)arqOut << "\nMEDIAS: MOVIMENTAÇÕES: " << mediaMovimentacoes << " COMPARAÇÕES: " << mediaComparacoes << " TEMPO DE EXECUÇÃO(EM SEGUNDOS): " << mediaMicroseconds / 1000000.0 << "\n\n";
            arqOut << "__________________________________________________________________________________________________________________\n";

            mediaComparacoes = 0;
            mediaMicroseconds = 0;
            mediaMovimentacoes = 0;
        }
    }
    arqBin.close();
    arqOut.close();
    arqSort.close();
}