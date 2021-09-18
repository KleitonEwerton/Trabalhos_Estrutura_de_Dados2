#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>

#include "Tools.h"
#include "ForcaBruta.h"
#include "KMP.h"
#include "BoyerMoore.h"
#include "Huffman.h"

using namespace std;



/**
 * @brief                                   Função que ferifica se determinado arquivo consta em uma determinada pasta
 * 
 * @param  arqName                          Nome do Arquivo a ser verificado 
 * @param endereco                          Endereço da pasta dos arquivos de entrada 
 * 
 * @return true 
 * @return false 
 */
bool verificaArquivo(string arqName, string endereco){

    
    
    ifstream arq(endereco + arqName, ios::in);

    if ( (arq.is_open()) ){
        arq.close();
        return true;
    }
        
    else{
        arq.close();
        cout <<endl<< "O arquivo " << arqName << " não foi encontrado na pasta "<< endereco << endl<<endl;
        return false;
    }
        
}
/**
 * @brief                                       Função para verificar se todos os arquivos necessarios estão na pasta arquivos_de_entrada
 * 
 * @param endereco                              Endereço da pasta dos arquivos de entrada
 * 
 * @return true                                 Nenhum arquivo faltando
 * @return false                                Algum arquivo faltando
 */
bool verificaInputFile(string endereco){

    //Arquivos necessários para o programa funcionar
    string file[13] = {"dna100000.txt", "dna1000000.txt", "dna10000000.txt", "padrao1.txt","padrao2.txt","padrao3.txt","padrao4.txt","padrao5.txt","padrao6.txt","padrao7.txt","padrao8.txt", "padrao9.txt","padrao10.txt"};

    for(int i = 0; i < 13;i++)
        if(!verificaArquivo(file[i], endereco))
            return false;
        
    return true;

}


/**
 * @brief                                       Menu para seleção do casamento padrão
 *
 * @param endereco                              Endereço da pasta dos arquivos de entrada
 */
void menu_casamento_padroes(string endereco){

    
    char resposta[] = "";
    int res = 0;
    int cond = 1;

    while (cond)
    {

        cout << endl<< endl<< "SELECIONE UMA DAS OPÇÕES ABAIXO: " << endl;
        cout << "1 - FORÇA BRUTA" << endl;
        cout << "2 - KMP" << endl;
        cout << "3 - BOYERMOORE" << endl;
        cout << "4 - SAIR" << endl;
        cin >> resposta;

        try
        {
            res = stoi(resposta);
        }
        catch (const exception &e){}

        switch (res){

        case 1:
            cond = 0;
            casamento_de_padroes(1, endereco);
            break;


        case 2:{

            cond = 0;
            casamento_de_padroes(2, endereco);
            break;
        }

        case 3:{

            cond = 0;
            casamento_de_padroes(3, endereco);
            break;
        }

        case 4:
            cond = 0;
            cout << "VOCÊ OPTOU POR SAIR" << endl;
            break;

        default:
            cout << "OPÇÃO INVÁLIDA" << endl;
            break;
        }
    }

}


/** 
 * @brief                                       Função do menu principal
 * 
 * @param endereco                              Endereço da pasta dos arquivos de entrada
 */
void main_menu(string endereco)
{

    char resposta[] = "";
    int res = 0;
    int cond = 1;

    while (cond)
    {

        cout << endl<< endl<< "SELECIONE UMA DAS OPÇÕES ABAIXO: " << endl;
        cout << "1 - Casamento de Padrão" << endl;
        cout << "2 - Método de Compressão" << endl;
        cout << "3 - para sair" << endl;

        cin >> resposta;

        try
        {
            res = stoi(resposta);
        }
        catch (const exception &e)
        {
        }

        switch (res)
        {

        case 1:
            cond = 0;
            menu_casamento_padroes(endereco);
            break;

        case 2:
        {
            cond = 0;
            string dna1;
            
            //100.000
            cout << "INICIANDO TESTE COM DNA 100.000" << endl;
            Huffman huf1;
            dna1 = leitura_arquivo1("dna100000.txt",endereco);
            huf1.metrica("../", "Huffman.txt", dna1, 100000.0);
            
            //1.000.000
            cout << "INICIANDO TESTE COM DNA 1.000.000" << endl;
            Huffman huf2;
            dna1 = leitura_arquivo1("dna1000000.txt",endereco);
            huf2.metrica("../", "Huffman.txt", dna1, 1000000.0);

            //10.000.000
            Huffman huf3;
            cout << "INICIANDO TESTE COM DNA 10.000.000" << endl;
            dna1 = leitura_arquivo1("dna10000000.txt",endereco);
            huf3.metrica("../", "Huffman.txt", dna1, 10000000.0);
            cout << "INFORMAÇÕES SALVAS NO ARQUIVO 'Huffman.txt' NA PASTA RAIZ DO PROJETO" << endl;
            
            break;
        }

        case 3:
            cond = 0;
            cout << "VOCÊ OPTOU POR SAIR" << endl;
            break;

        default:
            cout << "OPÇÃO INVÁLIDA" << endl;
            break;
        }
    }
}

