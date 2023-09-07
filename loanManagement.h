#ifndef LOANMANAGEMENT_H
#define LOANMANAGEMENT_H
#include <stdio.h>
#include "cjson/cJSON.h"
#include <stdlib.h>
#include "bookManagement.h"
char* loanFileName = "./data/loanData.json";

char* getFileContent1(char* filePath){
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
void printLoanData(){
    char* fileContent = getFileContent1(loanFileName);
    
    cJSON* jsonObject =  cJSON_Parse(fileContent); 

    if (jsonObject == NULL) {
        printf("Error al analizar el archivo JSON.\n");
        free(fileContent);
        return;
    }
        
    jsonObject = jsonObject->child; 
    cJSON* loanID;
    cJSON* userID;
    cJSON* bookName;
    cJSON* deliveryStatus;
    cJSON* rate;
        
    while (jsonObject) {
        loanID = cJSON_GetObjectItemCaseSensitive(jsonObject, "loanID");
        userID = cJSON_GetObjectItemCaseSensitive(jsonObject, "userID");
        bookName = cJSON_GetObjectItemCaseSensitive(jsonObject, "bookName");
        deliveryStatus = cJSON_GetObjectItemCaseSensitive(jsonObject, "deliveryStatus");
        rate = cJSON_GetObjectItemCaseSensitive(jsonObject, "rate");
        
        printf("loanID: %s\n", loanID->valuestring);
        printf("userID: %s\n", userID->valuestring);
        printf("bookName: %s\n", bookName->valuestring);
        printf("deliveryStatus: %s\n", deliveryStatus->valuestring);
        printf("rate: %s\n", rate->valuestring);
        printf("\n");
        jsonObject = jsonObject->next;
    }
    free(fileContent);
    cJSON_Delete(jsonObject);
}
#endif