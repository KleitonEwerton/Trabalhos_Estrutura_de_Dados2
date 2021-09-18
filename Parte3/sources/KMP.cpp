#include <iostream>
#include "KMP.h"
#include <string.h>
#include <chrono>
#include <fstream>

long long tempoKMP;
long long comparacoesKMP;
long long comparacoesPrefixo;

using namespace std;

void lpsArray(char* padrao, int X, int* lps);

/**
 * @brief Função de Casamento de Padrão: Método Knuth-Morris-Pratt                 
 * 
 * @param str String do texto
 * @param padrao String do padrão
 */
void kmp(char* str, char* padrao, ofstream &outFile){
    cout << "\nINICIANDO O ALGORITO KNUTH-MORRIS-PRATT NO PADRÃO "<< padrao << endl;
    outFile << "\nINICIANDO O ALGORITO KNUTH-MORRIS-PRATT NO PADRÃO "<< padrao << endl;

    int X = strlen(padrao);
    int Y = strlen(str);
    int qtdePadroes = 0;//  Quantidade de padrões na string
    comparacoesKMP = 0;
    auto inicio = chrono::high_resolution_clock::now();
    //Cria lps[] que conterá os valores de sufixo de prefixo mais longos para o padrão
    int lps[X];

    //Pré-processamento do padrão
    lpsArray(padrao, X, lps);

    int i = 0; //indice para str[]
    int j = 0; //indice para padrao[]

    while (i<Y)
    {
        comparacoesKMP++;
        if(padrao[j] == str[i]){
            j++;
            i++;
        }
        if(j==X){
            cout << "PADRÃO  ENCONTRADO! DO ÍNDICE " << i-j << " ATÉ O ÍNDICE " << i-j+X-1 << endl;
            outFile << "PADRÃO  ENCONTRADO! DO ÍNDICE " << i-j << " ATÉ O ÍNDICE " << i-j+X-1 << endl;

            qtdePadroes++;
            j=lps[j-1];
        }

        // incompatibilidade após j correspondências
        else if (i<Y && padrao[j] != str[i])
        {
            // Não corresponda aos caracteres lps [0..lps [j-1]], eles corresponderão de qualquer maneira
            if(j!=0)
                j=lps[j-1];
            else
                i = i+1;
        }
        
    }

    auto final = chrono::high_resolution_clock::now() - inicio;
    tempoKMP = chrono::duration_cast<chrono::microseconds>(final).count();

    if (qtdePadroes == 0)
    {
        cout << "NÃO FOI ENCONTRADO ESSE PADRÃO NO TEXTO. TEMPO DE EXECUÇÃO "<< tempoKMP / 1000000.0 << " SEGUNDOS. COMPARAÇÕES DA FUNÇÃO KMP: " <<comparacoesKMP<<". COMPARAÇÕES DA FUNÇÃO DE PREFIXO: " << comparacoesPrefixo << endl;
        outFile << "NÃO FOI ENCONTRADO ESSE PADRÃO NO TEXTO. TEMPO DE EXECUÇÃO "<< tempoKMP / 1000000.0 << " SEGUNDOS. COMPARAÇÕES DA FUNÇÃO KMP: " <<comparacoesKMP<<". COMPARAÇÕES DA FUNÇÃO DE PREFIXO: " << comparacoesPrefixo << endl;

    }else{
        if(qtdePadroes == 1){
            cout << "FOI ENCONTRADO APENAS UM PADRÃO NO TEXTO. TEMPO DE EXECUÇÃO "<< tempoKMP / 1000000.0 << " SEGUNDOS. COMPARAÇÕES DA FUNÇÃO KMP: "<<comparacoesKMP<<". COMPARAÇÕES DA FUNÇÃO DE PREFIXO: " <<comparacoesPrefixo<<endl;
            outFile << "FOI ENCONTRADO APENAS UM PADRÃO NO TEXTO. TEMPO DE EXECUÇÃO "<< tempoKMP / 1000000.0 << " SEGUNDOS. COMPARAÇÕES DA FUNÇÃO KMP: "<<comparacoesKMP<<". COMPARAÇÕES DA FUNÇÃO DE PREFIXO: " <<comparacoesPrefixo<<endl;

        }
            
        else{
            cout << "FORAM ENCONTRADOS " << qtdePadroes << " PADRÕES NO TEXTO. TEMPO DE EXECUÇÃO "<< tempoKMP / 1000000.0 << " SEGUNDOS. COMPARAÇÕES DA FUNÇÃO KMP: "<<comparacoesKMP<<". COMPARAÇÕES DA FUNÇÃO DE PREFIXO: " << comparacoesPrefixo<<endl;
            outFile << "FORAM ENCONTRADOS " << qtdePadroes << " PADRÕES NO TEXTO. TEMPO DE EXECUÇÃO "<< tempoKMP / 1000000.0 << " SEGUNDOS. COMPARAÇÕES DA FUNÇÃO KMP: "<<comparacoesKMP<<". COMPARAÇÕES DA FUNÇÃO DE PREFIXO: " << comparacoesPrefixo<<endl;

        }
            
    }
    
}

/**
 * @brief Preenche lps [] para determinado padrão de padrao[0..X-1]
 * 
 * @param padrao String do padrao
 * @param X Tamanho de padrao
 * @param lps Array que conterá valores de sufixo de prefixo
 */
void lpsArray(char* padrao, int X, int* lps){
    //comprimento do sufixo de prefixo anterior mais longo
    int tam = 0;

    lps[0] = 0; //lps[0] é sempre 0

    //o loop calcula lps [i] para i = 1 a X-1
    int i=1;

    comparacoesPrefixo = 0;

    while (i<X)
    {
        comparacoesPrefixo++;
        if (padrao[i] == padrao[tam])
        {
            tam++;
            lps[i] = tam;
            i++;
        }
        else{ //(padrao[i] != padrao[tam])
            if (tam!=0)
            {
                tam=lps[tam-1];
                //não incrementa i
            }
            else{ //if(tam==0)
                lps[i] = 0;
                i++;
            }
            
        }
        
    }
    
}
