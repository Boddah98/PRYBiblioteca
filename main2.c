#include <stdio.h>
#include "cjson/cJSON.h"
#include <dirent.h>
#include <stdlib.h>
#include "bookManagement.h"

#include "userManagement.h"

int main(){        
    //printBookData();
    //insertDataBatch();
    //getFileData()
    const char* filePath = "addFile.txt";
    analizeBookBatch(filePath);
    return 0;
}