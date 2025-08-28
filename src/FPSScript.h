//
// Created by Максим Процик on 06.08.2023.
//

#ifndef GAMETEST_FPSSCRIPT_H
#define GAMETEST_FPSSCRIPT_H

#include "GameObject/Components/Script.h"
#include "Serialization/ComponentFactory.h"

class FPSScript: public Script
{
public:
    void OnUpdate() override;
    SERIALIZABLE()
private:
    float m_toChangeScene = 5.0f;
    float m_totalTime = 0.0f;
    int m_framesCounted = 0;
};


#endif //GAMETEST_FPSSCRIPT_H
