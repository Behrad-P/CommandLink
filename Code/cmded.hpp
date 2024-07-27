
/**
 * @author  Behrad Pourhadi
 * @email   behradp32@gmail.com
 * @ide     Visual Studio Code
 * @brief   command-encoder-decoder (.hpp) 
*/


#ifndef __CMDED_HPP__
#define __CMDED_HPP__

#include <vector>
#include <string>

// command-encoder-decoder class 
class ced
{

private:

std :: vector<std :: vector<std :: string> > commandVec;
std :: vector<int> cmdlenVec;
std :: vector<int> decodedNumVec;
std :: vector<int> decodedCmdVec;

    /**
     * @brief  Check whether the string is numeric or not.
     * @param  str: Input string.
     * @retval 0: The string is not numeric.
     * @retval 1: The string is numeric.
     */
    bool isNum(std::string& str);
    
    public:
    
    // NOT PRESENT
    static const int NP = -1;
    // NOT A NUMBER
    static const int NAN = -2;
    
    /**
     * @brief  Parameterized constructor.
     * @param  cmdVec: Base Commands vector.
     * @retval None.
     */
    ced(const std::vector<std::vector<std::string>>& cmdVec);
    
    /**
     * @brief  Convert the input string to the number (index) of the base commands.
     * @param  inputStr: Input string.
     * @param  sepChar: Separator character, default: ' ' (There must be at least one separator character between each command and number).
     * @param  assignmentChar: Assignment character, default: '=' (Only numbers should be placed after this character with a separator character).
     * @retval None.
     */
    void decode(std::string inputStr, const char sepChar = ' ', const char assignmentChar = '=');
    
    /**
     * @brief  Convert the number (index) of input vector (eCmdVec) to a string of the base commands and concatenate it with given numbers (eNumVec).
     * @param  eCmdVec: Encode command vector.
     * @param  eNumVec: Encode number vector.
     * @param  sepChar: Separator character, default: ' ' (It is placed between each command and number).
     * @param  assignmentChar: Assignment character, default: '=' (It is placed between commands and numbers).
     * @retval "Cannot be encoded!": if there is an error.
     * @retval "Encoded command": if there is no error.
     */
    std::string encode(std::vector<int>& eCmdVec, std::vector<int>& eNumVec, const char sepChar = ' ', const char assignmentChar = '=') const;
    
    /**
     * @brief  Get the number (index) of the decoded commands.
     * @param  idx: Index of decoded commands.
     * @retval -1 (ced::NP): If not present.
     * @retval Index of the decoded command: If present.
     */
    inline int getCmd(const int idx) const
    {
        if (idx >= decodedCmdVec.size())
            return NP;
    
        return decodedCmdVec.at(idx);
    }
    
    /**
     * @brief  Get the given numbers.
     * @param  idx: Index of the given number to read.
     * @retval -1 (ced::NP): If not present.
     * @retval -2 (ced::NAN): If it is not numeric.
     * @retval Given number: If present and it is numeric.
     */
    inline int getNum(const int idx) const
    {
        if (idx >= decodedNumVec.size())
            return NP;
    
        return decodedNumVec.at(idx);
    }
    
    /**
     * @brief  Get the number of base commands.
     * @param  idx: Index of commands vector.
     * @retval -1 (ced::NP): If not present.
     * @retval Number of base commands: If present.
     */
    inline int getCmdSize(const int idx) const
    {
        if (idx >= cmdlenVec.size())
            return NP;
    
        return cmdlenVec.at(idx);
    }	
    
    /**
     * @brief  Get the number of decoded commands.
     * @param  None.
     * @retval Number of decoded commands.
     */
    inline int cmdAvailable() const
    {
        return decodedCmdVec.size();
    }	
    
    /**
     * @brief  Get the number of given numbers.
     * @param  None.
     * @retval Number of given numbers.
     */
    inline int numAvailable() const
    {
        return decodedNumVec.size();
    }


}; /* CED class */

#endif /* __CMDED_HPP__ */
