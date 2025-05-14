#ifndef CBOR_RECEIVER_HPP
#define CBOR_RECEIVER_HPP

#include <Arduino.h>
#include "SIM7080G_SERIAL.hpp"
#include <nlohmann/json.hpp>
#include <vector>

extern bool START_PIPELINE;

// Fonction pour lire les données CBOR depuis le SIM7080G et activer les flags si nécessaire
void lireEtDecoderCBOR();

#endif // CBOR_RECEIVER_HPP
