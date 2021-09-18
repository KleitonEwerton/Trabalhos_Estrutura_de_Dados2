#include <iostream>
#include <fstream>
#include "ForcaBruta.h"
#include <string.h>
#include <chrono>

long long microseconds1;
long long comparacoes1;

using namespace std;

/**
 * @brief                               Função de Casamento de Padrão: Método força bruta
 * 
 * @param texto                         String contendo o texto
 * @param padrao                        String contendo o padrão 
 */
void forca_bruta(char texto[], char padrao[], ofstream &outFile){
    
    cout << "\nINICIANDO O ALGORITOM DE FORÇA BRUTA COM O PADRÃO "<< padrao << endl;
    outFile<< "\nINICIANDO O ALGORITOM DE FORÇA BRUTA COM O PADRÃO "<< padrao << endl;

    int n = strlen(texto);              //  Tamanho do texto
    int m = strlen(padrao);             //  Tamanho do padrão

    if(n < m){
        cout << "NÃO FOI ENCONTRADO ESSE PADRÃO NO TEXTO, POIS O PADRÃO É MAIOR QUE O TEXTO" << endl;
        outFile << "NÃO FOI ENCONTRADO ESSE PADRÃO NO TEXTO, POIS O PADRÃO É MAIOR QUE O TEXTO" << endl;
        return;
    }


    int verificador = 0;                //  Tamanho do texto verificada
    int qntPadroesEncontrados = 0;      //  Quantidade de padrões encontrados
    comparacoes1 = 0;

    //calculando tempo
    auto inicio = chrono::high_resolution_clock::now();
    
    for(int s = 0; s < n-m+1; s++){
        verificador = 0;
        comparacoes1++;
        for(int i = 0; i < m; i++){
            comparacoes1++;
            if(padrao[i] != texto[s+i])
                break;
            
            if(padrao[i] == texto[s+i])
                verificador++;

        }

        //Se o verificador for igual ao tamahnho da string padrão é porque o padrao existe
        if(verificador == m){
            qntPadroesEncontrados++;
            cout << "PADRÃO  ENCONTRADO! DO ÍNDICE " << s << " ATÉ O ÍNDICE " << s+m-1 << endl;
            outFile << "PADRÃO  ENCONTRADO! DO ÍNDICE " << s << " ATÉ O ÍNDICE " << s+m-1 << endl;
        }

    }

    auto final = chrono::high_resolution_clock::now() - inicio;
    microseconds1 = chrono::duration_cast<chrono::microseconds>(final).count();

    if(qntPadroesEncontrados == 0){
        cout << "NÃO FOI ENCONTRADO ESSE PADRÃO NO TEXTO. TEMPO DE EXECUÇÃO "<< microseconds1 / 1000000.0 << " SEGUNDOS. COMPARAÇÕES: "<< comparacoes1 << endl;
        outFile << "NÃO FOI ENCONTRADO ESSE PADRÃO NO TEXTO. TEMPO DE EXECUÇÃO "<< microseconds1 / 1000000.0 << " SEGUNDOS. COMPARAÇÕES: "<< comparacoes1 << endl;
    }
        

    else
        if(qntPadroesEncontrados == 1){
            cout << "FOI ENCONTRADO APENAS UM PADRÃO NO TEXTO. TEMPO DE EXECUÇÃO "<< microseconds1 / 1000000.0 << " SEGUNDOS. COMPARAÇÕES: "<< comparacoes1 << endl;
            outFile << "FOI ENCONTRADO APENAS UM PADRÃO NO TEXTO. TEMPO DE EXECUÇÃO "<< microseconds1 / 1000000.0 << " SEGUNDOS. COMPARAÇÕES: "<< comparacoes1 << endl;
        }
            
        else{
            cout << "FORAM ENCONTRADOS " << qntPadroesEncontrados << " PADRÕES NO TEXTO. TEMPO DE EXECUÇÃO "<< microseconds1 / 1000000.0 << " SEGUNDOS. COMPARAÇÕES: "<< comparacoes1 << endl;
            outFile << "FORAM ENCONTRADOS " << qntPadroesEncontrados << " PADRÕES NO TEXTO. TEMPO DE EXECUÇÃO "<< microseconds1 / 1000000.0 << " SEGUNDOS. COMPARAÇÕES: "<< comparacoes1 << endl;
        }
            


}
