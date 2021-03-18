
#ifndef NDbfDatabase_FieldDescriptor
#define NDbfDatabase_FieldDescriptor

namespace DatabaseDbf
{
    #pragma pack (push, 1)
    struct FieldDescriptor
    {
        FieldDescriptor()
        {
            memset(this, 0, sizeof(FieldDescriptor));
        }
        char      mFieldname[11];
        char      mFieldType;
        uint8_t   mReseved01[4];
        uint8_t   mFieldLength;
        uint8_t   mFieldCount;
        uint8_t   mWorkAreaID;
        uint8_t   mExample;
        uint8_t   mReserved02[10];
        uint8_t   mFlagMdx;    
    };
    #pragma pack(pop)
};

#endif
