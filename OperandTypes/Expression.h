#ifndef SPREADSHEET_EXPRESSION_H
#define SPREADSHEET_EXPRESSION_H

#include "../Cell.h"


class CExpression : public CCell {
public:
    CExpression () {}
    CExpression( const std::string& position, const std::string& command );
    ~CExpression () {}

    virtual void printValue ( std::ostream& os ) const;

    virtual CNumber getValueFromCommand () const;
    virtual void    setValueFromCommand ();
};


#endif //SPREADSHEET_EXPRESSION_H
