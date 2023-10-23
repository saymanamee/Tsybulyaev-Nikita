// katalog.cpp: îïðåäåëÿåò òî÷êó âõîäà äëÿ êîíñîëüíîãî ïðèëîæåíèÿ.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include "stdlib.h"
#include "string"
#include "dirent.h"

using namespace std;

void processDirectory(const std::string& directoryPath) 
{ 
    DIR* dir = opendir(directoryPath.c_str());
    if (dir == nullptr) 
	{
        std::cerr << "Failed to open directory: " << directoryPath << std::endl;
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) 
	{
        std::string name = entry->d_name;
        if (name == "." || name == "..") 
		{
            continue;
        } 
        std::string fullPath = directoryPath + "/" + name;

        struct stat fileInfo;
        if (stat(fullPath.c_str(), &fileInfo) == -1) 
		{
            std::cerr << "Failed to get file info: " << fullPath << std::endl;
            continue;
        }
        
        if (S_ISDIR(fileInfo.st_mode)) 
		{
            processDirectory(fullPath);
        } else if (S_ISREG(fileInfo.st_mode)) 
		{
            std::cout << fullPath << std::endl;
        }
    }

    closedir(dir);
}

int main() 
{
    std::string directoryPath = "D:\DOS";
    processDirectory(directoryPath);
    printf("Checkout");

    return 0;
}
	
