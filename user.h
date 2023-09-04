#ifndef USER_H
#define USER_H

typedef struct user{
    int userId;
    char* userName; 
    char* address;      
}user;
user getNewUser(
    int pUserId,
    char* pUserName, 
    char* pAddress){

        user newUser;
        newUser.userId = pUserId;        
        newUser.userName = pUserName;
        newUser.address = pAddress;            
        return newUser;
}
#endif