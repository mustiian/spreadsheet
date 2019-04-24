#include "Number.h"

CNumber::CNumber(const std::string &command) : CExpression(command) {
    setValueFromCommand();
}

void CNumber::setValueFromCommand() {
    m_Value = strtod( m_Command.c_str(), NULL );
}

double CNumber::getValueNumber() const {
    return m_Value;
}

std::string CNumber::getValueString() const {
    return "";
}


