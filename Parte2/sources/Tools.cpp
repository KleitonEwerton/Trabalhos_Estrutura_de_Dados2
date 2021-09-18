#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>
#include "Artists.h"
#include "Tracks.h"
#include "Tools.h"

/**
 * @brief                                                               Função que converte todos os caracteres de uma string em maiusculo
 * 
 * @param s1                                                            char[] a ser convertida
 */
void maiusculo(char *nome)
{
    int tam = strlen(nome);

    for (int i = 0; i < tam; i++)
    {
        if (nome[i] >= 97 && nome[i] <= 122)
        {
            nome[i] = nome[i] - 32;
        }
    } //Caracter que indica o fim da string
}

/**
 * @brief                                                               Função que retorna a ordem alfabetica de dois artistas
 * 
 * @param posArt1                                                       A posição do artista 1 no arquivo binário
 * @param posArt2                                                       A posição do artista 2 no arquivo binário
 * @param caminho                                                       Caminho do arquivo binário artists.bin
 * @return int                                                          Retorno 1: o artista 1 é maior que o artista 2. Retorno -1: o artista 1 é menor que o artista 2
 *                                                                      Retorno 0: possuem o mesmo nome
 */
int artista_ordem_alfabetica(int posArt1, int posArt2, ifstream &arq)
{

    Artists art1;
    Artists art2;

    art1 = returnArtist(arq, posArt1);
    art2 = returnArtist(arq, posArt2);

    if (strcmp(art1.name, art2.name) > 0)
        return 1;

    if (strcmp(art1.name, art2.name) < 0)
        return -1;

    return 0;
}

/**
 * @brief                                                               Função que retorna a ordem alfabetica de dois artistas
 * 
 * @param posArt1                                                       A posição do artista 1 no arquivo binário
 * @param posArt2                                                       A posição do artista 2 no arquivo binário
 * @param caminho                                                       Caminho do arquivo binário artists.bin
 * @return int                                                          Retorno 1: o artista 1 é maior que o artista 2. Retorno -1: o artista 1 é menor que o artista 2
 *                                                                      Retorno 0: possuem o mesmo nome
 */
int artista_ordem_alfabetica2(char name1[], int posArt2, ifstream &arq)
{

    maiusculo(name1);

    Artists art2;

    art2 = returnArtist(arq, posArt2);

    if (strcmp(name1, art2.name) > 0)
        return 1;

    if (strcmp(name1, art2.name) < 0)
        return -1;

    return 0;
}

int artista_ordem_alfabetica3(char name1[], int posArt2, ifstream &arq)
{

    Artists art2;

    art2 = returnArtist(arq, posArt2);

    if (strcmp(name1, art2.name) > 0)
        return 1;

    if (strcmp(name1, art2.name) < 0)
        return -1;

    return 0;
}

/**
 * @brief                                                               Imprime um artista completo na tela apartir de sua posição no arquivo binário
 * 
 * @param posArt                                                        Posição do artista no arquivo binário
 * @param caminho                                                       Caminho do arquivo binário artists.bin
 */
void imprimeArtista(int posArt, ifstream &arq)
{

    Artists art1;

    art1 = returnArtist(arq, posArt);

    cout << "\nKEY: " << posArt << " NOME: " << art1.name << " ID: " << art1.id << " FOLLOWERS: " << art1.followers << " POPULARITY: " << art1.popularity << " GENRES: " << art1.genres << endl
         << endl;
}

/**
 * @brief                                                               Função que copia o id de um artista em certa posição para o char passado no parametô
 * 
 * @param Ids                                                           A string que será mudada
 * @param posArt2                                                       A posição do artista no arquivo binário
 * @param caminho                                                       Caminho do arquio binário
 */
void converte_pos_in_ID(char Ids[], int posArt2, ifstream &arq)
{

    Artists idA;
    idA = returnArtist(arq, posArt2);
    strcpy(Ids, idA.id);
}

char *retiraCaracteres(char *nome)
{
    int tam = strlen(nome);
    if (nome[0] >= 0 && nome[0] <= 47 || nome[0] >= 58 && nome[0] <= 64 || nome[0] >= 91 && nome[0] <= 255)
    {
        if (nome[1] >= 0 && nome[1] <= 47 || nome[1] >= 58 && nome[1] <= 64 || nome[1] >= 91 && nome[1] <= 255)
        {
            return (char *)"false";
        }
        else
        {
            memmove(nome, nome + 1, tam);
            return nome;
        }
    }
    else
    {
        return nome;
    }
}
