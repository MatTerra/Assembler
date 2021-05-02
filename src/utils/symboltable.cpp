//
// Created by mateusberardo on 28/02/2021.
//

#include "symboltable.h"


size_t SymbolTable::getSymbolCount() {
    return symbolTable.size();
}

void SymbolTable::addSymbol(std::string symbol, uint16_t address, bool isExtern) {
    lowerCaseString(symbol);
    if(hasSymbol(symbol))
        throw SymbolAlreadyExistsException(symbol);

    symbolTable.emplace(symbol, SymbolData(address, isExtern));
}

bool SymbolTable::hasSymbol(std::string symbol) {
    lowerCaseString(symbol);
    return symbolTable.find(symbol) != symbolTable.end();
}

uint16_t SymbolTable::getSymbolAddress(std::string symbol) {
    lowerCaseString(symbol);
    if(!hasSymbol(symbol))
        throw SymbolNotFoundException(symbol);
    return symbolTable[symbol].getAddress();
}

bool SymbolTable::isValidSymbol(std::string symbol) {
    return std::regex_match(symbol, std::regex("[a-zA-Z_][a-zA-Z0-9_]{0,19}"));
}

void SymbolTable::addExternSymbol(std::string symbol) {
    addSymbol(symbol, 0, true);
}

bool SymbolTable::isExternSymbol(std::string symbol) {
    lowerCaseString(symbol);
    if(!hasSymbol(symbol))
        throw SymbolNotFoundException(symbol);
    return symbolTable[symbol].isExternSymbol();
}

bool SymbolTable::isPublicSymbol(std::string symbol) {
    lowerCaseString(symbol);
    if(!hasSymbol(symbol))
        throw SymbolNotFoundException(symbol);
    return symbolTable[symbol].isPublicSymbol();
}

void SymbolTable::setPublicSymbol(std::string symbol) {
    lowerCaseString(symbol);
    if(!hasSymbol(symbol))
        throw SymbolNotFoundException(symbol);
    symbolTable[symbol].setPublic();
}
