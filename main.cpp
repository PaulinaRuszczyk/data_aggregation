#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
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
        std::unique_ptr<FILE, decltype(&pclose)> pipe(
                popen("curl GET --url \"https://www.castorama.pl/cataloginventory/index/checkAvailabilityInStores?qty=1&sku=319742\"", "r"), pclose);
        if (pipe)
            while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
                result += buffer.data();
        else
            throw std::runtime_error("popen() failed!");
        return result;
    }

};
int main()
{
    CRequest request;
    rapidjson::Document document;
    document.Parse(request.retriveData(1).c_str());
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    // Open the database
    rc = sqlite3_open("itemki.db", &db);

    if (rc) {
        std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }

  const char *sql_insert = "INSERT INTO users (id, name) VALUES ('John', 30);";

    rc = sqlite3_exec(db, sql_insert, 0, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        std::cout << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Record inserted successfully" << std::endl;
    }

    // Close the database
    sqlite3_close(db);
}
//TODO baza danych z rzeczami do wypelnienia tzn spraqwdzenia
//TODO pobieranie z bazy danych
//