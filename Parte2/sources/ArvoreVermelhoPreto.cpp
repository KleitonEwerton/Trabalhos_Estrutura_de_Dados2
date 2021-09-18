#include <iostream>
#include "ArvoreVermelhoPreto.h"
#include "string.h"
#include <fstream>
#include "Artists.h"
#include <chrono>
#include "Tools.h"
using namespace std;

int comparacoesBAVP = 0;
long long comparacoesIAVP = 0;

/**
 * @brief Construtor da nova Arvore Vermelho Preto
 * 
 * @param enderecoArqBin Endereco da pasta
 */
ArvoreVermelhoPreto::ArvoreVermelhoPreto(string enderecoArqBin)
{
    //Cada folha (NIL) é preta
    //No sentinela
    NIL = new NoArvoreVermelhoPreto;
    NIL->setCor(0);
    NIL->setEsq(NULL);
    NIL->setDir(NULL);

    //A raiz é preta
    raiz = NIL;

    this->enderecoArqBin = enderecoArqBin;
}

/**
 * @brief Destrutor da Arvore Vermelho-Preto
 * 
 */
ArvoreVermelhoPreto::~ArvoreVermelhoPreto()
{
    raiz = libera(raiz);
    delete NIL;
}

/**
 * @brief Auxilia na destrução da Arvore Vermelho-Preto
 * 
 * @param p Raiz
 * @return NoArvoreVermelhoPreto* 
 */
NoArvoreVermelhoPreto *ArvoreVermelhoPreto::libera(NoArvoreVermelhoPreto *p)
{
    if (p != NIL)
    {
        p->setEsq(libera(p->getEsq()));
        p->setDir(libera(p->getDir()));
        delete p;
        p = NIL;
    }
    return p;
}

/**
 * @brief Insercao na arvore Vermelho-Preto
 * 
 * @param idArtista Id do artista
 */
void ArvoreVermelhoPreto::insere(char *idArtista, int pos)
{
    //PRETO = 0
    //VERMELHO = 1

    t = new NoArvoreVermelhoPreto;

    //novo no
    string endereco = this->enderecoArqBin;
    ifstream arqBin(endereco + "artists.bin");

    //pega a localizacao no arquivo binario
    int local = pos;

    //Insere nó
    t->setPai(NULL);       //pai aponta para null
    t->setEsq(NIL);        //filho esquerdo aponta para a sentinela
    t->setDir(NIL);        //filho direito aponta para a sentinela
    t->setCor(1);          //cor vermelha
    t->setInfo(idArtista); //id do Artista
    t->setLocal(local);    //localizacao no arquivo binario

    Artists artista1, artista2;

    artista1 = returnArtist(arqBin, local);

    char *nomeArtista1, *nomeArtista2;

    //chama a funcao para retornar o nome ou conserta-lo
    nomeArtista1 = retiraCaracteres(artista1.name);

    NoArvoreVermelhoPreto *y, *x;
    y = NULL;
    x = this->raiz;

    //anda pela árvore para achar local de inserção
    comparacoesIAVP++;
    while (x != NIL)
    {
        y = x;
        artista2 = returnArtist(arqBin, x->getLocal()); //nome do no atual

        //chama a funcao para retornar o nome ou conserta-lo
        nomeArtista2 = retiraCaracteres(artista2.name);

        //Comparacoes para andar na arvore
        //resultado menor que zero = caracter nomeArtista1 eh menor (ordem alfabetica) do que nomeArtista2, ou seja, raiz
        if (strcmp(nomeArtista1, nomeArtista2) < 0)
        {
            comparacoesIAVP++;
            x = x->getEsq(); //desce na esquerda
        }

        //resultado maior que zero = caracter nomeArtista1 eh maior (ordem alfabetica) do que nomeArtista2, ou seja, raiz
        else if (strcmp(nomeArtista1, nomeArtista2) > 0)
        {
            comparacoesIAVP += 2;
            x = x->getDir(); //desce na direita
        }

        else
        {
            //igual
            //cout << "O artista " << nomeArtista1 << " ja esta na base de dados da Arvore Vermelho-Preto" << endl;
            comparacoesIAVP += 2;
            delete t;
            return;
        }
        comparacoesIAVP++;
    }
    //encontrou local de inserção

    //pai do t aponta para y
    t->setPai(y);

    //arvore vazia
    if (y == NULL)
    {
        comparacoesIAVP++;
        raiz = t;
    }

    else
    {
        artista2 = returnArtist(arqBin, y->getLocal()); //nome do no atual
        nomeArtista2 = retiraCaracteres(artista2.name);

        //compara os valores
        if (strcmp(nomeArtista1, nomeArtista2) < 0)
        {
            comparacoesIAVP += 2;
            //filho esquerdo aponta para t
            y->setEsq(t);
        }
        else if (strcmp(nomeArtista1, nomeArtista2) > 0)
        {
            comparacoesIAVP += 3;
            //filho direito aponta para t
            y->setDir(t);
        }
    }

    //verificacao com NULL porque o no pai eh "setado" com null, ou seja, raiz
    comparacoesIAVP++;
    if (t->getPai() == NULL)
    {
        //raiz preta
        t->setCor(0);

        //retorna porque eh a raiz e ja fez a recoloracao
        return;
    }

    //verifica nao existe avo
    comparacoesIAVP++;
    if (t->getPai()->getPai() == NULL)
    {
        //caso o avo nao existe, o no ja eh vermelho e a arvore esta balanceada, nao sendo necessario rotacionar ou recolorir
        return;
    }

    //chama para corrigir a arvore (quebra de propriedades)
    auxInsere(raiz, t);
    arqBin.close();
}

