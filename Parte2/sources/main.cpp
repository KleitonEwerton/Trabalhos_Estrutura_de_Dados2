#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>
#include "Artists.h"
#include "Tracks.h"
#include "LeituraArtist.h"
#include "LeituraTrack.h"
#include "MergeSort.h"
#include "Heapsort.h"
#include "QuickSort.h"
#include "InsertSort.h"
#include "Hash.h"
#include "ArvoreVermelhoPreto.h"
#include "ArvoreB.h"
#include "Tools.h"
#include <chrono>

using namespace std;

/**
 * @brief Retornar numero aleatório entre dois números
 * 
 * @param a número 1
 * @param b número 2
 * @return número aleatório
 */
int numAleatorio(int a, int b)
{

    return a + rand() % (b - a + 1);
}

/**
 * @brief Verifica se os arquivos .CSV existem
 * 
 * @param diArq Diretório
 * @return true se existem
 * @return false se não existem
 */
bool verificaArquivosCSV(string diArq)
{
    string dirArqArtCVS = diArq + "artists.csv";
    string dirArqTrackCSV = diArq + "tracks.csv";

    ifstream artCSV(dirArqArtCVS, ios::in);
    ifstream trackCSV(dirArqTrackCSV, ios::in);

    if ((artCSV.is_open()) && (trackCSV.is_open()))
        return true;
    else
        return false;
}

/**
 * @brief Cria um arquivo .dat 
 * 
 * @param dirArq Diretório
 */
void createArquivoHashDat(string dirArq)
{
    //Arquivo Hash padrão, utilizado para a primeira escrita
    string arqDat = dirArq + "hash.dat";

    ofstream outFile;
    outFile.open(arqDat, ios_base::app);
    outFile.seekp(0, ios::end);
    if (outFile.tellp() == 0)
    {

        outFile << "O primeiro parâmento de cada linha representa o tamanho total das musicas, e o segundo parâmetro o parâmetro para os artistas mais frequentes"
                << "\n"
                << "1000,10" << endl;
    }

    outFile.close();
}

/**
 * @brief Cria um arquivo .dat 
 * 
 * @param dirArq Diretório
 */
void createArquivoSortDate(string dirArq)
{
    string arqDat = dirArq + "sort.dat";

    ofstream outFile;
    outFile.open(arqDat);

    //constantes menores que as mencionadas no trabalho - vai depender do processador
    outFile << "O primeiro parâmento de cada linha representa o tamanho total dos dados, e o segundo parâmetro o numero de conjuntos"
            << "\n"
            << "1000,3"
            << "\n"
            << "5000,3"
            << "\n"
            << "10000,3"
            << "\n"
            << "50000,3"
            << "\n"
            << "80000,3" << endl;
    outFile.close();
}

/**
 * @brief Verifica se os arquivos binários existem
 * 
 * @param dirArq Diretório
 */
void verificaArquivosBin(string dirArq)
{

    string dirArqArt = dirArq + "artists.bin";
    string dirArqTra = dirArq + "tracks.bin";
    ifstream artBin(dirArqArt, ios::in);
    ifstream trackBin(dirArqTra, ios::in);

    if ((artBin.is_open()) && (trackBin.is_open()))
    {
        cout << "Todos arquivos binarios ja existem." << endl;
    }
    else if ((artBin.is_open()) && (!trackBin.is_open()))
    {
        cout << "O arquivo artist.bin existe, porem o arquivo tracks.bin nao. Sera feita sua construcao" << endl;
        leituraDeLinhasTrack(dirArq);
    }
    else if ((!artBin.is_open()) && (trackBin.is_open()))
    {
        cout << "O arquivo tracks.bin existe, porem o arquivo artists.bin nao. Sera feita sua construcao" << endl;
        leituraDeLinhasArtists(dirArq);
    }
    else
    {
        cout << "Nenhum arquivo binario existe. Ambos serao construidos" << endl;
        cout << "Iniciando leitura de artistas" << endl;
        leituraDeLinhasArtists(dirArq);
        cout << "Iniciando leitura de tracks" << endl;
        leituraDeLinhasTrack(dirArq);
    }
}

/**
 * @brief Modo de teste para os algoritmos de ordenação
 * 
 * @param pasta Diretório
 */
