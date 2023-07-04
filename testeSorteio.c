#include <stdlib.h>
#include <math.h>
#include <stdio.h>  

double random_exp(double mean){
    double sorteado = rand() / (RAND_MAX + 1.0);
    return -log(1-sorteado) / mean;
    
}

int main(){
    const int n_pct = 1000;
    const double pct_pequeno = 0.4, pct_medio = 0.5, pct_grande = 0.1;
    int tamanho_pct[n_pct];
    for(int i=0; i < n_pct; i++){
        double sorteado = rand()/(RAND_MAX +1.0);
        if(sorteado < pct_grande){
            tamanho_pct[i] = 1550;
        }
        else if(sorteado < pct_grande + pct_pequeno){
            tamanho_pct[i] = 40;
        }
        else(sorteado <  pct_grande + pct_pequeno + pct_medio);
        {
            tamanho_pct[i] = 550;
        }
    }
    return 0;
}