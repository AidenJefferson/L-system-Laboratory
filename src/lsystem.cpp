#include "lsystem.h"
#include <regex>
#include <string>
#include <sstream>
#include <iostream>
#include <QDebug>

namespace L_System{

    void LSystem::update(int r, std::string a, std::vector<Production_Rule> p, std::vector<std::pair<char, double>> ud) {
        Recursion = r;
        Axium = a;
        Modules.clear();
        Productions.clear();
        Productions = p;
        User_Defines.clear();
        User_Defines = ud;

        generate_system();

        if (Recursion > 1) {
            for (int i = 1; i < Recursion; i++) {
                iterate_system();
            }
        }
    }

    void LSystem::generate_system(void) {

        parse_axium();

    }

    void LSystem::iterate_system(void) {

        // clear current structure and copy
        std::vector<std::shared_ptr<Modules::Module>> previous = this->Modules;
        Modules.clear();

        for (auto X : previous) {
            is_match(X);
        }

        previous.clear();

    }

    void LSystem::parse_axium(void) {

        bool matched{false};
        std::regex regexp("[A-Zf?!^&+-<>]{1}\\(.*?\\)|[\\[\\]$]{1}");

        auto modules_begin = std::sregex_iterator(Axium.begin(), Axium.end(), regexp);
        auto modules_end = std::sregex_iterator();

        for (std::sregex_iterator i = modules_begin; i != modules_end; ++i) {
            matched = true;
            std::smatch match = *i;
            std::string s = match.str();
            parse_module(s);
        }

        if(matched == false) throw std::runtime_error("No Axiom given or Axiom entered incorrectly.");
    }

    void LSystem::parse_string(std::string& string) {

        std::regex regexp("[A-Zf?!^&+-<>]{1}\\(.*?\\)|[\\[\\]$]{1}");

        auto modules_begin = std::sregex_iterator(string.begin(), string.end(), regexp);
        auto modules_end = std::sregex_iterator();

        for (std::sregex_iterator i = modules_begin; i != modules_end; ++i) {
            std::smatch match = *i;
            std::string s = match.str();
            parse_module(s);
        }
    }

    void LSystem::parse_module(std::string& mod) {

        char symbol;
        char token;
        double first{ 0 }, second{ 0 };

        std::stringstream ss(mod);

        symbol = ss.get();

        if (symbol == '[' || symbol == ']' || symbol == '$') {
            module_create(symbol, 0);
            return;
        }

        token = ss.get();

        if (token == '(') {

            first = parse_expression(ss);
            token = ss.get();

            if (token == ')') {
                module_create(symbol, first);
                return;
            }
            else if (token == ',') {

                second = parse_expression(ss);
                token = ss.get();

                if (token == ')') {
                    module_create(symbol, first, second);
                    return;
                }
                else{
                    std::stringstream es;
                    es << "'" << symbol << "' module was entered incorrectly, see instructions for correct format.";
                    throw std::runtime_error(es.str());
                }
            }
            else {
                std::stringstream es;
                es << "'" << symbol << "' module was entered incorrectly, see instructions for correct format.";
                throw std::runtime_error(es.str());
            }
        }
        else {
            std::stringstream es;
            es << "'" << symbol << "' module was entered incorrectly, see instructions for correct format.";
            throw std::runtime_error(es.str());
        }
    }

    double LSystem::parse_expression(std::stringstream& ss) {

        double sum = parse_term(ss);
        char token = ss.get();

        while (true) {
            switch (token) {
            case '+':
                sum += parse_term(ss);
                token = ss.get();
                break;
            case '-':
                sum -= parse_term(ss);
                token = ss.get();
                break;
            default:
                ss.putback(token);
                return sum;
            }
        }
    }

    double LSystem::parse_term(std::stringstream& ss) {

        double sum = parse_primary(ss);
        char token = ss.get();

        while (true) {
            switch (token) {
            case '*':
                sum *= parse_primary(ss);
                token = ss.get();
                break;
            case '/':
            {
                double d = parse_primary(ss);
                if (d == 0) throw std::runtime_error("cannot divide by zero");
                sum /= d;
                token = ss.get();
                break;
            }
            default:
                ss.putback(token);
                return sum;
            }
        }
    }

    double LSystem::parse_primary(std::stringstream& ss) {

        char token = ss.get();
        double val{ 0 };

        switch (token) {

        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            ss.putback(token);
            ss >> val;
            return val;
        default:
            val = define_char_to_val(token);
            return val;
        }
    }

    double LSystem::define_char_to_val(char c) {

        for (uint16_t i = 0; i < User_Defines.size(); i++) {
            if (c == User_Defines[i].first) {
                return User_Defines[i].second;
            }
        }

        for (uint16_t i = 0; i < Temp_Defines.size(); i++) {
            if (c == Temp_Defines[i].first) {
                return Temp_Defines[i].second;
            }
        }

        std::stringstream error;
        error << "Variable '" << c << "' declared in L-system but no value given.";
        throw std::runtime_error(error.str());
    }

    void LSystem::module_create(const char& symbol, const double& first, const double& second) {

        auto mod = std::shared_ptr<Modules::Module>(new Modules::Placer{ symbol, first, second });
        Modules.push_back(mod);

    }

