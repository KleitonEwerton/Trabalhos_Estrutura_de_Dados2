#ifndef C202A63F_EF6B_4F3E_984A_1E22217193F8
#define C202A63F_EF6B_4F3E_984A_1E22217193F8
using namespace std;

#include <fstream>

struct Artists{

    char id[25];
    float followers;
    char genres[200]; 
    char name[400];
    int popularity;

};

void salvarArtistBin(ofstream &arq, Artists artist);

void createArtist(ofstream &arq, char id[], float followers, char genres[], char name[], int popularity);

Artists returnArtist(ifstream &arq, int n);

int nRegistrosArtists(ifstream &arq);

Artists *returnVetArtists(ifstream &arq, int nQuantidade);

Artists buscaArtist(ifstream &arq,string idArtist);

int localizarArtist(ifstream &arq,string idArtist);


#endif /* C202A63F_EF6B_4F3E_984A_1E22217193F8 */
