//  main.c
//  Reducao de Gauss
//  Created by Carolina Costa on 12/05/20.
//  Copyright © 2020 Carolina Costa. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int qtd_incognitas;
    double ** matriz;
    double * resultados;
    int linha, coluna;

	printf("Digite a quantidade de incognitas:\n");
	scanf("%d", &qtd_incognitas);
 
 	//Instancia Matriz e Arrays
    matriz = malloc(qtd_incognitas * sizeof(int));
    for (linha = 0; linha < qtd_incognitas; linha++) {
        matriz[linha] = malloc(qtd_incognitas * sizeof(int));
    }
	resultados = (double *) malloc(qtd_incognitas * sizeof(int));
        
    //Le valores das equacoes (Matriz)
    printf("Digite a matriz para resolucao:\n");
    for (linha = 0; linha < qtd_incognitas; linha++) {
        for (coluna = 0; coluna< qtd_incognitas + 1; coluna++) {
            int entrada;
            scanf("%d", &entrada);
			if (coluna != qtd_incognitas) {
            	matriz[linha][coluna] = entrada;
			} else {
            	resultados[linha] = entrada;
            }
        }
    }
    
    
    printf("Matriz recebida:\n");
	imprimirMatriz(matriz, resultados, qtd_incognitas);
	printf("Iniciando Resolucao...\n");
		
    //Eliminacao Gaussiana com pivotamento
    int ref_pivo;
    for (ref_pivo = 0; ref_pivo < qtd_incognitas; ref_pivo ++) {
    	printf("Eliminando %da coluna\n", ref_pivo + 1);
        double pivo = matriz[ref_pivo][ref_pivo];
        int indice_pivo = ref_pivo;
        
        //Identifica qual melhor linha, dentre as proximas, qual é para fazer eliminacao
        int proxima_linha;
        if (ref_pivo + 1 < qtd_incognitas) {
			for(proxima_linha = ref_pivo + 1 ; proxima_linha < qtd_incognitas; proxima_linha++) {
	            if(pivo == 0 || (matriz[proxima_linha][ref_pivo] == 1 && pivo != 1)){
	                pivo = matriz[proxima_linha][ref_pivo];
	                indice_pivo = proxima_linha;
	            }
        	}
		}
		
		//Verifica matriz singular
		if (pivo == 0) {
			printf("A matriz e singular\n");
            return 0;
		}
	   
	   	//Se outra linha foi escolhida como pivo
	    if (indice_pivo != ref_pivo) {
	    	printf("Linha %d trocada com linha %d\n", ref_pivo + 1, indice_pivo + 1);
	    	//Inverte linha pivo escolhido com linha corrente no for ref_pivo
            for(coluna = 0; coluna < qtd_incognitas; coluna++){
                double aux = matriz[ref_pivo][coluna];
                matriz[ref_pivo][coluna] = matriz[indice_pivo][coluna];
                matriz[indice_pivo][coluna] = aux;
            }
            //Inverte tbm o resultado da linha
            double aux = resultados[ref_pivo];
            resultados[ref_pivo] = resultados[indice_pivo];
            resultados[indice_pivo] = aux;
        }
        
        //Simplificaçao da linha do pivo
        if (matriz[ref_pivo][ref_pivo] != 1) {
        	for(coluna = 0; coluna < qtd_incognitas; coluna++) {
            	matriz[ref_pivo][coluna] = matriz[ref_pivo][coluna] / pivo;
            }
            resultados[ref_pivo] = resultados[ref_pivo] / pivo;
		}
        
       
        
       	//Eliminacao de fato
        for (linha = 0; linha < qtd_incognitas; linha++) {
        	if (linha == ref_pivo) {
        		continue;
			}
	        double razao = matriz[linha][ref_pivo];
	        for(coluna = 0 ; coluna < qtd_incognitas; coluna++) {
            	matriz[linha][coluna] = matriz[linha][coluna] - razao * matriz[ref_pivo][coluna];
            }
            resultados[linha] = resultados[linha] - razao * resultados[ref_pivo];
        }
        
        imprimirMatriz(matriz, resultados, qtd_incognitas);
        
    }
	
	//Exibicao dos resultados
    for(linha = 0; linha < qtd_incognitas; linha++){
        printf("%.1f\n", resultados[linha]);
    }
    
    //Liberando memoria alocada
    for(linha = 0; linha < qtd_incognitas; linha++){
        free(matriz[linha]);
    }
    free(resultados);
    free(matriz);
    
    printf("\n\n*** Tenha um bom dia =) ***\n\n");
}

void imprimirMatriz(double ** m, double * r, int length) {
	int l, c;
	for (l = 0; l < length; l++) {
		printf(" | "); 
		for (c = 0; c < length; c++) {
			printf(" %.1f ", m[l][c]);
		}
		printf(" | ");
		printf(" %.1f \n", r[l]);
	}
	printf("\n \n", r[l]);
}

