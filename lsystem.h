#ifndef LSYSTEM_H
#define LSYSTEM_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "production_rule.h"
#include "module.h"

namespace L_System {

    class LSystem {
    public:
        LSystem() {};

        void print(void);
        void update(int r, std::string a, std::vector<Production_Rule> p, std::vector<std::pair<char, double>> ud);

        // the vector Modules contains the current structure of the system
        std::vector<std::shared_ptr<Modules::Module>> Modules;

    private:

        // data storage, an L-system contains an Axiom, a series of Production-Rules and some user defined parameters
        int Recursion;
        std::string Axium;
        std::vector<Production_Rule> Productions;
        std::vector<std::pair<char, double>> User_Defines;
        std::vector<std::pair<char, double>> Temp_Defines;

        // functions used to iterate through the system
        void generate_system(void);
        void iterate_system(void);

        // functions used to parse the complex L-system parameters
        void parse_axium(void);
        void parse_string(std::string& string);
        void parse_module(std::string& module);
        double parse_expression(std::stringstream& ss);
        double parse_term(std::stringstream& ss);
        double parse_primary(std::stringstream& ss);
        void module_create(const char& symbol, const double& first, const double& second);
        void module_create(const char& symbol, const double& first);
        double define_char_to_val(char c);
        void is_match(std::shared_ptr<Modules::Module> X);

    };

}

#endif // LSYSTEM_H
