/*Matheus Campanha Ferreira - RA: 174435
 * O algoritmo funciona da seguinte maneira, é utilizado o selectAleatorio, 
dado em sala, que sempre procura pela mediana do vetor dado, sendo assim, 
sempre é passado para ele (mediana - inicio + 1), sendo mediana a posicao do 
vetor atual em que está a mediana e inicio, o inicio do vetor, sendo assim o 
algoritmo procura pela mediana na parte do vetor que o foi entregue. Além 
disso, para ir encontrado os separadores binarios é utilizada uma funcao 
encontraBinarios que vai dividindo o vetor em 2, pois, após encontrar a mediana 
do vetor inteiro, todos os numeros menores que a mediana estão para a esquerda 
e maiores, para a direita, sendo assim, com certeza os outros separadores 
binarios estão nessas outras metades do vetor e na ordem correta, e além disso, 
o k, que é o numero de separadores binarios, eh passado como k/2, pois assim 
encontraremos o numero correto de separadores e dividiremos os vetores apenas 
no necessário. Assim, combinando as funcoes de encontraBinarios que separa os 
vetores corretamente e selectAleatorio que procura a mediana da parte do 
vetor passado, teremos os separadores binarios, que sao colocados já em ordem 
em um vetor, que depois será impresso para disponibilizar a saída.*/
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
int particione(vector<int> &vetor, int p, int r);
void printvet(vector<int> vetor);
int selectAleatorio(vector<int> &vetor,int p, int r, int i);
int particioneAleatorio(vector<int> &vetor, int p, int r);
void encontraBinarios(vector<int> &vetor,vector<int> &separadores, int inicio, 
int fim, int k);
void ordenaSepBin(vector<int> &vetor);
void insereSepBin(vector<int> &vetor, int separadorBinario);

int main(){
    vector<int> vet;
    vector<int> separadoresBinarios;
    int k,i;
    long int n;
    int valor;
    cin >> n;
    cin >> k;
    
    for(i = 0;i < n;i++){
        cin >> valor;
        vet.push_back(valor);
    }
    srand(0);
    encontraBinarios(vet,separadoresBinarios,0,vet.size()-1,k);
    printvet(separadoresBinarios);
    cout << "\n";
}
void insereSepBin(vector<int> &vetor, int separadorBinario){
    int j;
    if(vetor.size() == 0)
        vetor.push_back(separadorBinario);
    else{
        /*Procura a posicao certa*/
        int flag = 0;
        for(j = 0;j < vetor.size() && (!flag);j++){
            if(vetor[j] > separadorBinario)
                flag = 1;
        }
        /*Se encontrou um numero maior*/
        if(flag)
            j -= 1;
        /*Insere no vetor na posicao correta*/
        vetor.insert(vetor.begin() + j,separadorBinario);
    }
}

void encontraBinarios(vector<int> &vetor,vector<int> &separadores, int inicio, 
int fim, int k){
    int sepBin;
    int mediana = (fim+inicio)/2;
    if(k>0){
         /*mediana-inicio + 1 = i-ésimo*/
        sepBin = selectAleatorio(vetor,inicio,fim,mediana-inicio+1);
        insereSepBin(separadores, sepBin);
        encontraBinarios(vetor,separadores,inicio,mediana-1,k/2);
        encontraBinarios(vetor,separadores,mediana+1,fim,k/2);
    }
    
}
/*Funcoes ensinadas em sala de aula*/
int particione(vector<int>& vetor, int p, int r){
    int x = vetor[r];
    int i = p-1;
    int aux,j;
    for(j = p; j<= r-1;j++){
        if(vetor[j] <= x){
            i++;
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
        }
    }
    aux = vetor[i+1];
    vetor[i+1] = vetor[r];
    vetor[r] = aux;
    return i+1;
}

int selectAleatorio(vector<int> &vetor,int p, int r, int i){
    if(p==r)
        return vetor[p];
    int q = particioneAleatorio(vetor,p,r);
    int k = q - p + 1;
    if(i==k)
        return vetor[q];
    else if(i<k)
        return selectAleatorio(vetor,p,q-1,i);
    else
        return selectAleatorio(vetor,q+1,r,i-k);
}

int particioneAleatorio(vector<int> &vetor, int p, int r){
    int x, aux;
    x = rand() % (r-p+1) + p;
    aux = vetor[x];
    vetor[x] = vetor[r];
    vetor[r] = aux;
    return particione(vetor,p,r);
}

void printvet(vector<int> vetor){
    int i;
    for(i = 0;i<vetor.size();i++){
        cout << vetor[i] << " ";
    }
    cout < "\n";
    
}