//
// Created by pulinka on 8/13/23.
//

#include "CDataBase.h"

CDataBase::CDataBase(std::string DBname):
        m_sDataBaseName(std::move(DBname))
{
    int rc;
    rc = sqlite3_open(m_sDataBaseName.c_str(), &m_Database);
    if (rc) {
        sqlite3_close(m_Database);
        throw std::runtime_error("Database Open failed!");
    }
}
void CDataBase::InsertData(const char *sql_insert){
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

std::vector<std::string> CDataBase::GetIds(const char *sql_select){
    int rc;
    char *zErrMsg = 0;
    std::string result;
    std::vector<std::string> words;
    rc = sqlite3_exec(m_Database, sql_select, [](void *data, int argc, char **argv, char **azColName) -> int {
        auto* result = static_cast<std::string *>(data);
        std::vector<std::string> temp;
        for(int i = 0; i < argc; i++) {
            if(std::string(azColName[i])=="id") {
                *result += argv[i];
                *result += "\n";
            }
        }
        return 0;
    }, &result, &zErrMsg);

    if (rc != SQLITE_OK) {
        sqlite3_free(zErrMsg);
        throw std::runtime_error("SQL error: "+std::string(zErrMsg));
    }

    while(result.find( '\n')!=std::string::npos){
        std::string tmp= result.substr(0, result.find('\n'));
        words.push_back( tmp);
        result.replace(0,result.find('\n')+1,"");
    }

    return words;
}
