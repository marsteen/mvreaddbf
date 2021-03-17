

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <cstring>


//typedef std::map<std::string, std::string> Trecord;



typedef std::vector<std::string> Trecord;

static std::vector<Trecord> database;

using namespace std;


#pragma pack (push, 1)
struct SDbfHeader
{
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

#pragma pack (push, 1)
struct SDbfFieldDescriptor
{
    SDbfFieldDescriptor()
    {
        memset(this, 0, sizeof(SDbfFieldDescriptor));
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

vector<SDbfFieldDescriptor> fieldVec;

/*
0–10 	11 bytes 	Field name in ASCII (zero-filled)
11 	1 byte 	Field type. Allowed values: C, D, F, L, M, or N (see next table for meanings)
12–15 	4 bytes 	Reserved
16 	1 byte 	Field length in binary (maximum 254 (0xFE)).
17 	1 byte 	Field decimal count in binary
18–19 	2 bytes 	Work area ID
20 	1 byte 	Example
21–30 	10 bytes 	Reserved
31 	1 byte 	Production MDX field flag; 1 if field has an index tag in the production MDX file, 0 if not 
*/

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        std::vector<int> fieldlenVec;
        //fstream fs(Filename, ios::in | ios::binary);
        std::ifstream dbffile(argv[1], std::ios::binary);
        if (dbffile.good())
        {
             SDbfHeader dbfheader;             
             dbffile.read((char*) &dbfheader, sizeof(SDbfHeader));
             
             cout << "mNumRecords=" << dbfheader.mNumRecords << endl;
             cout << "size:" << sizeof(SDbfFieldDescriptor) << endl;
             
             bool enddesc = false;
             int fieldnum;
             for (fieldnum = 0; !enddesc; fieldnum++)
             {
                char fielddesc[32];
                dbffile.read(fielddesc, 1);
                if (fielddesc[0] == 0x0D)
                {
                    enddesc = true;
                }
                else
                {         
                    char namebuff[12];
                    SDbfFieldDescriptor* dbffielddesc = (SDbfFieldDescriptor*) &fielddesc;
                    dbffile.read(fielddesc + 1, 31);
                    strncpy(namebuff, fielddesc, 11);
                    namebuff[11] = 0;

                    cout << "field: "    << fieldnum 
                        << " fielddesc=" << namebuff 
                        << " type=" << dbffielddesc->mFieldType 
                        << " length=" << (int) dbffielddesc->mFieldLength << endl;
                        
                    
                    fieldlenVec.push_back(dbffielddesc->mFieldLength);    
                    fieldVec.push_back(*dbffielddesc);
                    
                }
             }
             
             cout << "mNumRecords=" << dbfheader.mNumRecords << endl;
             for (int i = 0; i < dbfheader.mNumRecords; i++)
             {
                  char dummy;
                  dbffile.read((char*) &dummy, 1);
                  Trecord record;
                  
                  for (int f = 0; f < fieldnum; f++)
                  {
                      char fbuff[256];
                      memset(fbuff, 0, 256);
                      dbffile.read(fbuff, fieldVec[f].mFieldLength);
                      if (f == 3)
                      {
                         cout << "rec=" << fbuff << endl;
                      }
                      record.push_back(fbuff);
                  }
                  database.push_back(record);
             }             
        }
    }
    
    return 0;
}

