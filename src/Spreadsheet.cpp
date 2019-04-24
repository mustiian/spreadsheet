#include <fstream>
#include <sys/stat.h>
#include "Spreadsheet.h"

std::map< std::string, CCell > CSpreadsheet::m_GridOfCells;

const int CELLHEIGHT = 3;
const int MOVEFROMSPR  = 5;

void CSpreadsheet::start() {
    initscr();
    nocbreak();
    echo();

    std::string input, name;
    printw("Want to load spreadsheet?[Y/n]\n");
    input = getString();
    std::transform( input.begin(), input.end(), input.begin(), ::tolower );

    while ( input !="yes" && input != "y" &&
            input != "no" && input != "n" ){
        printw("Write Yes[y] or No[n]\n");
        input = getString();
        std::transform( input.begin(), input.end(), input.begin(), ::tolower );
    }

    if ( input == "yes" || input == "y"){
        printw("Write the name of spreadsheet:\n");
        name = getString();
        try {
            loadSpreeadSheet( name );
        } catch ( std::exception& e ) {
            printw ( "I don't know this file. " );
            set();
        }
    }else{
        set();
    }
    clear();
    refresh();
    updateSpreadSheet();
    mainProcessing();
}

void CSpreadsheet::set() {
    std::string name, size;
    std::istringstream iss;
    int height = 0, width = 0;
    printw("Write the name of new spreadsheet:\n");
    name = getString();
    setName( name );

    printw("Write height and width of new spreadsheet( max 26x26 ):\n");
    size = getString();
    iss.str(size);
    iss >> height >> width;
    while ( ( height > 26 || width > 26 ) ||
            ( height < 1 || width < 1 )){
        printw("Write height and width of new spreadsheet( max 26x26 ):\n");
        size.clear();
        iss.clear();
        height = 0;
        width = 0;
        size = getString();
        iss.str(size);
        iss >> height >> width;
    }
    setSize( height, width );
    setGrid();
}

void CSpreadsheet::setGrid() {
    char indexHeight = 'a';
    for (int i = 0; i <= m_Height; ++i) {
        for (int indexWidth = 1; indexWidth <= m_Width; ++indexWidth) {
            std::ostringstream position;
            position << indexHeight << indexWidth;
            m_GridOfCells[ position.str() ].setPosition( position.str() );
        }
        indexHeight++;
    }
}

void CSpreadsheet::mainProcessing() {
    std::string command, position, cellCommand, name;

    while ( true ){
        move(m_Height*CELLHEIGHT + MOVEFROMSPR, 0);
        printw("Write the command:\n");
        clrtoeol();
        command = getString();

        try{
            checkCommand( command, position, cellCommand, name );
        } catch ( std::exception& e){
            move(m_Height*CELLHEIGHT + MOVEFROMSPR + 2, 0);
            clrtoeol();
            printw( e.what() );
            printw("\n");
            command.clear();
            move(m_Height*CELLHEIGHT + MOVEFROMSPR, 0);
            continue;
        }
        move(m_Height*CELLHEIGHT + MOVEFROMSPR + 2, 0);
        clrtoeol();
        move(m_Height*CELLHEIGHT + MOVEFROMSPR, 0);
        std::transform( position.begin(), position.end(), position.begin(), ::tolower );
        try {
            if ( m_ActualCommand == "add" ) {
                addCellCommand(position, cellCommand);
                updateSpreadSheet();
            }else if ( m_ActualCommand == "print" ){
                printCommandCell( position );
            } else if ( m_ActualCommand == "exit" ){
                endwin();
                return;
            } else if ( m_ActualCommand == "load" ){
                loadSpreeadSheet( name );
                updateSpreadSheet();
            } else if ( m_ActualCommand == "save" ){
                saveSpreeadSheet();
            }
        } catch ( std::exception& e ){
            move(m_Height*CELLHEIGHT + MOVEFROMSPR + 2, 0);
            printw( e.what() );
            printw("\n");
            move(m_Height*CELLHEIGHT + MOVEFROMSPR, 0);
        }

        command.clear();
        position.clear();
        cellCommand.clear();
        name.clear();
    }
}

