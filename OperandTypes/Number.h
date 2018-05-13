#ifndef SPREADSHEET_NUMBER_H
#define SPREADSHEET_NUMBER_H

#include "../Cell.h"

class CNumber : public CCell {
public:
    CNumber () {}
    CNumber ( const std::string& position, const std::string& command );
    ~CNumber () {}

    CNumber operator + ( const CNumber&  other );
    CNumber operator - ( const CNumber&  other );
    CNumber operator / ( const CNumber&  other );
    CNumber operator * ( const CNumber&  other );

    virtual void printValue ( std::ostream& os ) const;

    virtual CNumber getValueFromCommand () const;
    virtual void    setValueFromCommand ();
};


#endif //SPREADSHEET_NUMBER_H
