
#include "bee.h"

/*
    F_CPU = 16MHz
    Prescaler : 64
    Pwm mode : center
    ->Fpwm = 16M*2/64
*/

#define F_TIMER_0          (CS02 << 0) | (CS01 << 0) | (CS00 << 1)
#define F_TIMER_1          (CS12 << 0) | (CS11 << 0) | (CS10 << 1)
#define F_TIMER_2          (CS22 << 0) | (CS21 << 0) | (CS20 << 1)

void pwm_init(PWM_PIN pin, uint16_t value)
{
    // switch (pin)
    // {
    // case PWM_PD3:
    // {
    //     DDRD |= (1 << 3);
    //     TCCR2A |= (1 << COM2B1) | (0 << WGM21) | (1 << WGM20);
    //     TCCR2B |= (0 << WGM22) | F_TIMER_2;
    //     pwm_write(PWM_PD3, value);
    //     break;
    // }
    // case PWM_PD5:
    // {
    //     DDRD |= (1 << 5);
    //     TCCR0A |= (1 << COM0B1) | (0 << WGM01) | (1 << WGM00);
    //     TCCR0B |= (0 << WGM02) | F_TIMER_0;
    //     pwm_write(PWM_PD5, value);
    //     break;
    // }
    // case PWM_PD6:
    // {
    //     DDRD |= (1 << 6);
    //     TCCR0A |= (1 << COM0A1) | (0 << WGM01) | (1 << WGM00);
    //     TCCR0B |= (0 << WGM02) | F_TIMER_0;
    //     pwm_write(PWM_PD6, value);
    //     break;
    // }
    // case PWM_PB1:
    // {
    //     DDRB |= (1 << 1);
    //     TCCR1A |= (1 << COM1A1) | (1 << WGM11) | (0 << WGM10);
    //     TCCR1B |= (1 << WGM13) | (0 << WGM12) | F_TIMER_1;
    //     ICR1H = 0x00;
    //     ICR1L = 0xff;
    //     pwm_write(PWM_PB1, value);
    //     break;
    // }
    // case PWM_PB2:
    // {
    //     DDRB |= (1 << 2);
    //     TCCR1A |= (1 << COM1B1) | (1 << WGM11) | (0 << WGM10);
    //     TCCR1B |= (1 << WGM13) | (0 << WGM12) | F_TIMER_1;
    //     ICR1H = 0x00;
    //     ICR1L = 0xff;
    //     pwm_write(PWM_PB2, value);
    //     break;
    // }
    // case PWM_PB3:
    // {
    //     DDRB |= (1 << 3);
    //     TCCR2A |= (1 << COM2A1) | (0 << WGM21) | (1 << WGM20);
    //     TCCR2B |= (0 << WGM22) | F_TIMER_2;
    //     pwm_write(PWM_PB3, value);
    //     break;
    // }
    // default:
    //     break;
    // }

    switch (pin)
    {
    case PWM_PD3:
    {
        DDRD |= (1 << 3);
        break;
    }
    case PWM_PD5:
    {
        DDRD |= (1 << 5);
        break;
    }
    case PWM_PD6:
    {
        DDRD |= (1 << 6);
        break;
    }
    case PWM_PB1:
    {
        DDRB |= (1 << 1);
        break;
    }
    case PWM_PB2:
    {
        DDRB |= (1 << 2);
        break;
    }
    case PWM_PB3:
    {
        DDRB |= (1 << 3);
        break;
    }
    default:
        break;
    }

    TCCR1A = 0b10100001;
    TCCR1B = 0b00000000|(0x01);

    TCCR2A = 0b10000001;
    TCCR2B = 0b00000000|(0x01);
}

void pwm_write(PWM_PIN pin, uint16_t value)
{
    switch (pin)
    {
    case PWM_PD3:
    {
        OCR2B = value;
        break;
    }
    case PWM_PD5:
    {
        OCR0B = value;
        break;
    }
    case PWM_PD6:
    {
        OCR0A = value;
        break;
    }
    case PWM_PB1:
    {
        OCR1AH = 0;
        OCR1AL = value;
        break;
    }
    case PWM_PB2:
    {
        OCR1BH = 0;
        OCR1BL = value;
        break;
    }
    case PWM_PB3:
    {
        OCR2A = value;
        break;
    }
    default:
        break;
    }
}

extern void bldc_init(void)
{
    pwm_init(DRV8302_INHA, 0);
    pwm_init(DRV8302_INHB, 0);
    pwm_init(DRV8302_INHC, 0);

    set_output(DRV8302_CONTROL_DIR,DRV8302_ENABLE);

    set_output(DRV8302_HANDLE_DIR,DRV8302_OC_ADJ);
    set_output(DRV8302_HANDLE_DIR,DRV8302_M_PWM);
    set_output(DRV8302_HANDLE_DIR,DRV8302_M_OC);

    WRITE(DRV8302_CONTROL_PORT,DRV8302_ENABLE,1);

    WRITE(DRV8302_HANDLE_PORT,DRV8302_OC_ADJ,1);
    WRITE(DRV8302_HANDLE_PORT,DRV8302_M_PWM,1);
    WRITE(DRV8302_HANDLE_PORT,DRV8302_M_OC,0);
}

