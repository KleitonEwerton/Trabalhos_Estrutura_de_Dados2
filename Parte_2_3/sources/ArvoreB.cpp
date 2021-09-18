#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>
#include "Artists.h"
#include <ctype.h>
#include "NoArvoreB.h"
#include "ArvoreB.h"
#include "Tools.h"
#include <chrono>

int ehMetrica = 0;
long long comparacoesIAB = 0;
long long comparacoesBAB = 0;
using namespace std;
/**
 * @brief                                                                                           Construct a new Arvore B:: Arvore B object
 * 
 * @param t                                                                                         Ordem da arvore b
 */
ArvoreB::ArvoreB(int t ){

    root = NULL;
    this->t = t;
}
/**
 * @brief                                                                                           Função principal de inserção de um valor
 *                      
 * @param val                                                                                       Valor a ser adicionado
 * @param caminho                                                                                   Caminho que contem o arquivo artists.bin
 */
void ArvoreB :: inserir ( int val, ifstream &arq)
        {
        int i ;
        NoArvoreB *c, *n ;                                                                          
        char name1[400];
        char *auxNome;

        
        Artists art1;
        art1 = returnArtist(arq, val);
        strcpy(name1, art1.name);
       

        auxNome = retiraCaracteres(name1);                                                           //Muda para miusculo e não insere caso o começo for caracteres especiais

        if(strcmp(auxNome, "false") == 0)
                return;

        int s = colocaValor ( val, auxNome,root, &i, &c, arq) ;
        if ( s ){                                                                                   //Caso sim uma nova raiz será adicionada, e um split na raiz ocorreu                            
                                                      
                n = new NoArvoreB(2*t+1);                                                           //Aloca um novo nó
                n -> contador = 1 ;                                                                 //Incrementa o contador do nó
                converte_pos_in_ID(n->Ids[1].id,i,arq);                                         //Muda o valor do ID
                n -> keys[1] = i ;                                                                  //A posição 1 representa a key do root
                n -> child[0] = root ;                                                              //A posição 0 dos child aponta para o antigo root
                n -> child[1] = c ;                                                                 //Coloca o nó que subiu no split
                root = n ;
    }
    
}
/**
 * @brief                                                                                       Função recursiva para inserção de um novo valor
 * 
 * @param val                                                                                   Valor a ser colocado
 * @param n                                                                                     No em que será inserido                                                                         
 * @param p                                                                                     Ponteiro que apontara para o valor a ser inserido
 * @param c                                                                                     O nó que subirá no split, caso ocora
 * @param arq                                                                               Caminho que contem o arquivo artists.bin
 * @return int                                                                                  Se 0 não ocorreu split na raiz se 1 ocorre uma troca de raiz
 */
int ArvoreB :: colocaValor ( int val, char nome[], NoArvoreB *n, int *p, NoArvoreB **c, ifstream &arq){
        int pos ;
        
        //Se n for NULL
        if ( n == NULL ){
                
                comparacoesIAB++;
                *p = val ;
                *c = NULL ;
                return 1 ;
        }
        else{

                //Inicia a busca no nó
                //Verifica se o nome é menor ou maior que o nome do no raiz
                if ( artista_ordem_alfabetica3(nome,n -> keys[1], arq) < 0){
                        comparacoesIAB++;
                        pos = 0 ;
                        
                }
                else{
                        
                        pos = n-> contador ;
                        //Verifica todas as outras posições
                        while (artista_ordem_alfabetica3(nome,n -> keys[pos], arq) < 0  && pos > 1 ){
                                ( pos )-- ;
                                comparacoesIAB++;
                        }
                }
                //Se já possuir uma keys que representa o mesmo nome é retirado
                if ( artista_ordem_alfabetica3(nome,n -> keys[pos], arq) == 0 ){
                        comparacoesIAB++;
                        return 0 ;
                
                }
                //Finaliza a busca no nó

                //Verifica se será split
                if ( colocaValor ( val,nome, n -> child[pos], p, c, arq) ){                       //Se os filhos da raiz estão cheios será feito um split na raiz, caso não a função continua até colocar o valor
                        if ( n -> contador < 2 * this->t ){
                                preencherNo ( *p, *c, n, pos,arq ) ;
                                comparacoesIAB+=2;
                                return 0 ;
                        }
                        else{
                                split ( *p, *c, n, pos, p, c,arq ) ;
                                return 1 ;
                        }
                }
                return 0 ;
        }
}


