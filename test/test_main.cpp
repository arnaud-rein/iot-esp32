#include <Arduino.h>
#include <unity.h>
#include <TEST.hpp>
#include "STEP_GNSS.hpp"
#include "SIM7080G_CATM1.hpp"
#include "SIM7080G_GNSS.hpp"
// #include "STEP_COMPOSE_JSON.hpp"
#include "STEP_COMPOSE_JSON.cpp"
#include "PIPELINE_GLOBAL.hpp"

// String tableauJSONString;

// struct DataGNSS
// {
//     Gnss gnss;
// };

// extern DataGNSS dataGNSS[5];

void setUp()
{
    // Ajout d'un délai pour éviter que le moniteur série manque les premiers logs
    delay(2000);
    Serial.println("Test débuté...");
}

void tearDown()
{
    Serial.println("Test terminé.");
}

// Test simple : Vérifier que 2 + 2 = 4
void test_math()
{
    TEST_ASSERT_EQUAL(4, 2 + 2);
}
void test_math2()
{
    TEST_ASSERT_EQUAL(5, 3 + 2);
}

void testH()
{
    String result = test();
    TEST_ASSERT_EQUAL_STRING("success", result.c_str());
}

void createGNSS()
{
    // Simuler la création de données GNSS
    dataGNSS[0].gnss.coordonnees.latitude.ent = 47;
    dataGNSS[0].gnss.coordonnees.latitude.dec = "000000";
    dataGNSS[0].gnss.coordonnees.longitude.ent = 4;
    dataGNSS[0].gnss.coordonnees.longitude.dec = "000000";
    dataGNSS[0].gnss.coordonnees.latitude.full = "47.000000";
    dataGNSS[0].gnss.coordonnees.longitude.full = "4.000000";
}

void createJSON_TEST()
{
    createGNSS();             // Créer des données GNSS pour le test
    nbCoordonnees = 1;        // Simuler le nombre de coordonnées
    imei = "860016044667504"; // Simuler l'IMEI

    step_compose_json_function();
    String expectedJSON = String("[{\"name\":\"") + "860016044667504" +
                          "\",\"position\":{\"latitude\":" + "47.000000" +
                          ",\"longitude\":" + "4.000000" + "}}]";
    TEST_ASSERT_EQUAL_STRING(expectedJSON.c_str(), tableauJSONString.c_str());
    // TEST_ASSERT_EQUAL(5, 3 + 2);
}

void SEND_MESSAGE_CBOR_TEST()
{

    step_catm1_function();
}

void setup()
{
    Serial.begin(115200);
    delay(3000); // Attendre 3 secondes avant de commencer les tests
    UNITY_BEGIN();
    // RUN_TEST(test_math);
    // RUN_TEST(test_math2);
    // RUN_TEST(testH);
    RUN_TEST(createJSON_TEST);
    UNITY_END();
}

void loop()
{
    // Laisser vide pour éviter une boucle infinie
}
