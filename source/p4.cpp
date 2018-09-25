#include <vector>
#include <iostream>
#include <stdio.h>
using namespace std;
void print_vetor(vector<int> vetor);
int main (void){
  int h;
  int n;
  vector<long long int> vet_frete;
  vector<long long int> vet_demanda;
  int in_aux, i, j, k;
  vector<long long int> vet_menorpreco;
  
  cin >> h;
  cin >> n;
  
  for(i = 0;i < n;i++){
    cin >> in_aux;
    vet_frete.push_back(in_aux);
    //Inicializa o vetor de menores preços
    in_aux = -1;
    vet_menorpreco.push_back(in_aux);
  }
  
  for(i = 0;i < n;i++){
    cin >> in_aux;
    vet_demanda.push_back(in_aux);
  }
  long long int novoestoque;
  long long int estoque;
  long long int menorpreco, preco;
  long long int dias;
  vet_menorpreco[n-1] = vet_frete[n-1];
  for(i = n - 2; i >= 0;i--){
      menorpreco = vet_frete[i] + vet_menorpreco[i+1];
      estoque = 0;
      dias = 1;
      for(j = i+1;j <= n-1;j++){
	novoestoque = dias*h*vet_demanda[j] + estoque;
	if(j != n-1)
	  preco = vet_frete[i] + novoestoque + vet_menorpreco[j+1];
	else
	  preco = vet_frete[i] + novoestoque;
	estoque = novoestoque;
	if(preco < menorpreco)
	  menorpreco = preco;
	dias++;
      }
      vet_menorpreco[i] = menorpreco;
  
  }
  cout << vet_menorpreco[0] << "\n";
  
  
  
//   print_vetor(vet_frete);
//   print_vetor(vet_demanda);
//   print_vetor(vet_menorpreco);
}

void print_vetor(vector<int> vetor){
  for(int k = 0;k < vetor.size();k++)
    cout << vetor[k] << " ";
  cout << "\n";
}