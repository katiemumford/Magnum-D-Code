/*/////INFORMATION/////
-this is where you declare functions used in driveBaseControl.cpp
-within driveBaseControl.cpp, there is an int called pct set to 5 to account for stick shift and "setDrive"
 
when you have a function that you only use within its OWN file (such as setDrive here) you do NOT have to declare it here
anything the main doesn't directly touch doesn't need to be defined (ints as well)

*note within driveBaseControl.cpp there is an int for pct and setDrive function
*/

int allowDriveForUser();