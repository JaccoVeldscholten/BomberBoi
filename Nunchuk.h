#ifndef NUNCHUK_H
#define NUNCHUK_H

#include <Wire.h>
#include <util/delay.h>

// Calibration accelerometer values, depends on your Nunchuk
#define NUNCHUK_ACCEL_X_ZERO 512
#define NUNCHUK_ACCEL_Y_ZERO 512
#define NUNCHUK_ACCEL_Z_ZERO 512

// Calibration joystick values
#define NUNCHUK_JOYSTICK_X_ZERO 127
#define NUNCHUK_JOYSTICK_Y_ZERO 128

uint8_t nunchuk_data[6];
uint8_t nunchuk_cali[16];

static void nunchuk_init_power()
{
    // Add power supply for port C2 (GND) and C3 (PWR)
    PORTC &= ~_BV(PORTC2);
    PORTC |= _BV(PORTC3);
    DDRC |= _BV(PORTC2) | _BV(PORTC3);
    _delay_ms(100);
}

static void nunchuk_init()
{
    Wire.begin();
    Wire.beginTransmission(0x52);
    Wire.write(0xF0);
    Wire.write(0x55);
    Wire.endTransmission();
    // _delay_ms(1);
    Wire.beginTransmission(0x52);
    Wire.write(0xFB);
    Wire.write(0x00);
    Wire.endTransmission();
    // _delay_ms(1);
}

static inline uint8_t nunchuk_decode_byte(uint8_t x)
{
    return x;
}

static uint8_t nunchuk_read()
{

    uint8_t i;
    Wire.requestFrom(0x52, 6);
    for (i = 0; i < 6 && Wire.available(); i++)
    {
        nunchuk_data[i] = nunchuk_decode_byte(Wire.read());
    }
    Wire.beginTransmission(0x52);
    Wire.write(0x00);
    Wire.endTransmission();
    return i == 6;
}

static uint8_t nunchuk_buttonZ()
{
    return (~nunchuk_data[5] >> 0) & 1;
}

static uint8_t nunchuk_buttonC()
{
    return (~nunchuk_data[5] >> 1) & 1;
}

/**
 * Retrieves the raw X-value of the joystick
 */
static uint8_t nunchuk_joystickX_raw()
{
    return nunchuk_data[0];
}

/**
 * Retrieves the raw Y-value of the joystick
 */
static uint8_t nunchuk_joystickY_raw()
{
    return nunchuk_data[1];
}

/**
 * Retrieves the calibrated X-value of the joystick
 */
static int16_t nunchuk_joystickX()
{
    return (int16_t)nunchuk_joystickX_raw() - (int16_t)NUNCHUK_JOYSTICK_X_ZERO;
}

/**
 * Retrieves the calibrated Y-value of the joystick
 */
static int16_t nunchuk_joystickY()
{
    return (int16_t)nunchuk_joystickY_raw() - (int16_t)NUNCHUK_JOYSTICK_Y_ZERO;
}

/**
 * Calculates the angle of the joystick
 */
static float nunchuk_joystick_angle()
{
    return atan2((float)nunchuk_joystickY(), (float)nunchuk_joystickX());
}

/**
 * Retrieves the raw X-value of the accelerometer
 */
static uint16_t nunchuk_accelX_raw()
{
    return ((uint16_t)nunchuk_data[2] << 2) | ((nunchuk_data[5] >> 2) & 3);
}

/**
 * Retrieves the raw Y-value of the accelerometer
 */
static uint16_t nunchuk_accelY_raw()
{
    return ((uint16_t)nunchuk_data[3] << 2) | ((nunchuk_data[5] >> 4) & 3);
}

/**
 * Retrieves the raw Z-value of the accelerometer
 */
static uint16_t nunchuk_accelZ_raw()
{
    return ((uint16_t)nunchuk_data[4] << 2) | ((nunchuk_data[5] >> 6) & 3);
}

/**
 * Retrieves the calibrated X-value of the accelerometer
 */
static int16_t nunchuk_accelX()
{
    return (int16_t)nunchuk_accelX_raw() - (int16_t)NUNCHUK_ACCEL_X_ZERO;
}

/**
 * Retrieves the calibrated Y-value of the accelerometer
 */
static int16_t nunchuk_accelY()
{
    return (int16_t)nunchuk_accelY_raw() - (int16_t)NUNCHUK_ACCEL_Y_ZERO;
}

/**
 * Retrieves the calibrated Z-value of the accelerometer
 */
static int16_t nunchuk_accelZ()
{
    return (int16_t)nunchuk_accelZ_raw() - (int16_t)NUNCHUK_ACCEL_Z_ZERO;
}

/**
 * Calculates the pitch angle THETA around y-axis of the Nunchuk in radians
 */
static float nunchuk_pitch()
{ // tilt-y
    return atan2((float)nunchuk_accelY(), (float)nunchuk_accelZ());
}

/**
 * Calculates the roll angle PHI around x-axis of the Nunchuk in radians
 */
static float nunchuk_roll()
{ // tilt-x
    return atan2((float)nunchuk_accelX(), (float)nunchuk_accelZ());
}

/**
 * A handy function to print either verbose information of the Nunchuk or a CSV stream for Processing
 */

#endif
