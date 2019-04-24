#ifndef SPREADSHEET_POINTER_H
#define SPREADSHEET_POINTER_H

#include "Expression.h"
#include <regex>
#include <list>
#include <unordered_map>

class CCell;

/*!
 * @file Pointer.h
 * @class CPointer
 * @brief Class represents pointer
 * to another cell
 */
class CPointer : public CExpression {
public:
    /*!
     * Default constructor
     */
    CPointer () {};

    /*!
     * Constructor create pointer with command
     * @param command Command
     */
    CPointer ( const std::string& command );

    /*!
     * Default destructor
     */
    ~CPointer () {}

    /*!
     * Check, if pointer refers directly
     * or indirectly to itself. 
     * In this cases throw exception
     * @param pos Position of cell
     */
    void CheckLoop ( std::string& pos ) const;

    /*!
     * Update all cells to which this pointer
     * refers directly or indirectly.
     * Throw exception, if cell with loop condition.
     * @param allPointers All pointer to which
     * this pointer refers directly or indirectly
     */
    void updateAllPointers( std::unordered_map< std::string, bool >& allPointers) const;

    /*!
     * Delete minus at the beginning of pointer
     * @param pointer Pointer to cell
     */
    void deleteMinus( std::string& pointer ) const;

    /*!
     * Get numerical value from pointer.
     * If pointer has string value or error message,
     * than throw exception
     * @return Numerical value
     */
    virtual double      getValueNumber () const;

    /*!
     * Get string value from pointer.
     * If pointer has numerical value or error
     * message, than throw exception
     * @return String value
     */
    virtual std::string getValueString () const;

    /*!
     * Get value from cell to which it points
     */
    virtual void        setValueFromCommand ();

private:
    /** Pointer to another cell **/
    CCell * m_Pointer;
};

#endif //SPREADSHEET_POINTER_H
