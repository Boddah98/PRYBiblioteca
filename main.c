#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Libro.h"

int main() {
    int salir = FALSE;
	int opcion;
	char c;

	ListaLibros* listaLibros = crearListaLibros();

	printf("\n------------------------------------------------\n|Bienvenido al sistema de Gestion de Biblioteca|\n------------------------------------------------\n\n");
	while (salir != TRUE){
		printf("Por favor seleccione una opcion:\n   1) Gestion de catalogo\n   2) Gestion de usuarios\n   3) Historial de prestamos\n   4) Vencimiento de prestamos\n   5) Estadisticas\n   7) Salir\nIngrese un numero: ");
		if (scanf("%i", &opcion) != 1 ){
			while ((c = getchar()) != '\n' && c != EOF) { }
			printf("Error: Por favor ingrese unicamente numeros enteros.\n\n");
    	}else {
			switch (opcion)
			{
			case 1:
				printf("Selecciono la opcion 1.\n\n");
				break;

			case 2:
				printf("Selecciono la opcion 2.\n\n");
				break;

			case 3:
				printf("Selecciono la opcion 3.\n\n");
				break;
            
			case 4:
				printf("Selecciono la opcion 4.\n\n");
				break;

            case 5:
				printf("Selecciono la opcion 5.\n\n");
				break;

            case 6:
				printf("Selecciono la opcion 6.\n\n");
				break;

            case 7:
				printf("El programa ha sido finalizado correctamente.\n\n");
                salir = TRUE;
				break;
                	
			default:
				while ((c = getchar()) != '\n' && c != EOF) { }
				printf("Error: Por favor ingrese una opcion valida.\n\n");
				break;
			}
		}
	}
	return 0;
}
