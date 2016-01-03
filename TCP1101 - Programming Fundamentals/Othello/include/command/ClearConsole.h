#ifndef CLEARCONSOLE_H_INCLUDED
#define CLEARCONSOLE_H_INCLUDED

#include "Ultis.h"

class ClearCommand: public Command
{
    public:
        ClearCommand()
        {
        }
        void execute()
        {
            ultis::clearConsole();
        }
    protected:
    private:
};

#endif // CLEARCONSOLE_H_INCLUDED
