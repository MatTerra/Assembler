//
// Created by mateusberardo on 28/02/2021.
//

#ifndef MONTADOR_SYMBOLTABLE_H
#define MONTADOR_SYMBOLTABLE_H

#include <unordered_map>
#include <string>


class SymbolTable {

public:
    ~SymbolTable();
    static SymbolTable *getInstance();
    size_t getSymbolCount();
    void addSymbol(std::string symbol, uint16_t address);

    bool hasSymbol(std::string string);

    uint16_t getSymbolAddress(std::string symbol);

private:
    SymbolTable() = default;
    static SymbolTable *instance;
    std::unordered_map<std::string, uint16_t> symbolTable;
};


#endif //MONTADOR_SYMBOLTABLE_H