void teste(string pasta)
{

    string arqDat = pasta + "sort.dat";
    ofstream outFile;
    outFile.open(arqDat);

    outFile << "O primeiro parâmento de cada linha representa o tamanho total dos dados, e o segundo parâmetro o numero de conjuntos\n";
    outFile << "100, 1";
    outFile.close();

    cout << "MODULO DE TESTE INICIADO" << endl;

    metricaMergeSort(pasta, "teste.txt", 1);
    metricaHeapsort(pasta, "teste.txt");
    metricaQuickSort(pasta, "teste.txt");
    metricaInsertSort(pasta, "teste.txt", 1);
}

/**
 * @brief Função do menu usado na primeira parte do trabalho prático
 * 
 * @param pasta Pasta raiz de onde os CSVs serão lidos e os binários Armazenados 
 */
void menu1(string pasta)
{
    ifstream arq(pasta + "tracks.bin", ios_base ::in | ios_base ::app);
    ifstream arq2(pasta + "artists.bin", ios_base ::in | ios_base ::app);

    int tam = nRegistrosTracks(arq);
    int aux1, aux2, aux3;
    char resposta;

    //verificar qual opcao foi escolhida
    bool v = 1;
    while (v)
    {

        cout << "\nMENU 1" << endl;
        cout << "Como voce gostaria de visualizar os dados?\n"
             << endl;
        cout << "    C para console" << endl;
        cout << "    F para arquivo" << endl;
        cout << "    P para pular" << endl;
        cin >> resposta;

        if (resposta == 'C' || resposta == 'c')
        {

            for (int i = 0; i < 10; i++)
            {

                //tamanho do arquivo artista
                aux1 = numAleatorio(0, tam);
                aux2 = nRegistrosArtists(arq2);
                aux3 = numAleatorio(0, aux2);

                Tracks tracks;
                tracks = returnTrack(arq, aux1);
                Artists artists;

                //arquivo posição
                artists = returnArtist(arq2, aux3);
                cout << "Artista = [Id: " << artists.id << " Seguidores: " << artists.followers << " Genero: " << artists.genres << " Nome: " << artists.name << " Popularidade: " << artists.popularity
                     << "] \nMusica = [Id :" << tracks.id << " Nome: " << tracks.name << " Popularidade: " << tracks.popularity << " Duracao: " << tracks.duration_ms << " Explicito: " << tracks.is_explicit << " Data de Lancamento: " << tracks.release_date << " Dancabilidade: " << tracks.danceability << " Energia: " << tracks.energy << " Chave: " << tracks.key << " Volume: " << tracks.loudness << " Modo: " << tracks.mode << " Discurso: " << tracks.speechiness << " Acustico: " << tracks.acousticness << " Instrumental: " << tracks.instrumentalness << " Vivacidade: " << tracks.liveness << " Valencia: " << tracks.valence << " Tempo: " << tracks.tempo << " Assinatura de tempo: " << tracks.time_signature << "]\n";
                cout << "\n-------------------------------------" << endl;
            }

            arq.close();
            arq2.close();
            v = 0;
        }

        else if (resposta == 'F' || resposta == 'f')
        {

            ofstream outFile;
            outFile.open(pasta + "Texto.txt", ios::out);

            if (!outFile)
                return;

            for (int i = 0; i < 100; i++)
            {

                Tracks tracks;
                aux1 = numAleatorio(0, tam);
                tracks = returnTrack(arq, aux1);

                //tamanho do arquivo artista
                aux2 = nRegistrosArtists(arq2);
                aux3 = numAleatorio(0, aux2);

                Artists artists;
                //arquivo posição
                artists = returnArtist(arq2, aux3);

                outFile << "Artista = [Id: " << artists.id << " Seguidores: " << artists.followers << " Genero: " << artists.genres << " Nome: " << artists.name << " Popularidade: " << artists.popularity
                        << "]\nMusica = [Id :" << tracks.id << " Nome: " << tracks.name << " Popularidade: " << tracks.popularity << " Duracao: " << tracks.duration_ms << " Explicito: " << tracks.is_explicit << " Data de Lancamento: " << tracks.release_date << " Dancabilidade: " << tracks.danceability << " Energia: " << tracks.energy << " Chave: " << tracks.key << " Volume: " << tracks.loudness << " Modo: " << tracks.mode << " Discurso: " << tracks.speechiness << " Acustico: " << tracks.acousticness << " Instrumental: " << tracks.instrumentalness << " Vivacidade: " << tracks.liveness << " Valencia: " << tracks.valence << " Tempo: " << tracks.tempo << " Assinatura de tempo: " << tracks.time_signature << "]\n";
            }

            cout << "Escrita feita no arquivo texto.txt. Ele estara na mesma pasta que os arquivos de entrada." << endl;
            outFile.close();
            arq.close();
            arq2.close();
            v = 0;
        }

        else
        {

            if (resposta == 'p' || resposta == 'P')
            {
                arq.close();
                arq2.close();
                v = 0;
            }
            else
            {
                cout << "Opcao Invalida" << endl;
            }
        }
    }
}

