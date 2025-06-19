#include "MachineEtat.hpp"

// Constructeur pour initialiser la structure ATCommandTask
ATCommandTask::ATCommandTask(String cmd, String expected, int maxRetries, unsigned long timeout)
    : state(IDLE), command(cmd), expectedResponse(expected), responseBuffer(""), lastSendTime(0),
      retryCount(0), MAX_RETRIES(maxRetries), TIMEOUT(timeout), isFinished(false), result(""),
      onErrorCallback(nullptr) {}

// Constructeur de la machine d'état
MachineEtat::MachineEtat() {}
unsigned long periodRandom = millis();
// Implémentation de la machine d’état
bool MachineEtat::updateATState(ATCommandTask &task)
{
    bool responseFound = false; // Ajout d'un booléen
    switch (task.state)
    {
    case IDLE:
        Serial.println("[IDLE] Prêt à envoyer : " + String(task.command));
        task.retryCount = 0;
        task.responseBuffer = "";
        task.state = SENDING;
        return false;

    case SENDING:
        Serial.println("[SENDING] Envoi de : " + String(task.command));
        Sim7080G.println(task.command);
        task.lastSendTime = millis();
        task.state = WAITING_RESPONSE;
        return false;

    case WAITING_RESPONSE:

        while (Sim7080G.available())
        {
            String response = Sim7080G.readStringUntil('\n'); // Lire une ligne complète
            response.trim();                                  // Nettoyer les espaces et sauts de ligne

            Serial.println("[RESPONSE] " + response);

            // Ajouter la ligne au buffer de réponse
            task.responseBuffer += response + "\n";

            // Vérifier si la réponse contient la chaîne attendue
            bool responseOK = MachineEtat::analyzeResponse(task.responseBuffer, task.expectedResponse);
            if (responseOK)
            {
                responseFound = true;   // Marquer la réponse comme trouvée
                task.isFinished = true; // ⬅️ Marquer la tâche comme terminée
                task.state = END;
                Serial.println("[SUCCESS] Réponse valide pour " + String(task.command));
                return true;
                // Sortir immédiatement de la boucle while
            }
        }

        // Timeout uniquement si aucune réponse n'a été trouvée dans le lapse de temps determiné
        if (millis() - task.lastSendTime > task.TIMEOUT)
        {
            Serial.println("[TIMEOUT] Pas de réponse complète pour " + String(task.command));
            task.state = RETRY;
            return false;
        }
        break;

    case RETRY:
        if (task.retryCount < task.MAX_RETRIES)
        {
            task.retryCount++;
            Serial.println("[RETRY] Tentative " + String(task.retryCount) + " pour " + String(task.command));
            task.state = SENDING;
            return false;
        }
        else
        {
            Serial.println("[ERROR] Échec après " + String(task.MAX_RETRIES) + " essais pour " + String(task.command));
            task.state = ERROR;
            task.isFinished = true;
            return false; // TO DO : remplacer par isBlocked ou function qui reboot
        }

    case ERROR:
        Serial.println("[ERROR] Problème avec " + String(task.command));
        if (task.onErrorCallback)
        {
            task.onErrorCallback(task); // Appel du callback spécifique à la commande
        }
        else
        {
            // Comportement par défaut si aucun callback n'est défini
            Serial.println("[ERROR] Aucun gestionnaire d'erreur spécifique, retour à IDLE.");
            task.state = IDLE;
            task.retryCount = 0;
            task.responseBuffer = "";
            task.isFinished = false;
        }
        return false;

    case END:
        return true; // La tâche est terminée

    default:

        Serial.println("[DEFAULT] État non reconnu pour " + String(task.command));
        task.state = IDLE;
        return false; // La tâche a eu un problème
    }
}

bool MachineEtat::analyzeResponse(const String &response, const String &expected)
{
    if (response.length() == 0)
        return false; // Ignore si réponse vide

    if (response.indexOf(expected) >= 0)
    {
        Serial.println("[MATCH] Réponse complète détectée !");
        return true;
    }

    // Vérifie si la réponse contient "OK" à la fin, ce qui est souvent un indicateur
    if (response.endsWith("OK") || response.indexOf("ERROR") >= 0)
    {
        Serial.println("[INFO] Réponse détectée mais pas complète...");
        return false;
    }

    return false;
}
