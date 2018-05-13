#ifndef SPREADSHEET_FUNCTION_H
#define SPREADSHEET_FUNCTION_H

#include "../Cell.h"

class CFunction : public CCell  {
public:
    CFunction () {}
    CFunction ( const std::string& position, const std::string& command );
    ~CFunction () {}

    void ABS ();
    void SIN ();
    void COS ();
    void CEIL ();
    void FLOOR ();

    void AVG( std::string start, std::string end );
    void MIN( std::string start, std::string end );
    void MAX( std::string start, std::string end );

    bool checkFunctionName();

    virtual void printValue ( std::ostream& os ) const;

    virtual CNumber getValueFromCommand () const;
    virtual void    setValueFromCommand ();

private:
    std::string m_FuncName;
};


#endif //SPREADSHEET_FUNCTION_H
