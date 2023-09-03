struct UsuarioSistema{
	char* id;
    char* nombre;
    char* direccion;
	struct UsuarioSistema *sig;
}typedef Usuario;

Usuario* crearUsuario(char* pId, char* pNombre, char* pDireccion){
	Usuario* usuarioNuevo = (Usuario*) malloc (sizeof(Usuario));
	usuarioNuevo-> id = pId;
    usuarioNuevo-> nombre = pNombre;
    usuarioNuevo-> direccion = pDireccion;
	usuarioNuevo-> sig = NULL;
	return usuarioNuevo;
}

struct ListaUsuarios{
	Usuario* primero;
	Usuario* ultimo;
	int vacio;
	int contador;
}typedef ListaUsuarios;

ListaUsuarios* crearListaUsuarios(){
	ListaUsuarios* listaNueva = (ListaUsuarios*) malloc (sizeof(ListaUsuarios));
	listaNueva-> primero = NULL;
	listaNueva-> ultimo = NULL;
	listaNueva-> vacio = TRUE;
	listaNueva-> contador = 0;
	return listaNueva;
}

void agregarUsuario(Usuario* usuario, ListaUsuarios* lista){
	if (lista-> vacio == TRUE){
		lista-> primero = usuario;
		lista-> ultimo = usuario;
		lista-> vacio = FALSE;

	}else{
		lista-> ultimo-> sig = usuario;
		lista-> ultimo = usuario;
	}
	lista-> contador++;
}

void imprimirListaUsuarios(ListaUsuarios *lista) {
	Usuario* usuarioActual = lista->primero;

	if(usuarioActual != NULL) {
		while(usuarioActual != NULL){
			printf("Numero de identificacion: %s \nNombre: %s \nDireccion: %s \n\n", usuarioActual->id, usuarioActual->nombre, usuarioActual->direccion);
			usuarioActual = usuarioActual->sig;
		}
	} else {
		printf("No se ha agregado ningun usuario por ahora.\n\n");
	}
}