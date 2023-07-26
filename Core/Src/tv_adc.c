/**
 * @file tv_adc.c
 * @author darkbe
 * @brief 
 * @version 0.1
 * @date 2023-07-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <main.h>
#include <tv_adc.h>
#include <tv_gpio.h>
#include <hw_ints.h>

void TV_ADC0_Init(void)
{
    /* Enable ADC0 */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(ADC0_BASE);

    /* configure pins as ADC */
    /** uncomment the following code to enable ADC0 functions
     * Channel0-7 are used for tracking module.
     * Channel8-11 are used for motor current detection.
     * Channel12 is used for battery voltage detection.
     * Channel13 is used for battery current detection.
     */
    // GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3); // ADC0_Channel0
    // GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_2); // ADC0_Channel1
    // GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_1); // ADC0_Channel2
    // GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_0); // ADC0_Channel3
    // GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_7); // ADC0_Channel4
    // GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_6); // ADC0_Channel5
    // GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_5); // ADC0_Channel6
    // GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_4); // ADC0_Channel7
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_5); // ADC0_Channel8
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_4); // ADC0_Channel9
    GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_3); // ADC0_Channel10
    GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_2); // ADC0_Channel11
    GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_1); // ADC0_Channel12
    GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_0); // ADC0_Channel13
    // GPIOPinTypeADC(GPIO_PORTK_BASE, GPIO_PIN_2); // ADC0_Channel14
    // GPIOPinTypeADC(GPIO_PORTK_BASE, GPIO_PIN_3); // ADC0_Channel15

    /* ADC sequence configuration */
    /* ADC0 Sequence0: 
     * has 8 sample channels, recommended to be 8 channel tracking module sampling. */
    /* ADC0 Sequence1:
     * has 4 sample channels, recommended to be 4 channel motor current sampling. */
    /* ADC0 Sequence2:
     * has 4 sample channels, recommended to be battery volt&current sampling */
    /* ADC0 Sequence3:
     * has 1 sample channel, recommanded to be inner temperature sensor sampling. */
    // ADCSequenceDisable(ADC0_BASE, ADC_SEQUENCE_0); // disable a sample sequence
    // ADCSequenceConfigure(ADC0_BASE, ADC_SEQUENCE_0, ADC_TRIGGER_PROCESSOR, 0);
    // ADCHardwareOversampleConfigure(ADC0_BASE, 5);
    // ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQUENCE_0, 0, ADC_CTL_CH0 ); // tracking module channel 1
    // ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQUENCE_0, 1, ADC_CTL_CH1 ); // tracking module channel 2
    // ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQUENCE_0, 2, ADC_CTL_CH2 ); // tracking module channel 3
    // ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQUENCE_0, 3, ADC_CTL_CH3 ); // tracking module channel 4
    // ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQUENCE_0, 4, ADC_CTL_CH4 ); // tracking module channel 5
    // ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQUENCE_0, 5, ADC_CTL_CH5 ); // tracking module channel 6
    // ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQUENCE_0, 6, ADC_CTL_CH6 ); // tracking module channel 7
    // ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQUENCE_0, 7, ADC_CTL_CH7 | ADC_CTL_IE | ADC_CTL_END); // tracking module channel 8
    // ADCSequenceEnable(ADC0_BASE, ADC_SEQUENCE_0); // enables a sample sequence
    // ADCIntClear(ADC0_BASE, ADC_SEQUENCE_0);       // clear sequence interrupt flag

    ADCSequenceDisable(ADC0_BASE, ADC_SEQUENCE_1); // disable a sample sequence
    ADCSequenceConfigure(ADC0_BASE, ADC_SEQUENCE_1, ADC_TRIGGER_PROCESSOR, 0);
    ADCHardwareOversampleConfigure(ADC0_BASE, 5);
    ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQUENCE_1, 0, ADC_CTL_CH8 ); // motor1 current
    ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQUENCE_1, 1, ADC_CTL_CH9 ); // motor2 current
    ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQUENCE_1, 2, ADC_CTL_CH10 ); // motor3 current
    ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQUENCE_1, 3, ADC_CTL_CH11 | ADC_CTL_IE | ADC_CTL_END); // motor4 current
    ADCSequenceEnable(ADC0_BASE, ADC_SEQUENCE_1); // enables a sample sequence
    ADCIntClear(ADC0_BASE, ADC_SEQUENCE_1);       // clear sequence interrupt flag

    ADCSequenceConfigure(ADC0_BASE, ADC_SEQUENCE_2, ADC_TRIGGER_PROCESSOR, 0);
    ADCHardwareOversampleConfigure(ADC0_BASE, 5);
    ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQUENCE_2, 0, ADC_CTL_CH12 ); // battery voltage
    ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQUENCE_2, 1, ADC_CTL_CH13 | ADC_CTL_IE | ADC_CTL_END); // battery current
    ADCSequenceEnable(ADC0_BASE, ADC_SEQUENCE_2); // enables a sample sequence
    ADCIntClear(ADC0_BASE, ADC_SEQUENCE_2);       // clear sequence interrupt flag

    ADCSequenceDisable(ADC0_BASE, ADC_SEQUENCE_3); // disable a sample sequence
    ADCSequenceConfigure(ADC0_BASE, ADC_SEQUENCE_3, ADC_TRIGGER_PROCESSOR, 0);
    ADCHardwareOversampleConfigure(ADC0_BASE, 5);
    ADCSequenceStepConfigure(ADC0_BASE, ADC_SEQUENCE_3, 0, ADC_CTL_TS | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, ADC_SEQUENCE_3); // enables a sample sequence
    ADCIntClear(ADC0_BASE, ADC_SEQUENCE_3);       // clear sequence interrupt flag
}

void ADC_GetMotorCurrent(uint32_t *ADCResultBuf)
{
    ADCProcessorTrigger(ADC0_BASE, ADC_SEQUENCE_1);             // trigger ADC sampling
    while(!ADCIntStatus(ADC0_BASE, ADC_SEQUENCE_1, false));     // wait for sampling end
    ADCIntClear(ADC0_BASE, ADC_SEQUENCE_1);                     // clear ADC interrupt flag
    ADCSequenceDataGet(ADC0_BASE, ADC_SEQUENCE_1, ADCResultBuf);// read ADC sampling value
}

void ADC_GetBatteryVoltAndCurrent(uint32_t *ADCResultBuf)
{
    ADCProcessorTrigger(ADC0_BASE, ADC_SEQUENCE_2);              // trigger ADC sampling
    while(!ADCIntStatus(ADC0_BASE, ADC_SEQUENCE_2, false));      // wait for sampling end
    ADCIntClear(ADC0_BASE, ADC_SEQUENCE_2);                      // clear ADC interrupt flag
    ADCSequenceDataGet(ADC0_BASE, ADC_SEQUENCE_2, ADCResultBuf); // read ADC sampling value
}

void ADC_GetInnerTemp(uint32_t *ADCResultBuf)
{
    ADCProcessorTrigger(ADC0_BASE, ADC_SEQUENCE_3);              // trigger ADC sampling
    while(!ADCIntStatus(ADC0_BASE, ADC_SEQUENCE_3, false));      // wait for sampling end
    ADCIntClear(ADC0_BASE, ADC_SEQUENCE_3);                      // clear ADC interrupt flag
    ADCSequenceDataGet(ADC0_BASE, ADC_SEQUENCE_3, ADCResultBuf); // read ADC sampling value
}

