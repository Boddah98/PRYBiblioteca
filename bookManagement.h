
#ifndef BOOKMANAGEMENT_H
#define BOOKMANAGEMENT_H
#include <stdio.h>
#include "cjson/cJSON.h"
#include <stdlib.h>
#include <stdbool.h>
#include "book.h"

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
    char strBookYear[4], strBookQuantity[4]; 
    //The book struct and cJSON are create for add to the json file
    book newBook = newBookFromArray(atributeArray); 
    cJSON* newBookJson = cJSON_CreateObject();

    //then, the atributes are asigned to the cJSON    
    cJSON_AddStringToObject(newBookJson, "name", newBook.name);
    cJSON_AddStringToObject(newBookJson, "author", newBook.author);            
    sprintf( strBookYear,"%d", newBook.year);
    cJSON_AddStringToObject(newBookJson, "year", strBookYear);
    cJSON_AddStringToObject(newBookJson, "genre", newBook.genre);
    cJSON_AddStringToObject(newBookJson, "resume", newBook.resume);
    sprintf( strBookQuantity,"%d", newBook.quantity);
    cJSON_AddStringToObject(newBookJson, "quantity",  strBookQuantity);
   
   //Its required to have array for the copys 
    cJSON* stockAtribute = cJSON_CreateArray();
    cJSON_AddItemToObject(newBookJson,"stock", stockAtribute);

    for(int i=1; i<=newBook.quantity; i++){ 
        cJSON* bookCopy = cJSON_CreateObject();
        char strBookId[4];
        sprintf( strBookId,"%d", i);
        cJSON_AddStringToObject(bookCopy, "bookId", strBookId);
        cJSON_AddStringToObject(bookCopy, "available", "true");
        cJSON_AddItemToArray(stockAtribute,bookCopy);
        
    }

    
    
    //The last json content is needed for add the new book 
    char* jsonContent = getFileContent(bookFileName);
    cJSON* jsonObject = cJSON_Parse(jsonContent);
    cJSON_AddItemToArray(jsonObject,newBookJson);
    

    FILE* file = fopen(bookFileName, "w" );
    char* strBookJson = cJSON_Print(jsonObject);

    fprintf(file, "%s", strBookJson);    
    free(strBookJson);
    fclose(file);
    cJSON_Delete(newBookJson);
    printf("El libro: %s se ha agregado. %d ejemplares disponibles\n", newBook.name,newBook.quantity);
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
    /*
    atribute = (char*)realloc(atribute, atributeSize);
    atribute[atributeSize - 1] = '\0';
    bookData[arrayIndex] = (char *)malloc(strlen(atribute) + 1);
    bookData[arrayIndex] = atribute;
    */
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
            //return;
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

void printBookData(){
    char* fileContent = getFileContent(bookFileName);
    
    cJSON* jsonObject =  cJSON_Parse(fileContent); 

    if (jsonObject == NULL) {
        printf("Error al analizar el archivo JSON.\n");
        free(fileContent);
        return;
    }
        
    jsonObject = jsonObject->child; 

    while (jsonObject) {
        cJSON* object = cJSON_GetObjectItemCaseSensitive(jsonObject, "name");
        cJSON* object2 = cJSON_GetObjectItemCaseSensitive(jsonObject, "year");
        
        printf("Name: %s\n", object->valuestring);
        printf("Year: %s\n", object2->valuestring);
        jsonObject = jsonObject->next;
    }
    free(fileContent);
    cJSON_Delete(jsonObject);
}
#endif