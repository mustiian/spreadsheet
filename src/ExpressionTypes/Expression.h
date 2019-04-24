#ifndef SPREADSHEET_EXPRESSION_H
#define SPREADSHEET_EXPRESSION_H

#include "Exception.h"
#include <string>

/*! @file Expression.h
 *  @class CExpression
 *  @brief Abstract Class represents
 *  number, function, pointer or string
 */
class CExpression {
public:
    /*!
     * Default constructor
     */
    CExpression () {};

    /*!
     * Constructor create expression with command.
     * @param command Original command
     */
    CExpression( const std::string& command ) : m_Command ( command ){ }

    /*!
     * Virtual destructor
     */
    virtual ~CExpression () = default;

    /*!
     * Virtual method, which return command of expression
     * @return Original command
     */
    virtual std::string getCommand () const { return m_Command; }

    /*!
     * Virtual method, which return numerical value
     * @return Numerical value
     */
    virtual double      getValueNumber () const = 0;

    /*!
     * Virtual method, which return string value
     * @return String value
     */
    virtual std::string getValueString () const = 0;

    /*!
     * Virtual method, which interpret command into the value
     */
    virtual void        setValueFromCommand ()  = 0;

protected:
    /** Comand **/
    std::string m_Command;
};

#endif //SPREADSHEET_EXPRESSION_H
