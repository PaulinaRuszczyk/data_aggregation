#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "CRequest.h"
#include "CDataBase.h"

int main() {
    CRequest request;

    CDataBase DB("../itemki.db");
    std::vector<std::string> vIds;

    try {
        vIds = DB.GetIds("SELECT * FROM names;");
    }
    catch (std::runtime_error &e) {
        std::cout << "Insert error: " << e.what();
    }

    for (const auto & vId : vIds) {
        std::string sql_insert = "INSERT INTO quantity(id, quantity, date) VALUES (" + vId + ", " +
                                 std::to_string(request.retriveData(vId)) + ", strftime ('%s', 'now'));";
        DB.InsertData(sql_insert.c_str());
        std::cout << "id " << vId << " quantity " << request.retriveData(vId) << std::endl;
    }
/*
    try{
        document.Parse<0>(request.retriveData(vIds[0]).c_str()).HasParseError();
        if (doc.Parse(sssss.c_str()).HasParseError() || !doc.IsObject() || !doc.HasMember("Response") || !doc["Response"].IsString())
        {
            return 0;
        }
       // document["quantity"].GetInt();
        assert(document.HasMember("quantity"));
        for (auto i = 0; i < document["quantity"].Size(); ++i)
        {
            std::cout << "port"<<i<<" = " << document["quantity"][i].GetUint() << std::endl;
        }
    }
    catch(std::runtime_error & e){
        std::cout << "Runtime error: " << e.what() << std::endl;
    }
*/

}