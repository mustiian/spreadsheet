#ifndef SPREADSHEET_COMMAND_H
#define SPREADSHEET_COMMAND_H

#include "ExpressionTypes/Expression.h"
#include <regex>
#include <list>
#include <vector>

/*! @file Command.h
 *  @class CCommand
 *  @brief Class represent command of cell 

 *  Command contain original command,
 *  expressions and operations with them
 */
class CCommand {
public:
    /*!
    *  Default constructor
    */
    CCommand () {};

    /*!
    *  Default destructor
    */
    ~CCommand ();

    /*!
     * Set value of cell.
     * Method decides what kinds of commands has and
     * how should count value of cell.
     * Command could be just a value ( string or number ) or
     * could be a big expression that needs to be parsed
     * @param valueNumber Numerical value of a cell
     * @param valueString String value of a cell
     */
    void setValueFromCommand ( double& valueNumber, std::string& valueString );

    /*!
     * Parsing command on expressions and operations
     * If operation is unknown or not enough expressions,
     * than throw exception
     */
    void parseCommand ();

    /*!
     * Parsing command on simple expressions.
     * Expressions are numbers, pointers, functions;
     * If expression if unknown, than throw exception
     * @param command Command without whitespaces and in lower case
     */
    void getExpressions ( std::string& command );

    /*!
     * Counting all expressions in valueNumber
     * @param valueNumber Numerical value of cell
     */
    void countValueNumber   ( double& valueNumber );

    /*!
     * When command is just a value, decides
     * what kind of expression got and add it
     */
    void setExpression      ();

    /*!
     * When command is just a value, decides
     * what kind of value to set
     * @param valueNumber Numerical value of cell
     * @param valueString String value of cell
     */
    void countExpression    ( double& valueNumber, std::string& valueString ) const;

    /*!
     * Clear Command.
     * Delete all expressions and operations
     */
    void deleteExpr ();

    /*!
     * Change original command to command
     * without whitespaces and in lower cases
     * Delete '=' in the begining of command
     * @return
     */
    std::string reformCommand ();

    /*!
     * Find the end of function.
     * Count brackets in function, until
     * number of closing and opening brackets become equal
     * @param position Start position
     * @param function Function
     * @return true, if function has end
     */
    bool findEndOfFunction ( size_t& position, const std::string& function ) const;

    /*!
     * Return original command
     * @return Original command
     */
    std::string getCommand () const;
    /*!
     * Set command of cell
     * @param com Command of cell
     */
    void        setCommand ( const std::string& com );
private:
    /** Original command **/
    std::string                   m_Command;
    /** Container of all expressions **/
    std::list   < CExpression * > m_Expressions;
    /** Container of all operations **/
    std::vector < char >          m_Operations;
};

#endif //SPREADSHEET_COMMAND_H
