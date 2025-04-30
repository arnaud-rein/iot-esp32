#ifndef MACHINE_ETAT_HPP
#define MACHINE_ETAT_HPP

#include <Arduino.h>
#include <SIM7080G_SERIAL.hpp>
#include "ARGALI_PINOUT.hpp"


// Définition des états de la machine d'état
enum ATState {
    IDLE,
    SENDING,
    WAITING_RESPONSE,
    PARSING,
    RETRY,
    ERROR, 
    END
};

// Structure pour gérer une tâche AT
struct ATCommandTask {
    ATState state;
    String command;
    String expectedResponse;
    String responseBuffer;
    unsigned long lastSendTime;
    int retryCount;
    const int MAX_RETRIES;
    const unsigned long TIMEOUT;
    bool isFinished;  // ⬅️ Ajout pour bloquer la réexécution
    String result; 
    ATCommandTask(String cmd, String expected, int maxRetries, unsigned long timeout);
};

// Classe de la machine d'état
class MachineEtat {
public:
    MachineEtat();
    void updateATState(ATCommandTask &task);
};

bool analyzeResponse(const String& response, const String& expected);

#endif
