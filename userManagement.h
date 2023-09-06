#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H
#include <stdio.h>
#include "cjson/cJSON.h"
#include <stdlib.h>
#include "user.h"


const char *userFileName = "./data/userData.json";

static char* getFileContent1(const char* filePath){
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

void printUserData(){
    char* fileContent = getFileContent(userFileName);
    
    cJSON* jsonObject =  cJSON_Parse(fileContent); 
    jsonObject = jsonObject->child;
    while (jsonObject) {
        cJSON* object = cJSON_GetObjectItemCaseSensitive(jsonObject, "userName");
        cJSON* object2 = cJSON_GetObjectItemCaseSensitive(jsonObject, "address");
        
        printf("Nombre usuario: %s\n", object->valuestring);
        printf("Direccion: %s\n", object2->valuestring);
        jsonObject = jsonObject->next;
    }
    free(fileContent);
    cJSON_Delete(jsonObject);
}

void insertUser(){
    //Creating data for add
    int userId = 5;
    char* name = "Allan Turing";
    char* address = "England";
    user newUser = getNewUser(userId, name, address);
    cJSON* userJson = cJSON_CreateObject();

    //cJSON_AddStringToObject(userJson, "userId", (char*)newUser.userId);
    cJSON_AddStringToObject(userJson, "userName", newUser.userName);
    cJSON_AddStringToObject(userJson, "address", newUser.address);

    
    //Getting userData for add a new element
    char* fileContent = getFileContent(userFileName);
    cJSON* jsonUserData = cJSON_Parse(fileContent); ;    
    char* jsonChar = cJSON_Print(jsonUserData);    

    cJSON_AddItemToArray(jsonUserData,userJson);
        
    FILE* file = fopen(userFileName, "w" );
    char* json_string = cJSON_Print(jsonUserData);
    printf("%s\n",jsonUserData);

    fprintf(file, "%s", json_string);
    

    free(json_string);
    fclose(file);
    cJSON_Delete(jsonUserData);
    
    printf(": %d, %s, %s Added \n", newUser.userId, newUser.userName, newUser.address);
}

#endif