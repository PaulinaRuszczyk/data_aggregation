#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "CRequest.h"
#include "CDataBase.h"

#include <aws/core/utils/Outcome.h>
#include <aws/core/utils/logging/AWSLogging.h>

#include <aws/dynamodb/model/GetItemRequest.h>
#include <aws/dynamodb/model/PutItemRequest.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/dynamodb/model/ScanRequest.h>

int main() {

    CDataBase *dataBase;
    try {
        dataBase = new CDataBase();
        std::vector<std::string> vIds = dataBase->GetIds();

        int i = dataBase->GetHighestLp();

        for (const auto &vId: vIds) {
            Aws::DynamoDB::Model::PutItemRequest putItemRequest;
            putItemRequest.SetTableName("quantities");  // Replace with your table name
            putItemRequest.AddItem("lp", Aws::DynamoDB::Model::AttributeValue().SetS(std::to_string(i)));
            putItemRequest.AddItem("id", Aws::DynamoDB::Model::AttributeValue().SetS(vId));

            if (CRequest::retriveData(vId) == NULL)
                putItemRequest.AddItem("quantity", Aws::DynamoDB::Model::AttributeValue().SetS("NULL"));
            else
                putItemRequest.AddItem("quantity", Aws::DynamoDB::Model::AttributeValue().SetS(
                        std::to_string(CRequest::retriveData(vId))));

            std::time_t currentTime = std::time(nullptr);
            putItemRequest.AddItem("date", Aws::DynamoDB::Model::AttributeValue().SetS(std::to_string(currentTime)));

            const Aws::DynamoDB::Model::PutItemOutcome outcome = dataBase->m_dynamoClient->PutItem(putItemRequest);
            i++;

            if (outcome.IsSuccess()) {
                std::cout << "Successfully added Item!" << std::endl;
            } else {
                std::cerr << "Failed to add item: " << outcome.GetError().GetMessage() << std::endl;
            }
        }
    }catch (std::runtime_error& e) {
        std::cout << e.what();
         }

    return 0;
}