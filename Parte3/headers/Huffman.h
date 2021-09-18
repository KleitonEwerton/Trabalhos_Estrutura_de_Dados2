#include "string.h"
#include "NoHuffman.h"
using namespace std;
class Huffman
{
public:
    Huffman()       {raiz = nullptr;};
    ~Huffman();

    void libera(NoHuffman *p);

    void imprimir(NoHuffman *p, string s);

    void codigo(NoHuffman *p, string s);

    void calcularFrequencia(string s);

    void codifica();

    void metrica(string huffman, string saida, string str, double tam);

    string decodifica(NoHuffman *p, string s);

    void codigoASCII(string s, string saida, double tam);

private:
    NoHuffman *raiz;
};