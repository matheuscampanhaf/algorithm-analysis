#include <stdio.h>
unsigned long long int num_inversoes = 0;

void printArray(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void intercalaEconta(int vet[], int inicio, int fim, int media){
    int num_vet1, num_vet2;
    /*Numero de elementos que vai em cada novo vetor*/
    num_vet1 = media - inicio + 1;
    num_vet2 = fim - media;


    int vet1[num_vet1];
    int vet2[num_vet2];

    /*Passando os elementos para os novos vetores*/
    int i = 0;
    while(i < num_vet1){
        vet1[i] = vet[inicio + i];
        i++;
    }
    int j = 0;
    while(j < num_vet2){
        vet2[j] = vet[media + 1 + j];
        j++;
    }


    int k = inicio;
    i = 0;
    j = 0;
   

    while((i < num_vet1) && (j < num_vet2)){
        if(vet1[i] <= vet2[j]){
            vet[k++] = vet1[i++];
        }
        else{
            num_inversoes += num_vet1 - i;
            vet[k++] = vet2[j++];
        }

        
    }

    while(i < num_vet1){
        vet[k++] = vet1[i++];
    }

    while(j < num_vet2){
        vet[k++] = vet2[j++];
    }
}

/* Funcao recursiva numInversoes que ordena o vetor e conta o numero de inversoes do mesmo*/
void numInversoes(int vet[], int inicio1, int fim1){
    int media1;
    /*Se fim é maior que o inicio, ainda da pra dividir, e divide até fim
    ser igual ao inicio*/
    if(fim1 > inicio1){
        media1 = inicio1 + (fim1 - inicio1)/2;
    
    /*Chama recursivamente à fim de implementar a Divisão e conquista*/
    numInversoes(vet, inicio1, media1);
    numInversoes(vet, media1+1,fim1);
    intercalaEconta(vet, inicio1, fim1, media1);
    }
}



int main(void){
    int num;
    /*Scaneando os parâmetros*/
    scanf("%d", &num);

    int vet[num];

    for(int i = 0;i < num;i++){
        scanf("%d", &vet[i]);
    }
    /*Chama a função recursiva pela primeira vez*/
    numInversoes(vet, 0, num - 1);
    printf("%llu\n", num_inversoes);
}
