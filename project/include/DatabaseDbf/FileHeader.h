
#ifndef NDbfDatabase_Fileheader_H
#define NDbfDatabase_Fileheader_H

#include <cstring>

namespace DatabaseDbf
{
    #pragma pack (push, 1)
    struct FileHeader
    {
        FileHeader()
        {
            memset(this, 0, sizeof(FileHeader));
        }
        uint8_t   mBase;
        uint8_t   mDateLastUpdate[3];
        uint32_t  mNumRecords;
        uint16_t  mBytesHeader;
        uint16_t  mBytesRecord;
        uint8_t   mReseved01[2];
        uint8_t   mFlagTransaction;
        uint8_t   mEncryption;
        uint8_t   mDOSmultiuser[12];
        uint8_t   mFlagMdxFile;
        uint8_t   mLanguageDriverID;
        uint8_t   mReseved02[2];    
    };
    #pragma pack(pop)
};

#endif