/**
 * @brief Função do menu usado na segunda parte do trabalho prático
 * 
 * @param enderecoPasta Pasta raiz de onde os arquivos .bin e .dat e  serão lidos
 */
void menu2(string enderecoPasta)
{

    bool v = 1;
    bool h = 1;
    string entrada;
    string opcaoHash;
    while (v)
    {
        cout << "\nMENU 2" << endl;
        cout << "Escolha o que será executado\n"
             << endl;

        cout << "    1.  Ordenação" << endl;
        cout << "    2.  Hash" << endl;
        cout << "    3.  Módulo de Teste" << endl;
        cout << "    4.  Pular" << endl;

        cin >> entrada;

        if (entrada == "1")
        {

            metricaMergeSort(enderecoPasta, "saida.txt", 5);
            metricaHeapsort(enderecoPasta, "saida.txt");
            metricaQuickSort(enderecoPasta, "saida.txt");
            metricaInsertSort(enderecoPasta, "saida.txt", 5);
            cout << "DADOS SALVOS NO ARQUIVO 'saida.txt'" << endl;
            v = 0;
        }
        else if (entrada == "2")
        {
            createArquivoHashDat(enderecoPasta); //Criação do arquivo Hash caso esteja vazio

            ifstream arqSort(enderecoPasta + "hash.dat");
            string aux7;
            getline(arqSort, aux7);

            string n1, m1;
            int parN, parM;
            if (arqSort.good())
            {

                getline(arqSort, n1, ',');
                getline(arqSort, m1, '\n');

                //Conver o valor para inteiro, caso ocorra um erro o valor 1000 é atribuido para parN e 10 para o parM
                try
                {
                    parN = stoi(n1);
                    parM = stoi(m1);
                }
                catch (const exception &e)
                {
                    parN = 1000;
                    parM = 10;
                }
            }
            arqSort.close();

            //Abrindo o arquivo binário para manipulação
            ifstream arqHash(enderecoPasta + "tracks.bin", ios_base ::in | ios_base ::app);

            //TAMANHO DA HASH É UM NUMERO PRIMO
            int tamanhoHash = 1301;

            //Criando uma tabela Hash
            HashMap tabelaHash(tamanhoHash, enderecoPasta);

            //Criando o vetor de Tracks
            Tracks *musica = returnVetTracks(arqHash, parN);

            char *idArtistsSCE;

            //Estraindo apenas os IDs de Artistas da Música
            for (int i = 0; i < parN; i++)
            {

                idArtistsSCE = strtok(musica[i].id_artists, " ,'[]\"");

                while (idArtistsSCE != NULL)
                {

                    tabelaHash.inserir(idArtistsSCE);
                    idArtistsSCE = strtok(NULL, " ,'[]\"");
                }
            }

            arqHash.close();

            //Retornando os mais Frequentes
            tabelaHash.maisFrequentes(parM, 0);
            v = 0;
            delete[] musica;
        }
        else if (entrada == "3")
        {
            teste(enderecoPasta);

            ifstream arqHash(enderecoPasta + "tracks.bin", ios_base ::in | ios_base ::app);

            //TAMANHO DA HASH UM NUMERO
            int tamanhoHash = 547;

            HashMap tabelaHash(tamanhoHash, enderecoPasta);

            Tracks *musica = returnVetTracks(arqHash, 1000);

            char *idArtistsSCE;

            for (int i = 0; i < 1000; i++)
            {

                idArtistsSCE = strtok(musica[i].id_artists, " ,'[]\"");

                while (idArtistsSCE != NULL)
                {

                    tabelaHash.inserir(idArtistsSCE);
                    idArtistsSCE = strtok(NULL, " ,'[]\"");
                }
            }

            arqHash.close();
            tabelaHash.maisFrequentes(10, 1);
            cout << "DADOS SALVOS NO ARQUIVO 'teste.txt'" << endl;
            v = 0;
            delete[] musica;
        }
        else if (entrada == "4")
        {
            v = 0;
        }
        else
        {
            cout << "Opção Inválidad\n";
        }
    }
}

