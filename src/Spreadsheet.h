#ifndef SPREADSHEET_SPREADSHEET_H
#define SPREADSHEET_SPREADSHEET_H

#include "Cell.h"
#include <map>
#include <algorithm>
#include <sstream>

/*! @file Spreadsheet.h
 *  @class CSpreadsheet
 *  @brief Simple spreadsheet engine
 */
class CSpreadsheet {
public:

    /*!
     *  Default constructor
     */
    CSpreadsheet ()  {};

    /*!
     *  Default destructor
     */
    ~CSpreadsheet () {};

    /*!
     *  Start working with spreadsheet.
     *  Ask for loading old spreadsheet
     */
    void start ();

    /*!
     *  Set new Spreadsheet.
     *  Ask for name and size of new spreadsheet
     */
    void set ();

    /*!
     *  Get command from User and decide what kind of command implement:
     *
     *  'save'  command save actual spreadsheet into file
     *
     *  'load'  command load spreadsheet
     *
     *  'print' command print command of cell
     *
     *  'add'   command set command for cell
     *
     *  'help'  command print all kinds of commands
     */
    void mainProcessing ();

    /*!
     * Add command into cell.
     * If cell doesn't exist, it's throw exception
     * @param position Position of cell
     * @param command  Original command of cell
     */
    void          addCellCommand ( const std::string& position,
                                   const std::string& command );

    /*!
     * Get pointer to cell on current position.
     * If cell doesn't exist, it's throw exception
     * @param position Position of cell
     * @return Pointer to cell
     */
    static CCell* getCell        ( const std::string& position );

    /*!
     * Check what kind of command user type.
     * Throw exception, if command is unknown
     * @param command Original command
     * @param position If command 'add', set position of cell from command
     * @param cellCommand If command 'add', set command of cell
     * @param name If command 'load', set the name of file from command
     */
    void          checkCommand   ( const std::string& command,
                                    std::string& position,
                                    std::string& cellCommand,
                                    std::string& name );

    /*!
     * Set name of spreadsheet
     * @param name Name of spreadsheet
     */
    void setName ( const std::string& name );

    /*!
     * Set size of spreadsheet
     * @param height Height of spreadsheet
     * @param width Width of spreadsheet
     */
    void setSize ( int height, int width );

    /*!
     *  Set grid of cells.
     *  For each cell set position
     */
    void setGrid ();

    /*!
     * Parse 'print' command.
     * From command get position of cell for printing.
     * If position isn't right, than throw exception
     * @param command Original command
     * @param position Position of cell
     */
    void parsePrintCommand ( const std::string& command,
                             std::string& position );

    /*!
     * Parse 'add' command.
     * From command get position of cell, get command for cell.
     * If cell of command isn't right, than throw exception
     * @param command Original command
     * @param position Position of cell
     * @param cellCommand Command for cell
     * @param matchPart Left part of original command
     */
    void parseAddCommand   ( const std::string& command,
                             std::string& position,
                             std::string& cellCommand,
                             const std::string& matchPart );

    /*!
     * Parse 'load' command.
     * From command get name of file for loading
     * @param command Original command
     * @param name Name of file
     */
    void parseLoadCommand  ( const std::string& command,
                             std::string& name );
    /*!
     * Print all kinds of avaliable commands.
     */
    void help();

    /*!
     * Update all cells in spreadsheet.
     * Cells update their values depending on commands
     */
    void updateSpreadSheet ();

    /*!
     * Save this spreadsheet. The name of file is a name of spreadsheet.
     * If method can't save spreadsheet, than throw exception
     */
    void saveSpreeadSheet  () const;

    /*!
     * Load new spreadsheet.
     * If file doesn't exist or method can't open it, than throw exception
     * @param name Name of file
     */
    void loadSpreeadSheet  ( const std::string& name );

    /*!
     *  Clear all cells.
     *  Set size of spreadsheet on zero and clear name of spreadsheet
     */
    void clearGrid();

    /*!
     * Get characters from user and reform them into string.
     * End when get newline
     * @return Command, what type User
     */
    std::string getString() const;

    /*!
     * Print all cells of spreadsheet
     */
    void print () const;

    /*!
     * Print command of cell.
     * @param position Position of cell
     */
    void printCommandCell ( const std::string& position ) const;

    /*!
     * Print value of cell.
     * indexHeight and indexWidth represent position in spreadsheet
     * @param indexHeight
     * @param indexWidth
     */
    void printCell( char indexHeight, int indexWidth ) const;

    /*!
     * Print head of spreadsheet.
     * Head is a row, where each cell has own number.
     */
    void printHead() const;

private:
    /** Name of spreadsheet **/
    std::string m_Name;
    /** Actual command to execute **/
    std::string m_ActualCommand;
    /** Height of spreadsheet **/
    int         m_Height;
    /** Width of spreadsheet **/
    int         m_Width;
    /** Grid of all cells **/
    static std::map< std::string, CCell > m_GridOfCells;
};

#endif //SPREADSHEET_SPREADSHEET_H
