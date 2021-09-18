/*
 * ============================================================================
 *
 *       Filename:  Quicksort.cpp
 *
 *    Description:  Implementação do algoritmo Quicksort
 *
 *        Version:  1.2
 *
 *         Author:  Ágata Meireles Carvalho (agata.meireles@gmail.com / agata.meireles@estudante.ufjf.br)
 *
 * ============================================================================
 */
#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
#include "Artists.h"
#include "QuickSort.h"
#include <math.h>
#include <chrono>

using namespace std;

//Variaveis acumuladoras que calculam a quantidade de trocas e as comparações de chave
int trocas = 0, comparacoes = 0;

/**
 * @brief Método de particionamento que é o núcleo do algoritmo Quicksort.
 * É a implementação utilizando o paradigma dividir para conquistar
 * 
 * @param vet Vetor a ser ordenado
 * @param p Primeiro elemento do vetor
 * @param q Último elemento do vetor
 * @return Endereço atual do pivô dentro do vetor 
 */
int particionamento(Artists vet[], int p, int q){
    int i = p;
    for(int j = p; j<q; j++){
        if(vet[j].followers<=vet[q].followers){
           comparacoes++;
            swap(vet[i++], vet[j]);
            trocas++;
        }
    }
    swap(vet[i], vet[q]);
    trocas++;

    return i;
}
/**
 * @brief Método que implementa o Quicksort recursivamente
 * 
 * @param vet Vetor a ser ordenado
 * @param p Primeiro elemento do vetor
 * @param r Último elemento do vetor
 */
void quicksort(Artists vet[], int p, int r){
    if(p >= r){
        return;
    }
    int pivo = particionamento(vet, p, r);

    quicksort(vet, p, pivo-1);
    quicksort(vet, pivo+1, r);

}

/**
 * @brief Função que salva em um arquivo txt, as metricas do algortimo
 * 
 * @param quick Diretório
 * @param nomeArq Arquivo txt
 */
void metricaQuickSort(string quick, string nomeArq)//tempo de execução e endereço da paste ./build
{
    ifstream arqBin(quick + "artists.bin");
    ifstream arqSort(quick + "sort.dat");
    ofstream arqOut(quick + nomeArq, ios_base::app); 

    arqOut << "REALIZANDO O TESTE DO QUICKSORT\n";
    cout << "REALIZANDO O TESTE DO QUICKSORT" << endl;

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

                quicksort(vet, 0, parN-1);

                auto final = chrono::high_resolution_clock::now() - inicio;
                microseconds = chrono::duration_cast<chrono::microseconds>(final).count();

                delete[] vet;

                arqOut << "\nMOVIMENTAÇÕES: " << trocas << " COMPARAÇÕES: " << comparacoes << " TEMPO DE EXECUÇÃO(EM SEGUNDOS): " << microseconds / 1000000.0 << "\n";

                mediaComparacoes += comparacoes;
                mediaMovimentacoes += trocas;
                mediaMicroseconds += microseconds;

                trocas = 0;
                comparacoes = 0;
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