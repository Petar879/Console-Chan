
#define _CRT_SECURE_NO_WARNINGS
#include "nlohmann/json.hpp"
#include "ConsoleChanHeader.h"
#include <iostream>
#include <string>
#include <Windows.h>


void DisplayAllBoards()
{
    nlohmann::json jsonData = LoadDataForAllBoards();
    int boardsSize = jsonData["boards"].size();
    for (int i = 0; i < boardsSize; i++)
    {
        std::string boardName = jsonData["boards"][i].value("board", "NOT FOUND");
        std::string titleName = jsonData["boards"][i].value("title", "NOT FOUND");
        std::cout << '/' << boardName << '/' << " - " << titleName << std::endl;
    }
}


void DisplaySpecificBoardThreads(char* boardName, int* currentPageIndex)
{
    system("chcp 65001");
    CleanScrean();
    nlohmann::json boardData = LoadDataFromSpecificBoard(boardName);
    int pagesCount = boardData.size();

    std::cout << *currentPageIndex << std::endl;
    
    std::cout << "Page " << *currentPageIndex + 1 << " out of " << pagesCount << std::endl << std::endl;
    int threadsCount = boardData[*currentPageIndex]["threads"].size();
    std::cout << "------------------------------------------------------" << std::endl;
    for (int y = 0; y < threadsCount; y++)
    {
        std::cout << "[ " << y << " ] ";

        std::string subjectText = boardData[*currentPageIndex]["threads"][y].value("sub", " ");
        std::string subjectComment = boardData[*currentPageIndex]["threads"][y].value("com", "NOT FOUND");

        PerformStringCleaning(subjectText);
        PerformStringCleaning(subjectComment);
        if (subjectText == " ")
        {
            std::cout <<  subjectComment << std::endl;
        }
        else
        {
            std::cout << subjectText << ": " << subjectComment << std::endl;
        }

        std::cout << "------------------------------------------------------" << std::endl;
    }
}

// Overload of DisplaySpecificBoardThreads for viewing the next or previous page
void DisplaySpecificBoardThreads(char* boardName, int* currentPageIndex, char command)
{
    system("chcp 65001");
    CleanScrean();
    nlohmann::json boardData = LoadDataFromSpecificBoard(boardName);
    std::cout << *currentPageIndex << std::endl;
    int pagesCount = boardData.size();
    int tmp = *currentPageIndex;
    if (command == '+')
    {
        if ((tmp + 1) > (pagesCount - 1))
        {
            std::cout << "You've reached the end of the active threads. Use the command \"pp\" to go back" << std::endl;
        }
        else
        {
            (*currentPageIndex)++;
            DisplaySpecificBoardThreads(boardName, currentPageIndex);
        }
    }
    else
    {
        if ((tmp - 1) <= 0)
        {
            std::cout << "There is nothing more, use \"lt\" to display the current page or \"np\" to view next page" << std::endl;
        }
        else
        {
            (*currentPageIndex)--;
            DisplaySpecificBoardThreads(boardName, currentPageIndex);
        }
    }
}

void DisplayCurrentThread(char* boardName, int* pageIndex, char* threadIndex)
{
    system("chcp 65001");
    CleanScrean();
    nlohmann::json boardData = LoadDataFromSpecificBoard(boardName);
    std::string threadIdString = std::to_string(boardData[*pageIndex]["threads"][atoi(threadIndex)]["no"].get<int>());
    char* threadIdCstring = new char[threadIdString.length()];
    strcpy(threadIdCstring, threadIdString.c_str());
    nlohmann::json threadData = LoadDataFromSpecificThread(boardName, threadIdCstring);
    int pagesCount = threadData["posts"].size();
    for (int i = 0; i < pagesCount; i++)
    {
        std::cout << "[ " << i << " ] ";
        std::string threadText = threadData["posts"][i].value("com", "");

        PerformStringCleaning(threadText);
        std::cout << threadData["posts"][i].value("now", "") << std::endl;
        std::cout << threadText << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;
    }
}

