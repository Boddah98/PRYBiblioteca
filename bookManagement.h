
#ifndef BOOKMANAGEMENT_H
#define BOOKMANAGEMENT_H
#include <stdio.h>
#include "cjson/cJSON.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 


const char *bookFileName = "./data/bookData.json";

char* getFileContent(const char* filePath){
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* fileContent = (char*)malloc(fileSize + 1);
    if (fileContent == NULL) {
        printf("No se pudo asignar memoria.\n");
        fclose(file);
        return NULL;
    }

    fread(fileContent, 1, fileSize, file);
    fclose(file);
    fileContent[fileSize] = '\0';
    
    
    
    return fileContent;
}
void insertBook(char** atributeArray){   
    
    //The book struct and cJSON are create for add to the json file
    
    cJSON* newBookJson = cJSON_CreateObject();

    //then, the atributes are asigned to the cJSON    
    cJSON_AddStringToObject(newBookJson, "name", atributeArray[0]);
    cJSON_AddStringToObject(newBookJson, "author", atributeArray[1]);                
    cJSON_AddStringToObject(newBookJson, "year", atributeArray[2]);
    cJSON_AddStringToObject(newBookJson, "genre", atributeArray[3]);
    cJSON_AddStringToObject(newBookJson, "resume", atributeArray[4]);    
    cJSON_AddStringToObject(newBookJson, "quantity",   atributeArray[5]);
   
   //Its required to have array for the copys 
    cJSON* stockAtribute = cJSON_CreateArray();
    cJSON_AddItemToObject(newBookJson,"stock", stockAtribute);

    for(int i=1; i <= atoi(atributeArray[5]); i++){ 
        cJSON* bookCopy = cJSON_CreateObject();
        char strBookId[4];
        sprintf( strBookId,"%d", i);
        cJSON_AddStringToObject(bookCopy, "bookId", strBookId);
        cJSON_AddStringToObject(bookCopy, "available", "true");
        cJSON_AddItemToArray(stockAtribute,bookCopy);
        
    }
    //The last json content is readed for concat the new book 
    char* jsonContent = getFileContent(bookFileName);
    cJSON* jsonObject = cJSON_Parse(jsonContent);
    cJSON_AddItemToArray(jsonObject,newBookJson);
    //Then the content is rewrite  
    FILE* file = fopen(bookFileName, "w" );
    char* strBookJson = cJSON_Print(jsonObject);
    fprintf(file, "%s", strBookJson);        
    fclose(file);
    //clear memory
    free(strBookJson);
    cJSON_Delete(newBookJson);
    printf("El libro: %s se ha agregado. %d ejemplares disponibles\n",atributeArray[0],atoi(atributeArray[5]));
}

bool isOnBatch(char* nameAtribute){
    
    char* fileBooksContent = getFileContent(bookFileName);
    cJSON* jsonObject = cJSON_Parse(fileBooksContent);
    if (jsonObject == NULL) {
        printf("Error al analizar el archivo JSON.\n");
        free(fileBooksContent);
        return false;
    }
        
    jsonObject = jsonObject->child; 

    while (jsonObject) {
        cJSON* object = cJSON_GetObjectItemCaseSensitive(jsonObject, "name");        
        char *bookName = object->valuestring;
        //printf("Name: %s\n", object->valuestring);
        if (strcmp(bookName, nameAtribute) == 0){
            printf("Este libro ya esta en stock\n\n");
            return true;            
        }        
        jsonObject = jsonObject->next;
    }
    free(fileBooksContent);
    cJSON_Delete(jsonObject);
    printf("Este libro no esta en stock\n\n");
    return false;
}

