#ifndef _CVRA_DC_H_
#define _CVRA_DC_H_

#include <aversive.h>

/** Number of motors per board. */
#define CVRA_DC_MOTOR_COUNT 6

/** Number of motors with index channel per board. */
#define CVRA_DC_INDEX_COUNT 3

/** @brief Set PWM.
 *
 * This function sets the PWM value of a given channel.
 * @param [in] device A pointer to the base adress of the device.
 * @param [in] channel The PWM channel to set.
 * @param [in] value The value of the PWM.
 * @note This function will clamp the value of the PWM as needed.
 * @todo Clamp the value of the PWM.
 */
void cvra_dc_set_pwm(void *device, int channel, int32_t value);

/** @brief Gets encoder position.
 *
 * This functions reads the position register of the board and returns its content.
 * @param [in] device A pointer to the base adress of the device.
 * @param [in] channel The encoder channel to read. 
 * @return The position of the asked encoder.
 */
int32_t cvra_dc_get_encoder(void *device, int channel);

/** @brief Set encoder position.
 *
 * This function writes the given value to the count register of the given
 * channel.
 * @param [in] device A pointer to the base adress of the device.
 * @param [in] channel The encoder channel to read. 
 * @param [in] value The value to write to the register.
 */
void cvra_dc_set_encoder(void *device, int channel, int32_t value);

/** @brief Get index value.
 *
 * This function reads the index register of the given channel and returns its content.
 * @param [in] device A pointer to the base adress of the device.
 * @param [in] channel The index channel to read.
 * @returns The value of the given register.
 * @warning Only channels 0 to 2 provide index registers. Trying to access any
 * other channel index will return 0.
 */
int32_t cvra_dc_get_index(void *device, int channel);

/** @brief Get current sensing value.
 *
 * This functions reads the current sense register of the given channel
 * and returns its content.
 * @param [in] device A pointer to the base adress of the device.
 * @param [in] channel The current sense channel to read.
 * @returns The content of the current sense register for this channel.
 */
int32_t cvra_dc_get_current(void *device, int channel);

/** Sets PWM0 from a control system.
 * @param [in] device The base adress of the device
 * @param [in] value The PWM value.
 */
void cvra_dc_set_pwm0(void *device, int32_t value);

/** Sets PWM1 from a control system.
 * @param [in] device The base adress of the device
 * @param [in] value The PWM value.
 */
void cvra_dc_set_pwm1(void *device, int32_t value);

/** Sets PWM2 from a control system.
 * @param [in] device The base adress of the device
 * @param [in] value The PWM value.
 */
void cvra_dc_set_pwm2(void *device, int32_t value);

/** Sets PWM3 from a control system.
 * @param [in] device The base adress of the device
 * @param [in] value The PWM value.
 */
void cvra_dc_set_pwm3(void *device, int32_t value);

/** Sets PWM4 from a control system.
 * @param [in] device The base adress of the device
 * @param [in] value The PWM value.
 */
void cvra_dc_set_pwm4(void *device, int32_t value);

/** Sets PWM5 from a control system.
 * @param [in] device The base adress of the device
 * @param [in] value The PWM value.
 */
void cvra_dc_set_pwm5(void *device, int32_t value);

/** Gets encoder 0 from control system.
 * @param [in] device The base adress of the device.
 * @returns The value of the encoder.
 */
int32_t cvra_dc_get_encoder0(void *device);

/** Gets encoder 1 from control system.
 * @param [in] device The base adress of the device.
 * @returns The value of the encoder.
 */
int32_t cvra_dc_get_encoder1(void *device);

/** Gets encoder 2 from control system.
 * @param [in] device The base adress of the device.
 * @returns The value of the encoder.
 */
int32_t cvra_dc_get_encoder2(void *device);

/** Gets encoder 3 from control system.
 * @param [in] device The base adress of the device.
 * @returns The value of the encoder.
 */
int32_t cvra_dc_get_encoder3(void *device);

/** Gets encoder 4 from control system.
 * @param [in] device The base adress of the device.
 * @returns The value of the encoder.
 */
int32_t cvra_dc_get_encoder4(void *device);

/** Gets encoder 5 from control system.
 * @param [in] device The base adress of the device.
 * @returns The value of the encoder.
 */
int32_t cvra_dc_get_encoder5(void *device);

int32_t cvra_dc_get_index0(void *device);
int32_t cvra_dc_get_index1(void *device);
int32_t cvra_dc_get_index2(void *device);
int32_t cvra_dc_get_index3(void *device);
int32_t cvra_dc_get_index4(void *device);
int32_t cvra_dc_get_index5(void *device);

#endif
