# Console-Chan

A simple console HTTP client for the site [4chan](https://4chan.org/) written in C++ and using the [read-only API](https://github.com/4chan/4chan-API)

External libraries used in the project:
- [OpenSSL](https://github.com/openssl/openssl)
- [cpp-httplib](https://github.com/yhirose/cpp-httplib)
- [nlohmann json](https://github.com/nlohmann/json) 


# List of commands

- **\[board code]** - Every board is represented by a specific code. For example: **po**(Papercraft & Origami), **a**(Anime & Manga), **v**(Video Games).
- **\[thread id]** - When a command for displaying threads is used (such as: lt, pp, np) the thread id can be found between square brackets.
- **\[response id]** - When a thread is displayed, the id of the response can be found between square brackets.

|**IN MAIN PAGE COMMANDS**| | |
|:-------------------|:-------------------|:-------------------|
| **Command name**   | **Description**      |*Use in program*|
|:-------------------|:---------------------|:---------------|
|lb			    |List all boards															|lb				 |
|cb		        |Load the specific board catalog											|cb \[board code]| 
|help		    |Shows all currently available commands										|help			 |
|**IN BOARD COMMANDS**|
|lt				|List all threads															|lt				 |
|np				|Load next page of threads													|np				 |
|pp				|Load previous page of threads												|pp				 |
|ct				|Go to specific thread														|ct [thread id]	 |
|ti				|**(Windows only)** Open thread image in browser							|ti[thread id]   |
|btm			|Back to board select														|btm			 |
|help		    |Shows all currently available commands										|help			 |
|**IN THREAD COMMANDS**|
|timg			|**(Windows only)** Load thread image										|timg			 |
|ld				|**(Windows only)** Loads specific data from thread (image, video and etc)	|ld [response id]|	
|btb			|Back to viewing threads													|btb			 |
|help		    |Shows all currently available commands										|help			 |
