#include "Artists.h"
#include "Tracks.h"

using namespace std;

void heapsortFollowers(Artists* vet, int n);
void build_max_heap(Artists* vet, int n);
void heapify(Artists* vet, int i, int n);
void metricaHeapsort(string heap, string nomeArq);