#include "./receiveCBOR.hpp"
using json = nlohmann::json;

bool START_PIPELINE = false;

void lireEtDecoderCBOR() {
    String reponse = Send_AT("AT+CARECV=0,100", 3000);

    int startQuote = reponse.indexOf("\"");
    int endQuote = reponse.lastIndexOf("\"");

    if (startQuote == -1 || endQuote == -1 || endQuote <= startQuote) {
        Serial.println("❌ Pas de chaîne CBOR détectée");
        return;
    }

    String hexPayload = reponse.substring(startQuote + 1, endQuote);
    Serial.println("📦 Payload hex : " + hexPayload);

    // Convertir la chaîne hexadécimale en bytes (std::vector<uint8_t>)
    std::vector<uint8_t> cborData;
    for (int i = 0; i < hexPayload.length(); i += 2) {
        String byteString = hexPayload.substring(i, i + 2);
        uint8_t byte = (uint8_t) strtol(byteString.c_str(), nullptr, 16);
        cborData.push_back(byte);
    }

    try {
        json j = json::from_cbor(cborData);
        Serial.println("✅ JSON décodé :");
        Serial.println(j.dump().c_str());  // Affiche le JSON complet

        if (j.contains("start") && j["start"] == true) {
            Serial.println("🚀 START_PIPELINE activé !");
            START_PIPELINE = true;
        }

    } catch (const std::exception &e) {
        Serial.print("❌ Erreur de décodage CBOR : ");
        Serial.println(e.what());
    }
}