bool determineLine(char* lineChar){

    // Variables required for parsing each separate atribute
    char* atribute = NULL;
    size_t atributeSize = 0;    
    
    //For manage the atributes of the book if is not found in the batch
    char **bookData = (char **)malloc(6 * sizeof(char *));
    int arrayIndex=0;
    char* chr = lineChar;
    int lenght = strlen(lineChar)+1;
    for(char* chr = lineChar; lenght!=0; *chr++){        
    
        atributeSize++;
        if (*chr=='|' || *chr == '\0' ){
            
            atribute = (char*)realloc(atribute, atributeSize);
            atribute[atributeSize - 1] = '\0';            
            
            //the [0] atribute is name
            if (arrayIndex==0){
                printf("Nombre de libro: %s\n", atribute);
                if(isOnBatch(atribute)==true){
                                                           
                    return true;
                }
            }
            //add the new atribute to the array
            bookData[arrayIndex] = (char *)malloc(strlen(atribute) + 1);
            strcpy(bookData[arrayIndex], atribute); 
                                     
            //set data
            free(atribute);            
            arrayIndex++;
            atribute = NULL;
            atributeSize = 0;
            
        }else{
            atribute = (char*)realloc(atribute, atributeSize);
            atribute[atributeSize - 1] = *chr;
        } 
        lenght--;
    }
    //With the array full of the line data, insertBook() funct writes at the json file    
    insertBook(bookData);
    return false;
}
void analizeBookBatch(const char* fileDocName) {
    char* dataBatch = getFileContent(fileDocName);
    if (dataBatch == NULL) {
        fprintf(stderr, "Error al leer el archivo.\n");
        return;
    }

    // Variables required for parsing each separate line
    char* line = NULL;
    size_t lineSize = 0;
    printf("Abriendo addFile.txt en busqueda de libros por agregar\n");
    for (char* chr = dataBatch; *chr != '\0'; chr++) {
        lineSize++;

        if (*chr == '\n' || *chr == '\0') {
            // NULL char
            line = (char*)realloc(line, lineSize);
            line[lineSize - 1] = '\0';

            printf("Analizando linea: \n");
            bool ret = determineLine(line);            
            free(line);
            line = NULL;
            lineSize = 0;
            
        } else {
            // concat
            line = (char*)realloc(line, lineSize);
            line[lineSize - 1] = *chr;
        }
    }

    // clear variables
    free(dataBatch);
    free(line);
}

//Función que lee los datos de los libros almacenados en los json, y los guarda en una lista dinámica.
void loadBookData(){
    char* fileContent = getFileContent(bookFileName);
    
    cJSON* jsonObject =  cJSON_Parse(fileContent); 

    if (jsonObject == NULL) {
        printf("Error al analizar el archivo JSON.\n");
        free(fileContent);
        
    }
        
    jsonObject = jsonObject->child;

    cJSON* name;
    cJSON* author;
    cJSON* year;
    cJSON* genre;
    cJSON* resume;
    cJSON* stock;
    cJSON* bookId;
    cJSON* available;
    Libro* libroNuevo;
    ListaLibros* listaLibros = crearListaLibros();

    while (jsonObject) {
        name = cJSON_GetObjectItemCaseSensitive(jsonObject, "name");
        author = cJSON_GetObjectItemCaseSensitive(jsonObject, "author");
        year = cJSON_GetObjectItemCaseSensitive(jsonObject, "year");
        genre = cJSON_GetObjectItemCaseSensitive(jsonObject, "genre");
        resume = cJSON_GetObjectItemCaseSensitive(jsonObject, "resume");
        stock = cJSON_GetObjectItemCaseSensitive(jsonObject, "stock")->child;
        printf(name->valuestring);

        while(stock) {
            bookId = cJSON_GetObjectItemCaseSensitive(stock, "bookId");
            available = cJSON_GetObjectItemCaseSensitive(stock, "available");
            libroNuevo = crearLibro(bookId->valuestring, name->valuestring, author->valuestring, year->valuestring, genre->valuestring, resume->valuestring, available->valuestring);
            agregarLibro(libroNuevo, listaLibros);
            stock = stock->next;
        }
        jsonObject = jsonObject->next;
    }
    free(fileContent);
    cJSON_Delete(jsonObject);
    imprimirListaLibros(listaLibros);
}

void printBookData(){
    char* fileContent = getFileContent(bookFileName);
    
    cJSON* jsonObject =  cJSON_Parse(fileContent); 

    if (jsonObject == NULL) {
        printf("Al parecer ha ocurrido un error al leer el json. por favor asegurese de este exista, y tenga el formato correcto.\n");
        free(fileContent);
        
    }
        
    jsonObject = jsonObject->child; 

    while (jsonObject) {
        cJSON* name = cJSON_GetObjectItemCaseSensitive(jsonObject, "name");
        cJSON* year = cJSON_GetObjectItemCaseSensitive(jsonObject, "year");
        
        printf("Name: %s\n", name->valuestring);
        printf("Year: %s\n", year->valuestring);
        jsonObject = jsonObject->next;
    }
    free(fileContent);
    cJSON_Delete(jsonObject);
}
#endif