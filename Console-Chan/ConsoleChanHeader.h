#include "nlohmann/json.hpp"
#ifndef _ConsoleChanHeader
#define _ConsoleChanHeader

//================ UI =====================
void DisplayAllBoards();
void DisplayMainMenuHelp();
void DisplayInBoardHelp();
void DisplayInThreadHelp();
void DisplaySpecificBoardThreads(char* boardName, int* currentPageIndex);
void DisplaySpecificBoardThreads(char* boardName, int* currentPageIndex, char command);
void DisplayCurrentThread(char* boardName, int* pageIndex, char* threadIndex);
void CleanScrean();
void MainPageMenuCommands();
void InBoardMenuCommands(char* boardName);
void InThreadMenuCommands(char* boardName, int* pageIndex, char* threadIndex);
void ViewThreadImage(char* boardName, int* pageIndex, char* threadIndex);
void ViewDataFromThread(char* boardName, int* pageIndex, char* threadIndex, char* postIndex);
//=========================================


//================ Business ===============
void PerformStringCleaning(std::string& source);
void ReplaceStringCharacters(std::string& source, const std::string& from, const std::string& to);
bool PerformMainPageCommand(std::string commandAndValue);
bool PerformInBoardCommands(char* boardName, std::string commandAndValue);
bool PerformInThreadCommands(char* boardName, int* pageIndex, char* threadIndex, std::string commandAndValue);
//=========================================


//================ Data ===================
bool isInputBoardCurrect(char* inputName);
nlohmann::json LoadDataForAllBoards();
nlohmann::json LoadDataFromSpecificBoard(char* boardName);
nlohmann::json LoadDataFromSpecificThread(char* boardName, char* threadId);
//=========================================
#endif