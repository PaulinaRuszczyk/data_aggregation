//
// Created by pulinka on 8/13/23.
//

#include <stdexcept>
#include <memory>
#include "CRequest.h"

int CRequest::retriveData(const std::string& identNumber){
    std::array<char, 128> buffer;
    std::string respond;
    std::string request="curl --request GET \\\n"
                        "  --url 'https://api.kingfisher.com/v1/mobile/stores/CAPL?filter%5Bean%5D="+identNumber+"&include=clickAndCollect%2Cstock&nearLatLong=52.172491%2C20.938261&page%5Bsize%5D=250' \\\n"
                                                                                                                 "  --header 'Authorization: Atmosphere atmosphere_app_id=kingfisher-EPgbIZbIpBzipu0bKltAFm1xler30LKmaF4vJH96' \\\n"
                                                                                                                 "  --cookie TS013aa2d6=011543659bd97db54671d1c15d5964995a47f65b2da76e8bde4826be936131024db94babdd19594c36ce3693a4e28e6f7f9efd33af";

    //std::string request="curl GET --url \"https://www.castorama.pl/cataloginventory/index/checkAvailabilityInStores?qty=1&sku="+std::to_string(identNumber)+"\"";

    std::unique_ptr<FILE, decltype(&pclose)> pipe(
            popen(request.c_str(), "r"), pclose);

    if (pipe)
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
            respond += buffer.data();
    else
        throw std::runtime_error("popen() failed!");

    int quantity=0;
    std::size_t found =respond.find("quantity");

    while(found!=std::string::npos)
    {
        respond=respond.substr(found+10,respond.size());
        quantity+=std::stoi(respond.substr(0,respond.find('}')));
        found =respond.find("quantity");
    }
    return quantity;
}