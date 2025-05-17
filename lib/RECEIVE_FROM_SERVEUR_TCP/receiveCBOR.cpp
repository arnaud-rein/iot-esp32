#include "./receiveCBOR.hpp"
using json = nlohmann::json;

bool START_PIPELINE = false;
void lireEtDecoderCBOR() {
    String reponse = Send_AT("AT+CARECV=0,100", 3000);
    Serial.println("=========== BRUTE RESPONSE ===========");
    Serial.println(reponse);

    // On isole la dernière ligne +CARECV: (cas où il y en aurait plusieurs)
    int lastIndex = reponse.lastIndexOf("+CARECV:");
    if (lastIndex == -1) {
        Serial.println("❌ Aucun +CARECV trouvé");
        return;
    }

    // Extrait uniquement cette ligne
    int endOfLine = reponse.indexOf('\n', lastIndex);
    String carecvLine = (endOfLine != -1) ? reponse.substring(lastIndex, endOfLine) : reponse.substring(lastIndex);
    carecvLine.trim();
    Serial.println("📦 Ligne sélectionnée : " + carecvLine);

    // Vérifie taille = 0
    if (carecvLine.indexOf(": 0") != -1) {
        Serial.println("📭 Aucun octet à décoder");
        return;
    }

    // Trouve la virgule
    int commaIndex = carecvLine.indexOf(',');
    if (commaIndex == -1) {
        Serial.println("❌ Virgule manquante");
        return;
    }

    // Données binaires après la virgule
    String brut = carecvLine.substring(commaIndex + 1);
    brut.trim();
    Serial.println("🔍 Donnée binaire brute : " + brut);

    std::vector<uint8_t> buffer;
    for (int i = 0; i < brut.length(); i++) {
        buffer.push_back((uint8_t) brut.charAt(i));
    }

    try {
        json j = json::from_cbor(buffer);
        Serial.print("✅ CBOR décodé : ");
        Serial.println(j.dump().c_str());

        if (j.contains("start") && j["start"] == true) {
            Serial.println("🚀 Pipeline activé !");
            // START_PIPELINE = true;
        }
    } catch (...) {
        Serial.println("❌ Erreur de décodage CBOR");
    }
}