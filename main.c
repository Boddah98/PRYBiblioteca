#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Libro.h"
#include "Usuario.h"

int libroExiste(char* nombreLibro){
	return FALSE;
}

// Función para verificar si una cadena contiene solo dígitos
int esNumero(const char *cadena) {
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (!isdigit(cadena[i])) {
            return FALSE;
        }
    }
    return TRUE;
}

void gestionCatalogo() {
	int salirNombre = TRUE;
	int salirCantidad = TRUE;

	char nombre[50];
	char autor[50];
	char anno[50];
	char genero[50];
	char resumen[200];
	char cantidad[50];

	printf("\n-----------------------\n| Gestion de catalogo |\n-----------------------\nPara poder registrar un libro nuevo en el sistema por favor ingrese los siguientes datos.\n\n");
	while(salirNombre){
		printf("Ingrese el nombre del libro: ");
		scanf(" %[^\t\n]s", &nombre);
		if(libroExiste(nombre)){
			printf("Error: Ese libro ya fue registrado en el sistema. Por favor ingrese el nombre de un libro nuevo.");
		}else {
			salirNombre = FALSE;
		}
	}

	printf("Ingrese el nombre del autor del libro: ");
	scanf(" %[^\t\n]s", &autor);
	printf("Ingrese el ano de publicacion del libro: ");
	scanf(" %[^\t\n]s", &anno);
	printf("Ingrese el genero del libro: ");
	scanf(" %[^\t\n]s", &genero);
	printf("Ingrese el resumen del libro: ");
	scanf(" %[^\t\n]s", &resumen);

	while(salirCantidad){
		printf("Ingrese la cantidad de ejemplares del libro: ");
		scanf(" %[^\t\n]s", &cantidad);

		if (esNumero(cantidad)) {
            salirCantidad = FALSE;
        } else {
            printf("Error: Debe ingresar un numero valido para la cantidad.\n");
        }
	}

	Libro* libroNuevo = crearLibro(nombre, autor, anno, genero, resumen);
	printf("\n-> El libro ha sido registrado correctamente en el sistema\n\n");
}

int usuarioExiste(char* idUsuario){
	return FALSE;
}

void gestionUsuario(){
	int salirIdentidad = TRUE;

	char id[50];
	char nombre[50];
	char direccion[60];

	printf("\n-----------------------\n| Gestion de usuarios |\n-----------------------\nPara poder registrar un usuario nuevo en el sistema por favor ingrese los siguientes datos.\n\n");
	while(salirIdentidad){
		printf("Ingrese el numero de identificacion del usuario: ");
		scanf(" %[^\t\n]s", &id);

		if (esNumero(id)) {
            salirIdentidad = FALSE;
        } else {
            printf("Error: Debe ingresar un numero valido para la identidad (solo numeros).\n");
        }
	}

	printf("Ingrese el nombre del usuario: ");
	scanf(" %[^\t\n]s", &nombre);
	printf("Ingrese la direccion del usuario: ");
	scanf(" %[^\t\n]s", &direccion);

	Usuario* usuarioNuevo = crearUsuario(id, nombre, direccion);
	printf("\n-> El usuario ha sido registrado correctamente en el sistema\n\n");
}

int main() {
    int salir = FALSE;
	int opcion;
	char c;

	printf("\n-------------------------------------------------\n| Bienvenido al sistema de Gestion de Biblioteca |\n-------------------------------------------------\n\n");
	while (salir != TRUE){
		printf("Por favor seleccione una opcion:\n   1) Gestion de catalogo\n   2) Gestion de usuarios\n   3) Historial de prestamos\n   4) Vencimiento de prestamos\n   5) Estadisticas\n   7) Salir\nIngrese un numero: ");
		if (scanf("%i", &opcion) != 1 ){
			while ((c = getchar()) != '\n' && c != EOF) { }
			printf("Error: Por favor ingrese unicamente numeros enteros.\n\n");
    	}else {
			switch (opcion)
			{
			case 1:
				gestionCatalogo();
				break;

			case 2:
				gestionUsuario();
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