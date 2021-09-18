#include "NoArvoreVermelhoPreto.h"
#include <string.h>
#include <iostream>
#include <iomanip>

using namespace std;

class ArvoreVermelhoPreto
{
private:
    NoArvoreVermelhoPreto *raiz; // ponteiro para o No raiz da árvore
    NoArvoreVermelhoPreto *NIL;    // no sentinela
    NoArvoreVermelhoPreto *t;    // no para auxiliar insercao
    string enderecoArqBin;

public:
    ArvoreVermelhoPreto(string enderecoArqBin);
    ~ArvoreVermelhoPreto();
    NoArvoreVermelhoPreto* libera(NoArvoreVermelhoPreto *p);
    void insere(char *key, int pos);
    void auxInsere(NoArvoreVermelhoPreto *r, NoArvoreVermelhoPreto *p);
    void rotacaoEsquerda(NoArvoreVermelhoPreto *r, NoArvoreVermelhoPreto *p);
    void rotacaoDireita(NoArvoreVermelhoPreto *r, NoArvoreVermelhoPreto *p);

    bool buscaArquivo(char *key);
    bool auxBuscaArquivo(NoArvoreVermelhoPreto *r, char *key);

    void buscaConsole(char *key);
    void auxBuscaConsole(NoArvoreVermelhoPreto *r, char *key);

    void imprime();
    void auxImprime(NoArvoreVermelhoPreto *);
    void metricaArvoreVermelhoPreto(string arvoreVP, string nomeArq, int opcao);
};

