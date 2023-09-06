
#ifndef BOOKMANAGEMENT_H
#define BOOKMANAGEMENT_H
#include <stdio.h>
#include "cjson/cJSON.h"
#include <stdlib.h>
#include <stdbool.h>
const char *bookFileName = "./data/bookData.json";

static char* getFileContent(const char* filePath){
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
            printf("Name: %s true\n", bookName);
            return true;
            
        }
        jsonObject = jsonObject->next;
    }
    free(fileBooksContent);
    cJSON_Delete(jsonObject);
    return false;
}

bool determineLine(char* lineChar){
    printf("buscando\n");
    // Variables required for parsing each separate atribute
    char* atribute = NULL;
    size_t atributeSize = 0;
    // For manage the order of the loop
    bool isOn = false;
    bool possibleToFound = true;
    //For manage the atributes of the book if is not found in the batch
    char **bookData = (char **)malloc(6 * sizeof(char *));
    int wordIndex=0;
    
    for(char* chr = lineChar; *chr!='\0'; *chr++){
        
        atributeSize++;
        if (*chr=='|'){
            atribute = (char*)realloc(atribute, atributeSize);
            atribute[atributeSize - 1] = '\0';
            printf("Nombre de libro: %s\n", atribute);
            if(isOnBatch(atribute)){
                printf("%s\n","is on");
                isOn = true;
                strcpy(bookData[wordIndex], atribute);
                return false;
            }
            
            free(atribute);
            atribute = NULL;
            atributeSize = 0;
            
        }else{
            atribute = (char*)realloc(atribute, atributeSize);
            atribute[atributeSize - 1] = *chr;
        } 
    }
    return false;
}
void insertBookBatch(const char* fileDocName) {
    char* dataBatch = getFileContent(fileDocName);
    if (dataBatch == NULL) {
        fprintf(stderr, "Error al leer el archivo.\n");
        return;
    }

    // Variables required for parsing each separate line
    char* line = NULL;
    size_t lineSize = 0;

    for (char* chr = dataBatch; *chr != '\0'; chr++) {
        lineSize++;

        if (*chr == '\n' || *chr == '\0') {
            // NULL char
            line = (char*)realloc(line, lineSize);
            line[lineSize - 1] = '\0';

            printf("Línea: %s\n", line);
            determineLine(line);
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