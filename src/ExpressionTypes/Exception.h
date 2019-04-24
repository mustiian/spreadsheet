#ifndef SPREADSHEET_EXCEPTION_H
#define SPREADSHEET_EXCEPTION_H

#include <exception>
#include <iostream>

/*!
 *  Operation is not '+', '-', '/' or '*'
 */
class InvalidOperation : public  std::exception{
public:
    virtual const char* what() const throw()
    {
        return "#OPR ";
    }
};

/*!
 * This kind of expression is not exist
 */
class InvalidExpression : public  std::exception{
public:
    virtual const char* what() const throw()
    {
        return "#ARG ";
    }
};

/*!
 * Formula refers directly or indirectly to itself
 */
class InvalidPointerLoop : public  std::exception{
public:
    virtual const char* what() const throw()
    {
        return "#LOOP";
    }
};

/*!
 * Function is not 'abs', 'cos', 'sin', 'ceil', 'floor',
 * 'avg', 'max' or 'min'
 */
class InvalidFunction : public  std::exception{
public:
    virtual const char* what() const throw()
    {
        return "#FUNC";
    }
};

/*!
 * Incorect value of pointer
 * ( need numerical, but get string or
 *  need string, but get numerical )
 */
class InvalidPointerValue : public  std::exception{
public:
    virtual const char* what() const throw()
    {
        return "#RES ";
    }
};

/*!
 * Missing expression in command
 */
class InvalidNumberOfVariables : public  std::exception{
public:
    virtual const char* what() const throw()
    {
        return "#VAR ";
    }
};

/*!
 * Cell with this position doesn't exist
 */
class InvalidCeilPosition : public  std::exception{
public:
    virtual const char* what() const throw()
    {
        return "#CELL";
    }
};

/*!
 * Cell with this position doesn't exist ( for spreadsheet )
 */
class InvalidCell : public  std::exception{
public:
    virtual const char* what() const throw()
    {
        return "Invalid cell";
    }
};

/*!
 *  Invalid position for printing
 */
class InvalidCommandPrint : public  std::exception{
public:
    virtual const char* what() const throw()
    {
        return "Invalid format of command print ( print <position> )";

    }
};

/*!
 * Invalid format of commad add
 */
class InvalidCommandAdd : public  std::exception{
public:
    virtual const char* what() const throw()
    {
        return  "Invalid format of command add ( <position> = <command> )";

    }
};

/*!
 * Command of this type is unknown
 */
class InvalidCommand : public  std::exception{
public:
    virtual const char* what() const throw()
    {
        return  "Invalid command ( Type 'help' for help )";

    }
};

/*!
 * Can't save the file
 */
class InvalidFileForSave : public  std::exception{
public:
    virtual const char* what() const throw()
    {
        return  "Can't save this file";

    }
};

/*!
 * Can't load the file
 */
class InvalidFileToLoad : public  std::exception{
public:
    virtual const char* what() const throw()
    {
        return  "Can't load this file";

    }
};

#endif //SPREADSHEET_EXCEPTION_H
