#include <fstream>
#include <aws/dynamodb/model/ScanRequest.h>
#include "CDataBase.h"

#include <stdexcept>
#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h>
#include <aws/core/utils/logging/AWSLogging.h>

#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/core/client/ClientConfiguration.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <filesystem>


CDataBase::CDataBase()
{
    std::pair <std::string, std::string> keys =getCredentials();
    Aws::Auth::AWSCredentials credentials(keys.first, keys.second);
    Aws::InitAPI( m_options);
    Aws::Client::ClientConfiguration clientConfiguration;
    clientConfiguration.region = "eu-north-1";// Change to your desired region
    m_dynamoClient=new Aws::DynamoDB::DynamoDBClient(credentials, clientConfiguration);
}

CDataBase::~CDataBase() {
    Aws::ShutdownAPI( m_options);
}

std::pair<std::string, std::string> CDataBase::getCredentials(){

    std::filesystem::path currentDir = std::filesystem::current_path();
    std::filesystem::path filePath = currentDir / "Credentials.env";
    std::ifstream credentialsFile(filePath);
    std::string keys;
    if(!credentialsFile.is_open())
        throw  std::runtime_error("Cannot find credentials file. ");
    getline (credentialsFile, keys);
    std::string accessKey= keys.substr(keys.find("accessKeyId:")+12, keys.find('\n'));

    getline (credentialsFile, keys);
    std::string secretKey= keys.substr(keys.find("secretKey:")+10, keys.find('\n'));
    return std::make_pair(accessKey, secretKey);
};

std::vector<std::string> CDataBase::GetIds(){
    std::vector <std::string> vIds;
    Aws::DynamoDB::Model::ScanRequest scanRequest;
    scanRequest.SetTableName("names");
    const Aws::DynamoDB::Model::ScanOutcome& outcome = m_dynamoClient->Scan(scanRequest);

    if (outcome.IsSuccess()) {
        const auto& items = outcome.GetResult().GetItems();

        for (const auto& item : items) {
            auto nameValue = item.find("id");
            if (nameValue != item.end())
                vIds.push_back(nameValue->second.GetS());
        }
    } else {
        throw std::runtime_error("Unable to connect to Data Base. Try again later!"+outcome.GetError().GetMessage());
    }
    return vIds;
}
int CDataBase::GetHighestLp() {
    Aws::DynamoDB::Model::ScanRequest scanQuantityRequest;
    scanQuantityRequest.SetTableName("test");

    int i;
    const Aws::DynamoDB::Model::ScanOutcome& outcomeOfQuantity = m_dynamoClient->Scan(scanQuantityRequest);
    if (outcomeOfQuantity.IsSuccess()) {
        const auto& items = outcomeOfQuantity.GetResult().GetItems();
        std::vector<int> lp;
        for (const auto& item : items) {
            auto nameValue = item.find("lp");
            if (nameValue != item.end())
                lp.push_back(std::stoi(nameValue->second.GetS().c_str()));
        }
        lp.empty() ?  i=0 : i = *max_element(std::begin(lp), std::end(lp))+1;
    } else {
        throw std::runtime_error("Unable to connect to Data Base. Try again later!"+outcomeOfQuantity.GetError().GetMessage());    }
    return i;
}