#include "Pointer.h"
#include "../Spreadsheet.h"

CPointer::CPointer(const std::string &command) : CExpression(command) {
    CheckLoop( m_Command );
    setValueFromCommand();
}


void CPointer::CheckLoop(std::string& pos) const {
    std::string command, thisPointer = pos;
    std::list <std::string> listPointers;
    std::unordered_map<std::string, bool > allPointers;
    std::regex reg ("[a-zA-z][0-9]+");
    std::cmatch cm;

    deleteMinus(thisPointer);

    listPointers.push_back( thisPointer );
    allPointers[thisPointer] = true;

    while ( ! listPointers.empty() ){
        command = CSpreadsheet::getCell( listPointers.front() )->getCommand();
        if ( command[0] == '=' ){
            std::transform( command.begin(), command.end(), command.begin(), ::tolower );
            while ( regex_search(command.c_str(), cm, reg) ){
                for (const auto &pointer : cm) {
                    if ( thisPointer == pointer )
                        throw InvalidPointerLoop();
                    if ( ! allPointers[pointer] ){
                        listPointers.push_back( pointer );
                        allPointers[pointer] = true;
                    }
                }
                command = cm.suffix().str();
            }
        }
        command.clear();
        listPointers.pop_front();
    }
    updateAllPointers(allPointers);
}

void CPointer::updateAllPointers( std::unordered_map< std::string, bool >& allPointers) const {
    for( const auto position : allPointers ){
        CSpreadsheet::getCell( position.first ) -> setValueFromCommand();
        if ( CSpreadsheet::getCell( position.first )->getError() == "#LOOP")
            throw InvalidPointerLoop();
    }
}

void CPointer::deleteMinus(std::string& pointer) const {
    if ( pointer[0] == '-' )
        pointer.erase( pointer.begin() );
}

void CPointer::setValueFromCommand() {
    std::string thisPointer = m_Command;
    deleteMinus( thisPointer );

    m_Pointer = CSpreadsheet::getCell( thisPointer );
}

double CPointer::getValueNumber() const {
    if ( m_Pointer->getValueString().empty() && m_Pointer->getError().empty() ){
        if ( m_Command[0] == '-' )
            return (-1)*m_Pointer->getValueNumber();
        else
            return m_Pointer->getValueNumber();
    } else
        throw InvalidPointerValue();
}

std::string CPointer::getValueString() const {
    if ( m_Pointer->getError().empty() )
        return m_Pointer->getValueString();
    else
        throw InvalidPointerValue();
}
