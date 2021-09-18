#include <iostream>
#include "Huffman.h"
#include "string.h"
#include <fstream>
#include <bits/stdc++.h>
#include <chrono>
#include <iomanip>

using namespace std;

/**
 * @brief Comparacao para ordenar a fila de prioridade
 * 
 */
struct compara
{
    //retorno booleano
    bool operator()(NoHuffman *p, NoHuffman *q)
    {
        //retorna true se a frequencia de p eh maior do que p
        //retorna false se a frequencia de p eh menor do que p
        return (p->getFrequencia() > q->getFrequencia());
    }
};

map<char, string> cod;                                           //cotabilizar os bits
map<char, int> freq;                                             //contabilizar a frequencia de cada caracter
priority_queue<NoHuffman *, vector<NoHuffman *>, compara> filaP; //fila de prioridades para nos folhas
int taxa = 0;

/**
 * @brief Destrutor do Huffman
 * 
 */
Huffman::~Huffman()
{
    libera(raiz);
    //cout << "Destrutor" << endl;
}

void Huffman::libera(NoHuffman *p)
{
    if (p != nullptr)
    {
        libera(p->getEsq());
        libera(p->getDir());
        delete p;
    }
}

/**
 * @brief Anda pela arvore armazenando os codigos em um map
 * 
 * @param p No Huffman 
 * @param s String vazia
 */
void Huffman::codigo(NoHuffman *p, string s)
{
    //se o no for nulo, retorna
    if (p == nullptr)
    {
        return;
    }
    //encontrou no folha
    if (p->getNome() != '$')
    {
        cod[p->getNome()] = s;
    }

    //anda pela arvore
    codigo(p->getEsq(), s + "0");
    codigo(p->getDir(), s + "1");
}

/**
 * @brief Calcular a frequencia de cada caracter armazenando no map
 * 
 * @param s String a ser codificada
 */
void Huffman::calcularFrequencia(string s)
{
    for (int i = 0; i < s.size(); i++)
    {
        freq[s[i]]++;
    }
}

/**
 * @brief Funcao para realizar codificacao
 * 
 */
void Huffman::codifica()
{
    //nos para auxiliar na codificacao
    NoHuffman *esq, *dir, *topo;

    //cria um no folha para cada caracter adicionando na fila de prioridades
    for (map<char, int>::iterator v = freq.begin(); v != freq.end(); v++)
    {
        filaP.push(new NoHuffman(v->first, v->second));
    }

    //repete a estrutura ate que a fila de prioridade tenha mais de um no
    while (filaP.size() != 1)
    {
        //removendo dos nos com maior prioridade (menor frequencia)
        esq = filaP.top();
        filaP.pop();
        dir = filaP.top();
        filaP.pop();

        topo = new NoHuffman('$', esq->getFrequencia() + dir->getFrequencia());
        //cria um novo no com a frequencia sendo a soma dos dois nos

        //os dois nos agora sao filhos desse novo no
        topo->setEsq(esq);
        topo->setDir(dir);

        //insere o novo no na fila de prioridades
        filaP.push(topo);
    }
    raiz = filaP.top();
    codigo(filaP.top(), "");
}

/**
 * @brief Andando pela arvore e decodificando a mensagem
 * 
 * @param p No Huffman
 * @param s String a ser decodificada
 * @return String decodificada
 */
string Huffman::decodifica(NoHuffman *p, string s)
{
    //no for nulo, retorna mensagem de erro
    if (p == nullptr)
        return "ERRO AO DECODIFICAR";

    string resp = "";   //string auxiliar para decodificacao
    NoHuffman *aux = p; //no auxiliar para decodificacao

    //enquanto for menor que o tamanho da string a ser decodificada
    for (int i = 0; i < s.size(); i++)
    {
        //se a string nessa posicao for 0
        if (s[i] == '0')
        {
            //desce pela esquerda
            aux = aux->getEsq();
        }
        else
        {
            //se for 1, desce pela direita
            aux = aux->getDir();
        }

        //quando chega no no folha, adiciona o caracter na string auxiliar
        if (aux->getEsq() == nullptr && aux->getEsq() == nullptr)
        {
            resp += aux->getNome();
            aux = p; //retorna na raiz
        }
    }
    //retorna a string decodificada
    return resp;
}

/**
 * @brief Pega a string codificada e retornar o decimal corresponde a 8 bits
 * 
 * @param s String que contém os caracteres a serem codificados/decodificados
 * @param saida Nome do arquivo em que as informações vão ser salvas
 * @param tam Tamanho do arquivo de leitura para calculo da taxa de compressao
 */
