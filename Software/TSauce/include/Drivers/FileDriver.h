#ifndef FILEDRIVER_H_
#define FILEDRIVER_H_

#include <stdio.h>
#include <stdlib.h>

#include <fstream>

//The data structure of a file. One per file
struct BBP3FileHeader;

//The Header of a BBP3 memory Chunk
struct BBP3ChunkHeader;

//The data structure of a page on the file look up table
struct BBP3FilePage
{
    /*
        Pagesize: size of this page
        FileMagic: magic of the page (NOT FILE MAGIC! This magic is to tell what kind of page this is)
        FileNameSize: amount of chars of name
        FileName: (string of name)
        parentChunkPtr: Pointer to the parent page (such as directory or whatever)
        MetadataSize: amount of bytes allocated to metadata
        metadata: (metadata)
        FilePtr: Pointer to chunk of first chunk
    */
    unsigned int PageSize;
    unsigned int Magic;
    BBP3FilePage* ParentChunkPtr;
    unsigned int MetadataSize;
    unsigned int* Metadata;
    BBP3FileHeader* FilePtr;
    unsigned int fileNameSize;
    unsigned char* fileName;
    BBP3FilePage* next;
};

struct BBP3ChunkHeader
{
    unsigned int residesAt;
    unsigned int size;
    BBP3ChunkHeader* nextChunk;
    BBP3ChunkHeader* nextRelevantChunk;
};

struct BBP3FileHeader: BBP3ChunkHeader
{
    unsigned int magic;
    unsigned int encoding;
    unsigned int size;
    BBP3FileHeader* header;
    BBP3ChunkHeader** chunks;
};


class FileSeeker
{
    private:
        char* loadedAt;
    public:
        FileSeeker(BBP3FilePage);
        void Load();
        char GetByteAt(long);
};

class FileDriver
{
    public:
        static BBP3FilePage* Seek(char* name);
        static BBP3FilePage* mkDir(char* win, char* name);
        static BBP3FilePage* mkDir(char* win, char* parent, char* name);
        static BBP3FilePage* CreateFile(char* win, BBP3FilePage* parent, char* name, int size, char* data);
        
};


#endif