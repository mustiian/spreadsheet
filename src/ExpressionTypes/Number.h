#ifndef SPREADSHEET_NUMBER_H
#define SPREADSHEET_NUMBER_H

#include "Expression.h"

/*!
 * @file Number.h
 * @class CNumber
 * @brief Class represents
 * a numerical value
 */
class CNumber : public CExpression {
public:
    /*!
    *  Default constructor
    */
    CNumber () {};

    /*!
     * Constructor create number with command
     * Command represent string value of number
     * @param command Command
     */
    CNumber ( const std::string& command );

    /*!
    *  Default destructor
    */
    ~CNumber () {}

    /*!
     * Get numerical value
     * @return Numerical value
     */
    virtual double      getValueNumber () const;

    /*!
     * Get string value of function
     * ( for number it's empty string )
     * @return String value
     */
    virtual std::string getValueString () const;

    /*!
     * Interpret command into numerical value
     */
    virtual void        setValueFromCommand ();

private:
    /** Numerical value **/
    double m_Value;
};


#endif //SPREADSHEET_NUMBER_H
