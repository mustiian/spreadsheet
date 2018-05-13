#ifndef SPREADSHEET_SPREADSHEET_H
#define SPREADSHEET_SPREADSHEET_H

#include <map>
#include "Cell.h"
#include "OperandTypes/String.h"
#include "OperandTypes/Number.h"
#include "OperandTypes/Function.h"
#include "OperandTypes/Pointer.h"
#include "OperandTypes/Expression.h"

class CSpreadsheet {
public:
    CSpreadsheet  ( std::string name ) : m_Name ( name )
    {
    }
    ~CSpreadsheet ();

    void   addCell ( std::string position, std::string command );
    static CCell* getCell ( std::string ) const;
    bool   checkCommand () const;
    std::string SetCommand ( const std::string& command );

    void updateSpreadSheet ();
    void saveSpreeadSheet  ();
    void loadSpreeadSheet  ( const std::string& name );

    void print ( std::iostream& os );
private:
    std::string m_Name;
    static std::map< std::string, CCell > m_GridOfCells;
};


#endif //SPREADSHEET_SPREADSHEET_H
