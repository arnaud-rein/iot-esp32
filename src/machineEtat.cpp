    #include "MachineEtat.hpp"

    // Constructeur pour initialiser la structure ATCommandTask
    ATCommandTask::ATCommandTask(String cmd, String expected, int maxRetries, unsigned long timeout)
        : state(IDLE), command(cmd), expectedResponse(expected), responseBuffer(""), lastSendTime(0),
        retryCount(0), MAX_RETRIES(maxRetries), TIMEOUT(timeout), isFinished(false), result("") {}

    // Constructeur de la machine d'état
    MachineEtat::MachineEtat() {}

    // Implémentation de la machine d’état
    void MachineEtat::updateATState(ATCommandTask &task) {
        bool responseFound = false;  // Ajout d'un booléen
        switch (task.state) {
            case IDLE:
                Serial.println("[IDLE] Prêt à envoyer : " + String(task.command));
                task.retryCount = 0;
                task.responseBuffer = "";
                task.state = SENDING;
                break;

            case SENDING:
                Serial.println("[SENDING] Envoi de : " + String(task.command));
                Sim7080G.println(task.command);
                task.lastSendTime = millis();
                task.state = WAITING_RESPONSE;
                break;

            case WAITING_RESPONSE:
            
            
                while (Sim7080G.available()) {
                    String response = Sim7080G.readStringUntil('\n'); // Lire une ligne complète
                    response.trim(); // Nettoyer les espaces et sauts de ligne
            
                    Serial.println("[RESPONSE] " + response);
            
                    // Ajouter la ligne au buffer de réponse
                    task.responseBuffer += response + "\n";
            
                    // Vérifie si la réponse reçue contient la fin attendue
                    if (analyzeResponse(task.responseBuffer, task.expectedResponse)) {
                        Serial.println("[MATCH] Réponse complète détectée !");
                        task.state = PARSING;
                        responseFound = true;  // Marquer la réponse comme trouvée
                        task.isFinished = true;  // ⬅️ Marquer la tâche comme terminée
                        task.state = END;
                        Serial.println("[SUCCESS] Réponse valide pour " + String(task.command));
                        break;  // Sortir immédiatement de la boucle while
                    }
                }
            
                // Timeout uniquement si aucune réponse n'a été trouvée
                if (!responseFound && (millis() - task.lastSendTime > task.TIMEOUT)) {
                    Serial.println("[TIMEOUT] Pas de réponse complète pour " + String(task.command));
                    task.state = RETRY;
                }
                break;
        
                

            // case PARSING:
            //     Serial.println("[PARSING] Réponse reçue : " + task.responseBuffer);
            //     if (task.responseBuffer.indexOf(task.expectedResponse) >= 0) {
            //         Serial.println("[SUCCESS] Réponse valide pour " + String(task.command));
            //         task.isFinished = true;  // ⬅️ Marquer la tâche comme terminée
            //         task.state = IDLE;
            //     } else {
            //         Serial.println("[FAIL] Réponse incorrecte pour " + String(task.command));
            //         task.state = RETRY;
            //     }
            //     break;

            case RETRY:
                if (task.retryCount < task.MAX_RETRIES) {
                    task.retryCount++;
                    Serial.println("[RETRY] Tentative " + String(task.retryCount) + " pour " + String(task.command));
                    task.state = SENDING;
                } else {
                    Serial.println("[ERROR] Échec après " + String(task.MAX_RETRIES) + " essais pour " + String(task.command));
                    task.state = ERROR;
                    task.isFinished = true; // TO DO : remplacer par isBlocked ou function qui reboot 
                }
                break;

            case ERROR:
                Serial.println("[ERROR] Problème avec " + String(task.command));
                task.state = IDLE;
                break;

            case END:
                
                break;
        }
    }


    bool analyzeResponse(const String& response, const String& expected) {
        if (response.length() == 0) return false; // Ignore si réponse vide

        if (response.indexOf(expected) >= 0) {
            Serial.println("[MATCH] Réponse complète détectée !");
            return true;
        }

        // Vérifie si la réponse contient "OK" à la fin, ce qui est souvent un indicateur
        if (response.endsWith("OK") || response.indexOf("ERROR") >= 0) {
            Serial.println("[INFO] Réponse détectée mais pas complète...");
            return false;
        }

        return false;
    }

