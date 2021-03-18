
#include <iostream>
#include <DatabaseDbf/Database.h>

using namespace std;

namespace DatabaseDbf
{
    
    //---------------------------------------------------------------------------
    //
    // Klasse:    Database
    // Methode:   
    //
    //
    //---------------------------------------------------------------------------

    bool Database::openFile(const std::string& filename)
    {
        bool r = false;

        mFileStream.open(filename.c_str(), std::ios::binary);
        if (mFileStream.good())
        {
             
             mFileStream.read((char*) &mFileHeader, sizeof(FileHeader));
             
             cout << "mNumRecords=" << mFileHeader.mNumRecords << endl;
             cout << "size:" << sizeof(FieldDescriptor) << endl;
             
             bool enddesc = false;
             int fieldnum;
             mRecordSize = 0;
             for (fieldnum = 0; !enddesc; fieldnum++)
             {
                char fielddesc[32];
                mFileStream.read(fielddesc, 1);
                if (fielddesc[0] == 0x0D)
                {
                    enddesc = true;
                }
                else
                {         
                    char namebuff[12];
                    FieldDescriptor* dbffielddesc = (FieldDescriptor*) &fielddesc;
                    mFileStream.read(fielddesc + 1, 31);
                    strncpy(namebuff, fielddesc, 11);
                    namebuff[11] = 0;

                    cout << "field: "    << fieldnum 
                        << " fielddesc=" << namebuff 
                        << " type=" << dbffielddesc->mFieldType 
                        << " length=" << (int) dbffielddesc->mFieldLength << endl;
                        
                    mRecordSize += (int) dbffielddesc->mFieldLength;                                                            
                    mFieldVec.push_back(*dbffielddesc);                    
                }
             }
             mFirstRecordPos = mFileStream.tellg();
             
             r = true;
             
        }
        return r;
    }
        
    //---------------------------------------------------------------------------
    //
    // Klasse:    Database
    // Methode:   closeFile
    //
    //
    //---------------------------------------------------------------------------
    
    void Database::closeFile()
    {
        mFileStream.close();
    }

    //---------------------------------------------------------------------------
    //
    // Klasse:    Database
    // Methode:   getRecord
    //
    //
    //---------------------------------------------------------------------------

    bool Database::getRecord(int i, Trecord& record)
    {
        bool r = false;
        if (i < mFileHeader.mNumRecords)
        {
            size_t filePos = (size_t) mFirstRecordPos + (mRecordSize + 1) * i;
            mFileStream.seekg(filePos, ios::beg);            
            record.clear();
            
            char deleteIndicator;
            mFileStream.read(&deleteIndicator, 1);
            
            for (auto it = mFieldVec.begin(); it != mFieldVec.end(); ++it)
            {
                char fbuff[256];
                memset(fbuff, 0, 256);
                mFileStream.read(fbuff, it->mFieldLength);
                record.push_back(fbuff);
            }
            r = true;            
        }
        return r;
    }

    //---------------------------------------------------------------------------
    //
    // Klasse:    Database
    // Methode:   getRecordCount
    //
    //
    //---------------------------------------------------------------------------

    int  Database::getRecordCount() const
    {
        return mFileHeader.mNumRecords;
    }
    
    //---------------------------------------------------------------------------
    //
    // Klasse:    Database
    // Methode:   readAll
    //
    //
    //---------------------------------------------------------------------------

    void Database::readAll(std::vector<Trecord>& recordVec)
    {
        int i = 0;
        Trecord record;        
        while (getRecord(i++, record))
        {
            recordVec.push_back(record);
        }
    }
    
    //---------------------------------------------------------------------------
    //
    // Klasse:    Database
    // Methode:   showAll
    //
    //
    //---------------------------------------------------------------------------

    void Database::showAll(int fieldNum)
    {
        int i = 0;
        Trecord record;        
        while (getRecord(i++, record))
        {
            cout << i << ":" << record[fieldNum] << endl;
        }
    }   
}
