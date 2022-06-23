#include <unity.h>
#include <timer_systick.h>
#include <pin_gpio.h>
#include <stm32f1xx.h>
#include <stdbool.h>

static GPIO_TypeDef miPuerto;
#define MI_PIN 13
static Pin miPin;
void setUp(void)
{
    miPin = (Pin){0};
    miPuerto = (GPIO_TypeDef){.CRL=0X44444444, .CRH=0X44444444};
    Pin_init(&miPin,&miPuerto,MI_PIN);
}
void tearDown(void){}

//LEER EL PIN
static void pin_debeLeerEstadoPin_0(void)
{
    const bool estadoPin = Pin_lee(&miPin);
    TEST_ASSERT_FALSE(estadoPin);
}

static void pin_debeLeerEstadoPin_1(void)
{
    miPuerto.IDR =1 << MI_PIN;
    const bool estadoPin = Pin_lee(&miPin);
    TEST_ASSERT_TRUE(estadoPin);
}

static void pin_debePermitirPonerSalidaEnCero(void)
{
    miPuerto.IDR =1 << MI_PIN;
    Pin_escribe(&miPin,0);
    const uint32_t reset = miPuerto.BRR | (miPuerto.BSRR >> 16);
    const uint32_t set = miPuerto.BSRR & ((1UL << 16)-1UL);
    enum{RESET_ESPERADO = (1UL << MI_PIN), SET_ESPERADO = 0};
    TEST_ASSERT_EQUAL_HEX32(RESET_ESPERADO,reset);
    TEST_ASSERT_EQUAL_HEX32(RESET_ESPERADO,set);
}

static void pin_debePermitirPonerSalidaEnUno(void)
{
    miPuerto.IDR =1 << MI_PIN;
    Pin_escribe(&miPin,1);
    const uint32_t reset = miPuerto.BRR | (miPuerto.BSRR >> 16);
    const uint32_t set = miPuerto.BSRR & ((1UL << 16)-1UL);
    enum{RESET_ESPERADO =0, SET_ESPERADO = (1UL << MI_PIN)};
    TEST_ASSERT_EQUAL_HEX32(RESET_ESPERADO,reset);
    TEST_ASSERT_EQUAL_HEX32(RESET_ESPERADO,set);
}


int main(void)
{
    TimerSysTick_init();
    TimerSysTick_esperaMilisegundos(500);
    UNITY_BEGIN();
    RUN_TEST (pin_debeLeerEstadoPin_0);
    RUN_TEST (pin_debeLeerEstadoPin_1);
    RUN_TEST (pin_debePermitirPonerSalidaEnCero);
    RUN_TEST (pin_debePermitirPonerSalidaEnUno);
    UNITY_END();
    for (;;);
    
}