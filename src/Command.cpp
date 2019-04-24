#include "Command.h"

#include "ExpressionTypes/Number.h"
#include "ExpressionTypes/Pointer.h"
#include "ExpressionTypes/Function.h"
#include "ExpressionTypes/String.h"

void CCommand::setValueFromCommand( double& valueNumber, std::string& valueString ) {
    if ( m_Command.empty() ) return;

    deleteExpr();

    if ( m_Command[0] == '=' ){
        parseCommand();
    } else {
        setExpression();
    }

    if ( ! m_Operations.empty() ){
        countValueNumber(valueNumber);
    } else {
        countExpression( valueNumber, valueString );
    }
}
void CCommand::parseCommand() {
    std::string command = reformCommand();
    char operation;

    while ( !command.empty() ){

        getExpressions( command );

        if ( !command.empty() ){
            if (    command[0] != '*' && command[0] != '/' &&
                    command[0] != '+' && command[0] != '-' )
                throw InvalidOperation();

            operation = command[0];
            command.erase( command.begin() );
            m_Operations.push_back( operation );
        }
    }

    if ( m_Operations.size() == m_Expressions.size() )
        throw InvalidNumberOfVariables();
}

void CCommand::getExpressions(std::string &command) {
    std::string expression, matchPart;
    std::regex reg;
    std::cmatch cm;

    reg = "^-?[a-z][0-9]+";

    if ( regex_search(command.c_str(), cm, reg) ){
        expression = cm.str();
        m_Expressions.push_back( new CPointer( expression ) );
    }

    reg = "^-?[0-9]+\\.[0-9]+|^-?[0-9]+";

    if ( regex_search(command.c_str(), cm, reg) ){
        expression = cm.str();
        m_Expressions.push_back( new CNumber( expression ) );
    }

    reg = "^-?abs\\(|^-?cos\\(|^-?sin\\(|"
          "^-?floor\\(|^-?ceil\\(|"
          "^-?avg\\(|^-?max\\(|^-?min\\(";
    if ( regex_search(command.c_str(), cm, reg) ) {
        size_t position = cm.str().size() + 1;
        reg = "^-?abs\\(.*\\)|^-?cos\\(.*\\)|"
              "^-?sin\\(.*\\)|^-?floor\\(.*\\)|"
              "^-?ceil\\(.*\\)|^-?avg\\(.*\\)|"
              "^-?max\\(.*\\)|^-?min\\(.*\\)";
        regex_search(command.c_str(), cm, reg);
        matchPart = cm.str();
        if ( findEndOfFunction( position, matchPart ) ){
            expression.assign( matchPart, 0, position);
            m_Expressions.push_back( new CFunction( expression ) );
        }
    }

    if ( expression.empty() ){
        throw InvalidExpression();
    }

    command.erase(command.begin(), command.begin() + expression.size() );
}

bool CCommand::findEndOfFunction(size_t& position, const std::string& function) const {
    int counter = 1;
    while ( counter != 0 && position != function.size() ){
        if (function[position] == '(' ){
            counter++;
        } else if ( function[position] == ')' ){
            counter--;
        }
        position ++;
    }
    return ( counter == 0 );
}

void CCommand::countValueNumber( double& valueNumber  ) {
    double tmpRes;
    std::vector< double > allOperands;
    for ( const auto& expr : m_Expressions ){
        allOperands.push_back( expr->getValueNumber() );
    }

    for (size_t pos = 0; pos < m_Operations.size(); ++pos) {
        if ( m_Operations[pos] == '*' ){
            tmpRes = allOperands[pos] * allOperands[pos + 1];
        }
        else if ( m_Operations[pos] == '/' ){
            tmpRes = allOperands[pos] / allOperands[pos + 1];
        } else continue;

        allOperands.erase( allOperands.begin() + pos, allOperands.begin() + pos + 1 );
        allOperands.insert( allOperands.begin() + pos, tmpRes );
        m_Operations.erase( m_Operations.begin() + pos );
        pos--;
    }
    valueNumber = allOperands[0];
    for (size_t pos = 0; pos < m_Operations.size(); ++pos) {
        if ( m_Operations[pos] == '+' ){
            valueNumber += allOperands[pos + 1];
        }
        else if ( m_Operations[pos] == '-' ){
            valueNumber -= allOperands[pos + 1];
        } else continue;
    }
}

std::string CCommand::reformCommand() {
    std::string tmpResult, command;
    std::cmatch cm;
    std::regex reg;

    reg = "[[:s:]]+";

    std::regex_replace(back_inserter(tmpResult), m_Command.begin(), m_Command.end(), reg, "");

    reg = "^=?";

    std::regex_replace(back_inserter(command), tmpResult.begin(), tmpResult.end(), reg, "");
    std::transform( command.begin(), command.end(), command.begin(), ::tolower );

    return command;
}

void CCommand::countExpression(double& valueNumber, std::string& valueString) const {
    if ( ! m_Expressions.front()->getValueString().empty() ){
        valueString =  m_Expressions.front()->getValueString();
    } else
        valueNumber = m_Expressions.front()->getValueNumber();
}

void CCommand::setExpression() {
    std::string tmpResult, command;
    std::cmatch cm;
    std::regex reg;

    reg = "^-?[0-9]+$|^-?[0-9]+\\.[0-9]+[[:s:]]*$";

    if ( regex_search(m_Command.c_str(), cm, reg) ){
        reg = "[[:s:]]+";
        std::regex_replace(back_inserter(command), m_Command.begin(), m_Command.end(), reg, "");
        m_Expressions.push_back( new CNumber( command ) );
    } else {
        m_Expressions.push_back( new CString( m_Command ) );
    }
}

void CCommand::deleteExpr() {
    if ( !m_Expressions.empty() ){
        for (auto& expression : m_Expressions) {
            delete expression;
        }
        m_Operations.clear();
        m_Expressions.clear();
    }
}

CCommand::~CCommand() {
    deleteExpr();
}

std::string CCommand::getCommand() const {
    return m_Command;
}

void CCommand::setCommand(const std::string &com) {
    m_Command = com;
}
