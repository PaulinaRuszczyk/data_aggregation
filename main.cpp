#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <vector>
#include "sqlite3.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <stdio.h>

class CRequest{
public:
    std::string retriveData(int identNumber){
        std::array<char, 128> buffer;
        std::string result;
        std::string request="curl GET --url \"https://www.castorama.pl/cataloginventory/index/checkAvailabilityInStores?qty=1&sku="+std::to_string(identNumber)+"\"";
        std::unique_ptr<FILE, decltype(&pclose)> pipe(
                popen(request.c_str(), "r"), pclose);
        if (pipe)
            while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
                result += buffer.data();
        else
            throw std::runtime_error("popen() failed!");
        return result;
    }

};

class CDataBase{
    std::string m_sDataBaseName;
    sqlite3 *m_Database;
public:
    CDataBase(std::string DBname):
            m_sDataBaseName(DBname)
    {
        int rc;

        rc = sqlite3_open(m_sDataBaseName.c_str(), &m_Database);

        if (rc) {
            sqlite3_close(m_Database);
            throw std::runtime_error("Database Open failed!");
        }
    }

    ~CDataBase() {
        sqlite3_close(m_Database);
    }

    void InsertData(const char *sql_insert){
        int rc;
        char *zErrMsg = 0;
        rc = sqlite3_exec(m_Database, sql_insert, 0, 0, &zErrMsg);

        if (rc != SQLITE_OK) {
            sqlite3_free(zErrMsg);
            throw std::runtime_error("SQL error: " + std::string(zErrMsg));
        } else {
            std::cout << "Record inserted successfully" << std::endl;
        }

    }

   std::string GetData(const char *sql_select){
        int rc;
        char *zErrMsg = 0;
        std::string result;

        rc = sqlite3_exec(m_Database, sql_select, [](void *data, int argc, char **argv, char **azColName) -> int {
            std::string * result = static_cast<std::string *>(data);
            std::vector<std::string> temp;
            for(int i = 0; i < argc; i++) {
                *result += azColName[i];
                *result += ": ";
                *result += argv[i] ? argv[i] : "NULL";
                *result += "\n";
            }
            std::cout<<result;
            return 0;
        }, &result, &zErrMsg);

        if (rc != SQLITE_OK) {
            sqlite3_free(zErrMsg);
            throw std::runtime_error("SQL error: "+std::string(zErrMsg));
        }

        return result;
    }

private:  void getListwaId(std::string result){
        std::vector<std::string> temp;
        std::vector<std::vector<std::string>> listwyId;
      //  while(result.find())

    }
};

int main()
{
    CRequest request;
    rapidjson::Document document;
    const char *sql_insert = "SELECT * FROM users;";

    CDataBase DB("itemki.db");
    try{
        DB.GetData(sql_insert);
    }
    catch(std::runtime_error & e) {
        std::cout << "Insert error: " << e.what();
    }

    try{
        document.Parse(request.retriveData(1).c_str());
    }
    catch(std::runtime_error & e){
        std::cout << "Runtime error: " << e.what() << std::endl;
    }


}
//TODO baza danych z rzeczami do wypelnienia tzn spraqwdzenia
//TODO pobieranie z bazy danych
//