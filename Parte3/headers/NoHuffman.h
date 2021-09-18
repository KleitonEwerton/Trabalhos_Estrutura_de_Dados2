#include "string.h"
using namespace std;

class NoHuffman
{
public:
  NoHuffman(){};
  ~NoHuffman(){};

  //Construtor para alocar novo no
  NoHuffman(char nome, int frequencia)
  {
    this->nome = nome;             //Caracter
    this->frequencia = frequencia; //Frequencia do caracter
    esquerdo = nullptr;
    direito = nullptr;
  }

  void setFrequencia(int fq) { frequencia = fq; };
  void setNome(char name) { nome = name; };

  int getFrequencia() { return frequencia; };
  char getNome() { return nome; };

  NoHuffman *getEsq() { return esquerdo; };
  NoHuffman *getDir() { return direito; };

  void setEsq(NoHuffman *p) { esquerdo = p; };
  void setDir(NoHuffman *p) { direito = p; };

private:
  char nome;           /// informacao do no (caracter)
  int frequencia;      /// informacao do no (frequencia)
  NoHuffman *esquerdo; /// ponteiro para o filho esquerdo
  NoHuffman *direito;  /// ponteiro para o filho direito
};