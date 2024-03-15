
/**
 * @author  Behrad Pourhadi
 * @email   behradp32@gmail.com
 * @ide     Arduino IDE
 * @brief   arduino-command-decoder (.hpp) 
*/


#ifndef __ARDCD_HPP__
#define __ARDCD_HPP__

template<int MAX_CMD_SIZE, int MAX_NUM_SIZE>
// arduino-command-decoder class
class ardCd
{

private:

String *baseCommand[MAX_CMD_SIZE];
int *decodedCmd, *decodedNum;
int decodedCmdIt, decodedNumIt;
int cmdLen[MAX_CMD_SIZE];
bool memoryStatus; 

    /**
     * @brief  Check whether the string is numeric or not
     * @param  str: Input string
     * @retval 0: The string is not numeric
     * @retval 1: The string is numeric
     */
    bool isNum(String& str) const;

public:

// NOT PRESENT
static const int NP = -1;
// NOT a NUMBER
static const int NaN = -2;

    /**
     * @brief  Constructor 
     * @param  None
     * @retval None
     */
    ardCd();

    /**
     * @brief  Destructor  
     * @param  None
     * @retval None
     */
    ~ardCd();

    /**
     * @brief  Convert the input string to the number (index) of the base commands
     * @param  inputStr: Input string 
     * @param  sepChar: Separator character, default: ' ' (There must be at least one separator character between each commands and numbers)
     * @param  assignmentChar: Assignment character, default: '=' (Only numbers should be placed after this character(with separator character))
     * @retval 0: If there is a problem with memory allocation
     * @retval 1: If there is no problem
     */
    bool decode(String inputStr, const char sepChar = ' ', const char assignmentChar = '=');

    /**
     * @brief  Add or replace base command
     * @param  baseCmd: An array of base commands
     * @param  size: Number of base commands
     * @param  idx: The number or index of the base command array where new commands will be stored. (it starts from 0)
     * @retval "Memory allocation was successful": If there is no problem
     * @retval "Index out of bounds!": If Index is out of bounds
     * @retval "Memory allocation failed!": If there is a problem with memory allocation
     */
    String addBaseCmd(const String baseCmd[], const size_t size, const int idx);

    /**
     * @brief  Get the number (index) of the decoded commands
     * @param  idx: Index of decoded commads
     * @retval -1 (ardCd<MAX_CMD_SIZE, MAX_NUM_SIZE> :: NP): If not present
     * @retval Index of the decoded command: If present
     */
    inline int getCmd(const int idx) const
    {
        if(idx >= decodedCmdIt || idx < 0)
            return NP;

        return decodedCmd[idx];
    }

    /**
     * @brief  Get the  given numbers
     * @param  idx: Index of the given number to read
     * @retval -1 (ardCd<MAX_CMD_SIZE, MAX_NUM_SIZE> :: NP): If not present
     * @retval -2 (ardCd<MAX_CMD_SIZE, MAX_NUM_SIZE> :: NaN): If it is not numeric
     * @retval Given number: If present and it is numeric
     */
    inline int getNum(const int idx) const
    {
        if(idx >= decodedNumIt || idx < 0)
            return NP;

        return decodedNum[idx];
    }

    /**
     * @brief  Get the number of decoded commands  
     * @param  None
     * @retval Number of decoded commands ( <= MAX_CMD_SIZE)
     */
    inline int cmdAvailable() const
    {
        return decodedCmdIt;
    }	

    /**
     * @brief  Get the number of given numbers
     * @param  None
     * @retval Number of given numbers ( <= MAX_NUM_SIZE)
     */
    inline int numAvailable() const
    {
        return decodedNumIt;
    }

    /**
     * @brief  Get the memory status
     * @param  None
     * @retval 0: If there is a problem with memory allocation
     * @retval 1: If there is no problem
     */
    inline bool memStatus() const
    {
        return memoryStatus;
    }

}; /* ardCd class */

#include "implementation/ardCdImpl.hpp"

#endif /* __ARDCD_HPP__ */

