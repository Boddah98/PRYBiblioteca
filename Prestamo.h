struct PrestamoDeLibro{
	char* id;
    Usuario* usuario;
    int estadoPrestamo;
    char* nombreEjemplar;
    char* idEjemplar;
    int estadoEntregaTardia;
	struct PrestamoDeLibro *sig;
}typedef Prestamo;

Prestamo* crearPrestamo(char* pId, Usuario* pUsuario, int pEstadoPrestamo, char* pNombreEjemplar, char* pIdEjemplar, int pEstadoEntregaTardia){
	Prestamo* prestamoNuevo = (Prestamo*) malloc (sizeof(Prestamo));
	prestamoNuevo-> id = pId;
    prestamoNuevo-> usuario = pUsuario;
    prestamoNuevo-> estadoPrestamo = pEstadoPrestamo;
    prestamoNuevo-> nombreEjemplar = pNombreEjemplar;
    prestamoNuevo-> idEjemplar = pIdEjemplar;
    prestamoNuevo-> estadoEntregaTardia = pEstadoEntregaTardia;
	prestamoNuevo-> sig = NULL;
	return prestamoNuevo;
}

struct ListaPrestamos{
	Prestamo* primero;
	Prestamo* ultimo;
	int vacio;
	int contador;
}typedef ListaPrestamos;

ListaPrestamos* crearListaPrestamos(){
	ListaPrestamos* listaNueva = (ListaPrestamos*) malloc (sizeof(ListaPrestamos));
	listaNueva-> primero = NULL;
	listaNueva-> ultimo = NULL;
	listaNueva-> vacio = TRUE;
	listaNueva-> contador = 0;
	return listaNueva;
}

void agregarPrestamo(Prestamo* prestamo, ListaPrestamos* lista){
	if (lista-> vacio == TRUE){
		lista-> primero = prestamo;
		lista-> ultimo = prestamo;
		lista-> vacio = FALSE;

	}else{
		lista-> ultimo-> sig = prestamo;
		lista-> ultimo = prestamo;
	}
	lista-> contador++;
}

void imprimirListaPrestamos(ListaPrestamos *lista) {
	Prestamo* prestamoActual = lista->primero;

	if(prestamoActual != NULL) {
		while(prestamoActual != NULL){
			printf("ID: %s \nUsuario: %s \n\n", prestamoActual->id, prestamoActual->usuario->nombre);
            if (prestamoActual->estadoPrestamo) {
                printf("Estado del prestamo: Activo");
            }else{
                printf("Estado del prestamo: Finalizado")
            }

            printf("Nombre ejemplar: %s \nID ejemplar: %s \n\n", prestamoActual->nombreEjemplar, prestamoActual->idEjemplar);
            if (prestamoActual->estadoEntregaTardia) {
                printf("Estado de entrega tardia: Si");
            }else{
                printf("Estado de entrega tardia: No")
            }
			prestamoActual = prestamoActual->sig;
		}
	} else {
		printf("No se ha agregado ningun prestamo por ahora.\n\n");
	}
}