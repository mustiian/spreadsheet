#include "Function.h"
#include "../Spreadsheet.h"
#include "Pointer.h"

CFunction::CFunction(const std::string &command) : CExpression(command){
    std::string reformedCommand = reformCommand();
    if ( m_FuncName == "max" ||
         m_FuncName == "min" ||
         m_FuncName == "avg" )
        getPositionsForFunction ( reformedCommand );
    else {
        m_CommandLine.setCommand( reformedCommand );
        m_CommandLine.parseCommand();
        m_CommandLine.countValueNumber( m_Value );
        setValueFromCommand();
    }

    if ( m_Command[0] == '-')
        m_Value *= -1;
}

double CFunction::getValueNumber() const {
    return m_Value;
}

std::string CFunction::getValueString() const {
    return "";
}

void CFunction::setValueFromCommand() {
    if ( m_FuncName == "floor" ){
        floor();
    } else if ( m_FuncName == "ceil" ){
        ceil();
    } else if ( m_FuncName == "cos" ){
        cos();
    } else if ( m_FuncName == "sin" ){
        sin();
    } else if ( m_FuncName == "abs" ){
        abs();
    } else throw InvalidFunction();
}

std::string CFunction::reformCommand() {
    std::string command = m_Command;
    std::cmatch cm;
    std::regex reg;
    if ( command[0] == '-' )
        command.erase( command.begin() );

    while ( command[0] != '(' ){
        m_FuncName.push_back( command[0] );
        command.erase( command.begin() );
    }
    command.erase( command.begin() );
    command.erase( command.end() - 1 );

    return command;
}

void CFunction::getPositionsForFunction( std::string& command ) {
    std::string startPos, endPos;
    std::cmatch cm;
    std::regex reg;

    reg = "^[a-z][0-9]+:[a-z][0-9]+$";

    if ( regex_search(command.c_str(), cm, reg) ){
        reg = "[a-z][0-9]+";
        regex_search(command.c_str(), cm, reg);
        startPos = cm.str();

        command = cm.suffix().str();
        regex_search(command.c_str(), cm, reg);
        endPos = cm.str();
    } else throw InvalidFunction();

    if ( startPos > endPos )
        throw InvalidCeilPosition();
    else if ( startPos == endPos ){
        m_Value = CSpreadsheet::getCell( startPos )->getValueNumber();
        return;
    }

    CPointer str;
    str.CheckLoop(startPos);
    str.CheckLoop(endPos);

    if ( m_FuncName == "max" ){
        calculateFunction(startPos, endPos, max);
    } else if ( m_FuncName == "min" ){
        calculateFunction(startPos, endPos, min);
    } else if ( m_FuncName == "avg" )
        calculateFunction(startPos, endPos, avg);
}

void CFunction::calculateFunction(std::string &start, std::string& end, double (*func)(char, char, int, int)) {
    int startNumber, endNumber;
    char startLetter, endLetter;

    startLetter = start[0];
    endLetter   = end[0];
    start.erase( start.begin() );
    end.erase( end.begin() );

    startNumber = atoi( start.c_str() );
    endNumber   = atoi( end.c_str() );

    m_Value = func ( startLetter, endLetter, startNumber, endNumber );
}

double CFunction::max(char startLetter,
                    char endLetter,
                    int  startNumber,
                    int  endNumber) {
    double maxNumber = 0;
    int tmpNum = startNumber;
    std::ostringstream os;

    os.str("");
    os << startLetter << startNumber;
    maxNumber = CSpreadsheet::getCell( os.str() )->getValueNumber();

    for ( ; startLetter <= endLetter; startLetter++ ){
        startNumber = tmpNum;
        for ( ; startNumber <= endNumber; ++startNumber) {
            os.str("");
            os << startLetter << startNumber;
            if ( CSpreadsheet::getCell( os.str() )->getValueNumber() > maxNumber)
                maxNumber = CSpreadsheet::getCell( os.str() )->getValueNumber();
        }
    }
    return maxNumber;
}

double CFunction::min(char startLetter,
                    char endLetter,
                    int  startNumber,
                    int  endNumber) {
    double minNumber = 0;
    int tmpNum = startNumber;
    std::ostringstream os;

    os.str("");
    os << startLetter << startNumber;
    minNumber = CSpreadsheet::getCell( os.str() )->getValueNumber();

    for ( ; startLetter <= endLetter; startLetter++ ){
        startNumber = tmpNum;
        for ( ; startNumber <= endNumber; ++startNumber) {
            os.str("");
            os << startLetter << startNumber;
            if ( CSpreadsheet::getCell( os.str() )->getValueNumber() < minNumber)
                minNumber = CSpreadsheet::getCell( os.str() )->getValueNumber();
        }
    }

    return minNumber;
}

double CFunction::avg(char startLetter,
                    char endLetter,
                    int  startNumber,
                    int  endNumber) {
    double avgNumber = 0;
    int tmpNum = startNumber, counter = 0;
    std::ostringstream os;

    for ( ; startLetter <= endLetter; startLetter++ ){
        startNumber = tmpNum;
        for ( ; startNumber <= endNumber; ++startNumber) {
            os.str("");
            os << startLetter << startNumber;
            avgNumber += CSpreadsheet::getCell( os.str() )->getValueNumber();
            counter++;
        }
    }

    return avgNumber / counter;
}

void CFunction::floor() {
    m_Value = std::floor( m_Value );
}

void CFunction::ceil() {
    m_Value = std::ceil( m_Value );
}

void CFunction::cos() {
    m_Value = std::cos( m_Value );
}

void CFunction::sin() {
    m_Value = std::sin( m_Value );
}

void CFunction::abs() {
    m_Value = std::abs( m_Value );
}