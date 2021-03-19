//
// Created by mateusberardo on 28/02/2021.
//

#include "symboltable.h"

size_t SymbolTable::getSymbolCount() {
    return symbolTable.size();
}

void SymbolTable::addSymbol(std::string symbol, uint16_t address) {
    lowerCaseString(symbol);
    if(hasSymbol(symbol))
        throw SymbolAlreadyExistsException(symbol);
    symbolTable.emplace(symbol, address);
}



bool SymbolTable::hasSymbol(std::string symbol) {
    lowerCaseString(symbol);
    return symbolTable.find(symbol) != symbolTable.end();
}

uint16_t SymbolTable::getSymbolAddress(std::string symbol) {
    lowerCaseString(symbol);
    if(!hasSymbol(symbol))
        throw SymbolNotFoundException(symbol);
    return symbolTable[symbol];
}

bool SymbolTable::isValidSymbol(std::string symbol) {
    return std::regex_match(symbol, std::regex("[a-zA-Z_][a-zA-Z0-9_]{0,19}"));
}
