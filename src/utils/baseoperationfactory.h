//
// Created by mateusberardo on 01/03/2021.
//

#ifndef MONTADOR_BASEOPERATIONFACTORY_H
#define MONTADOR_BASEOPERATIONFACTORY_H

#include <unordered_map>
#include <string>
#include <vector>
#include "baseoperation.h"
#include "operations/addoperation.h"
#include "operations/suboperation.h"

template <typename T>
class BaseFactory {

public:
    template <typename TDerived>
    void registerType(std::string name)
    {
        static_assert(std::is_base_of<T, TDerived>::value,
                "Factory::registerType doesn't accept this"
                " type because doesn'T derive from base class");
        _createFuncs[name] = &createFunc<TDerived>;
    }
    T* create(std::string name, std::vector<uint16_t> operands) {
        if (_createFuncs.find(name) != _createFuncs.end()) {
            return _createFuncs[name](operands);
        }
        return nullptr;
    }


private:
    template <typename TDerived>
    static T* createFunc(std::vector<uint16_t> operands)
    {
        return new TDerived(operands);
    }

    typedef T* (*PCreateFunc)(std::vector<uint16_t>);
    std::unordered_map<std::string ,PCreateFunc> _createFuncs;
};

static BaseFactory<BaseOperation> *getBaseOperationFactory(){
    auto *operFactory = new BaseFactory<BaseOperation>();
    operFactory->registerType<AddOperation>("add");
    operFactory->registerType<SubOperation>("sub");
    return operFactory;
}


#endif //MONTADOR_BASEOPERATIONFACTORY_H