//
// Created by mateusberardo on 28/02/2021.
//

#ifndef MONTADOR_SYMBOLTABLE_H
#define MONTADOR_SYMBOLTABLE_H

#include <unordered_map>
#include <set>
#include <string>
#include <regex>
#include <exceptions/symbolalreadyexistsexception.h>
#include <exceptions/symbolnotfoundexception.h>
#include "stringutils.h"

class SymbolData{
public:
    SymbolData(){};
    SymbolData(uint16_t address): address(address), isExtern(false){};
    SymbolData(uint16_t address, bool isExtern):address(address),
        isExtern(isExtern){};

    uint16_t getAddress() { return address; }
    bool isExternSymbol() { return isExtern; }

    bool isPublicSymbol(){ return isPublic; };

    void setPublic(){ isPublic = true; };

private:
    uint16_t address;
    bool isExtern;
    bool isPublic = false;
};

class SymbolTable {

public:
    size_t getSymbolCount();
    void addSymbol(std::string symbol, uint16_t address, bool isExtern=false);
    void addExternSymbol(std::string symbol);
    bool hasSymbol(std::string symbol);
    uint16_t getSymbolAddress(std::string symbol);
    static bool isValidSymbol(std::string symbol);
    bool isExternSymbol(std::string symbol);

    bool isPublicSymbol(std::string string);

    void setPublicSymbol(std::string string);

    std::vector<std::string> getPublicSymbols();

private:
    std::unordered_map<std::string, SymbolData> symbolTable;
    std::set<std::string> publicSymbols;
};


#endif //MONTADOR_SYMBOLTABLE_H
