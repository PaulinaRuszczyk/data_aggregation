//
// Created by pulinka on 8/13/23.
//

#ifndef CASTORAMA_CDATABASE_H
#define CASTORAMA_CDATABASE_H

#include <iostream>
#include <vector>
#include "sqlite3.h"


class CDataBase{
    std::string m_sDataBaseName;
    sqlite3 *m_Database;
public:
    CDataBase(std::string DBname);

    ~CDataBase() {
        sqlite3_close(m_Database);
    }

    void InsertData(const char *sql_insert);

    std::vector<std::string> GetIds(const char *sql_select);

private:
};



#endif //CASTORAMA_CDATABASE_H
