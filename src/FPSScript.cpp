//
// Created by Максим Процик on 06.08.2023.
//

#include "FPSScript.h"
#include "GameObject/Components/Rendering/RenderableText.h"
#include "Modules/Time.h"
#include "Game/Game.h"

REGISTER(FPSScript)

void FPSScript::OnUpdate()
{
    m_totalTime += Time::GetInstance()->TimeDelta;
    m_framesCounted++;
    m_toChangeScene -= Time::GetInstance()->TimeDelta;

    if (m_framesCounted > 60)
    {
        int fps = (int) ((float) m_framesCounted / (m_totalTime + 0.0001));
        RenderableText* textComp = m_GameObject->FindComponent<RenderableText>();
        textComp->SetText(std::to_string(fps));
        textComp->Width = 0.1;
        textComp->Height = 0.05;
        m_framesCounted = 0;
        m_totalTime = 0.0f;
    }
}