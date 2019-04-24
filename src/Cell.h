#ifndef SPREADSHEET_CELL_H
#define SPREADSHEET_CELL_H

#include "Command.h"
#include <ncurses.h>

/*! @file Cell.h
 *  @class CCell
 *  @brief Class represents cell 

 *  Cell contain massage about error,
 *  different values, position
 *  in spreadsheet and command
 */
class CCell {
public:
    /*!
    *  Default constructor
    */
    CCell () {};

    /*!
    *  Default destructor
    */
    ~CCell() {};

    /*!
     * Return current position
     * @return Position of cell
     */
    std::string  getPosition () const;

    /*!
     * Return error message
     * @return Error message
     */
    std::string  getError    () const;

    /*!
     * Return original command
     * @return Original command
     */
    std::string  getCommand  () const;
    /*!
     * Set position of cell in spreadsheet
     * @param newPos New position
     */
    void         setPosition ( const std::string& newPos );
    /*!
     * Set new original command of cell
     * @param newCom New command
     */
    void         setCommand  ( const std::string& newCom );

    /*!
     * Return a numerical value of cell
     * @return Numerical value
     */
    double       getValueNumber () const;

    /*!
     * Return a string value of cell
     * @return String value
     */
    std::string  getValueString () const;

    /*!
     * Set value of cell, depending on the command
     * If command isn't right, will set error message
     */
    void         setValueFromCommand ();

    /*!
     * Clear cell, clear command
     */
    void         clearCell();

    /*!
     * Print value of cell.
     * The maximum size of the value is 8 symbols
     * or the output will be limited.
     * If cell has error, than print error message
     */
    void         printValue () const;

private:
    /** Error message **/
    std::string m_Error;
    /** Numerical value **/
    double      m_ValueNumber = 0;
    /** String value **/
    std::string m_ValueString;
    /** Position of cell in spreadsheet **/
    std::string m_Position;
    /** contains original command of cell **/
    CCommand    m_Command;
};

#endif //SPREADSHEET_CELL_H
