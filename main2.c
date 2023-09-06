#include <stdio.h>
#include "cjson/cJSON.h"
#include <dirent.h>
#include <stdlib.h>
#include "bookManagement.h"
#include "book.h"
#include "userManagement.h"

int main(){        
    //printUserData();
    //insertDataBatch();
    //getFileData()
    const char* filePath = "addFile.txt";
    insertBookBatch(filePath);
    return 0;
}