/**
 * @brief Corrigir insercoes na arvore Vermelho-Preto
 * 
 * @param r Raiz da arvore
 * @param t No para ser corrigido
 */
void ArvoreVermelhoPreto::auxInsere(NoArvoreVermelhoPreto *r, NoArvoreVermelhoPreto *t)
{
    //so para ter certeza que a raiz esta certa
    raiz = r;

    //nos para auxiliar a recoloracao/rotacao
    NoArvoreVermelhoPreto *tio, *pai, *avo;

    //enquando o pai e vermelho
    comparacoesIAVP++;
    while (t->getPai()->getCor() == 1)
    {
        //verifica se o pai eh igual o tio
        if (t->getPai() == t->getPai()->getPai()->getDir())
        {
            tio = t->getPai()->getPai()->getEsq();

            //Tio é vermelho
            if (tio->getCor() == 1)
            {
                comparacoesIAVP += 2;
                pai = t->getPai();
                avo = t->getPai()->getPai();

                //Troca as cores do pai, do tio e do avô
                pai->setCor(0);
                tio->setCor(0);
                avo->setCor(1);

                //O avô se torna o novo nó para verificar as violações
                t = avo;
            }
            else //O tio é preto
            {
                //verifica se eh igual
                if (t == t->getPai()->getEsq())
                {
                    comparacoesIAVP += 3;
                    pai = t->getPai();

                    //pai se torna o no para rotacao
                    t = pai;

                    //rotaciona para a direita em torno do pai
                    rotacaoDireita(r, t);
                }

                pai = t->getPai();
                avo = t->getPai()->getPai();

                //trocs as cores do pai e do avô
                pai->setCor(0);
                avo->setCor(1);

                //O avô se torna o novo nó para verificar as violações
                //Gire para a esquerda ao redor do avô
                rotacaoEsquerda(r, avo);
            }
        }
        else
        {
            //mesmas operacoes do if, porem para a direita
            tio = t->getPai()->getPai()->getDir();

            //tio eh vermelho
            if (tio->getCor() == 1)
            {
                comparacoesIAVP += 2;
                pai = t->getPai();
                avo = t->getPai()->getPai();

                //Troca as cores do pai, do tio e do avô
                pai->setCor(0);
                tio->setCor(0);
                avo->setCor(1);

                //O avô se torna o novo nó para verificar as violações
                t = avo;
            }
            else //tio eh preto
            {
                //verifica se eh igual
                if (t == t->getPai()->getDir())
                {
                    comparacoesIAVP += 3;
                    pai = t->getPai();

                    //pai se torna o no para rotacao
                    t = pai;

                    //rotaciona para a esquerda em torno do pai
                    rotacaoEsquerda(r, t);
                }

                pai = t->getPai();
                avo = t->getPai()->getPai();

                //troca as cores do pai e do avô
                pai->setCor(0);
                avo->setCor(1);

                //rotaciona para a direita em torno do avo
                rotacaoDireita(r, avo);
            }
        }

        //no eh igual a raiz, sai
        comparacoesIAVP++;
        if (t == raiz)
        {
            break;
        }
        comparacoesIAVP++; //while
    }
    //recolore a raiz para cor preta
    raiz->setCor(0);
}

