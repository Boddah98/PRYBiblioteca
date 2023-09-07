#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H
#include <stdio.h>
#include "cjson/cJSON.h"
#include <stdlib.h>
#include "bookManagement.h"


const char *userFileName = "./data/userData.json";

void printUserData(){
    char* fileContent = getFileContent(userFileName);
    
    cJSON* jsonObject =  cJSON_Parse(fileContent); 
    jsonObject = jsonObject->child;
    while (jsonObject) {
        cJSON* userID = cJSON_GetObjectItemCaseSensitive(jsonObject, "userID");
        cJSON* name = cJSON_GetObjectItemCaseSensitive(jsonObject, "userName");
        cJSON* address = cJSON_GetObjectItemCaseSensitive(jsonObject, "address");
        printf("->\n");
        printf("\tNombre usuario: %s\n", name->valuestring);
        printf("\tID de usuario: %s\n", userID->valuestring);
        printf("\tDireccion: %s\n", address->valuestring);
        jsonObject = jsonObject->next;
    }
    free(fileContent);
    cJSON_Delete(jsonObject);
}
//receives the id of the user is gonna be inserted 
bool checkForUserID(char* idForEvaluate){
    char* fileContent = getFileContent(userFileName);
    cJSON* jsonObject =  cJSON_Parse(fileContent); 
    jsonObject = jsonObject->child;
    while (jsonObject){
        cJSON* currentId = cJSON_GetObjectItemCaseSensitive(jsonObject,"userID"); 
        char *strCurrentID = currentId->valuestring;        
        if (strcmp(strCurrentID,idForEvaluate)==0){                //Compares the id introduced with the rest 
            free(fileContent);            
            cJSON_Delete(jsonObject);
            return true;
        }
        free(strCurrentID);
        jsonObject = jsonObject->next;
        
    }
    cJSON_Delete(jsonObject);
    free(fileContent);
    return false;
}
bool insertUser(char * userId, char* name, char* address ){
    if(checkForUserID(userId)){
        return false;
    }
    //Creating cJSON object for add data    
    cJSON* userJson = cJSON_CreateObject();
    cJSON_AddStringToObject(userJson, "userID", userId);
    cJSON_AddStringToObject(userJson, "userName", name);
    cJSON_AddStringToObject(userJson, "address", address);
    
    //Getting userData for add a new element
    char* fileContent = getFileContent(userFileName);
    cJSON* jsonUserData = cJSON_Parse(fileContent);       
    cJSON_AddItemToArray(jsonUserData,userJson);            
    
    //File open for write the user added 
    FILE* file = fopen(userFileName, "w" );
    char* json_string = cJSON_Print(jsonUserData);    
    fprintf(file, "%s", json_string);
    // clear memory
    free(json_string);
    fclose(file);
    cJSON_Delete(jsonUserData);    
    return true;
}

#endif