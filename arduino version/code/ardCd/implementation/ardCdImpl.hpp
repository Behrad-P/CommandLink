
/**
 * @author  Behrad Pourhadi
 * @email   behradp32@gmail.com
 * @ide     Arduino IDE
 * @brief   arduino-command-decoder implementation (.hpp) 
*/


#ifndef __ARDCDIMPL_HPP__
#define __ARDCDIMPL_HPP__

template<int MAX_CMD_SIZE, int MAX_NUM_SIZE>
bool ardCd<MAX_CMD_SIZE, MAX_NUM_SIZE> :: isNum(String& str) const
{
    if(str == "")
        return false;

    for (char ch : str)
    {
        if (!isDigit(ch))
        {
            return false;
        }
    }

    return true;
}

template<int MAX_CMD_SIZE, int MAX_NUM_SIZE>
ardCd<MAX_CMD_SIZE, MAX_NUM_SIZE> :: ardCd()
{
    decodedCmdIt = 0;
    decodedNumIt = 0;
    memoryStatus = true;

    for(int it = 0; it < MAX_CMD_SIZE; it++)
    {
        cmdLen[it] = 0;

        if(baseCommand[it] != nullptr)
        {
            delete [] baseCommand[it];
            baseCommand[it] = nullptr;
        }	
    }
    
    if(decodedCmd != nullptr)
    {
        delete [] decodedCmd;
        decodedCmd = nullptr;
    }

    if(decodedNum != nullptr)
    {
        delete [] decodedNum;
        decodedNum = nullptr;
    }

    decodedCmd = new int[MAX_CMD_SIZE];
    decodedNum = new int[MAX_NUM_SIZE];

    if(decodedCmd == nullptr || decodedNum == nullptr)
        memoryStatus = false;
}

template<int MAX_CMD_SIZE, int MAX_NUM_SIZE>
bool ardCd<MAX_CMD_SIZE, MAX_NUM_SIZE> :: decode(String inputStr, const char sepChar, const char assignmentChar)
{

String temp = "";
int assignmentFlag = 0, cmdNum = 0; 
int inputStrLen = 0;

    if(memoryStatus == false)
        return false;
        
    decodedCmdIt = 0;
    decodedNumIt = 0;
    inputStr += sepChar;
    inputStrLen = inputStr.length();

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
                    temp += "NaN";
            }
        }

        else if(it == 0 || (it > 0 && inputStr[it - 1] == sepChar))
            continue;

        else
        {
            if(assignmentFlag == 0)
            {	
                if(decodedCmdIt < MAX_CMD_SIZE)
                {
                    while(cmdNum < cmdLen[decodedCmdIt])
                    {
                        if(baseCommand[decodedCmdIt][cmdNum] == temp)
                        {
                            decodedCmd[decodedCmdIt] = cmdNum;
                            break;
                        }
                        cmdNum++;
                    }

                    if(cmdNum == cmdLen[decodedCmdIt])
                        decodedCmd[decodedCmdIt] = NP;
                        
                    cmdNum = 0;
                    decodedCmdIt++;
                }	
            }

            else
            {
                if(decodedNumIt < MAX_NUM_SIZE)
                {
                    if(isNum(temp) == false)
                        decodedNum[decodedNumIt] = NaN;

                    else
                        decodedNum[decodedNumIt] = temp.toInt();
                    
                    decodedNumIt++;
                }
            }

            temp = ""; 
        }   
    } 

    return true;
}

template<int MAX_CMD_SIZE, int MAX_NUM_SIZE>
String ardCd<MAX_CMD_SIZE, MAX_NUM_SIZE> :: addBaseCmd(const String baseCmd[], const size_t size, const int idx)
{
    if(idx >= MAX_CMD_SIZE || idx < 0)
        return "Index out of bounds!";
    
    cmdLen[idx] = size;

    if(baseCommand[idx] != nullptr)
    {
        delete [] baseCommand[idx];
        baseCommand[idx] = nullptr;
    }

    baseCommand[idx] = new String[size];

    if(baseCommand[idx] == nullptr)
    {
        memoryStatus = false;
        return "Memory allocation failed!";
    }

    for(int it = 0; it < size; it++)
    {
        baseCommand[idx][it] = baseCmd[it];
    }

    return "Ok";
}

#endif /*__ARDCDIMPL_HPP__*/
