

#include <iostream>
#include <DatabaseDbf/Database.h>




//typedef std::map<std::string, std::string> Trecord;



//vector<SDbfFieldDescriptor> fieldVec;

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
        
        DatabaseDbf::Database dbase;
        if (dbase.openFile(argv[1]))
        {
            dbase.showAll(3);
            dbase.closeFile();
            
        }
        /*
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
             int recordLength = 0;
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
                        
                    recordLength += (int) dbffielddesc->mFieldLength;                                                            
                    fieldVec.push_back(*dbffielddesc);                    
                }
             }
             
             cout << "mNumRecords=" << dbfheader.mNumRecords << endl;
             cout << "recordLength=" << recordLength << " bytes" << endl;
             
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
        */
    }
    
    return 0;
}

