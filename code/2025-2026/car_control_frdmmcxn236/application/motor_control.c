#include "motor_control.h"
#include "board.h"
#include "peripherals.h"
#include "fsl_device_registers.h"
#include "fsl_ctimer.h"
#include "fsl_clock.h"
#include "fsl_common.h"
#include "fsl_debug_console.h"

#include "FreeRTOS.h"
#include "task.h"

#define MOTOR_PWM_MIN_US 1000U
#define MOTOR_PWM_MAX_US 1200U
#define MOTOR_PWM_DIRECTION_MAX_DIFF_US 40U

static uint32_t motor_us_to_ticks(uint16_t us)
{
#ifdef CTIMER1_TICK_FREQ
    return (CTIMER1_TICK_FREQ / 1000000U) * us;
#else
    uint32_t timerClock = CLOCK_GetFreq(kCLOCK_BusClk);
    return (timerClock / 1000000U) * us;
#endif
}

static uint32_t motor_get_period_ticks(void)
{
#ifdef CTIMER1_TICK_FREQ
    return (CTIMER1_TICK_FREQ / 1000U) * 20U;
#else
    uint32_t timerClock = CLOCK_GetFreq(kCLOCK_BusClk);
    return (timerClock / 1000U) * 20U;
#endif
}

static uint16_t motor_clamp_pulse_us(int32_t pulseWidthUs)
{
    if (pulseWidthUs < (int32_t)MOTOR_PWM_MIN_US) {
        return MOTOR_PWM_MIN_US;
    }
    if (pulseWidthUs > (int32_t)MOTOR_PWM_MAX_US) {
        return MOTOR_PWM_MAX_US;
    }
    return (uint16_t)pulseWidthUs;
}

static void motor_set_dual_pulse_us(uint16_t leftPulseUs, uint16_t rightPulseUs)
{
    uint32_t leftDutyTicks = motor_get_period_ticks() - motor_us_to_ticks(leftPulseUs);
    uint32_t rightDutyTicks = motor_get_period_ticks() - motor_us_to_ticks(rightPulseUs);

    CTIMER_UpdatePwmPulsePeriod(CTIMER1_PERIPHERAL, CTIMER1_PWM_0_CHANNEL, leftDutyTicks);
    CTIMER_UpdatePwmPulsePeriod(CTIMER1_PERIPHERAL, CTIMER1_PWM_1_CHANNEL, rightDutyTicks);
}

void Init_pwm_motor(void)
{
    uint32_t periodTicks = motor_get_period_ticks();

    // Initialiser le CTimer
    ctimer_config_t ctimerConfig;
    CTIMER_GetDefaultConfig(&ctimerConfig);
    CTIMER_Init(CTIMER1_PERIPHERAL, &ctimerConfig);

    // Démarrer le timer
    CTIMER_StartTimer(CTIMER1_PERIPHERAL);

    // 1. Envoyer 2000 µs inversé (0 µs) et brancher la batterie
    PRINTF("Branchez la batterie maintenant (2000 µs inversé)...\r\n");
    CTIMER_StopTimer(CTIMER1_PERIPHERAL);
    CTIMER_SetupPwmPeriod(CTIMER1_PERIPHERAL, CTIMER1_PWM_PERIOD_CH, CTIMER1_PWM_0_CHANNEL, periodTicks,
                          periodTicks - motor_us_to_ticks(2000), false);
    CTIMER_SetupPwmPeriod(CTIMER1_PERIPHERAL, CTIMER1_PWM_PERIOD_CH, CTIMER1_PWM_1_CHANNEL, periodTicks,
                          periodTicks - motor_us_to_ticks(2000), false);
    CTIMER_StartTimer(CTIMER1_PERIPHERAL);
    SDK_DelayAtLeastUs(4000000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    //vTaskDelay(pdMS_TO_TICKS(50000));

    // 2. Envoyer 1000 µs inversé (1000 µs)
    PRINTF("Signal à 1000 µs (inversé)...\r\n");
    CTIMER_StopTimer(CTIMER1_PERIPHERAL);
    CTIMER_SetupPwmPeriod(CTIMER1_PERIPHERAL, CTIMER1_PWM_PERIOD_CH, CTIMER1_PWM_0_CHANNEL, periodTicks,
                          periodTicks - motor_us_to_ticks(1000), false);
    CTIMER_SetupPwmPeriod(CTIMER1_PERIPHERAL, CTIMER1_PWM_PERIOD_CH, CTIMER1_PWM_1_CHANNEL, periodTicks,
                          periodTicks - motor_us_to_ticks(1000), false);
    CTIMER_StartTimer(CTIMER1_PERIPHERAL);
    SDK_DelayAtLeastUs(3000000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    //vTaskDelay(pdMS_TO_TICKS(50000));

//    // 3. Passer à 1500 µs inversé (500 µs)
//    PRINTF("Point neutre (1500 µs inversé)...\r\n");
//    CTIMER_StopTimer(CTIMER1_PERIPHERAL);
//    CTIMER_SetupPwmPeriod(CTIMER1_PERIPHERAL, CTIMER1_PWM_PERIOD_CH, CTIMER1_PWM_0_CHANNEL, periodTicks,
//                          periodTicks - motor_us_to_ticks(1500), false);
//    CTIMER_SetupPwmPeriod(CTIMER1_PERIPHERAL, CTIMER1_PWM_PERIOD_CH, CTIMER1_PWM_1_CHANNEL, periodTicks,
//                          periodTicks - motor_us_to_ticks(1500), false);
//    CTIMER_StartTimer(CTIMER1_PERIPHERAL);
//    SDK_DelayAtLeastUs(1000000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    //vTaskDelay(pdMS_TO_TICKS(50000));
}

void motor_update(int direction, uint16_t speed)
{
    uint16_t clampedSpeed = speed;
    if (clampedSpeed > 100U) {
        clampedSpeed = 100U;
    }

    int32_t clampedDirection = direction;
    if (clampedDirection < -100) {
        clampedDirection = -100;
    } else if (clampedDirection > 100) {
        clampedDirection = 100;
    }

    uint16_t basePulseUs = motor_clamp_pulse_us((int32_t)(MOTOR_PWM_MIN_US + (uint32_t)clampedSpeed * 2U));
    int32_t directionOffsetUs = (clampedDirection * (int32_t)MOTOR_PWM_DIRECTION_MAX_DIFF_US) / 100;

    uint16_t leftPulseUs = motor_clamp_pulse_us((int32_t)basePulseUs + directionOffsetUs);
    uint16_t rightPulseUs = motor_clamp_pulse_us((int32_t)basePulseUs - directionOffsetUs);

    motor_set_dual_pulse_us(leftPulseUs, rightPulseUs);
}
