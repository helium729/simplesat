#ifndef SIMPLESAT_LITERAL_H
#define SIMPLESAT_LITERAL_H

#include <string>
#include <exception>
#include <vector>

namespace simplesat
{

    /**
     * @brief The literal class represents a boolean variable in a SAT problem.
     * 
     */
    class literal
    {
    public:
        /**
         * @brief Construct a new literal object.
         * 
         */
        literal();

        /**
         * @brief Destroy the literal object.
         * 
         */
        virtual ~literal();

        /**
         * @brief Assigns a boolean value to the literal.
         * 
         * @param value The boolean value to assign.
         */
        void assign(bool value);

        /**
         * @brief Unassigns the literal.
         * 
         */
        void unassign();

        /**
         * @brief Gets the state of the literal.
         * 
         * @return int The state of the literal. 0 = false, 1 = true, -1 = unassigned.
         */
        int get_state();

        /**
         * @brief Gets the value of the literal.
         * 
         * @return true The literal is true.
         * @return false The literal is false.
         */
        bool get_value();

        /**
         * @brief Checks if the literal is assigned.
         * 
         * @return true The literal is assigned.
         * @return false The literal is unassigned.
         */
        bool is_assigned();
        std::vector<size_t> clause_ids;

    private:
        int state; // 0 = false, 1 = true, -1 = unassigned
        
    };  
    
} // namespace simplesat

#endif //SIMPLESAT_LITERAL_H