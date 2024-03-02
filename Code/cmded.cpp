
/**
 * @author  Behrad Pourhadi
 * @email   behradp32@gmail.com
 * @ide     Visual Studio Code
 * @brief   command-encoder-decoder (.cpp) 
*/


#include <ctype.h>
#include "cmded.hpp"

static const int np = -1;
static const int nan = -2;

bool ced :: isNum(std :: string& str)
{
    if(str.empty() == true)
        return false;

    for (char ch : str)
    {
        if (!isdigit(ch))
        {
            return false;
        }
    }

    return true;
}

ced :: ced(const std :: vector<std :: vector<std :: string> >& cmdVec) : commandVec(cmdVec)
{
    for(int it = 0; it < cmdVec.size(); it++)
        cmdlenVec.push_back(cmdVec[it].size());
}

void ced :: decode(std :: string inputStr, const char sepChar, const char assignmentChar)
{
    
std :: string temp = "";
int assignmentFlag = 0, cmdIt = 0, cmdNum = 0; 
size_t inputStrLen = 0;

    inputStr += sepChar;
    inputStrLen = inputStr.size();

    for(int it = 0; it < inputStrLen; it++)
    {
        if(inputStr[it] != sepChar)
        {
            if(inputStr[it] != assignmentChar)
                temp += inputStr[it];
            else
            {
                assignmentFlag = 1;
                it++;
                if(inputStr[it] != sepChar)
                    temp += "NAN";
            }
        }
        else if(it == 0 || (it > 0 && inputStr[it - 1] == sepChar))
            continue;

        else
        {
            if(assignmentFlag == 0)
            {	
                if(cmdIt < commandVec.size())
                {
                    for(std :: string& str : commandVec[cmdIt])
                    {
                        if(str == temp)
                        {
                            decodedCmdVec.push_back(cmdNum);
                            break;
                        }
                        cmdNum++;
                    }

                    if(cmdNum == cmdlenVec[cmdIt])
                        decodedCmdVec.push_back(np);
                        
                    cmdNum = 0;
                    cmdIt++;
                }
            }
            
            else
            {
                if(isNum(temp) == false)
                    decodedNumVec.push_back(nan);
                    
                else
                    decodedNumVec.push_back(stoi(temp));
            }

            temp.clear();  
        }   
    }   
}

std :: string ced :: encode(std :: vector<int>& eCmdVec, std :: vector<int>& eNumVec, const char sepChar, const char assignmentChar) const
{

std :: string temp = "";
int eCmdVecSize = eCmdVec.size();
int eNumVecSize = eNumVec.size();

    if(eCmdVec.size() > commandVec.size())
        return "Can not be encoded!";

    for(int it = 0; it < eCmdVecSize; it++)
    {
        temp += commandVec[it].at(eCmdVec[it]);
        temp += sepChar;
    }

    temp += assignmentChar;
    temp += sepChar;

    for(int it = 0; it < eNumVecSize; it++)
    {
        temp += std :: to_string(eNumVec[it]);
        temp += sepChar;
    }

    return temp;
}



