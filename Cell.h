#ifndef SPREADSHEET_CELL_H
#define SPREADSHEET_CELL_H

#include "OperandTypes/Number.h"
#include "Spreadsheet.h"
#include <vector>

//https://github.com/mustiian/spreadsheet.git

class CCell {
public:
    CCell () {}
    CCell ( const std::string& position, const std::string& command ):
            m_Position ( position ),
            m_Command  ( command )
    {
    }
    virtual ~CCell();

    std::string  getPosition ( ) const { return m_Position; }
    std::string  getCommand  ( ) const { return m_Command;  }
    void         setPosition ( const std::string& newPos ) { m_Position = newPos; }
    void         setCommand  ( const std::string& newCom ) { m_Command  = newCom; }

    void getOperandsAndOperationsFromCommand ();

    virtual void printValue ( std::ostream& os ) const = 0;

    virtual CNumber getValueFromCommand () const = 0;
    virtual void    setValueFromCommand () = 0;

    friend std::ostream& operator << ( std::ostream& os, const CCell& cell );

protected:
    std::string m_Command;
    double m_Value;
    std::vector < CCell * > m_Operands;
    std::vector < std::string > m_Operations;

private:
    std::string m_Position;
};

#endif //SPREADSHEET_CELL_H
