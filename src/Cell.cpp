#include "Cell.h"

const int CELLWIDTH  = 8;

void CCell::setValueFromCommand() {
    try{
        m_ValueNumber = 0;
        m_ValueString.clear();
        m_Command.setValueFromCommand(m_ValueNumber, m_ValueString);
    } catch ( std::exception& e ) {
        m_Error = e.what();
        return;
    }
    m_Error.clear();
}


void CCell::printValue() const {
    if ( m_Command.getCommand().empty() )
        printw("        ");
    else if ( ! m_Error.empty() ){
        printw(" ");
        printw( m_Error.c_str() );
        printw("  ");
    }
    else{
        if ( ! m_ValueString.empty() ){
            if ( m_ValueString.size() > CELLWIDTH )
            {
                std::string partValue (m_ValueString, 0, 5);
                printw( partValue.c_str() );
                printw("...");
            } else {
                printw( m_ValueString.c_str() );
                for (size_t i = 0; i <(CELLWIDTH - m_ValueString.size()) ; ++i) {
                    printw(" ");
                }
            }
        }
        else{
            std::ostringstream os;
            os << m_ValueNumber;
            if ( os.str().size() > CELLWIDTH ){
                std::string partValue (os.str(), 0, 5);
                printw( partValue.c_str() );
                printw("...");
            } else {
                std::string partValue (os.str());
                printw( partValue.c_str() );
                for (size_t i = 0; i < (CELLWIDTH - partValue.size()); ++i) {
                    printw(" ");
                }
            }
        }
    }
}

void CCell::setCommand(const std::string &newCom) {
    m_Command.setCommand( newCom );
    setValueFromCommand();
}

void CCell::clearCell() {
    m_Command.deleteExpr();
}

void CCell::setPosition(const std::string &newPos) {
    m_Position = newPos;
}

std::string CCell::getCommand() const {
    return m_Command.getCommand();
}

std::string CCell::getPosition() const {
    return m_Position;
}

std::string CCell::getError() const {
    return m_Error;
}

double CCell::getValueNumber() const {
    return m_ValueNumber;
}

std::string CCell::getValueString() const {
    return m_ValueString;
}

