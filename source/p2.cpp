/*Aluno: Matheus Campanha Ferreira - RA: 174435*/
/* O problema foi resolvido da seguinte maneira: é criado um heap de arvores 
mais velhas e um heap de arvores que representam a idade maxima de no minimo 
60% das arvores da especie. Sendo assim, o heap de arvores velhas eh utilizado 
para ver a arvore mais velha de todas as especies e o heap de 60% é utilizado 
para comparar com essa maior idade. Já que estamos utilizando a propriedade de 
max heap, todo mundo abaixo do no raiz tem valor menor ou igual que o da raiz, 
sendo assim, ao comparar o primeiro no do heap60% com o primeiro no do 
heapvelhas saberemos se temos arvores velhas ou nao, pois, se o primeiro nó do 
heap60% nao for maior que 60% da maior arvore, os seus filhos nao serao, pois 
obedecem à propriedade do max heap. Além disso, é necessário verificar se a 
arvore mais velha do heapvelhas está atualizada, pois ela pode ter sido cortada 
durante o processo*/
#include <vector>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>

using namespace std;

struct arvore{
  int especie;
  int idade;
  bool operator <(const arvore &d)const{
    return idade < d.idade;
  }
};
struct especie{
  vector<arvore> arvores;
  int arvore_velha;
};


int main (){
  int num_especies, num_arvores;
  int i, j;
  int idade;
  int num_cortes = 0;
  int todas_especies_jovens = 0;

  cin >> num_especies;

  vector<especie> vetor_especies;
  vector<arvore> heapvelhas;
  vector<arvore> heap60;
  vector<int> especies_cortadas;

  /*Scaneia as especies e suas respectivas arvores*/
  for(i = 0;i < num_especies;i++){
    especie aux;
    vetor_especies.push_back(aux);
    cin >> num_arvores;
    for(j = 0;j < num_arvores;j++){
      cin >> idade;
      arvore new_arvore;
      new_arvore.especie = i;
      new_arvore.idade = idade;
      vetor_especies[i].arvores.push_back(new_arvore);
//    Coloca no vetor de heap60
      if(j == ceil(0.6*num_arvores)-1){
	heap60.push_back(new_arvore);
      }
//    Coloca no vetor de heapvelhas
      if(j == num_arvores - 1){
          vetor_especies[i].arvore_velha = idade;
	  heapvelhas.push_back(new_arvore);
      }
    }
  }
// faz o heap dos vetoressss
  make_heap(heapvelhas.begin() , heapvelhas.end());
  make_heap(heap60.begin(), heap60.end());
 
  int flag_atualizacao;
  while(!todas_especies_jovens){
    /*verifica se a arvore mais velha está atualizada*/
    flag_atualizacao = 0;
    int especie_aux;
    while(!flag_atualizacao){
      /*Pega a especie da arvore mais velha do heap*/
      especie_aux = heapvelhas.front().especie;
      /*Verifica se a idade da arvore mais velha da especie é a mesma ainda*/
      if(heapvelhas.front().idade != vetor_especies[especie_aux].arvore_velha){
	/*Se nao for, tira do heap e insere no heap a nova arvore mais velha da especie*/
	pop_heap(heapvelhas.begin() , heapvelhas.end());
	heapvelhas.pop_back();
	heapvelhas.push_back(vetor_especies[especie_aux].arvores.back());
	push_heap(heapvelhas.begin() , heapvelhas.end());
      }
      /*Se for, setamos a flag de atualizacao*/
      else
	flag_atualizacao = 1;
    }

    /*Agora que estamos com o heapvelhas atualizado, verificamos o heap60 e checamos os cortes*/
    int flag_cortes = 0;
    while(heap60.front().idade > 0.6*heapvelhas.front().idade && heap60.size() 
!= 0){
            // 	Coloca a especie na lista das especies que devem ser cortadas
            especies_cortadas.push_back(heap60.front().especie);
            pop_heap(heap60.begin(), heap60.end());
            heap60.pop_back();
            flag_cortes = 1;
      }
//    Se nao foi feito nenhum corte, quer dizer que são todas jovens
      if(!flag_cortes){
        todas_especies_jovens = 1;
      }
    
    /*Soma no numero de cortes o tamanho do vetor de especies cortadas*/
    num_cortes += especies_cortadas.size();

    /*Agora, precisamos ir em cada especie que foi cortada cortando a
     * arvore mais velha e mudar o seu campo arvore mais velha*/
    for(i = 0;i < especies_cortadas.size();i++){
      vetor_especies[especies_cortadas[i]].arvores.pop_back();
      vetor_especies[especies_cortadas[i]].arvore_velha = vetor_especies[especies_cortadas[i]].arvores.back().idade;
      /*Agora que fizemos os cortes, precisamos colocar as arvores que estao
       * com o indice de 60% no heap*/
      heap60.push_back(vetor_especies[especies_cortadas[i]].arvores[ceil(0.6*vetor_especies[especies_cortadas[i]].arvores.size()) - 1]);
      push_heap(heap60.begin(), heap60.end());
    }
   
    /*Limpa o vetor de especies cortadas para a proxima iteracao*/
    especies_cortadas.clear();
  }

  cout << num_cortes << "\n";


  return 0;
}
