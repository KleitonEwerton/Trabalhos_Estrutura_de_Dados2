#include <iostream>
#include <iomanip>
#include <string.h>
#include "Registro.h"
#include "Tracks.h"

using namespace std;

class HashMap
{
private:
    Registro **table;
    unsigned int tamanho;
    string enderecoArqBin;
    int tamVetorHash;

public:
    HashMap(unsigned int, string enderecoArqBin);
    ~HashMap();

    int get(int key);
    void inserir(char *idA);
    void printHash();
    int convertToInt(char *idA);
    int busca(char *idA);
    void maisFrequentes(int m, bool teste);
    void quickHash(Registro **vet, int p, int r);
    int particionamentoHash(Registro **vet, int p, int q);
};

/**
 * @brief Construtor
 * 
 * @param tam Tamanho da tabela hash
 * @param enderecoArqBin Endereço do arquivo artists.bin
 */
HashMap::HashMap(unsigned int tam, string enderecoArqBin)
{

    this->enderecoArqBin = enderecoArqBin; //Definindo o endereço do arquivo artists.bin para o busca do Artista no arquivo binários

    this->tamVetorHash = 0;
    this->tamanho = tam; //Tamanho do vetor da Hash

    table = new Registro *[tamanho]; //Alocando dinâmicamente o vetor contento os registro

    for (int i = 0; i < tamanho; i++)
        table[i] = nullptr; //Inicializando todas as possições como nullptr
}

/**
 * @brief Destrutor da tabela Hash
 * 
 */
HashMap::~HashMap()
{
    for (int i = 0; i < tamanho; ++i)
    {
        Registro *entrada = table[i];
        while (entrada != nullptr)//percorre por todos os registros contidos no mesmo endereço da tabela hash e os desaloca
        {
            Registro *anterior = entrada;
            entrada = entrada->proximo;
            delete anterior;
        }
    }

    delete[] table;
}

/**
 * @brief Função para converter o ID em um valor inteiro
 * 
 * @param idA id do artista
 * @return id transformado em número inteiro
 */
int HashMap::convertToInt(char *idA)
{   
    int i, valor = 7;
    int tam = strlen(idA);
    for (int i = 0; i < tam; i++)
    {
        valor = 31 * valor + (int)idA[i];
    }
    return valor;
}

/**
 * @brief Insere um registro na tabela hash, somente se não existir 
 * 
 * @param idA id do artista
 */
void HashMap::inserir(char *idA)
{   
    int key = convertToInt(idA);

    int hash = (key % tamanho);

    Registro *anterior = nullptr;
    Registro *entrada = table[hash];

    while (entrada != nullptr)//percorre por toda a possição da tabela hash buscando um local vazio ou verifica se já existe
    {
        anterior = entrada;
        if (entrada->getIdA() == idA)
        {

            entrada->quantidade += 1;//caso o valor já exista apenas sua quantidade é aumentada
            return;
        }

        entrada = entrada->proximo;
    }

    if (entrada == nullptr)
    {

        entrada = new Registro(idA);//Cria um novo registro e o coloca no fim da lista
        tamVetorHash += 1;
        if (anterior == nullptr)
            table[hash] = entrada;

        else
            anterior->proximo = entrada;
    }
    else
        entrada->setId(idA);
}

/**
 * @brief Imprime a tabela Hash
 * 
 */
void HashMap::printHash()
{
    Registro **aux = table;
    Registro *no;

    for (int i = 0; i < tamanho; i++)
    {

        no = aux[i];

        if (no != nullptr)
        {

            while (no != nullptr)
            {

                cout << "Posição na Hash " << i << "      ID do Artista: " << no->getIdA() << " Quantidade: " << no->quantidade << endl;
                no = no->proximo;
            }
        }
        else
        {
            cout << "Posição na Hash " << i << "     NULL" << endl;
        }
    }
}

/**
 * @brief Determina qual a musica mais popular dos m artistas mais frequentes
 * 
 * @param m Artistas mais frequentes
 * @param teste Indicar se vai escrever no arquivo .txt ou imprimir na tela
 */
