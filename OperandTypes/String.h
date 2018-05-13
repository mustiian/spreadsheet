#ifndef SPREADSHEET_STRING_H
#define SPREADSHEET_STRING_H

#include "../Cell.h"

class CString : public CCell {
public:
    CString ()  {}
    CString ( const std::string& position, const std::string& command );
    ~CString () {}

    virtual void printValue ( std::ostream& os ) const;

    std::string getString () const;
    void setString ( std::string string ) const;

    virtual CNumber getValueFromCommand () const;
    virtual void    setValueFromCommand ();

private:
    std::string m_String;
};


#endif //SPREADSHEET_STRING_H