void menu3(string enderecoPasta)
{
    bool v = 1;
    bool h = 1;
    string entrada;
    string opcaoHash;
    while (v)
    {
        cout << "\nMENU 3" << endl;
        cout << "Escolha o que será executado\n"
             << endl;

        cout << "    1.  Árvore Vermelho-Preto" << endl;
        cout << "    2.  Árvore B" << endl;
        cout << "    3.  Sair" << endl;

        cin >> entrada;

        if (entrada == "1")
        {
            int opcao;
            ArvoreVermelhoPreto arv(enderecoPasta);
            bool a = 1;
            while (a)
            {
                cout << "Agora escolha um modo\n"
                     << endl;
                cout << "    1.  Modo Ánalise" << endl;
                cout << "    2.  Modo Teste" << endl;
                cin >> opcao;

                if (opcao == 1)
                {
                    arv.metricaArvoreVermelhoPreto(enderecoPasta, "saida.txt", 1);
                    cout << "DADOS SALVOS NO ARQUIVO 'saida.txt'" << endl;
                    a = 0;
                }
                else if (opcao == 2)
                {
                    arv.metricaArvoreVermelhoPreto(enderecoPasta, "saida.txt", 2);
                    a = 0;
                }
                else
                {
                    cout << "Opção Inválida\n";
                }
            }
            v = 0;
        }
        else if (entrada == "2")
        {
            int tamMinAB;
            cout<<"Escolha a ordem minima da arvore B: ";
            cin>>tamMinAB;
            if(tamMinAB < 2){
                cout << "TAMANHO INVÁLIDO" << endl;
                break;
            }
            bool a = 1;
            int opcao1;
            ArvoreB *ArvB20;
            ArvoreB *ArvB202;
            while (a)
            {
                cout << "Agora escolha um modo\n"
                     << endl;
                cout << "    1.  Modo Ánalise" << endl;
                cout << "    2.  Modo Teste" << endl;
                cin >> opcao1;
            if (opcao1 == 1)
                {
                    ArvoreB *ArvB20 = new ArvoreB(tamMinAB);
                    ArvB20->metricaArvoreB(enderecoPasta,1);
                    cout << "DADOS SALVOS NO ARQUIVO 'saida.txt'" << endl;
                    delete ArvB20;
                    a = 0;
                }
                else if (opcao1 == 2)
                {
                    ArvoreB *ArvB202 = new ArvoreB(tamMinAB);
                    ArvB202->metricaArvoreB(enderecoPasta,2);
                    a = 0;
                    delete ArvB202;
                }
                else
                {
                    cout << "Opção Inválida\n";
                }
            
            
            
            v = 0;
            }
        }

        else if (entrada == "3")
        {
            v = 0;
        }
        else
        {
            cout << "Opção Inválidad\n";
        }
    }
}

int main(int arqc, char *arqv[])
{

    if (!arqv[1])
    { //Verifica os argumentos
        cout << "Não foi passado o endereço da pasta contendo os CSVs" << endl;
        return -1;
    }

    else
    {
        if (strlen(arqv[1]) < 10)
        { //Verifica o tamanho do argumento
            cout << "Endereço muito curto, tente novamente" << endl;
            return -1;
        }
    }

    string dirArq(arqv[1]);
    bool resp = verificaArquivosCSV(dirArq);

    if (resp)
    {

        verificaArquivosBin(dirArq);   //! IMPORTANTE
        createArquivoSortDate(dirArq); //! IMPORTANTE
        //menu1(dirArq);
        //menu2(dirArq);
        menu3(dirArq);
        // char * idA = new char[25];
        // converteToIntId(idA,3,dirArq);
        // cout<< idA;
        

        
    }
    else
        cout << "CSV inexistente" << endl;
    return 0;
}
