class NoArvoreVermelhoPreto
{
  public:
    NoArvoreVermelhoPreto()               { };
    ~NoArvoreVermelhoPreto()              { };
    
    void setLocal(int l) { local = l; };
    void setInfo(char *val) { info = val; };
    void setCor(bool c) {cor = c;};
    void setEsq(NoArvoreVermelhoPreto *p) { esq = p; };
    void setDir(NoArvoreVermelhoPreto *p) { dir = p; };
    void setPai(NoArvoreVermelhoPreto *p) { pai = p; };
    
  
    NoArvoreVermelhoPreto* getEsq()       { return esq; };
    NoArvoreVermelhoPreto* getPai()       { return pai; };
    NoArvoreVermelhoPreto* getDir()       { return dir; };

    char *getInfo()         { return info; };
    bool getCor()         { return cor; };
    int getLocal()         { return local; };
      
  private:

    //atributos
    char *info;   // informação do No (char)
    bool cor;   //cor do No (bool)
    int local;  //localizacao do No no arquivo binario
    NoArvoreVermelhoPreto* pai; // ponteiro para o pai
    NoArvoreVermelhoPreto* dir; // ponteiro para o filho a direita
    NoArvoreVermelhoPreto* esq; // ponteiro para o filho a esquerda
};
