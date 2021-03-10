//
// Created by mateusberardo on 28/02/2021.
//

#include <exceptions/symbolalreadyexistsexception.h>
#include "symboltable.h"
#include "exceptions/symbolnotfoundexception.h"

size_t SymbolTable::getSymbolCount() {
    return symbolTable.size();
}

void SymbolTable::addSymbol(std::string symbol, uint16_t address) {
    if(hasSymbol(symbol))
        throw SymbolAlreadyExistsException(symbol);
    symbolTable.emplace(symbol, address);
}

bool SymbolTable::hasSymbol(std::string symbol) {
    return symbolTable.find(symbol) != symbolTable.end();
}

uint16_t SymbolTable::getSymbolAddress(std::string symbol) {
    if(!hasSymbol(symbol))
        throw SymbolNotFoundException(symbol);
    return symbolTable[symbol];
}