const int sine_array[200] = {0, 79, 158, 237, 316, 395, 473, 552, 631, 710, 789, 867, 946, 1024, 1103, 1181, 1260, 1338, 1416, 1494, 1572, 1650, 1728, 1806, 1883, 1961, 2038, 2115, 2192, 2269, 2346, 2423, 2499, 2575, 2652, 2728, 2804, 2879, 2955, 3030, 3105, 3180, 3255, 3329, 3404, 3478, 3552, 3625, 3699, 3772, 3845, 3918, 3990, 4063, 4135, 4206, 4278, 4349, 4420, 4491, 4561, 4631, 4701, 4770, 4840, 4909, 4977, 5046, 5113, 5181, 5249, 5316, 5382, 5449, 5515, 5580, 5646, 5711, 5775, 5839, 5903, 5967, 6030, 6093, 6155, 6217, 6279, 6340, 6401, 6461, 6521, 6581, 6640, 6699, 6758, 6815, 6873, 6930, 6987, 7043, 7099, 7154, 7209, 7264, 7318, 7371, 7424, 7477, 7529, 7581, 7632, 7683, 7733, 7783, 7832, 7881, 7930, 7977, 8025, 8072, 8118, 8164, 8209, 8254, 8298, 8342, 8385, 8428, 8470, 8512, 8553, 8594, 8634, 8673, 8712, 8751, 8789, 8826, 8863, 8899, 8935, 8970, 9005, 9039, 9072, 9105, 9138, 9169, 9201, 9231, 9261, 9291, 9320, 9348, 9376, 9403, 9429, 9455, 9481, 9506, 9530, 9554, 9577, 9599, 9621, 9642, 9663, 9683, 9702, 9721, 9739, 9757, 9774, 9790, 9806, 9821, 9836, 9850, 9863, 9876, 9888, 9899, 9910, 9920, 9930, 9939, 9947, 9955, 9962, 9969, 9975, 9980, 9985, 9989, 9992, 9995, 9997, 9999, 10000, 10000};

float _sin(float a)
{
    if (a < _PI_2)
    {
        return 0.0001f * sine_array[_round(126.6873f * a)];
    }
    else if (a < _PI)
    {
        return 0.0001f * sine_array[398 - _round(126.6873f * a)];
    }
    else if (a < _3PI_2)
    {
        return -0.0001f * sine_array[-398 + _round(126.6873f * a)];
    }
    else
    {
        return -0.0001f * sine_array[796 - _round(126.6873f * a)];
    }
}

float _cos(float a)
{
    float a_sin = a + _PI_2;
    a_sin = a_sin > _2PI ? a_sin - _2PI : a_sin;
    return _sin(a_sin);
}

float normalizeAngle(float angle)
{
    float a = fmod(angle, _2PI);
    return a >= 0 ? a : (a + _2PI);
}

volatile uint8_t voltage_limit = 24;
volatile float dc_a; //!< currently set duty cycle on phaseA
volatile float dc_b; //!< currently set duty cycle on phaseB
volatile float dc_c; //!< currently set duty cycle on phaseC

volatile float Ua;
volatile float Ub;
volatile float Uc;

void writeDutyCycle3PWM(float dc_a,  float dc_b, float dc_c){
  // transform duty cycle from [0,1] to [0,255]
    pwm_write(DRV8302_INHA, 255.0f*dc_a);
    pwm_write(DRV8302_INHB, 255.0f*dc_b);
    pwm_write(DRV8302_INHC, 255.0f*dc_c);
}

void setPwm(float _Ua, float _Ub, float _Uc) {

  // limit the voltage in driver
  _Ua = _constrain(_Ua, 0.0f, voltage_limit);
  _Ub = _constrain(_Ub, 0.0f, voltage_limit);
  _Uc = _constrain(_Uc, 0.0f, voltage_limit);
  // calculate duty cycle
  // limited in [0,1]
  dc_a = _constrain(_Ua / voltage_limit, 0.0f , 1.0f );
  dc_b = _constrain(_Ub / voltage_limit, 0.0f , 1.0f );
  dc_c = _constrain(_Uc / voltage_limit, 0.0f , 1.0f );

  // hardware specific writing
  // hardware specific function - depending on driver and mcu

  writeDutyCycle3PWM(dc_a, dc_b, dc_c);
}

char text_pwm[20];

extern void bldc_move_sine_pwm(float Uq, float Ud, float angle_el)
{
   
    float center;
    int Ualpha,Ubeta;
    float _ca,_sa;
    angle_el = normalizeAngle(angle_el);

    _ca = _cos(angle_el);
    _sa = _sin(angle_el);
    // Inverse park transform
    Ualpha = _ca * Ud - _sa * Uq; // -sin(angle) * Uq;
    Ubeta = _sa * Ud + _ca * Uq;  //  cos(angle) * Uq;

    // center = modulation_centered ? (driver->voltage_limit)/2 : Uq;
    center = voltage_limit / 2;
    // Clarke transform
    Ua = Ualpha + center;
    Ub = -0.5f * Ualpha + _SQRT3_2 * Ubeta + center;
    Uc = -0.5f * Ualpha - _SQRT3_2 * Ubeta + center;

    // sprintf(text_pwm,"%3.2f %3.2f %3.2f \n",Ua,Ub,Uc);
    // serial_print(text_pwm);

    setPwm(Ua, Ub, Uc);
}