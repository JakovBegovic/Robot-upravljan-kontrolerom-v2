#include "HrdwrController.h"

namespace
{
    /*
    *   HrdwrController private variables
    */

    // IN1, IN2, IN3, IN4
    const uint8_t ledPINs[ 4 ] = { 19, 23, 22, 21 };

    const uint8_t motorEnPIN = 13;
    const uint32_t pwmFreq = 5000; // Hz
    const float dutyCycleMin = 10.0f;


    /*
    *   HrdwrController private functions
    */

    void setupMcpwm()
    {
        mcpwm_gpio_init( MCPWM_UNIT_0, MCPWM0A, motorEnPIN );

        mcpwm_config_t pwm_config;
        pwm_config.frequency = pwmFreq;
        pwm_config.cmpr_a = 0;
        pwm_config.cmpr_b = 0;
        pwm_config.counter_mode = MCPWM_UP_COUNTER;
        pwm_config.duty_mode = MCPWM_DUTY_MODE_0;

        mcpwm_init( MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config );
    }

    void driveForward()
    {
        digitalWrite( ledPINs[ 0 ], HIGH );
        digitalWrite( ledPINs[ 1 ], LOW );
        digitalWrite( ledPINs[ 2 ], HIGH );
        digitalWrite( ledPINs[ 3 ], LOW );
    }

    void driveBackward()
    {
        digitalWrite( ledPINs[ 0 ], LOW );
        digitalWrite( ledPINs[ 1 ], HIGH );
        digitalWrite( ledPINs[ 2 ], LOW );
        digitalWrite( ledPINs[ 3 ], HIGH );
    }

    void turnLeft()
    {
        digitalWrite( ledPINs[ 0 ], HIGH );
        digitalWrite( ledPINs[ 1 ], LOW );
        digitalWrite( ledPINs[ 2 ], LOW );
        digitalWrite( ledPINs[ 3 ], HIGH );
    }

    void turnRight()
    {
        digitalWrite( ledPINs[ 0 ], LOW );
        digitalWrite( ledPINs[ 1 ], HIGH );
        digitalWrite( ledPINs[ 2 ], HIGH );
        digitalWrite( ledPINs[ 3 ], LOW );
    }

    void stop()
    {
        digitalWrite( ledPINs[ 0 ], LOW );
        digitalWrite( ledPINs[ 1 ], LOW );
        digitalWrite( ledPINs[ 2 ], LOW );
        digitalWrite( ledPINs[ 3 ], LOW );
    }
}

void HrdwrController::setup()
{
    for ( int i = 0;
          i < ( sizeof( ledPINs ) / sizeof(*ledPINs ) );
          i++ )
    {
        pinMode( ledPINs[ i ], OUTPUT );
        digitalWrite( ledPINs[ i ], LOW );
    }

    setupMcpwm();

    controlLEDs( CommsController::getRecievedMsg() );
}

void HrdwrController::controlLEDs( msgStruct msg )
{
    float dutyCycle = ( msg.speed / 4095.0f ) * 100.0f;

    if( dutyCycle < dutyCycleMin )
    {
        dutyCycle = dutyCycleMin;
    }

    if( msg.rotation == 0 )
    {
        switch( msg.moveDirection )
        {
            case 0:
                stop();
                break;

            case 1:
                driveForward();
                break;

            case -1:
                driveBackward();
                break;
        }
    }
    else
    {
        switch( msg.rotation )
        {
            case 1:
                turnRight();
                break;

            case -1:
                turnLeft();
                break;
        }
    }

    mcpwm_set_duty( MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, dutyCycle );
}