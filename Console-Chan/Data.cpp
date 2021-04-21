#define CPPHTTPLIB_OPENSSL_SUPPORT

#include "nlohmann/json.hpp"

#include "httplib.h"
#include "ConsoleChanHeader.h"
httplib::Client FourChanAPI("https://a.4cdn.org");

//#define _TESTING_APP

//Returns board list in JSON format
nlohmann::json LoadDataForAllBoards()
{
    
    auto res = FourChanAPI.Get("/boards.json");
    nlohmann::json j_complete =  nlohmann::json::parse(res->body);

    #ifdef _TESTING_APP
        std::cout << res->status << std::endl;
    #endif

    return j_complete;
}


// Return board threads list in JSON format
nlohmann::json LoadDataFromSpecificBoard(char* boardName)
{
    //https://a.4cdn.org/{board name}/catalog.json
    std::string apiResponseString = "/" + std::string(boardName) + "/catalog.json";
    const char* charApiResponseString = apiResponseString.c_str();
    auto res = FourChanAPI.Get(charApiResponseString);
    nlohmann::json j_complete = nlohmann::json::parse(res->body);

    #ifdef _TESTING_APP
        std::cout << res->status << std::endl;
    #endif

    return j_complete;
}

// Returns a selected thread in JSON format
nlohmann::json LoadDataFromSpecificThread(char* boardName ,char* threadId)
{
    //https://a.4cdn.org/po/thread/570368.json
    std::string apiResponseString = "/" + std::string(boardName) + "/thread/" + std::string(threadId) + ".json";
    const char* charApiResponseString = apiResponseString.c_str();
    auto res = FourChanAPI.Get(charApiResponseString);
    nlohmann::json j_complete = nlohmann::json::parse(res->body);

    #ifdef _TESTING_APP
        std::cout << res->status << std::endl;
    #endif

    return j_complete;
}

// Function for checking if the user inputted board is available
bool isInputBoardCurrect(char* inputName)
{
    std::string apiResponseString = "/" + std::string(inputName) + "/catalog.json";
    const char* charApiResponseString = apiResponseString.c_str();
    auto res = FourChanAPI.Get(charApiResponseString);
    
    if (res->status == 404)
    {
        return false;
    }

    return true;
}