void ViewDataFromThread(char* boardName, int* pageIndex, char* threadIndex, char* postIndex)
{
     //Check if OS is supported
    #ifdef _WIN32
        nlohmann::json boardData = LoadDataFromSpecificBoard(boardName);
        std::string threadIdString = std::to_string(boardData[*pageIndex]["threads"][atoi(threadIndex)]["no"].get<int>());
        char* threadIdCstring = new char[threadIdString.length()];
        strcpy(threadIdCstring, threadIdString.c_str());
        nlohmann::json threadData = LoadDataFromSpecificThread(boardName, threadIdCstring);

        // Check if the thread comment exists or if there is media in thread
        if (!threadData["posts"][atoi(postIndex)]["tim"].is_null())
        {
            long long int threadImageId = threadData["posts"][atoi(postIndex)]["tim"];
            std::string threadImageFormat = threadData["posts"][atoi(postIndex)].value("ext", "");
            std::string imageNameAndUrl = std::string(boardName) + '/' + std::to_string(threadImageId) + threadImageFormat;

            std::string imageUrl = "https://i.4cdn.org/" + imageNameAndUrl;
            ShellExecuteA(NULL, "open", imageUrl.c_str(), NULL, NULL, NULL);

        }
        else
        {
            std::cout << "No media on selected thread" << std::endl;
            
        }
    #else
        std::cout << "This command is only for Windows" << std::endl;
    #endif
}

// Function for inputing commands in the main menu(before entering a board)
// If the command is incorrect or changing to board, it will countinue
void MainPageMenuCommands()
{
    CleanScrean();
    bool isCommandSuccessful = false;
    std::string inputValue;

    do
    {
        std::cout << "> ";
        std::getline(std::cin, inputValue, '\n');
    } while (!PerformMainPageCommand(inputValue));
}

// Function for inputing commands when a valid board is selected
// If the command is incorrect or changing to main/thread, it will countinue
void InBoardMenuCommands(char* boardName)
{
    bool isCommandSuccessful = false;
    std::string inputValue;
    do
    {
        std::cout << boardName << "> ";
        std::getline(std::cin, inputValue, '\n');
    } while (!PerformInBoardCommands(boardName, inputValue));
}

// Function for inputing commands when in thread
// If the command is incorrect or changing to main/board, it will countinue
void InThreadMenuCommands(char* boardName, int* pageIndex, char* threadIndex)
{
    bool isCommandSuccessful = false;
    std::string inputValue;
    do
    {
        std::cout << boardName << "\\" << threadIndex << "> ";
        std::getline(std::cin, inputValue, '\n');
    } while (!PerformInThreadCommands(boardName, pageIndex, threadIndex, inputValue));
}

void ViewThreadImage(char* boardName, int* pageIndex, char* threadIndex)
{
    //Check if OS is supported
    #ifdef _WIN32
        nlohmann::json boardData = LoadDataFromSpecificBoard(boardName);
        
        // Check if the thread comment exists or if there is media in thread
        if (!boardData[*pageIndex]["threads"][atoi(threadIndex)]["tim"].is_null())
        {
            long long int threadImageId = boardData[*pageIndex]["threads"][atoi(threadIndex)]["tim"];
            std::string threadImageFormat = boardData[*pageIndex]["threads"][atoi(threadIndex)].value("ext", "");
            std::string imageUrl = "https://i.4cdn.org/" + std::string(boardName) + '/' + std::to_string(threadImageId) + threadImageFormat;
            ShellExecuteA(NULL, "open", imageUrl.c_str(), NULL, NULL, NULL);
        }
        else
        {
            std::cout << "No media on selected thread" << std::endl;

        }
    #else
    std::cout << "This command is only for Windows" << std::endl;
    #endif

   
}

void DisplayMainMenuHelp()
{
    std::cout << std::endl;
    std::cout << "\"lb\": List all boards" << std::endl;
    std::cout << "\"cb [board code]\": Load specific board catalog" << std::endl;
    std::cout << "\"help\": Shows all currently available commands" << std::endl;
    std::cout << std::endl;
}

void DisplayInBoardHelp()
{
    std::cout << std::endl;
    std::cout << "\"lt\": List all threads" << std::endl;
    std::cout << "\"pp\": Load previous page of threads" << std::endl;
    std::cout << "\"np\": Load next page of threads" << std::endl;
    std::cout << "\"ct [thread index]\": Go to specific thread" << std::endl;
    std::cout << "\"ti [thread index]\": (Windows only) Open thread image in browser" << std::endl;
    std::cout << "\"btm\": Back to board select" << std::endl;
    std::cout << "\"help\": Shows all in board commands" << std::endl;
    std::cout << std::endl;
}

void DisplayInThreadHelp()
{
    std::cout << std::endl;
    std::cout << "\"timg\": Load thread image" << std::endl;
    std::cout << "\"ld [board code]\": (Windows only) Loads specific data from thread (img/video)" << std::endl;
    std::cout << "\"btb\": Back to viewing threads" << std::endl;
    std::cout << "\"help\": Shows all main page commands" << std::endl;
    std::cout << std::endl;
}

void CleanScrean()
{
    #ifdef _WIN32
    #define CLEAR "cls"
    #else //In any other OS
    #define CLEAR "clear"
    #endif
    system(CLEAR);
}