/**
 * @brief Rotacao para a esquerda na arvore Vermelho-Preto
 * 
 * @param r Raiz
 * @param p No para fazer a rotacao
 */
void ArvoreVermelhoPreto::rotacaoEsquerda(NoArvoreVermelhoPreto *r, NoArvoreVermelhoPreto *p)
{
    raiz = r;

    //definicao do y
    NoArvoreVermelhoPreto *y = p->getDir();

    //filho esquerdo de y sera o filho direiro de p
    p->setDir(y->getEsq());

    //se o filho esquerdo de y for diferente do no sentinela
    comparacoesIAVP++;
    if (y->getEsq() != NIL)
    {
        //o pai do filho esquerdo sera o no p
        y->getEsq()->setPai(p);
    }

    //pai de y vira pai de p
    y->setPai(p->getPai());

    //se o pai nao existe, ou seja, raiz
    comparacoesIAVP++;
    if (p->getPai() == NULL)
    {
        //a raiz recebe o no y
        this->raiz = y;
    }
    //caso o pai exista
    else
    {
        //se o no p e igual o filho esquerdo do pai
        if (p == p->getPai()->getEsq())
        {
            comparacoesIAVP++;
            //o filho esquerdo do pai recebe y
            p->getPai()->setEsq(y);
        }
        //se nao e igual
        else
        {
            comparacoesIAVP++;
            //o filho direito do pai recebe y
            p->getPai()->setDir(y);
        }
    }
    //p se torna o filho esquerdo de y
    y->setEsq(p);
    //y se torna o pai de p
    p->setPai(y);
}

/**
 * @brief Rotacao para a esquerda na arvore Vermelho-Preto
 * 
 * @param r Raiz
 * @param p No para fazer a rotacao
 */
void ArvoreVermelhoPreto::rotacaoDireita(NoArvoreVermelhoPreto *r, NoArvoreVermelhoPreto *p)
{
    raiz = r;
    NoArvoreVermelhoPreto *x = p->getEsq();
    p->setEsq(x->getDir());

    comparacoesIAVP++;
    if (x->getDir() != NIL)
    {
        x->getDir()->setPai(p);
    }

    x->setPai(p->getPai());

    if (p->getPai() == NULL)
    {
        comparacoesIAVP++;
        this->raiz = x;
    }
    else if (p == p->getPai()->getDir())
    {
        comparacoesIAVP += 2;
        p->getPai()->setDir(x);
    }
    else
    {
        comparacoesIAVP += 2;
        p->getPai()->setEsq(x);
    }
    x->setDir(p);
    p->setPai(x);
}

/**
 * @brief Imprimir a arvore Vermelho-Preto
 * 
 */
void ArvoreVermelhoPreto::imprime()
{
    if (raiz == NIL)
    {
        cout << "Arvore Vazia" << endl;
        return;
    }
    auxImprime(raiz); //chama funcao auxiliar
}

/**
 * @brief Imprimir a arvore Vermelho-Preto no console
 * 
 * @param p Raiz
 */
