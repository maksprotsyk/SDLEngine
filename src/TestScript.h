//
// Created by Максим Процик on 01.08.2023.
//

#ifndef GAMETEST_TESTSCRIPT_H
#define GAMETEST_TESTSCRIPT_H

#include "GameObject/Components/Script.h"
#include "Serialization/ComponentFactory.h"

class TestScript: public Script
{
public:
    void OnStart() override;
    void OnUpdate() override;

    SERIALIZABLE()
};


#endif //GAMETEST_TESTSCRIPT_H
