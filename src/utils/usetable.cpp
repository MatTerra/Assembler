//
// Created by mateusberardo on 28/04/2021.
//
#include "usetable.h"

void UseTable::addSymbolUse(std::string symbol, uint16_t addr) {
    usedSymbols.insert(symbol);
    useTable[symbol].insert(useTable[symbol].end(), addr);
}

std::vector<uint16_t> UseTable::getSymbolUse(std::string symbol) {
    return useTable[symbol];
}

std::vector<std::string> UseTable::getUsedSymbols() {
    return std::vector<std::string>(usedSymbols.begin(), usedSymbols.end());
}