void ArvoreVermelhoPreto::auxImprime(NoArvoreVermelhoPreto *p)
{
    //como vai descer na arvore, faz a verificacao novamente
    if (p != NIL)
    {
        auxImprime(p->getEsq());

        cout << "ID: " << p->getInfo() << endl;

        string endereco = this->enderecoArqBin;
        ifstream arqBin(endereco + "artists.bin");

        Artists artista = returnArtist(arqBin, p->getLocal()); //nome do no atual

        cout << "Nome: " << retiraCaracteres(artista.name) << endl;
        cout << "Seguidores: " << artista.followers << endl;

        char *genero = strtok(artista.genres, "'[]\"");
        cout << "Genero: ";
        while (genero != NULL)
        {
            cout << genero;
            genero = strtok(NULL, "'[]\"");
        }
        cout << endl;

        cout << "Popularidade: " << artista.popularity << endl;

        bool corI = p->getCor();

        if (corI == 0)
        {
            cout << "Cor: Preto" << endl;
        }
        else
        {
            cout << "Cor: Vermelho" << endl;
        }

        /*
        //So pra saber
        if (p->getPai() == NULL)
        {
            cout << "Nao tem pai" << endl;
        }
        else
        {
            artista = returnArtist(arqBin, p->getPai()->getLocal()); //nome do no atual
            cout << "Pai: " << retiraCaracteres(artista.name) << endl;
        }

        if (p->getEsq() == NIL)
        {
            cout << "Nao tem filho esquerdo" << endl;
        }
        else
        {
            artista = returnArtist(arqBin, p->getEsq()->getLocal()); //nome do no atual
            cout << "Filho esquerdo:: " << retiraCaracteres(artista.name) << endl;
        }

        if (p->getDir() == NIL)
        {
            cout << "Nao tem filho direito" << endl;
        }
        else
        {
            artista = returnArtist(arqBin, p->getDir()->getLocal()); //nome do no atual
            cout << "Filho direito:: " << retiraCaracteres(artista.name) << endl;
        }
        */

        cout << "----------------------------------------" << endl;
        auxImprime(p->getDir());
        arqBin.close();
    }
}

/**
 * @brief Busca na arvore Vermelho-Preto para exibicao no console
 * 
 * @param nomeA Nome a ser pesquisado 
 */
void ArvoreVermelhoPreto::buscaConsole(char *nomeA)
{
    auxBuscaConsole(this->raiz, nomeA); //chama funcao auxiliar
}

/**
 * @brief Auxilia na busca na arvore Vermelho-Preto 
 * 
 * @param r Raiz
 * @param nomeA Nome a ser pesquisado
 */
void ArvoreVermelhoPreto::auxBuscaConsole(NoArvoreVermelhoPreto *r, char *nomeA)
{
    bool igual = false;
    NoArvoreVermelhoPreto *temp = r;
    NoArvoreVermelhoPreto *item = NULL;

    string endereco = this->enderecoArqBin;
    ifstream arqBin(endereco + "artists.bin");

    Artists artista1;
    while (!igual)
    {
        //arvore esta vazia ou chegou na folha
        if (temp == NIL)
        {
            comparacoesBAVP++;
            break;
        }
        else
        {
            artista1 = returnArtist(arqBin, temp->getLocal()); //nome do no atual
            char *nomeArtista1;
            //chama a funcao para retornar o nome ou conserta-lo
            nomeArtista1 = retiraCaracteres(artista1.name);

            if (strcmp(nomeA, nomeArtista1) < 0)
            {
                comparacoesBAVP += 2;
                temp = temp->getEsq(); //desce na arvore pela esquerda
            }

            else if (strcmp(nomeA, nomeArtista1) > 0)
            {
                //comparacoes aumenta 3 porque ele testa o if antes do else e o 1° if juntamente com 2° tambem
                comparacoesBAVP += 3;
                temp = temp->getDir(); //desce na arvore pela direita
            }

            else
            {
                //+3 porque teste 3 if
                //2° if (no eh nil)
                //2° if (caracter nomeA eh menor (ordem alfabetica) do que nomeArtista1)
                //3° if (caracter nomeA eh maior (ordem alfabetica) do que nomeArtista1)
                comparacoesBAVP += 3;
                igual = true;
                item = temp;
            }
        }
    }

    //se achou o nome, imprime todas as informacoes
    if (igual)
    {
        cout << "__________________________________________________________________________________________________________________" << endl;
        cout << "\nInformacoes do artista" << endl;
        Artists artista = returnArtist(arqBin, temp->getLocal()); //nome do no atual

        cout << "ID: " << artista.id << endl;
        cout << "Nome: " << retiraCaracteres(artista.name) << endl;
        cout << "Seguidores: " << artista.followers << endl;

        char *genero = strtok(artista.genres, "'[]\"");
        cout << "Genero: ";
        while (genero != NULL)
        {
            cout << genero;
            genero = strtok(NULL, "'[]\"");
        }
        cout << endl;
        cout << "Popularidade: " << artista.popularity << endl;
        cout << "__________________________________________________________________________________________________________________" << endl;
    }
    //se nao achou o nome, informa o usuario
    else
        cout << "\nO nome " << nomeA << " nao consta na base de dados." << endl;
    arqBin.close();
}

