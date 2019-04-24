#ifndef SPREADSHEET_FUNCTION_H
#define SPREADSHEET_FUNCTION_H

#include "Expression.h"
#include "../Command.h"
#include <regex>
#include <cstdio>

/*! @file Function.h
 *  @class CFunction
 *  @brief Class represent function
 *
 *  Function contain name of fuction,
 *  numerical value and command line
 *  for big expression
 */
class CFunction : public CExpression  {
public:
    /*!
    *  Default constructor
    */
    CFunction () {}

    /*!
     * Constructor create function with command and
     * decides what kind of function has.
     * Get expressions and operasions from command,
     * if function like 'abs', 'sin, 'cos', 'ceil', 'floor'
     * @param command Command of function
     */
    CFunction ( const std::string& command );

    /*!
     *  Default destructor
     */
    ~CFunction () {}

    /*!
     * Set the absolute value of a number
     * of value of function
     */
    void abs ();

    /*!
     * Set sinus of value of function
     */
    void sin ();

    /*!
     * Set cosine of value of function
     */
    void cos ();

    /*!
     * Rounds value of function upward
     */
    void ceil ();

    /*!
     * Rounds value of function downward
     */
    void floor ();

    /*!
     * Find average number between start position
     * and end position. Each position has
     * letter and number.
     * @param startLetter Letter of start position
     * @param endLetter Letter of end position
     * @param startNumber Number of start position
     * @param endNumber Number of end position
     * @return Average number
     */
    static double avg(char startLetter,
             char endLetter,
             int  startNumber,
             int  endNumber);

    /*!
     * Find minimum number between start position
     * and end position. Each position has
     * letter and number.
     * @param startLetter Letter of start position
     * @param endLetter Letter of end position
     * @param startNumber Number of start position
     * @param endNumber Number of end position
     * @return Minimum number
     */
    static double min( char startLetter,
              char endLetter,
              int  startNumber,
              int  endNumber);
    /*!
     * Find maximum number between start position
     * and end position. Each position has
     * letter and number.
     * @param startLetter Letter of start position
     * @param endLetter Letter of end position
     * @param startNumber Number of start position
     * @param endNumber Number of end position
     * @return Maximum number
     */
    static double max( char startLetter,
              char endLetter,
              int  startNumber,
              int  endNumber );

    /*!
     * Delete brackets and name of function from command
     * @return
     */
    std::string reformCommand ();
    /*!
     * For functions 'max', 'min', 'avg' get
     * start position and end position
     * @param command Command of function
     */
    void        getPositionsForFunction ( std::string& command  );

    /*!
     * Calculate value using function
     * @param start Start position
     * @param end End position
     * @param func Function 'max' or 'min' or 'avg'
     */
    void        calculateFunction ( std::string& start,
                                    std::string& end,
                                    double (*func)(char, char, int, int) );

    /*!
     * Get numerical value of function
     * @return Numerical value
     */
    virtual double      getValueNumber () const;
    /*!
     * Get string value of function ( empty string )
     * @return String value
     */
    virtual std::string getValueString () const;

    /*!
     * Set value for function
     */
    virtual void        setValueFromCommand ();

private:
    /** name of function **/
    std::string m_FuncName;
    /** command of function **/
    CCommand    m_CommandLine;
    /** Numerical value **/
    double      m_Value;
};

#endif //SPREADSHEET_FUNCTION_H
