
/**
 * @author  Behrad Pourhadi
 * @email   behradp32@gmail.com
 * @ide     Visual Studio Code
 * @brief   command-encoder-decoder (.hpp) 
*/


#ifndef __CMDED_HPP__
#define __CMDED_HPP__

#include <iostream>
#include <vector>

// command-encoder-decoder namespace
namespace ced
{

// NOT PRESENT
constexpr int NP = -1;
// NOT A NUMBER
constexpr int NAN = -2;

	// Command-Encoder-Decoder class 
    class CED
    {

	private:
    
	std :: vector<std :: vector<std :: string> > commandVec;
	std :: vector<int> cmdlenVec;
	std :: vector<int> decodedNumVec;
	std :: vector<int> decodedCmdVec;
	bool isNumeric;

        /**
         * @brief  Check whether the string is numeric or not
         * @param  str: Input string
         * @retval 0: The string is not numeric
         * @retval 1: The string is numeric
         */
        bool isNum(std :: string& str);

        public:

        /**
         * @brief  Constructor 
         * @param  cmdVec: base Commands vector
         * @retval None
         */
		CED(const std :: vector<std :: vector<std :: string> >& cmdVec);

        /**
         * @brief  Convert the input string to the number (index) of the base commands
         * @param  inputStr: Input string 
         * @param  sepChar: Separator character, default: ' ' (There must be at least one separator character between each commands and numbers)
         * @param  assignmentChar: Assignment character, default: '=' (Only numbers should be placed after this character(with separator character))
         * @retval None
         */
        void decode(std :: string inputStr, const char sepChar = ' ', const char assignmentChar = '=');

        /**
         * @brief  Convert the number (index) of input vector(eCmdVec) to string of the base commands and concatinate it with given numbers(eNumVec)
         * @param  eCmdVec: Encode command vector 
         * @param  eNumVec: Encode number vector 
         * @param  sepChar: Separator character, default: ' ' (it is placed between each command and number)
         * @param  assignmentChar: Assignment character, default: '=' (it is placed between commands and numbers)
         * @retval "Can not be encoded!": if there is an error
         * @retval "Encoded command": if there is no error
         */
        std :: string encode(std :: vector<int>& eCmdVec, std :: vector<int>& eNumVec, const char sepChar = ' ', const char assignmentChar = '=') const;

        /**
         * @brief  Get the number (index) of the decoded commands
         * @param  idx: index of decoded commads
         * @retval -1 (ced :: NP): if not present
         * @retval index of the decoded command: if present
         */
        inline int getCmd(const int idx) const
        {
            if(idx >= decodedCmdVec.size())
                return NP;

            return decodedCmdVec.at(idx);
        }

        /**
         * @brief  Get the  given numbers
         * @param  idx: index of the given number to read
         * @retval -1 (ced :: NP): if not present
         * @retval -2 (ced :: NAN): if it is not numeric
         * @retval given number: if present and it is numeric
         */
        inline int getNum(const int idx) const
        {
            if(idx >= decodedNumVec.size())
                return NP;

            if(isNumeric == false && decodedNumVec.at(idx) == 0)
                return NAN;

            return decodedNumVec.at(idx);
        }

        /**
         * @brief  Get the number of base commands
         * @param  idx: index of commands vector
         * @retval -1 (ced :: NP): if not present
         * @retval number of base commands: if present
         */
        inline int getCmdSize(const int idx) const
        {
            if(idx >= cmdlenVec.size())
                return NP;

            return cmdlenVec.at(idx);
        }	
        
        /**
         * @brief  Get the number of decoded commands
         * @param  None
         * @retval number of decoded commands
         */
        inline int cmdAvailable() const
        {
            return decodedCmdVec.size();
        }	

        /**
         * @brief  Get the number of given numbers
         * @param  None
         * @retval number of given numbers
         */
        inline int numAvailable() const
        {
            return decodedNumVec.size();
        }

    }; /* CED class */

} /* ced namespace */

#endif /* __CMDED_HPP__ */
