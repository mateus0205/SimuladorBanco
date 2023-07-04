#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> 

typedef struct little_
{
    unsigned long int no_eventos;
    double tempo_anterior;
    double soma_areas;
} little;

double aleatorio()
{
    double u = rand() / ((double)RAND_MAX + 1);
   
    u = 1.0 - u;
    return (u);
}

double minimo(double num1, double num2)
{
    if (num1 < num2)
    {
        return num1;
    }
    return num2;
}

double maximo(double num1, double num2)
{
    if (num1 > num2)
    {
        return num1;
    }
    return num2;
}
void inicia_little(little *l)
{
    l->no_eventos = 0;
    l->tempo_anterior = 0.0;
    l->soma_areas = 0.0;
}

int main()
{
    double tempo_simulacao = 36000.0;
    double tempo_decorrido = 0.0;
    double intervalo_medio_chegada = 0.2;
    double tempo_medio_servico;
    double chegada;
    double servico;
    double soma_tempo_servico = 0.0;
    unsigned long int fila = 0; // usigned long = para usar todo espaço de memoria, sendo somente numeros positivos
    unsigned int max_fila = 0;
    double tempo_controle = 0.0;
    /*
    little
    */
    little e_n;
    little e_w_chegada;
    little e_w_saida;

    inicia_little(&e_n);
    inicia_little(&e_w_chegada);
    inicia_little(&e_w_saida);

    /*
    little
    */

    srand(10000);
    
    
    
    
    
    printf("Informe o tempo de simulacao (segundos): ");
    scanf("%lf", &tempo_simulacao);
    printf("Informe o intervalo entre chegadas (segundos): ");
    scanf("%lf", &intervalo_medio_chegada);
    printf("Informe o tempo medio de servicos (segundos): ");
    scanf("%lf", &tempo_medio_servico);

    // gerando o tempo de chegada da primeira requisicao
    chegada = (-1.0 / (1.0 / intervalo_medio_chegada)) * log(aleatorio());
    while (tempo_decorrido <= tempo_simulacao)
    {
        if (tempo_decorrido > tempo_controle)
        {
            double soma_areas_chegada = e_w_chegada.soma_areas + (tempo_controle - e_w_chegada.tempo_anterior) * e_w_chegada.no_eventos;
            double soma_areas_saida = e_w_saida.soma_areas + (tempo_controle - e_w_saida.tempo_anterior) * e_w_saida.no_eventos;
            double e_n_final = e_n.soma_areas / (tempo_controle);
            double e_w_final = (soma_areas_chegada - soma_areas_saida) / (double)e_w_chegada.no_eventos;
            double lambda = e_w_chegada.no_eventos / (tempo_controle);

            printf("E_N = %lf\n", e_n_final);
            printf("E_W = %lf\n", e_w_final);
            printf("Erro_Little = %lf\n", e_n_final - lambda * e_w_final);
            printf("Ocupacao = %lf\n", soma_tempo_servico / maximo(tempo_controle, servico));
            tempo_controle += 100.00;
        }
        tempo_decorrido = !fila ? chegada : minimo(chegada, servico); 
        if (tempo_decorrido == chegada)
        {
            // printf("Chegada em %lF.\n", tempo_decorrido);
            if (!fila)
            {
                servico = tempo_decorrido + (-1.0 / (1.0 / tempo_medio_servico)) * log(aleatorio());
                soma_tempo_servico += servico - tempo_decorrido;
            }
            fila++;
            max_fila = fila > max_fila ? fila : max_fila;
            chegada = tempo_decorrido + (-1.0 / (1.0 / intervalo_medio_chegada)) * log(aleatorio());

            e_n.soma_areas += (tempo_decorrido - e_n.tempo_anterior) * e_n.no_eventos;
            e_n.tempo_anterior = tempo_decorrido;
            e_n.no_eventos++;

            e_w_chegada.soma_areas += (tempo_decorrido - e_w_chegada.tempo_anterior) * e_w_chegada.no_eventos;
            e_w_chegada.tempo_anterior = tempo_decorrido;
            e_w_chegada.no_eventos++;

            
        }
        else
        {
            
            fila--;

            if (fila)
            {
                servico = tempo_decorrido + (-1.0 / (1.0 / tempo_medio_servico)) * log(aleatorio());
                soma_tempo_servico += servico - tempo_decorrido;
            }
           
            e_n.soma_areas += (tempo_decorrido - e_n.tempo_anterior) * e_n.no_eventos;
            e_n.tempo_anterior = tempo_decorrido;
            e_n.no_eventos--;

            e_w_saida.soma_areas += (tempo_decorrido - e_w_saida.tempo_anterior) * e_w_saida.no_eventos;
            e_w_saida.tempo_anterior = tempo_decorrido;
            e_w_saida.no_eventos++;
        }
    }
    e_n.soma_areas += (tempo_decorrido - e_n.tempo_anterior) * e_n.no_eventos;

    e_w_chegada.soma_areas += (tempo_decorrido - e_w_chegada.tempo_anterior) * e_w_chegada.no_eventos;

    e_w_saida.soma_areas += (tempo_decorrido - e_w_saida.tempo_anterior) * e_w_saida.no_eventos;

    double e_n_final = e_n.soma_areas / tempo_decorrido;
    e_w_saida.soma_areas += (tempo_decorrido - e_w_saida.tempo_anterior) * e_w_saida.no_eventos;
    double e_w_final = (e_w_chegada.soma_areas - e_w_saida.soma_areas) / e_w_chegada.no_eventos;
    double lambda = e_w_chegada.no_eventos / tempo_decorrido;

    /* 
    printf("\nDados flavio: ");
    printf("E[N] = %lf\n", e_n_final);
    printf("E[W] = %lf\n", e_w_final);
    printf("Lambda = %lf\n", lambda);
    printf("Little: %.20lf\n", e_n_final - lambda * e_w_final);
    printf("Ocupacao: %lf\n", soma_tempo_servico / maximo(tempo_decorrido, servico));
    printf("Max_fila: %d\n", max_fila);
    */
    return 0;
}
