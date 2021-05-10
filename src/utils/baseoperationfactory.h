//
// Created by mateusberardo on 01/03/2021.
//

#ifndef MONTADOR_BASEOPERATIONFACTORY_H
#define MONTADOR_BASEOPERATIONFACTORY_H

#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>
#include <operations/loadoperation.h>
#include <operations/storeoperation.h>
#include <operations/inputoperation.h>
#include <operations/outputoperation.h>
#include <operations/stopoperation.h>
#include <datatypes/spacedatatype.h>
#include <datatypes/constdatatype.h>
#include <operations/externoperation.h>
#include <operations/publicoperation.h>
#include "baseoperation.h"
#include "operations/addoperation.h"
#include "operations/suboperation.h"
#include "operations/muloperation.h"
#include "operations/divoperation.h"
#include "operations/jmpoperation.h"
#include "operations/jmpnoperation.h"
#include "operations/jmppoperation.h"
#include "operations/jmpzoperation.h"
#include "operations/copyoperation.h"
#include "datatype.h"
#include "stringutils.h"

template <typename T>
class BaseOperationFactory {

public:
    template <typename TDerived>
    void registerType(std::string name)
    {
        static_assert(std::is_base_of<T, TDerived>::value,
                "Factory::registerType doesn't accept this"
                " type because doesn'T derive from base class");
        _createFuncs[name] = &createFunc<TDerived>;
    }

    T* create(std::string name, std::vector<std::string> operands) {
        lowerCaseString(name);
        if (_createFuncs.find(name) != _createFuncs.end()) {
            return _createFuncs[name](operands);
        }
        return nullptr;
    }


private:
    template <typename TDerived>
    static T* createFunc(std::vector<std::string> operands)
    {
        return new TDerived(operands);
    }

    typedef T* (*PCreateFunc)(std::vector<std::string>);
    std::unordered_map<std::string ,PCreateFunc> _createFuncs;
};

static BaseOperationFactory<BaseOperation> *getBaseOperationFactory(){
    auto *operFactory = new BaseOperationFactory<BaseOperation>();
    operFactory->registerType<AddOperation>("add");
    operFactory->registerType<SubOperation>("sub");
    operFactory->registerType<MulOperation>("mul");
    operFactory->registerType<DivOperation>("div");
    operFactory->registerType<JmpOperation>("jmp");
    operFactory->registerType<JmpnOperation>("jmpn");
    operFactory->registerType<JmppOperation>("jmpp");
    operFactory->registerType<JmpzOperation>("jmpz");
    operFactory->registerType<CopyOperation>("copy");
    operFactory->registerType<LoadOperation>("load");
    operFactory->registerType<StoreOperation>("store");
    operFactory->registerType<InputOperation>("input");
    operFactory->registerType<OutputOperation>("output");
    operFactory->registerType<StopOperation>("stop");
    return operFactory;
}

static BaseOperationFactory<BaseOperation> *getModuleOperationFactory(){
    auto *operFactory = new BaseOperationFactory<BaseOperation>();
    operFactory->registerType<ExternOperation>("extern");
    operFactory->registerType<PublicOperation>("public");
    return operFactory;
}


#endif //MONTADOR_BASEOPERATIONFACTORY_H
