#ifndef SPREADSHEET_POINTER_H
#define SPREADSHEET_POINTER_H

#include "../Cell.h"

class CPointer : public CCell {
public:
    CPointer () {}
    CPointer ( const std::string& position, const std::string& command );
    ~CPointer () {}

    static bool CheckLoop ( std::string startCell ) const;

    virtual void printValue ( std::ostream& os ) const;

    virtual CNumber getValueFromCommand () const;
    virtual void    setValueFromCommand ();

private:
    CCell * m_Pointer;
};


#endif //SPREADSHEET_POINTER_H
