#include <stdio.h>
#include "cjson/cJSON.h"
#include <dirent.h>
#include <stdlib.h>
#include "Libro.h"
#include "bookManagement.h"
#include "loanManagement.h"
#include "userManagement.h"

int main(){
    /*
    char * userId = "115040072";
    char* name = "Maria Turing";
    char* address = "England";
    insertUser(userId,name,address);
    //checkForUserID(userId);
    printUserData();
    //const char* filePath = "addFile.txt";
    //analizeBookBatch(filePath);
    */        
    printBookData();
    return 0;
}