#ifndef EDA48EBB_A540_42DE_9540_8CABD9A2B3FD
#define EDA48EBB_A540_42DE_9540_8CABD9A2B3FD

#include "NoArvoreB.h"

using namespace std;

class ArvoreB
{
        private :

                NoArvoreB *root ;
                int t;
                static void imprimeAux ( NoArvoreB *root, ifstream &arq ) ;
                static void desaloca ( NoArvoreB *root ) ;
                int colocaValor ( int val, char nome[],NoArvoreB *n, int *p, NoArvoreB **c, ifstream &arq) ;
                void preencherNo ( int val, NoArvoreB *c, NoArvoreB *n, int pos ,ifstream &arq) ;
                void split ( int val,NoArvoreB *c, NoArvoreB *n,int pos, int *pVal, NoArvoreB **newnode, ifstream &arq);
                int buscaAux(char str[], int *pos, NoArvoreB *root, ifstream &arq);
        public :
                
                ArvoreB(int t);
                ~ArvoreB();
                int busca(char str[], ifstream &arq);
                void inserir ( int val, ifstream &arq) ;
                void imprime(ifstream &arq) ;
                void metricaArvoreB(string caminho, int key);        
                
} ;

#endif /* EDA48EBB_A540_42DE_9540_8CABD9A2B3FD */
