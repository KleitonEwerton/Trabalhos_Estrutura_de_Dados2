#include <iostream>
#include <iomanip>
using namespace std;

class Registro //HashNode
{
private:
    char *idA;  //Char do ID
public:

    Registro *proximo;  //Ponteiro para o proxímo registro
    int quantidade;     //Quantidade que já foi armazenada com esse mesmo ID
    
    /**
     * @brief Construtor padrão
     * 
     */
    Registro(){
        this->quantidade = 1;
        this->proximo = nullptr;
    }
    
    /**
     * @brief Construtor
     * 
     * @param idA id do artista
     */
    Registro(char *idA){
        this->idA = idA;
        this->proximo = nullptr;
        this->quantidade = 1;
        
        
    }
    /**
     * @brief Retorna o ID
     * 
     * @return id do artista 
     */
    char *getIdA()
    {   
        return idA;
    }
    /**
     * @brief Atualiza o ID
     * 
     * @param idA id do artista 
     */
    void setId(char *idA)
    {   
        this->idA = idA;
    }
};