void CSpreadsheet::checkCommand(const   std::string& command,
                                        std::string& position,
                                        std::string& cellCommand,
                                        std::string& name) {
    std::string tmpResult;
    std::cmatch cm;
    std::regex reg;

    reg = "^[[:s:]]*(print)[[:s:]]+";
    if ( regex_search(command.c_str(), cm, reg) ) {
        parsePrintCommand(command, position);
        return;
    }

    reg = "^[[:s:]]*(help)[[:s:]]*";
    if ( regex_search(command.c_str(), cm, reg) ){
        help();
        return;
    }

    reg =  "^[[:s:]]*[a-zA-Z][0-9]+[[:s:]]+=?";
    if ( regex_search(command.c_str(), cm, reg) ){
        parseAddCommand(command, position, cellCommand, cm.str() );
        return;
    }

    reg =  "^[[:s:]]*(exit)[[:s:]]*";
    if ( regex_search(command.c_str(), cm, reg) ){
        m_ActualCommand = "exit";
        return;
    }

    reg = "^[[:s:]]*(load)[[:s:]]+";
    if ( regex_search(command.c_str(), cm, reg) ){
        parseLoadCommand(command, name);
        return;
    }

    reg = "^[[:s:]]*(save)[[:s:]]*";
    if ( regex_search(command.c_str(), cm, reg) ){
        m_ActualCommand = "save";
        return;
    }

    throw InvalidCommand();
}

void CSpreadsheet::addCellCommand(const std::string& position,
                           const std::string& command) {
    if ( m_GridOfCells.count( position ) > 0 )
        m_GridOfCells[ position ].setCommand( command );
    else
        throw InvalidCell();

}

CCell *CSpreadsheet::getCell(const std::string &position) {
    if ( m_GridOfCells.count( position ) > 0 )
        return &m_GridOfCells[ position ];
    else
        throw InvalidCeilPosition();
}

void CSpreadsheet::updateSpreadSheet() {
    for ( auto &cell : m_GridOfCells ) {
        cell.second.setValueFromCommand();
    }
    print();
}

void CSpreadsheet::saveSpreeadSheet() const {
    std::ofstream file;

    mkdir( "./src/SaveFiles", S_IRWXU + S_IRGRP );

    file.open("./src/SaveFiles/" + m_Name + ".txt", std::ofstream::trunc);

    if ( ! file.is_open() ) {
        throw InvalidFileForSave();
    }

    file << m_Name << std::endl;
    file << m_Height << ' ' << m_Width << std::endl;

    for ( auto &cell : m_GridOfCells ) {
        file << cell.second.getPosition() << ' ';
        file << cell.second.getCommand() << std::endl;
    }

    file.close();

    move(m_Height*CELLHEIGHT + MOVEFROMSPR + 2, 0);
    printw( "File save" );
    printw("\n");
    move(m_Height*CELLHEIGHT + MOVEFROMSPR, 0);

}

void CSpreadsheet::loadSpreeadSheet(const std::string& name) {
    std::ifstream file;
    std::string command, position, cellCommand, size;
    std::istringstream iss;
    std::regex reg;
    std::cmatch cm;


    file.open("./src/SaveFiles/" + name + ".txt");

    if ( ! file.is_open() ) {
        throw InvalidFileToLoad();
    }

    if ( ! m_Name.empty() ){
        clearGrid();
    }

    getline( file, m_Name );
    getline( file, size );
    iss.str(size);
    iss >> m_Height >> m_Width;

    std::getline( file, command );
    while ( ! command.empty() ){
        reg =  "^[[:s:]]*[a-zA-Z][0-9]+[[:s:]]+=?";
        regex_search(command.c_str(), cm, reg);
        parseAddCommand(command, position, cellCommand, cm.str() );
        m_GridOfCells[ position ].setPosition( position );
        m_GridOfCells[ position ].setCommand( cellCommand );
        command.clear();
        position.clear();
        cellCommand.clear();
        std::getline( file, command );
    }
    file.close();

    clear();
    refresh();

    move(m_Height*CELLHEIGHT + MOVEFROMSPR + 2, 0);
    printw( "File load" );
    printw("\n");
    move(m_Height*CELLHEIGHT + MOVEFROMSPR, 0);
}

void CSpreadsheet::printCommandCell(const std::string& position) const {
    move(m_Height*CELLHEIGHT + MOVEFROMSPR + 2, 0);
    clrtoeol();
    std::string command ( position + ':' + getCell( position ) -> getCommand() );
    printw( command.c_str() );
    printw("\n");
    move(m_Height*CELLHEIGHT + MOVEFROMSPR, 0);
}

