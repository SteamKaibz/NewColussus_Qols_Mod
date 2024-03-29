#pragma once

#include <windows.h>
#include <wincrypt.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <locale>
#include <codecvt>
#include "../Config/Config.h"
#include <shlwapi.h>
#include "../K_Utils/K_Utils.h"
#include "../K_Utils/K_Utils.h"

class Md5Check
{

private:
    

    
   

   


public:

    static constexpr size_t HASHSIZE = 16;

    static constexpr  int BUFSIZE = 1024;

    static bool GetFileMD5Hash(const wchar_t* fileName, BYTE* md5Hash);

    static std::string getHashArrayAsStr(BYTE* hashArray, size_t arrSize);

    static bool hexStringToByteArray(const std::string& hexString, std::vector<BYTE>& byteArray);

    static bool delete_file(const std::string& filename);





   

};