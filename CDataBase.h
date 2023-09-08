//
// Created by pulinka on 8/13/23.
//

#ifndef CASTORAMA_CDATABASE_H
#define CASTORAMA_CDATABASE_H

#include <iostream>
#include <vector>
#include <aws/core/Aws.h>
#include <aws/dynamodb/DynamoDBClient.h>


class CDataBase{
    Aws::SDKOptions m_options;
    static std::pair<std::string, std::string> getCredentials();
public:
    Aws::DynamoDB::DynamoDBClient *m_dynamoClient;

    CDataBase();
    ~CDataBase();

    std::vector<std::string> GetIds();
    int GetHighestLp();

};



#endif //CASTORAMA_CDATABASE_H