/**
 * @brief                                                                                       Função para preencher o no
 * 
 * @param val                                                                                   Valor da inserção
 * @param c                                                                                     O nó que subirá no split, caso ocora
 * @param raiz                                                                                  No pai 
 * @param pos                                                                                   Posição do ultimo no valido
 */
void ArvoreB :: preencherNo ( int val, NoArvoreB *c, NoArvoreB *raiz, int pos ,ifstream &arq)
{
        int i ;
        //Move os valores para a posição ordenada
        for ( i = raiz->contador ; i > pos ; i-- )
        {
                comparacoesIAB++;
                raiz->keys[i + 1] = raiz->keys[i] ;
                raiz->child[i + 1] = raiz->child[i] ;
                raiz->Ids[i + 1] = raiz->Ids[i];
        }
        //Coloca os novos valores e altera o child da posição pos + 1 se for uma inserção na folha o valor de c será null
        raiz->keys[pos + 1] = val ;
        raiz->child[pos + 1] = c ;
        converte_pos_in_ID(raiz->Ids[pos+1].id,val,arq);
        raiz->contador++ ;
}

/**
 * @brief                                                                                       Função responsavél pelo split 
 * 
 * @param val                                                                                   O valor da inserção, usado na chamada recursiva do preencher_no
 * @param c                                                                                     O nó que subirá no split
 * @param n                                                                                     Antigo no pai, usado para dividir o valor já armazenados
 * @param pos                                                                                   A posição em que será alocado o novo nó
 * @param pVal                                                                                  O ponteiro com o valor que será colocado no nó, que será usado na função inserir
 * @param novoNo                                                                                Novo no que será alocado                                                                              
 * @param arq                                                                               Caminho que contem o arquivo artists.bin
 */
void ArvoreB :: split ( int val, NoArvoreB *c, NoArvoreB *n,int pos, int *pVal, NoArvoreB **novoNo , ifstream &arq)
{
        int i, meio, contN;
        *novoNo = new NoArvoreB(this->t*2+1);                                                   //Aloca o novo nó
        //Define o meio
        if ( pos <= this->t ){
                meio = this->t ;
                comparacoesIAB++;}
        else
                meio = this->t + 1 ;

        //Muda metade dos nos de n para o novoNo
        for ( i = meio + 1 ; i <= 2 * this->t ; i++ ){

                (*novoNo) -> keys[i - meio] = n -> keys[i] ;
                (*novoNo) -> Ids[i -meio] = n ->Ids[i];
                (*novoNo) -> child[i - meio] = n -> child[i] ;
                comparacoesIAB++;
        }
        
        contN = this->t * 2 - meio ;
        (*novoNo)->contador = contN;
        n -> contador = meio ;

        //Decide em qual nó o novo valor será inserido
        if ( pos <= this->t ){
                preencherNo( val, c, n, pos ,arq) ;
                comparacoesIAB++;}
        else
                preencherNo( val, c, *novoNo, pos - meio ,arq) ;

        *pVal = n -> keys[n -> contador] ;
        (*novoNo)-> child[0] = n -> child[n -> contador] ;
        n->contador-- ;
}

/**
 * @brief 
 * 
 * @param arq                                                                               Caminho que contem o arquivo artists.bin  
 */
void ArvoreB :: imprime( ifstream &arq){

        imprimeAux( root, arq) ;                                                            //Chama a função auxiliar de busca recursiva
}
void ArvoreB ::  imprimeAux( NoArvoreB *root , ifstream &arq){
        int i=0;
        if ( root != NULL ){

                for ( i = 0 ; i < root -> contador ; i++ ){
                        imprimeAux ( root -> child[i], arq) ;
                        imprimeArtista(root-> keys[i+1],arq);
                        cout<< root->Ids[i+1].id<<endl;
                }
                imprimeAux( root -> child[i], arq) ;
        }
}

/**
 * @brief                                                                                       Função de busca de um artista
 * 
 * @param str                                                                                   String contendo o nome do artista a ser buscado
 * @param arq                                                                               Caminho que contem o arquivo artists.bin  
 */

