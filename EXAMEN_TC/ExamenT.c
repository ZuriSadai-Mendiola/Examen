#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int existe(char* elemento, char* lenguaje[], int tamanio) {
   int i;
    for (i = 0; i < tamanio; i++) {
        if (strcmp(lenguaje[i],elemento)==0){
            return 1;
        }
    }
    return 0;
}

void unionLenguajes(char* lenguajeA[], int tamanioA, char *lenguajeU[], int tamanioU) {
    printf("Unión de A y U: {");
    int i;
    for ( i = 0; i < tamanioA; i++) {
        printf("%s", lenguajeA[i]);
        if (i < tamanioA - 1) {
            printf(", ");
        }
    }
    for (i = 0; i < tamanioU; i++) {
        if (!existe(lenguajeU[i], lenguajeA, tamanioA)) {
            printf(", %s", lenguajeU[i]);
        }
    }
    printf("}\n");
}

void complemento(char *lenguajeA[], int tamanioA, char* lenguajeU[], int tamanioU) {
    printf("Complemento de A : {");
    int primero = 1;
    int i;
    for (i = 0; i < tamanioU; i++) {
        if (!existe(lenguajeU[i], lenguajeA, tamanioA)) {
            if (!primero) {
                printf(", ");
            }
            printf("%s", lenguajeU[i]);
            primero = 0;
        }
    }
    printf(",...}\n");
}

void interseccion(char *lenguajeA[],int tamanioA, char *lenguajeU[],int tamanioU){
	char* inter[100];
	int interTam=0;  
	int i,j ;
    for(i=0;i<tamanioA;i++) {
        int encontrado = 0;
        for (j=0;j<tamanioU&&!encontrado;j++){
            if (strcmp(lenguajeA[i],lenguajeU[j])==0){
                encontrado=1;
            }
        }
        // Si se encontró en ambos conjuntos, verificar si ya está en `inter`
        if(encontrado){
            int existe=0;
            int k; 
            for(k=0;k< interTam&&!existe;k++){
                if(strcmp(inter[k],lenguajeA[i])==0) {
                    existe=1;
                }
            }
			if(!existe){
				inter[interTam] = malloc(strlen(lenguajeA[i]) + 1); 
				   strcpy(inter[interTam++],lenguajeA[i]);
			}
        }
    }
	printf("Interseccion de A y U: { ");
	for(i=0;i<interTam;i++){
		printf("%s", inter[i]);
		if(i<interTam-1){
			printf(", ");
		}
    }
    printf(" }\n");
}
	
void diferencia(char *lenguajeA[], int tamanioA, char *lenguajeU[], int tamanioU) {
    printf("Diferencia de A en U: {");
    int i, j;
    int primero = 1;  // Variable para controlar la impresión de la coma
    for (i=0; i < tamanioA; i++) {
        int estaEnLenguajeU = 0; 
        for (j = 0; j < tamanioU; j++) {
            if (strcmp(lenguajeA[i], lenguajeU[j]) == 0) {
                estaEnLenguajeU=1; 
            }
        }

        if (estaEnLenguajeU == 0) {
            if (!primero) {
                printf(", "); 
            }
            printf("%s", lenguajeA[i]);
            primero=0;  
        }	
    }	

    printf(" }\n");
}


int main(){
	int opcion,j;
    int tamanioA, tamanioU;
	
    printf("--------------------------------\n");
    printf("| Propiedades de los lenguajes |\n");
    printf("--------------------------------\n\n");
    
    do{
		
		printf("Ingrese el tamaño del lenguaje A: ");
		scanf("%d", &tamanioA);
		char *lenguajeA[tamanioA] ;

		printf("Ingrese los elementos del lenguaje A (separados por espacios):\n");
		int i;
		for (i = 0; i < tamanioA; i++) {
			lenguajeA[i] = (char*)malloc(100 * sizeof(char));
			scanf("%s", lenguajeA[i]); 
		}

		printf("Ingrese el tamaño del lenguaje U: ");
		scanf("%d", &tamanioU);
		char *lenguajeU[tamanioU];

		printf("Ingrese los elementos del lenguaje U (separados por espacios):\n");
		for ( i = 0; i < tamanioU; i++) {
			lenguajeU[i] = (char*)malloc(100 * sizeof(char));
			scanf(" %s", lenguajeU[i]);
		}
		
		printf("\nLos lenguajes introducidos son:\n");
		printf("A={");
		for(i=0;i<tamanioA;i++){
			printf("%s ",lenguajeA[i]);
			 if(i<tamanioA-1){
				printf(", ");
			}
		}
		printf("}\n");

		printf("U={");
		for(j=0;j<tamanioU;j++){
			printf("%s ",lenguajeU[j]);
			 if(j<tamanioU-1){
				printf(", ");
			}
		}
		printf("}\n");
		
		do{	
			printf("\nSelecciona la propiedad que deseas usar:\n\n");
			printf("-------------------------\n");
			printf("| Unión ---> 1          |\n");
			printf("| Intersección ---> 2   |\n");
			printf("| Complemento ---> 3     |\n");
			printf("| Diferencia ---> 4      |\n");	
			printf("-------------------------\n\n");
			
			printf("Ingrese su elección | 1 | 2 | 3 | 4 |: ");
			scanf("%d", &opcion);
		
			switch(opcion){
				case 1:
				unionLenguajes(lenguajeA, tamanioA, lenguajeU, tamanioU);
						break;
				case 2:
			    interseccion(lenguajeA, tamanioA, lenguajeU, tamanioU);	
					break;
				case 3:
				complemento(lenguajeA, tamanioA, lenguajeU, tamanioU);
					break;
				case 4:
				diferencia(lenguajeA, tamanioA, lenguajeU, tamanioU);
					break;
				default: printf("Error, esta opción no se encuentra en el menú de propiedades\n");
				}
				printf("\n¿Te gustaría probar otra propiedad? Si->1 No->2\n");
				scanf("%d", &opcion);
			
			}while(opcion!=2);
			printf("\n¿Desearías ingresar nuevos lenguajes? Si->1 No->2\n");
			scanf("%d", &opcion);

    }while(opcion!=2);

    return 0;
}
