#define TRUE  1
#define FALSE 0

struct LibroLiteratura{
	char* id;
	char* nombre;
    char* autor;
    char* annoPublicacion;
    char* genero;
    char* resumen;
	char* disponible;
	struct LibroLiteratura *sig;
}typedef Libro;

Libro* crearLibro(char* pId, char* pNombre, char* pAutor, char* pAnnoPublicacion, char* pGenero, char* pResumen, char* pAvailable){
	Libro* libroNuevo = (Libro*) malloc (sizeof(Libro));
	libroNuevo-> id = pId;
	libroNuevo-> nombre = pNombre;
    libroNuevo-> autor = pAutor;
    libroNuevo-> annoPublicacion = pAnnoPublicacion;
    libroNuevo-> genero = pGenero;
    libroNuevo-> resumen = pResumen;
	libroNuevo-> disponible = pAvailable;
	libroNuevo-> sig = NULL;
	return libroNuevo;
}

struct ListaLibros{
	Libro* primero;
	Libro* ultimo;
	int vacio;
	int contador;
}typedef ListaLibros;

ListaLibros* crearListaLibros(){
	ListaLibros* listaNueva = (ListaLibros*) malloc (sizeof(ListaLibros));
	listaNueva-> primero = NULL;
	listaNueva-> ultimo = NULL;
	listaNueva-> vacio = TRUE;
	listaNueva-> contador = 0;
	return listaNueva;
}

void agregarLibro(Libro* libro, ListaLibros* lista){
	if (lista-> vacio == TRUE){
		lista-> primero = libro;
		lista-> ultimo = libro;
		lista-> vacio = FALSE;

	}else{
		lista-> ultimo-> sig = libro;
		lista-> ultimo = libro;
	}
	lista-> contador++;
}

void imprimirListaLibros(ListaLibros *lista) {
	Libro* libroActual = lista->primero;

	if(libroActual != NULL) {
		while(libroActual != NULL){
			printf("ID: %s \nNombre: %s \nAutor: %s \nAno de publicacion: %s \nGenero: %s \nResumen: %s \nDisponibilidad: %s \n\n", libroActual->id, libroActual->nombre, libroActual->autor, libroActual->annoPublicacion,  libroActual->genero, libroActual->resumen, libroActual->disponible);
			libroActual = libroActual->sig;
		}
	} else {
		printf("No se ha agregado ningun libro por ahora.\n\n");
	}
}