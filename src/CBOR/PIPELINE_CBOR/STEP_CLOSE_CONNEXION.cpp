#include "./../pipeline.hpp"
ATCommandTask taskCBOR_CLOSE("AT+CACLOSE=0", "OK", 15, 100);
void STEP_CLOSE_CONNEXION_FUNCTION()
{
    if (chrono(100))
    {
        Serial.println("[STEP_CLOSE_CONNEXION] init");
        if (resetCommandCLOSE_CONNEXION)
        {
        }
        if (!taskCBOR_CLOSE.isFinished)
        {
            machineCBOR.updateATState(taskCBOR_CLOSE);
        }
        else
        {
            Serial.println("[STEP_CLOSE_CONNEXION] success");
            taskCBOR_CLOSE.state = IDLE;
            taskCBOR_CLOSE.isFinished = false;
            resetCommandCLOSE_CONNEXION = false;
            currentStepCBOR = STEP_END;
        }
    }
}