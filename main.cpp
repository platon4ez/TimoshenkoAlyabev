#include <iostream>
#include <Windows.h>

#pragma pack(push,1)

struct RARHeaderData
{
    unsigned short HeadCRC;
    unsigned char HeadType;
    unsigned short Flags;
    unsigned int PackSize;
    unsigned int UnpSize;
    unsigned int HostOS;
    unsigned int FileCRC;
    unsigned int FileTime;
    unsigned int UnpVer;
    unsigned int Method;
    unsigned short NameSize;
    unsigned int FileAttr;
};

struct RARHeaderDataEx
{
    RARHeaderData HeaderData;
    char ArcName[260];
    char FileName[260];
    unsigned int RedirType;
    char RedirName[260];
};

#pragma pack(pop)

void archivec (unsigned char* data, int size)
{
    unsigned char* ptr = data;

    while (ptr < data + size)
    {
        RARHeaderDataEx* header = (RARHeaderDataEx*)ptr;

        if (header->HeaderData.HeadType == 0x74) // FILE_HEAD
        {
            std::cout << header->FileName << std::endl;
        }

        ptr += header->HeaderData.PackSize + sizeof(RARHeaderData);
    }
}

int main()
{
    HANDLE file = CreateFile("archive.rar", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (file == INVALID_HANDLE_VALUE)
    {
        std::cout << "Failed to open file" << std::endl;
        return 1;
    }

    DWORD size = GetFileSize(file, NULL);
    unsigned char* buffer = new unsigned char[size];

    DWORD bytesRead;
    if (!ReadFile(file, buffer, size, &bytesRead, NULL))
    {
        std::cout << "Failed to read file" << std::endl;
        CloseHandle(file);
        delete[] buffer;
        return 1;
    }

    archivec(buffer, size);

    CloseHandle(file);
    delete[] buffer;

    return 0;
}
