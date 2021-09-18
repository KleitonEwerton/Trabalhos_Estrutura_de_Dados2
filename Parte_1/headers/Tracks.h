#ifndef BB5A53D7_8961_48D1_A8F7_22A65CABCA3E
#define BB5A53D7_8961_48D1_A8F7_22A65CABCA3E
using namespace std;



struct Tracks{
    
    char id[50];
    char name[2000];
    int popularity;
    int duration_ms;
    bool is_explicit; 
    char artists[2000]; 
    char id_artists[2000];
    char release_date[20];
    float danceability;
    float energy;
    int key;
    float loudness;
    bool mode;
    float speechiness;
    float acousticness;
    float instrumentalness;
    float liveness;
    float valence;
    float tempo;
    int time_signature;

};

void salvarTrackBin(ofstream &arq, Tracks track);

void createTrack(ofstream &arq, char id[], char name[], int popularity, int duration_ms, bool is_explicit,char artists[],char id_artists[],
                    char release_date[],float danceability,float energy,int key,float loudness,bool mode,float speechiness,float acousticness,
                    float instrumentalness,float liveness,float valence,float tempo,int time_signature);

Tracks returnTrack(ifstream &arq,int n);

int nRegistrosTracks(ifstream &arq);

Tracks *returnVetTracks(ifstream &arq, int nQuantidade);


#endif /* BB5A53D7_8961_48D1_A8F7_22A65CABCA3E */
