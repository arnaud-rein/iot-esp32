#include <Arduino.h>
#include <unity.h>
#include <TEST.hpp>

void setUp() {
    // Ajout d'un délai pour éviter que le moniteur série manque les premiers logs
    delay(2000);  
    Serial.println("Test débuté...");
}

void tearDown() {
    Serial.println("Test terminé.");
}

// Test simple : Vérifier que 2 + 2 = 4
void test_math() {
    TEST_ASSERT_EQUAL(4, 2 + 2);
}
void test_math2() {
    TEST_ASSERT_EQUAL(5, 3 + 2);
}

void testH(){
    String result = test();
    TEST_ASSERT_EQUAL_STRING("success", result.c_str());
}



void setup() {
    Serial.begin(115200);
    delay(3000); // Attendre 3 secondes avant de commencer les tests
    UNITY_BEGIN();
    // RUN_TEST(test_math);
    // RUN_TEST(test_math2);
    RUN_TEST(testH);
    UNITY_END();
}

void loop() {
    // Laisser vide pour éviter une boucle infinie
}