/**
 * @brief Busca na arvore Vermelho-Preto para escrita no arquivo
 * 
 * @param nomeA Nome a ser pesquisado
 * @return true se encontrou o artista
 * @return false se nao encontrou o artista
 */
bool ArvoreVermelhoPreto::buscaArquivo(char *nomeA)
{
    return auxBuscaArquivo(this->raiz, nomeA); //chama funcao auxiliar
}

/**
 * @brief  Auxilia na busca na arvore Vermelho-Preto 
 * 
 * @param r Raiz
 * @param nomeA Nome a ser pesquisado
 * @return true se encontrou o artista
 * @return false se nao encontrou o artista
 */
bool ArvoreVermelhoPreto::auxBuscaArquivo(NoArvoreVermelhoPreto *r, char *nomeA)
{
    bool igual = false;
    NoArvoreVermelhoPreto *temp = r;
    NoArvoreVermelhoPreto *item = NULL;

    string endereco = this->enderecoArqBin;
    ifstream arqBin(endereco + "artists.bin");

    Artists artista1;
    while (!igual)
    {
        //arvore esta vazia ou chegou na folha
        if (temp == NIL)
        {
            comparacoesBAVP++;
            break;
        }
        else
        {
            artista1 = returnArtist(arqBin, temp->getLocal()); //nome do no atual

            char *nomeArtista1;

            //chama a funcao para retornar o nome ou conserta-lo
            nomeArtista1 = retiraCaracteres(artista1.name);

            if (strcmp(nomeA, nomeArtista1) < 0)
            {
                comparacoesBAVP += 2;
                temp = temp->getEsq(); //desce na arvore pela esquerda
            }

            else if (strcmp(nomeA, nomeArtista1) > 0)
            {
                //comparacoes aumenta 3 porque ele testa o if antes do else e o 1° if juntamente com 2° tambem
                comparacoesBAVP += 3;
                temp = temp->getDir(); //desce na arvore pela direita
            }

            else
            {
                //+3 porque teste 3 if
                //2° if (no eh nil)
                //2° if (caracter nomeA eh menor (ordem alfabetica) do que nomeArtista1)
                //3° if (caracter nomeA eh maior (ordem alfabetica) do que nomeArtista1)
                comparacoesBAVP += 3;
                igual = true;
                item = temp;
            }
        }
    }

    arqBin.close();
    return igual;
}

/**
 * @brief Realizar a insercao e busca do(s) artista(s) na arvore Vermelho-Preto
 * 
 * @param arvoreVP Endereco da pasta
 * @param nomeArq Nome do arquivo de texto
 * @param opcao Gerar um relatorio ou realizar uma busca simples 
 */
