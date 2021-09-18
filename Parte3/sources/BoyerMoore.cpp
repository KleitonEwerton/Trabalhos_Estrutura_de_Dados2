#include <iostream>
#include "BoyerMoore.h"
#include <string.h>
#include <fstream>
#include <chrono>

long long microsecondsBM;
long long comparacoesBM;


void casamentoCompleto(int vetorTroca[], int vertorBorda[], string padrao) {
   int n = padrao.size();       //tamanho total do padrão
   int i = n;
   int j = n+1;
   vertorBorda[i] = j;

   comparacoesBM+=1;
   while(i > 0) {
      // busca para i-1 e j-1 são itens diferentes
      comparacoesBM+=1;
      while(j <= n && padrao[i-1] != padrao[j-1] ) {
         comparacoesBM+=1;
         if(vetorTroca[j] == 0)
            vetorTroca[j] = j-i; 
         j = vertorBorda[j];       
      }
      i--;
      j--;
      vertorBorda[i] = j;
   }  
}

void casamentoParcial(int vetorTroca[], int vertorBorda[], string padrao) {
   int n = padrao.size();    //tamanho total do padrão
   int j;
   j = vertorBorda[0];
   comparacoesBM+=1;
   for(int i = 0; i<n; i++) {
      comparacoesBM+=2; //1 comparação pelo for e outra pelo if abaixo;
      if(vetorTroca[i] == 0)
         vetorTroca[i] = j;       //quando a troca == 0 troca o valor para o do array de borda.
         comparacoesBM+=1;
         if(i == j)
            j = vertorBorda[j];
   }
}

void boyermoore(string sequenciaTotal, string padrao, int array[], int *index, ofstream &outFile) {
   cout << "\nINICIANDO O ALGORITOM DE BOYER-MOORE COM O PADRÃO "<< padrao << endl;
   outFile<< "\nINICIANDO O ALGORITOM DE BOYER-MOORE COM O PADRÃO "<< padrao << endl;
      
   int tamPadrao = padrao.length();
               
   int tamSequenciaTotal = sequenciaTotal.size();
          
   comparacoesBM = 0;
   if(tamPadrao > tamSequenciaTotal){
      outFile << "NÃO FOI ENCONTRADO ESSE PADRÃO NO TEXTO, POIS O PADRÃO É MAIOR QUE O TEXTO" << endl;
      return;
   }

   auto inicio = chrono::high_resolution_clock::now(); //INICIO DA CONTAGEM DO TEMPO DE EXECUÇÃO

   int vertorBorda[tamPadrao+1];
   int vetorTroca[tamPadrao + 1];

   for(int i = 0; i<=tamPadrao; i++) {
      vetorTroca[i] = 0;     //todas posicoes do array de troca recebem 0 para iniciar a marcação de posição
   }

   casamentoCompleto(vetorTroca, vertorBorda, padrao);
   casamentoParcial(vetorTroca, vertorBorda, padrao);
   int shift = 0;
   
   comparacoesBM+=1;  //INDEPENDENTE DE SATISFAZER OU NÃO HÁ COMPARAÇÃO
   while(shift <= (tamSequenciaTotal - tamPadrao)) {
      int j = tamPadrao - 1;
      comparacoesBM+=1; 
      while(j >= 0 && padrao[j] == sequenciaTotal[shift+j]) {
         j--;
         comparacoesBM+=1;
      }

      comparacoesBM+=1;
      if(j < 0) {
         (*index)++;
         array[(*index)] = shift;
         shift += vetorTroca[0];
      }else {
          shift += vetorTroca[j+1];
      }
   }

   auto final = chrono::high_resolution_clock::now() - inicio;

   microsecondsBM = chrono::duration_cast<chrono::microseconds>(final).count();

   if(*index == -1){
      outFile << "O padrão não foi encontrado em lugar algum do texto" << endl;
      outFile << "O tempo de busca foi: " << microsecondsBM / 1000000.0 << "SEGUNDOS  e o número de comparações foram de: " << comparacoesBM << endl;
   }
   else{
      for(int i = 0; i <= *index; i++) {
         outFile <<"O padrao foi encontrado da posição: " << array[i] << "até a posição "<< array[i]+tamPadrao   << endl;
      }
      outFile << "O padrão foi encontrado em "<< *index << " locais" << endl;
      outFile << "O tempo de busca foi: " << microsecondsBM / 1000000.0 << "SEGUNDOS  e o número de comparações foram de: " << comparacoesBM << endl;
   }
}