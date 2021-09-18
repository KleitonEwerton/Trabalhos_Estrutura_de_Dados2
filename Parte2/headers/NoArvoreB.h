#ifndef E8E62114_AB5D_46C6_9A7F_D97C2326588C
#define E8E62114_AB5D_46C6_9A7F_D97C2326588C

#include <vector>

using namespace std;

struct Id{

        char id[25];
};

struct NoArvoreB{

        int contador;
        vector<int> keys;                       //Um vector para as chaves                     
        vector <Id> Ids;                        //Um vector para os Ids
        vector <NoArvoreB *> child;             //Um vector para os filhos

        //Construtor do nó para modificar o tamanho dos vetores
        NoArvoreB(int tam){
                
                keys.resize(tam);
                child.resize(tam);
                Ids.resize(tam);
        };
} ;

#endif /* E8E62114_AB5D_46C6_9A7F_D97C2326588C */