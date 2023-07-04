#include <stdio.h>
int main(){
    char esp, loc;
    float rem;
    printf("Randstad- area do candidato");

    printf("Digite a especialidade do candidato: ");
    scanf("%c", &esp);

    printf("Digite a localizacao do candidato: ");
    scanf("%c", &loc);

    printf("Digite o salario do candidato: ");
    scanf("%f", &rem);

    printf("exibindo dados do candidato: %c %c %f", esp, loc, rem);

}