int ArvoreB::busca(char str[], ifstream &arq){
        int pos;
        buscaAux(str, &pos, root,arq);
        return 0;
}
/**
 * @brief                                                                                       Função auxiliar na busca recursiva de um artista
 *      
 * @param str                                                                                   String contendo o nome do artista a ser buscado
 * @param pos                                                                                   Posição da busca
 * @param root                                                                                  No em que será feito a busca
 * @param arq                                                                               Caminho que contem o arquivo artists.bin              
 */             
int ArvoreB::buscaAux(char str[], int *pos, NoArvoreB *root, ifstream &arq){
        ehMetrica=0;
        if (root == NULL){
                comparacoesBAB++;
                return 0;
        }

        if (artista_ordem_alfabetica2(str, root -> keys[1], arq) < 0){
                *pos = 0;
                comparacoesBAB++;}

        else{
                *pos = root -> contador ;
                while (artista_ordem_alfabetica2(str, root -> keys[*pos], arq) < 0  && *pos > 1 ){
                        ( *pos )-- ;
                        comparacoesBAB++;
                }
                if (artista_ordem_alfabetica2(str, root -> keys[*pos], arq) == 0 ){
                        comparacoesBAB++;
                        cout << "\nArtista "<< str << " encontrado. Sua KEY: "<< root->keys[*pos] << endl <<endl;
                        ehMetrica=1;
                        return 1;
                }  
        }

        buscaAux(str, pos, root->child[*pos], arq);
        
        return 0;
}
/**
 * @brief                                                                                       Função de metricas da arvore B
 *      
 * @param caminho                                                                                   String contendo o diretorio de artists.bin
 * @param key                                                                                       Chave para saber se temos de implementar o modulo de teste ou modulo de analise.     
 */      