void ArvoreVermelhoPreto::metricaArvoreVermelhoPreto(string arvoreVP, string nomeArq, int opcao)
{
    ifstream arqBin(arvoreVP + "artists.bin");

    cout << "REALIZANDO A INSERCAO NA ARVORE VERMELHO-PRETO" << endl;

    long long microseconds;
    long long mediaMicroseconds = 0;
    long long mediaComparacoes = 0;
    long long mediaMovimentacoes = 0;

    //insercao
    // int nRegistro = 100;
    int nRegistro = nRegistrosArtists(arqBin);
    auto inicio = chrono::high_resolution_clock::now();
    char *idArtistsSCE, *nome;
    for (int i = 0; i < nRegistro; i++)
    {
        Artists vet = returnArtist(arqBin, i);
        //verifica se precisa corrigir o nome
        nome = retiraCaracteres(vet.name);

        //caso  funcao nao retorne false, quer dizer que o nome eh valido e insere
        if (strcmp(nome, "false") != 0)
        {
            idArtistsSCE = vet.id;
            insere(idArtistsSCE, i);
        }
    }
    auto final = chrono::high_resolution_clock::now() - inicio;
    microseconds = chrono::duration_cast<chrono::microseconds>(final).count();

    cout << "REALIZANDO A BUSCA NA ARVORE VERMELHO-PRETO\n";
    bool resp;
    if (opcao == 1)
    {
        ofstream arqOut(arvoreVP + nomeArq, ios_base::app);
        arqOut << "ARVORE VERMELHO-PRETO\n";
        arqOut << "\nTEMPO DE EXECUÇÃO DA INSERÇÃO(EM SEGUNDOS) PARA " << nRegistro << " INSERÇÕES: " << microseconds / 1000000.0 << "\n";
        arqOut << "\nTOTAL DE COMPARAÇÕES DA INSERÇÃO PARA " << nRegistro << " INSERÇÕES: " << comparacoesIAVP << "\n";
        arqOut << "__________________________________________________________________________________________________________________" << endl;
        //busca
        int m = 100;
        char *nomeArtista;
        Artists *vet = returnVetArtists(arqBin, m);
        for (int i = 0; i < m; i++)
        {
            nomeArtista = retiraCaracteres(vet[i].name);
            auto inicio1 = chrono::high_resolution_clock::now();
            //caso  funcao nao retorne false, quer dizer que o nome eh valido e insere
            if (strcmp(nome, "false") != 0)
                resp = buscaArquivo(nomeArtista);
            else //para evitar que pesquise a palavra false na arvore se o nome nao eh valido, pesquisa esse nome, mesmo sabendo que ele nao se encontra
            {
                resp = buscaArquivo(vet[i].name);
            }

            auto final1 = chrono::high_resolution_clock::now() - inicio1;
            microseconds = chrono::duration_cast<chrono::microseconds>(final1).count();

            //caso a funcao retorne true, ou seja, achou o artista
            if (resp)
            {
                //escreve as informacoes no arquivo
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
            //caso nao tenha achado, tambem escreve no arquivo informando ao usuario
            else
            {
                arqOut << "\nO ARTISTA " << nomeArtista << " NAO CONSTA NA BASE DE DADOS DA ARVORE VERMELHO-PRETO\n";
            }

            arqOut << "\nTEMPO DE EXECUÇÃO DA BUSCA(EM SEGUNDOS): " << microseconds / 1000000.0 << "\n";
            arqOut << "\nTOTAL DE COMPARAÇÕES DA BUSCA: " << comparacoesBAVP << "\n";
            arqOut << "__________________________________________________________________________________________________________________" << endl;
            mediaMicroseconds += microseconds;
            mediaComparacoes += comparacoesBAVP;
            comparacoesBAVP = 0;
        }
        delete[] vet;
        mediaMicroseconds /= m;
        mediaComparacoes /= m;

        arqOut << "\nMEDIAS BUSCA: COMPARAÇÕES: " << mediaComparacoes << " TEMPO DE EXECUÇÃO(EM SEGUNDOS): " << mediaMicroseconds / 1000000.0 << "\n";
        arqOut << "__________________________________________________________________________________________________________________\n\n";
        arqOut.close();
    }
    else
    {
        char b[400];
        //tratando o enter do usuario, pois eh interpretado como um caracter da busca
        cin.getline(b, 400);

        cout << "Digite o nome para busca: ";
        cin.getline(b, 400);

        //converte o nome para maiusculo, pois na ordenacao os nomes sao convertidos
        maiusculo(b);

        //realiza a busca
        buscaConsole(b);
        comparacoesBAVP = 0;
    }
    comparacoesIAVP = 0;
    arqBin.close();
}