void Huffman::codigoASCII(string s, string saida, double tam)
{
    ofstream arqOut(saida, ios_base::app);
    string num = s; //string auxiliar
    string auxS;    //string auxilia

    int len = num.length();  //tamanho da string
    int aux = 0, tamAux = 0; //auxiliar na mensagem
    arqOut << "\n\n8 BITS  |  DECIMAL\n";

    //anda pela string
    for (int i = 0; i <= len - 1; i++)
    {
        auxS += s[i];
        aux++; //soma mais um

        //caso tenha rodado 8 caracteres
        if (aux == 8)
        {
            taxa++;
            tamAux += aux; //quantidade de casas que andou na string
            arqOut << auxS << "     " << stoi(auxS, 0, 2) << "\n";

            //retorna para os valores de origem
            auxS.clear();
            aux = 0;
        }
    }
    //caso nao tenho dado 8 caracteres, retorna para origem
    if (aux > 0 && aux != 8)
    {
        taxa++;
        num = s.substr(tamAux, s.length() - tamAux); //pega a string sem a quantidade de casas que andou
        //faz a conversao
        arqOut << num << "     " << stoi(num, 0, 2) << "\n\n";
    }
    //calculando taxa de compressao
    double comp = (tam - taxa) / (tam);
    arqOut << "\n\nTAXA DE COMPRESSÃO: " << setiosflags(ios::fixed) << setprecision(2) << comp * 100.0 << "%" << endl;
    taxa = 0;
    arqOut.close();
}

/**
 * @brief Realizar todos os testes do huffman e salvar no arquivo de texto
 * 
 * @param huffman Endereço da pasta dos arquivos de entrada
 * @param saida Nome do arquivo em que as informações vão ser salvas
 * @param str String que contém os caracteres a serem codificados/decodificados
 * @param tam Tamanho do arquivo de leitura
 */
void Huffman::metrica(string huffman, string saida, string str, double tam)
{
    auto execucao = chrono::high_resolution_clock::now();
    long long microseconds; //calcular o tempo

    string codificacao, decodificacao; //strings responsaveis pelo armazenamento da codificacao/decodificacao

    //calculando tempo
    auto inicio = chrono::high_resolution_clock::now();
    calcularFrequencia(str); //calculo da frequencia de todos os caracteres
    codifica(); //codificacao
    auto final = chrono::high_resolution_clock::now() - inicio;
    microseconds = chrono::duration_cast<chrono::microseconds>(final).count();

    ofstream arqOut(huffman + saida, ios_base::app); //abrino arquivo
    arqOut << "SEQUÊNCIA ALEATÓRIA DE DNA CONSISTINDO EM " << tam << " BASES\n\n";       //escrevendo no arquivo
    arqOut << "LETRA | FREQUENCIA | CODIGO\n";       //escrevendo no arquivo
    auto a = freq.begin();                           //auxiliar para escrever a frequencia
    for (auto v = cod.begin(); v != cod.end(); v++)  //escrever os caracteres, codigo e frequencia
    {
        arqOut << "  " << v->first << "         ";
        if (a != freq.end())
        {
            arqOut << a->second;
        }
        arqOut << "         " << v->second << "\n";
        a++;
    }

    for (auto i : str)
    {
        codificacao += cod[i];
    }
    arqOut << "\n\nTEMPO DE EXECUÇÃO DA CODIFICAÇÃO (EM SEGUNDOS): " << microseconds / 1000000.0 << "\n";

    arqOut << "\n\nCODIFICAÇÃO \n\n"
           << codificacao << "\n";
    
    codigoASCII(codificacao, huffman + saida, tam); //calcular taxa de compressao

    //calculando tempo
    auto inicio1 = chrono::high_resolution_clock::now();
    decodificacao = decodifica(filaP.top(), codificacao);
    auto final1 = chrono::high_resolution_clock::now() - inicio1;
    microseconds = chrono::duration_cast<chrono::microseconds>(final1).count();

    
    arqOut << "TEMPO DE EXECUÇÃO DA DECODIFICAÇÃO (EM SEGUNDOS): " << microseconds / 1000000.0 << "\n";
    arqOut << "\nDECODIFICAÇÃO\n\n"
           << decodificacao << "\n";

    //limpando as estruturas para a proxima codificacao/decodificacao
    freq.clear();
    cod.clear();
    filaP.pop();
    auto fimExecucao = chrono::high_resolution_clock::now() - execucao;
    microseconds = chrono::duration_cast<chrono::microseconds>(fimExecucao).count();
    arqOut << "\n\nTEMPO TOTAL DE EXECUÇÃO (EM SEGUNDOS): " << microseconds / 1000000.0 << "\n";
    arqOut << "______________________________________________________________________________________________________________________\n\n";
    arqOut.close();
}