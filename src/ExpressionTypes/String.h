#ifndef SPREADSHEET_STRING_H
#define SPREADSHEET_STRING_H

#include "Expression.h"

/*!
 * @file String.h
 * @class CString
 * @brief Class represents
 * a string value
 */
class CString : public CExpression {
public:
    /*!
     * Default constructor
     */
    CString () {};

    /*!
     * Constructor create string with command
     * Command represent string value
     * @param command Command
     */
    CString ( const std::string& command );

    /*!
     * Default destructor
     */
    ~CString () {}

    /*!
     * Throw exception, because string hasn't got
     * numerical number
     * @return
     */
    virtual double      getValueNumber () const;

    /*!
     * Get string value of string
     * @return String value
     */
    virtual std::string getValueString () const;

    /*!
     * Set string value from command
     */
    void                setValueFromCommand ();

private:
    /** String value **/
    std::string m_String;
};

#endif //SPREADSHEET_STRING_H
