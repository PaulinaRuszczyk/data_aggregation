#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "CRequest.h"
#include "CDataBase.h"

int main() {
    CRequest request;

    CDataBase DB("/home/pulinka/Desktop/cpp/Castorama/itemki.db");
    std::vector<std::string> vIds;

    try {
        vIds = DB.GetIds("SELECT * FROM names;");
    }
    catch (std::runtime_error &e) {
        std::cout << "Insert error: " << e.what();
    }

    for (const auto & vId : vIds) {
        std::string sql_insert;
        if(request.retriveData(vId)!=NULL)
            sql_insert = "INSERT INTO quantity(id, quantity, date) VALUES (" + vId + ", " +
                                 std::to_string(request.retriveData(vId)) + ", strftime ('%s', 'now'));";
        else
            sql_insert = "INSERT INTO quantity(id, quantity, date) VALUES (" + vId + ", NULL,  strftime ('%s', 'now'));";

        DB.InsertData(sql_insert.c_str());
        std::cout << "id " << vId << " quantity " << request.retriveData(vId) << std::endl;
    }
}