void ArvoreB::metricaArvoreB(string caminho, int key){
        long long tempoInsercao;
        long long tempoBusca;
        long long tempoBuscaTotal;
        long long mediaMicroseconds = 0;
        long long mediaComparacoes = 0;
        //Variaveis que contam o tempo

        auto inicioBuscaUnico = chrono::high_resolution_clock::now();
        auto finalBuscaUnico = chrono::high_resolution_clock::now() - inicioBuscaUnico;
        auto inicioBuscaTotal = chrono::high_resolution_clock::now();
        auto finalBuscaTotal =chrono::high_resolution_clock::now() - inicioBuscaTotal;
        long long somatorioBusca;
        //Inicialização dos cronometros.

        ehMetrica = 1;
        ifstream arq(caminho + "artists.bin"); //Arquivo de entrada

        //QUANTIDADE A SER INSERIDA
        int nRegistro = nRegistrosArtists(arq);
        //QUANTIDA A SER BUSCADA
        int nRegistroB = 100;
        
        cout << "INICIANDO MÉTRICA ARVORE B DE ORDEM: " << this->t << " - INSERINDO "<< nRegistro <<" VALORES"<<endl;
        ofstream arqOut(caminho + "saida.txt", ios_base::app);
        // ArvoreB *ArvB201 = new ArvoreB(20);
        auto inicioInsercao = chrono::high_resolution_clock::now();
        for (int i = 0; i < nRegistro; i++)
                inserir(i, arq);
        cout << "INSERÇÃO FINALIZADA. INICIANDO BUSCA"<<endl;

        auto finalInsercao = chrono::high_resolution_clock::now() - inicioInsercao;
        tempoInsercao = chrono::duration_cast<chrono::microseconds>(finalInsercao).count();
        arqOut << "\n TEMPO DE EXECUÇÃO(EM SEGUNDOS) PARA " << nRegistro << " INSERÇÕES E ORDEM " << this->t << ": " << tempoInsercao / 1000000.0 << "\n";
        arqOut << "\n NUMERO DE COMPARACOES PARA 10.000 INSERÇÕES E ORDEM " << this->t <<": "<< comparacoesIAB << "\n";
        
        char *idArtistsSCE, *nome;
        char *nomeArtista;
        if(key == 1){//Executa o modulo de teste, buscando 100 registros dentre todos os registros do arquivo binário

                Artists *vet = returnVetArtists(arq, nRegistroB);
                inicioBuscaTotal = chrono::high_resolution_clock::now(); 
                for (int i = 0; i < nRegistroB; i++){
                    inicioBuscaUnico = chrono::high_resolution_clock::now();    
                    nomeArtista = vet[i].name;
                    busca(nomeArtista,arq);
                    if(ehMetrica == 1){ //Se a função de busca encontrar o artista com nome da posição vet[i] será impresso suas informações 
                                arqOut << "\nINFORMACOES DO ARTISTA" << endl;
                                arqOut << "ID: " << vet[i].id << endl;
                                arqOut << "NOME: " << retiraCaracteres(nomeArtista) << endl;
                                arqOut << "SEGUIDORES: " << vet[i].followers << endl;

                                char *genero = strtok(vet[i].genres, "'[]\"");
                                arqOut << "GENERO: ";
                        while (genero != NULL)
                        {
                                arqOut << genero;
                                genero = strtok(NULL, "'[]\"");
                        }
                                arqOut << endl;
                                arqOut << "POPULARIDADE: " << vet[i].popularity << endl;
                        }
                        else{
                            arqOut << "\nO ARTISTA " << nomeArtista << " NAO CONSTA NA BASE DE DADOS DA ARVORE B\n";    
                        }
                    finalBuscaUnico = chrono::high_resolution_clock::now() - inicioBuscaUnico;
                    somatorioBusca = chrono::duration_cast<chrono::microseconds>(finalBuscaUnico).count();
                    arqOut << "TEMPO DE EXECUÇÃO DE BUSCA(EM SEGUNDOS): "<<somatorioBusca / 1000000.0 << "\n";
                    arqOut << "TOTAL DE COMPARAÇÕES DA BUSCA: "<<comparacoesBAB << "\n";
                    arqOut << "___________________________________________________________________________" <<endl;
                    mediaComparacoes+=comparacoesBAB;
                    comparacoesBAB=0;
                    mediaMicroseconds += somatorioBusca;
                    //Zerando contadores para o próximo loop
                }
                finalBuscaTotal = chrono::high_resolution_clock::now() - inicioBuscaTotal;
                tempoBuscaTotal = chrono::duration_cast<chrono::microseconds>(finalBuscaTotal).count();  
                delete[] vet;    
                arqOut << "\n TEMPO DE EXECUÇÃO(EM SEGUNDOS) PARA "<<nRegistroB<<" VALORES BUSCADOS: "<< tempoBuscaTotal/  1000000.0 << "\n";
        }
        else if(key==2){ //Executa o modulo de teste, buscando na arvore um artista digitado pelo usuário.
            char manual[400];    
            cin.getline(manual, 400);
            cout << "Digite o nome para busca: ";
            cin.getline(manual, 400);
            busca(manual,arq);
            arqOut << "\n TEMPO DE EXECUÇÃO(EM SEGUNDOS) PARA "<<1<<" VALOR BUSCADO: "<< tempoBuscaTotal/  1000000.0 << "\n";
        }
         mediaMicroseconds/= nRegistro;
         mediaComparacoes/= nRegistro;
        
        
        
        arqOut << "\n TEMPO MEDIO DE BUSCA (EM SEGUNDOS): " << mediaMicroseconds / 1000000.0 << "\n";
        
        arqOut << "\n NUMERO DE COMPARACOES EM BUSCA PARA "<<nRegistro<<" VALORES INSERIDOS E ORDEM "<<this->t<< ": "<< comparacoesBAB << "\n\n";
        arqOut << "__________________________________________________________________________________________________________________\n";
       
        
        comparacoesIAB=0;
        comparacoesBAB=0;
        arqOut.close();
        arq.close(); //!IMPORTANTE

}

/**
 * @brief                                                                                       Função auxiliar do destructor, usada recursivamente para desalocar todos os filhos
 * 
 * @param root                                                                                  No da arvoreB que será feito a recursividade inicial
 */
void ArvoreB :: desaloca ( NoArvoreB *root )
{
        int i=0;
        if ( root != NULL ){

                for (i = 0 ; i < root -> contador ; i++ ){                                      //Percore por todos os childs de root
                        desaloca ( root -> child[i] ) ;                                         //Chama desaloca com cada um dos childs de root
                        delete (root -> child[i]);                                              //Deleta os childs de root
                }
                desaloca ( root -> child[i] ) ;
                delete ( root -> child[i] ) ;
        }
}

ArvoreB :: ~ArvoreB( )
{
        // cout << "\n\n\n________________________DESTRUTOR___________________________\n\n\n" << endl;
        desaloca( root ) ;
	delete root;
        // cout << "\n\n\n_______________________FIM DESTRUTOR_________________________\n\n\n" << endl;
}