void HashMap::maisFrequentes(int m, bool teste)
{
    //Escreve em um arquivo, caso for um teste, a música mais popular dos m masi frequentes artista. Caso não for um teste ela imprime na tela
    //Sua busca e feita no arquivo binário de Tracks
    Registro **aux = table;
    Registro *no;
    Registro **vet = new Registro *[tamVetorHash];

    bool t = teste;
    string end = this->enderecoArqBin;
    ofstream outFile(end + "teste.txt", ios_base::app);

    int j = 0;

    for (int i = 0; i < tamanho; i++)
    {

        no = aux[i];

        if (no != nullptr)
        {

            while (no != nullptr)
            {
                vet[j] = no;
                j += 1;
                no = no->proximo;
            }
        }
    }
    //ordenando em quick sort
    quickHash(vet, 0, j - 1);

    ifstream arqBin(enderecoArqBin + "tracks.bin");
    int nReg = nRegistrosArtists(arqBin);

    Tracks maior;
    Tracks tracks;
    char aux2[2000];
    char nomeMusica[5000];
    int popularidade;
    int n;
    n = m;
    if (n > tamVetorHash)
        n = tamVetorHash-1;

    if (t)
    {
        cout<< "MODO TESTE"<<endl;
        cout << "BUSCANDO A MUSICA MAIS POPULAR DOS " << n << " ARTISTAS MAIS FREQUENTES NO ARQUIVO BINÁRIO " << endl;
    }
    else
    {
        
        cout<< "MODO HASH"<<endl;
        cout << "BUSCANDO A MUSICA MAIS POPULAR DOS " << n << " ARTISTAS MAIS FREQUENTES NO ARQUIVO BINÁRIO " << endl;
    }

    
    for (int g = 0; g < n; g++)
    {   
        for (int p = 0; p < (586672 - 1); p++)//pecorre todo o arquivo binário em busca da música mais popular de cada Artists
        {

            tracks = returnTrack(arqBin, p);

            strcpy(aux2, tracks.id_artists);

            if (strstr(aux2, vet[g]->getIdA()))
            {
                maior = tracks;
                if (tracks.popularity > maior.popularity)
                    maior = tracks;
                strcpy(nomeMusica, tracks.name);
                popularidade = tracks.popularity;
            }
        }

        if (t)
        {
            outFile << "O ARTISTA COM O ID '" << vet[g]->getIdA() << "' POSSUI A MÚSICA '" << nomeMusica << "' COMO SUA MAIS POPULAR. POPULARIDADE: " << popularidade << "\n";
        }
        else
        {
            cout << "O ARTISTA COM O ID '" << vet[g]->getIdA() << "' POSSUI A MÚSICA '" << nomeMusica << "' COMO SUA MAIS POPULAR. POPULARIDADE: " << popularidade << endl;
        }
    }

    outFile.close();
    arqBin.close();
    delete[] vet;
}

/**
 * @brief Busca um ID na tabela hash
 * 
 * @param IdA id do artista
 * @return int 
 */
int HashMap::busca(char *IdA)
{   
    bool flag = false;
    int key = convertToInt(IdA);
    int hash = (key % tamanho); //divisao
    Registro *entrada = table[hash];
    while (entrada != nullptr)
    {
        if (entrada->getIdA() == IdA)
        {
            while (entrada->proximo != nullptr)
            {
                cout << entrada->getIdA() << " " << hash << endl;
                entrada = entrada->proximo;
            }
            flag = true;
        }
        entrada = entrada->proximo;
    }
    if (!flag)
        return 1;
    return 0;
}

/**
 * @brief Função principal do quickSort para a tabela hash
 * 
 * @param vet Vetor a ser ordenado
 * @param p Primeiro elemento do vetor
 * @param r Último elemento do vetor
 */
void HashMap::quickHash(Registro **vet, int p, int r)
{  
    if (p >= r)
    {
        return;
    }
    int pivo = particionamentoHash(vet, p, r);
    quickHash(vet, p, pivo - 1);
    quickHash(vet, pivo + 1, r);
}

/**
 * @brief Função de particionamento da ordenação em quickSort
 * 
 * @param vet Vetor a ser ordenado
 * @param p Primeiro elemento do vetor
 * @param q Último elemento do vetor
 * @return Endereço atual do pivô dentro do vetor 
 */
int HashMap::particionamentoHash(Registro **vet, int p, int q)
{   
    int i = p;
    for (int j = p; j < q; j++)
    {
        if (vet[j]->quantidade >= vet[q]->quantidade)
        {
            swap(vet[i++], vet[j]);
        }
    }
    swap(vet[i], vet[q]);
    return i;
}
