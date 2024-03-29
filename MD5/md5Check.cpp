#include "md5Check.h"



bool Md5Check::GetFileMD5Hash(const wchar_t* fileName, BYTE* md5Hash) {
    HCRYPTPROV hCryptProv = NULL;
    HCRYPTHASH hHash = NULL;
    DWORD hashSize = 0;
    DWORD cbRead = 0;
    BYTE data[BUFSIZE];
    std::ifstream file(fileName, std::ios::binary);

    if (!file)
    {
        std::string fileNameStr = K_Utils::wide_to_narrow(fileName);
        logErr("MD5Hash: Failed to open file: %s", fileNameStr.c_str());
        return false;
    }

    if (!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
    {
        logErr("MD5Hash failed with error code: %d", GetLastError());
        return false;
    }

    if (!CryptCreateHash(hCryptProv, CALG_MD5, 0, 0, &hHash))
    {
        logErr("MD5Hash failed with error code: %d", GetLastError());
        CryptReleaseContext(hCryptProv, 0);
        return false;
    }

    while (file)
    {
        file.read((char*)data, BUFSIZE);
        std::streamsize streamSize = file.gcount();
        unsigned long cbRead = static_cast<unsigned long>(streamSize);
        if (!CryptHashData(hHash, data, cbRead, 0))
        {
            logErr("MD5Hash failed with error code: %d", GetLastError());
            CryptDestroyHash(hHash);
            CryptReleaseContext(hCryptProv, 0);
            return false;
        }
    }

    hashSize = HASHSIZE;
    if (!CryptGetHashParam(hHash, HP_HASHVAL, md5Hash, &hashSize, 0))
    {
        logErr("MD5Hash failed with error code: %d", GetLastError());
        CryptDestroyHash(hHash);
        CryptReleaseContext(hCryptProv, 0);
        return false;
    }

    CryptDestroyHash(hHash);
    CryptReleaseContext(hCryptProv, 0);

    return true;
}


std::string Md5Check::getHashArrayAsStr(BYTE* hashArray, size_t arrSize) {
    std::stringstream ss;
    for (size_t i = 0; i < arrSize; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hashArray[i]);
    }
    std::string result = ss.str();
    return result;
}



bool Md5Check::hexStringToByteArray(const std::string& hexString, std::vector<BYTE>& byteArray) {
    if (hexString.size() % 2 != 0) {
        return false;
    }

    byteArray.clear();

    for (size_t i = 0; i < hexString.size(); i += 2) {
        std::string byteString = hexString.substr(i, 2);

        BYTE byteValue = static_cast<BYTE>(std::stoul(byteString, nullptr, 16));

        byteArray.push_back(byteValue);
    }

    return true;
}


 bool Md5Check::delete_file(const std::string& filename) {
    try
    {
        return remove(filename.c_str()) == 0;
    }
    catch (const std::exception& ex)
    {
        logErr("delete_file exception: %s", ex.what());
    }

}
