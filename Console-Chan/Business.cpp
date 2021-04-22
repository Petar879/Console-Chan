#define _CRT_SECURE_NO_WARNINGS
#include "ConsoleChanHeader.h"
#include <iostream>

int pageIndex = 0;
int* currentPageIndex = &pageIndex;

// Function for performing the available commands for main page view
bool PerformMainPageCommand(std::string commandAndValue)
{
	char* inputValueCstr = new char[commandAndValue.length() + 1];
	strcpy(inputValueCstr, commandAndValue.c_str());
	char* inputCommand = strtok(inputValueCstr, " ");
	if (std::string(inputCommand) == "lb")
	{
		DisplayAllBoards();
		return false;
	}
	else if (std::string(inputCommand) == "cb")
	{
		inputCommand = strtok(NULL, " ");
		if (inputCommand == NULL)
		{
			std::cout << "Error, cb needs a board code" << std::endl;
		}
		else
		{
			if (isInputBoardCurrect(inputCommand))
			{
				InBoardMenuCommands(inputCommand);
			}
			else
			{
				std::cout << "Board name " << inputCommand << " doesn't exist." << std::endl;
			}
		}
		

		return false;
	}
	else if (std::string(inputCommand) == "help")
	{
		DisplayMainMenuHelp();
		return false;
	}
	else
	{
		std::cout << "Uknokwn command, type \"help\" to view all currently available commands" << std::endl;
		return false;
	}
	delete[] inputValueCstr;
}

// Function for performing the available commands for thread commands
bool PerformInBoardCommands(char* boardName, std::string commandAndValue)
{
	char* inputValueCstr = new char[commandAndValue.length() + 1];
	strcpy(inputValueCstr, commandAndValue.c_str());
	char* inputCommand = strtok(inputValueCstr, " ");

	if (std::string(inputCommand) == "lt")
	{
		DisplaySpecificBoardThreads(boardName, currentPageIndex);
		return false;
	}
	else if (std::string(inputCommand) == "np")
	{
		std::cout << pageIndex << std::endl;
		DisplaySpecificBoardThreads(boardName, currentPageIndex, '+');
		return false;
	}
	else if (std::string(inputCommand) == "pp")
	{
		std::cout << pageIndex << std::endl;
		DisplaySpecificBoardThreads(boardName, currentPageIndex, '-');
		return false;
	}
	else if (std::string(inputCommand) == "ct")
	{
		inputCommand = strtok(NULL, " ");
		DisplayCurrentThread(boardName, currentPageIndex, inputCommand);
		InThreadMenuCommands(boardName, currentPageIndex, inputCommand);
	}
	else if (std::string(inputCommand) == "ti")
	{
		inputCommand = strtok(NULL, " ");
		ViewThreadImage(boardName, currentPageIndex, inputCommand);
		return false;
	}
	else if (std::string(inputCommand) == "btm")
	{
		MainPageMenuCommands();
	}
	else if (std::string(inputCommand) == "help")
	{
		DisplayInBoardHelp();
		return false;
	}
	else
	{
		std::cout << "Uknokwn command, type \"help\" to view all currently available commands" << std::endl;
		return false;
	}
	delete[] inputValueCstr;
}


// Function for performing the available commands for thread commands
bool PerformInThreadCommands(char* boardName, int* currentPageInde,char* threadIndex, std::string commandAndValue)
{
	char* inputValueCstr = new char[commandAndValue.length() + 1];
	strcpy(inputValueCstr, commandAndValue.c_str());
	char* inputCommand = strtok(inputValueCstr, " ");


	if (std::string(inputCommand) == "timg")
	{
		ViewThreadImage(boardName, currentPageIndex, threadIndex);
		return false;
	}
	else if (std::string(inputCommand) == "ld")
	{
		inputCommand = strtok(NULL, " ");
		ViewDataFromThread(boardName, currentPageIndex, threadIndex, inputCommand);
		return false;
	}
	else if (std::string(inputCommand) == "btb")
	{
		InBoardMenuCommands(boardName);
		return false;
	}
	else if (std::string(inputCommand) == "help")
	{
		DisplayInThreadHelp();
		return false;
	}
	else
	{
		std::cout << "Uknokwn command, type \"help\" to view all currently available commands" << std::endl;
		return false;
	}
}

// Function replacing characters in string, used for PerformStringCleaning()
void ReplaceStringCharacters(std::string& source, const std::string& from, const std::string& to)
{
	std::string newString;
	newString.reserve(source.length());  // avoids a few memory allocations

	std::string::size_type lastPos = 0;
	std::string::size_type findPos;
	while (std::string::npos != (findPos = source.find(from, lastPos)))
	{


		newString.append(source, lastPos, findPos - lastPos);
		newString += to;
		lastPos = findPos + from.length();
	}

	// Care for the rest after last occurrence
	newString += source.substr(lastPos);

	source.swap(newString);
}

// Function for enterpreting in console html tags
void PerformStringCleaning(std::string& source)
{
	

	ReplaceStringCharacters(source, "&#039", "'");

	// Apply "quote" look
	ReplaceStringCharacters(source, "<span class=\"quote\">&gt;", "\x1b[0;32 >");
	ReplaceStringCharacters(source, "</span>", "\x1b[0m");

	//Apply bold coloring
	ReplaceStringCharacters(source, "<b>", "\x1b[0;36m");
	ReplaceStringCharacters(source, "</b>", "\x1b[0m");

	//Apply italic coloring
	ReplaceStringCharacters(source, "<i>", "\x1b[1;33m");
	ReplaceStringCharacters(source, "</i>", "\x1b[0m");

	//Handle handle new lines
	ReplaceStringCharacters(source, "<br>\n", "\n");
	ReplaceStringCharacters(source, "<br>", "\n");


}



