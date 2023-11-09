#ifndef SIMPLESAT_LITERAL_H
#define SIMPLESAT_LITERAL_H

#include <string>
#include <exception>

namespace simplesat
{

    class literal
    {
    public:
        literal();
        virtual ~literal();

        void assign(bool value);
        void unassign();

        int get_state();
        bool get_value();
        bool is_assigned();
    private:
        int state; // 0 = false, 1 = true, -1 = unassigned
    };  
    
} // namespace simplesat

#endif //SIMPLESAT_LITERAL_H