    void LSystem::module_create(const char& symbol, const double& first) {

        std::shared_ptr<Modules::Module> mod;

        switch (symbol) {
        case 'F':
            mod = std::shared_ptr<Modules::Module>(new Modules::Forward{ first });
            break;
        case 'f':
            mod = std::shared_ptr<Modules::Module>(new Modules::NoForward{ first });
            break;
        case '+':
            mod = std::shared_ptr<Modules::Module>(new Modules::LeftTurn{ first });
            break;
        case '-':
            mod = std::shared_ptr<Modules::Module>(new Modules::RightTurn{ first });
            break;
        case '^':
            mod = std::shared_ptr<Modules::Module>(new Modules::UpPitch{ first });
            break;
        case '&':
            mod = std::shared_ptr<Modules::Module>(new Modules::DownPitch{ first });
            break;
        case '$':
            mod = std::shared_ptr<Modules::Module>(new Modules::Virtical{});
            break;
        case '<':
            mod = std::shared_ptr<Modules::Module>(new Modules::LeftRoll{ first });
            break;
        case '>':
            mod = std::shared_ptr<Modules::Module>(new Modules::RightRoll{ first });
            break;
        case '[':
            mod = std::shared_ptr<Modules::Module>(new Modules::StartBranch{});
            break;
        case ']':
            mod = std::shared_ptr<Modules::Module>(new Modules::EndBranch{});
            break;
        case '!':
            mod = std::shared_ptr<Modules::Module>(new Modules::SetWidth{ first });
            break;
        default:
            std::stringstream ss;
            ss << "Module '" << symbol << "' was entered incorrectly. Please see instructions for module formats.";
            throw std::runtime_error(ss.str());
            break;
        }

        Modules.push_back(mod);
    }

    void LSystem::print(void) {

        std::cout << "L_System Created:" << std::endl
            << "\tRecursion: " << Recursion << std::endl
            << "\tAxium: " << Axium << std::endl
            << "\tProductions: " << std::endl;

        for (uint16_t i = 0; i < Productions.size(); i++) {
            std::cout << "\t\t" << Productions[i].Presessor << " --> " << Productions[i].Successor << std::endl;
        }

        std::cout << "\tDefines: " << std::endl;

        for (uint16_t i = 0; i < User_Defines.size(); i++) {
            std::cout << "\t\t" << User_Defines[i].first << " = " << User_Defines[i].second << std::endl;
        }

        std::cout << "\tModules: " << std::endl;

        for (auto X : Modules) {
            std::cout << "\t\t";
            X->print();
        }

    }

    void LSystem::is_match(std::shared_ptr<Modules::Module> X) {

        bool found{ false };

        for (uint16_t i = 0; i < Productions.size(); i++) {

            if (X->type() == Productions[i].Presessor[0]) {

                found = true;

                switch(X->type()){
                case 'F':
                    Temp_Defines.push_back({ Productions[i].Presessor[2], X->value1() });	// need to get data from text module into temp_vals to read for parse, this code will put the char written in the application and value of actual
                    parse_string(Productions[i].Successor);									// this should put the modules in the structure now
                    Temp_Defines.clear();													// clear Temp_defines
                    break;
                case 'f':
                    Temp_Defines.push_back({ Productions[i].Presessor[2], X->value1() });
                    parse_string(Productions[i].Successor);
                    Temp_Defines.clear();
                    break;
                case '+':
                    Temp_Defines.push_back({ Productions[i].Presessor[2], X->value1() });
                    parse_string(Productions[i].Successor);
                    Temp_Defines.clear();
                    break;
                case '-':
                    Temp_Defines.push_back({ Productions[i].Presessor[2], X->value1() });
                    parse_string(Productions[i].Successor);
                    Temp_Defines.clear();
                    break;
                case '^':
                    Temp_Defines.push_back({ Productions[i].Presessor[2], X->value1() });
                    parse_string(Productions[i].Successor);
                    Temp_Defines.clear();
                    break;
                case '&':
                    Temp_Defines.push_back({ Productions[i].Presessor[2], X->value1() });
                    parse_string(Productions[i].Successor);
                    Temp_Defines.clear();
                    break;
                case '$':
                    parse_string(Productions[i].Successor);
                    break;
                case '<':
                    Temp_Defines.push_back({ Productions[i].Presessor[2], X->value1() });
                    parse_string(Productions[i].Successor);
                    Temp_Defines.clear();
                    break;
                case '>':
                    Temp_Defines.push_back({ Productions[i].Presessor[2], X->value1() });
                    parse_string(Productions[i].Successor);
                    Temp_Defines.clear();
                    break;
                case '[':
                    parse_string(Productions[i].Successor);
                    break;
                case ']':
                    parse_string(Productions[i].Successor);
                    break;
                case '!':
                    Temp_Defines.push_back({ Productions[i].Presessor[2], X->value1() });
                    parse_string(Productions[i].Successor);
                    Temp_Defines.clear();
                    break;
                case 'A': case 'B': case 'C': case 'D': case 'E': case 'G': case 'H': case 'I':
                case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P': case 'Q':
                case 'R': case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y':
                case 'Z':
                    Temp_Defines.push_back({ Productions[i].Presessor[2], X->value1() });
                    Temp_Defines.push_back({ Productions[i].Presessor[4], X->value2() });
                    parse_string(Productions[i].Successor);
                    Temp_Defines.clear();
                    break;
                }
                return;

            }
        }
        if(found == false) {
            Modules.push_back(X);
        }
    }

}