/**
 * @brief Função que lê determinado arquivo e o convete para uma string
 * 
 * @param arqName Nome do arquivo a ser aberto
 * @param endereco Endereço da pasta dos arquivos de entrada
 * @return string que corresponde ao arquivo
 */
string leitura_arquivo1(string arqName,string endereco)
{
    cout << "\nINICIANDO A LEITURA DO ARQUIVO " << arqName << " NA PASTA: arquivos_de_entrada" << endl;
    ifstream arq(endereco + arqName);
    string str, aux;

    //lendo todo o arquivo de uma vez
    string texto((istreambuf_iterator<char>(arq)), istreambuf_iterator<char>());

    //percorrendo a string e retirando quebra de linhas
    for (int i = 0; i < texto.size(); i++)
    {
        if ((int) texto[i] != 13 && (int) texto[i] != 10)
            str += texto[i];
    }
    
            
    arq.close();
    return str;
}

/**
 * @brief                                       Função que lê determinado arquivo e o convete para uma string, passada como parâmetro, eliminando todas as quebras de texto
 * 
 * @param arqName                               Nome do arquivo a ser aberto
 * @param str                                   String quem vai receber o texto extraído
 * @param endereco                              Endereço da pasta dos arquivos de entrada
 */
void leitura_arquivo2(string arqName, char *str, string endereco){

    cout << "\nINICIANDO A LEITURA DO ARQUIVO " << arqName << " NA PASTA: arquivos_de_entrada" << endl;

    string arqCaminho = "../arquivos_de_entrada/"; 
    ifstream arq(arqCaminho + arqName);
    //Lê todo o arquivo de uma vez e o armazena na string de texto
    string texto((istreambuf_iterator<char>(arq)), istreambuf_iterator<char>());
    arq.close();

    int bi = 0;
    int ai = 0;
    int tamTexto = texto.size();

    char *a = new char[tamTexto + 1];   //String que será usado para auxiliar na remoção de \n
    char *b = new char[tamTexto + 1];   //String que será o resultado final

    strcpy(a, texto.c_str());
    int i = strlen(a);
    //Retira todos os \n e não letras
    for(;ai < i; ai++)
        if(a[ai] > 96 && a[ai] < 122){  

            b[bi] = a[ai];
            bi++;

        }
    b[bi] = '\0';   //Marca o fim da string
    delete [] a;
    
    strcpy(str, b);
    delete [] b;
}


/**
 * @brief                                   Função que chama um determinado método de casamento de padrão, extraindo textos de arquivos de entrada
 * 
 * @param opcao                             1 para Força Bruta, 2 para o KMP e 3 para o BoyerMoore
 * @param endereco                          Endereço da pasta dos arquivos de entrada
 */
void casamento_de_padroes(int opcao, string endereco){

    //Nome dos arquivos de entrada
    string filesDNA[13] = {"dna100000.txt", "dna1000000.txt", "dna10000000.txt"};
    string filesPadrao[10] = {"padrao1.txt","padrao2.txt","padrao3.txt","padrao4.txt","padrao5.txt","padrao6.txt","padrao7.txt", "padrao8.txt", "padrao9.txt","padrao10.txt"};

    //Arquivo para saida dos dados
    ofstream outFile("../Casamento_De_Padroes.txt", ios_base::app);

    char *dna = new char[10000001];
    char *padrao = new char[200];

    for(int i = 0; i<3;i++){            //LAÇO PARA EXECULTAR EM CADA UM DOS ARQUIVOS DE DNA

        leitura_arquivo2(filesDNA[i], dna, endereco);     //Lê o arquivo de dna

        cout << endl<<endl<<endl;
        outFile << endl<<endl<<endl;

        for(int j = 0; j<10; j++){      //LAÇO PARA EXECULTAR EM CADA UM DOS ARQUIVOS DE PADRÃO

            cout << "\n\nPARA O ARQUIVO " << filesDNA[i];
            outFile << "\n\nPARA O ARQUIVO " << filesDNA[i];

            leitura_arquivo2(filesPadrao[j], padrao, endereco);   //Lê o arquivo de padrão

            //LOCAL DOS ALGORITMOS
            switch (opcao){


            case 1:
                forca_bruta(dna, padrao, outFile);
                break;


            case 2:
                kmp(dna, padrao, outFile);
                break;


            case 3:
                int *locArray = new int[strlen(dna)];
                int index=-1;
                boyermoore(dna,padrao,locArray,&index,outFile);
                break;
                delete [] locArray;

            }

            cout << "\n\n_________________________________________________________\n\n" << endl;
            
        }
        
    }
    
    outFile.close();
    cout << "INFORMAÇÕES SALVAS NO ARQUIVO 'Casamento_De_Padroes.txt' NA PASTA RAIZ DO PROJETO" << endl;
    delete [] dna;
    delete [] padrao;
        
    

}
