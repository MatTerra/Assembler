//
// Created by mateusberardo on 28/04/2021.
//

#ifndef MONTADOR_USETABLE_H
#define MONTADOR_USETABLE_H

#include <string>
#include <vector>
#include <set>
#include <unordered_map>

class UseTable {
public:
    void addSymbolUse(std::string symbol, uint16_t addr);
    std::vector<uint16_t> getSymbolUse(std::string symbol);

    std::vector<std::string> getUsedSymbols();

private:
    std::unordered_map<std::string, std::vector<uint16_t>> useTable;
    std::set<std::string> usedSymbols;
};


#endif //MONTADOR_USETABLE_H
