//
// Created by mateusberardo on 28/02/2021.
//

#include "symboltable.h"
#include "symbolnotfoundexception.h"

SymbolTable* SymbolTable::instance = nullptr;

SymbolTable *SymbolTable::getInstance() {
    if (instance == nullptr){
        instance = new SymbolTable();
    }
    return instance;
}

size_t SymbolTable::getSymbolCount() {
    return symbolTable.size();
}

void SymbolTable::addSymbol(std::string symbol, uint16_t address) {
    symbolTable.emplace(symbol, address);
}

bool SymbolTable::hasSymbol(std::string symbol) {
    return symbolTable.find(symbol) != symbolTable.end();
}

SymbolTable::~SymbolTable() {
    instance = nullptr;
}

uint16_t SymbolTable::getSymbolAddress(std::string symbol) {
    if(!instance->hasSymbol(symbol))
        throw SymbolNotFoundException(symbol);
    return symbolTable[symbol];
}