void CSpreadsheet::printHead() const {
    printw(" ");
    for (int j = 0; j <= m_Width; ++j) {
        printw("_________");
    }
    printw("\n");
    printw("|");
    for (int j = 0; j <= m_Width; ++j) {
        printw("        |");
    }
    printw("\n");
    printw("|        |");
    for (int j = 1; j <= m_Width; ++j) {
        if ( j > 9)
            printw("%d      |", j);
        else
            printw("%d       |", j);
    }
    printw("\n");
    printw("|");
    for (int j = 0; j <= m_Width; ++j) {
        printw("________|");
    }
    printw("\n");
}

void CSpreadsheet::print() const {
    char indexHeight = 'a';
    move(0, 0);

    printHead();

    for (int i = 0; i < m_Height; ++i) {
        printw("|        |");
        for (int j = 0; j < m_Width; ++j) {
            printw("        |");
        }
        printw("\n");
        printw("|    %c   |", indexHeight);
        for (int indexWidth = 1; indexWidth <= m_Width; ++indexWidth) {
            printCell(indexHeight, indexWidth);
        }
        indexHeight++;
        printw("\n");
        printw("|________|");
        for (int j = 0; j < m_Width; ++j) {
            printw("________|");
        }
        printw("\n");
    }
}

void CSpreadsheet::printCell(char indexHeight, int indexWidth) const {
    std::ostringstream position, command;
    position << indexHeight << indexWidth;
    m_GridOfCells[ position.str() ].printValue( );
    printw("|");
}

void CSpreadsheet::help() {
    m_ActualCommand = "help";
    move(m_Height*CELLHEIGHT + MOVEFROMSPR + 3, 0);
    printw("Add value:  '<position> = <command>' or '<position> <value>'\n");
    printw("Print cell: 'print <position>'\n");
    printw("Exit:       'exit'\n");
    printw("Save file:  'save'\n");
    printw("Load file:  'load <name>'\n");

    move(m_Height*CELLHEIGHT + MOVEFROMSPR, 0);
}

void CSpreadsheet::parsePrintCommand(const std::string&command, std::string& position) {
    std::cmatch cm;
    std::regex reg;

    reg = "^[[:s:]]*(print)[[:s:]]+";
    regex_replace(back_inserter(position), command.begin(), command.end(), reg, "");

    reg = "[a-zA-Z][0-9]+";
    regex_search(position.c_str(), cm, reg);
    position = cm.str();

    if ( position.empty() ){
        throw InvalidCommandPrint();
    }

    m_ActualCommand = "print";
}

void CSpreadsheet::parseAddCommand(const std::string& command, std::string& position, std::string& cellCommand, const std::string& matchPart) {
    std::regex reg;
    std::cmatch cm;

    reg = "[[:s:]]+=?";
    regex_replace(back_inserter(position), matchPart.begin(), matchPart.end(), reg,  "");

    if ( position.empty() ){
        throw InvalidCommandAdd();
    }

    reg = "^[[:s:]]*" + position + "[[:s:]]*";

    regex_replace(back_inserter(cellCommand), command.begin(), command.end(), reg,  "");

    m_ActualCommand = "add";
}

void CSpreadsheet::parseLoadCommand(const std::string& command, std::string& name) {
    std::regex reg;
    std::cmatch cm;
    std::string matchPart;

    reg = "load";
    std::regex_replace(back_inserter(matchPart), command.begin(), command.end(), reg,  "");

    reg = "[ ]+";
    std::regex_replace(back_inserter(name), matchPart.begin(), matchPart.end(), reg,  "");

    m_ActualCommand = "load";
}

void CSpreadsheet::setSize(int height, int width) {
    m_Height = height; m_Width = width;
}

void CSpreadsheet::setName(const std::string& name) {
    m_Name = name;
}

void CSpreadsheet::clearGrid() {
    for ( auto& cell : m_GridOfCells ) {
        cell.second.clearCell();
    }
    m_Width = 0;
    m_Height = 0;
    m_Name.clear();
}

std::string CSpreadsheet::getString() const {
    std::string input;

    nocbreak();
    echo();

    int ch = getch();

    while ( ch != '\n' )
    {
        input.push_back( ch );
        ch = getch();
    }
    return input;
}
