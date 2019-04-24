#include "String.h"

CString::CString(const std::string &command) : CExpression(command) {
    setValueFromCommand();
}

void CString::setValueFromCommand() {
    m_String = m_Command;
}

double CString::getValueNumber() const {
    throw InvalidExpression();
}

std::string CString::getValueString() const {
    return m_String;
}
