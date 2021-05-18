#ifndef PRODUCTION_RULE_H
#define PRODUCTION_RULE_H

#include <string>

// Production rule for the L-system
struct Production_Rule {

    Production_Rule(std::string p, std::string s)
        : Presessor{ p }, Successor{ s }
    {
    }

    std::string Presessor;
    std::string Successor;

};

#endif // PRODUCTION_RULE_H
