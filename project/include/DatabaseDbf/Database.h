
#ifndef CDatabaseDbf_H
#define CDatabaseDbf_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <cstring>

#include <DatabaseDbf/FieldDescriptor.h>
#include <DatabaseDbf/FileHeader.h>

namespace DatabaseDbf
{

    typedef std::vector<std::string> Trecord;
    
    class Database
    {
        public:
            
            bool openFile(const std::string& filename);
            void readAll(std::vector<Trecord>& recordVec);
            int  getRecordCount() const;
            bool getRecord(int i, Trecord& record);
            void closeFile();
            void showAll(int fieldNum);
            
        protected:
            
            std::ifstream  mFileStream;
            std::streampos mFirstRecordPos;
            
            FileHeader mFileHeader;             
            std::vector<FieldDescriptor> mFieldVec;
            //std::vector<Trecord>         mRecordVec;
            
            unsigned int mRecordSize;

        
    };
}

#endif
