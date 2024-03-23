/*
 * vl53l4cd_class.cpp
 *
 *  Created on: 21 mars 2024
 *      Author: TANG Huong Cam (hctang@insa-toulouse.fr)
 */

#ifndef MYDRIVERS_VL53L4CD_CLASS_H_
#define MYDRIVERS_VL53L4CD_CLASS_H_
#include "fsl_debug_console.h"
#include "fsl_port.h"
#include "pin_mux.h"
#include "fsl_i2c.h"
#include "fsl_gpio.h"


/**
 * @attention : this driver is created for the LiDAR always in running (xshut is always high)
 * @reference : library VL53L4CD_class.h for Arduino and STM32
 * @use : call the function Init at first, then call GetDistance to get the measured distance
 */


/**
 *  @brief LiDAR's Configuration
 */
//I2C1
#define LIDAR1_SCL_PIN 	1U
#define LIDAR1_SDA_PIN	0U
#define LIDAR1_PORT		PORTE
#define LIDAR1_GPIO 	GPIOE
#define LIDAR1_I2C		I2C1

//I2C0
#define	LIDAR2_SCL_PIN 	0U
#define LIDAR2_SDA_PIN 	1U
#define LIDAR2_PORT		PORTB
#define LIDAR2_GPIO 	GPIOB
#define LIDAR2_I2C 		I2C0


/**
 *  @brief Driver version
 */

#define VL53L4CD_IMPLEMENTATION_VER_MAJOR       1
#define VL53L4CD_IMPLEMENTATION_VER_MINOR       0
#define VL53L4CD_IMPLEMENTATION_VER_BUILD       0
#define VL53L4CD_IMPLEMENTATION_VER_REVISION  	0

/**
 *  @brief Driver error type
 */

typedef uint8_t VL53L4CD_Error;

#define VL53L4CD_ERROR_NONE					((uint8_t)0U)
#define VL53L4CD_ERROR_XTALK_FAILED			((uint8_t)253U)
#define VL53L4CD_ERROR_INVALID_ARGUMENT		((uint8_t)254U)
#define VL53L4CD_ERROR_TIMEOUT				((uint8_t)255U)


/**
 *  @brief Inner Macro for API. Not for user, only for development.
 */

#define VL53L4CD_SOFT_RESET     						((uint16_t)0x0000))
#define VL53L4CD_I2C_SLAVE_DEVICE_ADDRESS      			((uint16_t)0x0001)
#define VL53L4CD_VHV_CONFIG_TIMEOUT_MACROP_LOOP_BOUND  	((uint16_t)0x0008)
#define VL53L4CD_XTALK_PLANE_OFFSET_KCPS 				((uint16_t)0x0016)
#define VL53L4CD_XTALK_X_PLANE_GRADIENT_KCPS     		((uint16_t)0x0018)
#define VL53L4CD_XTALK_Y_PLANE_GRADIENT_KCPS     		((uint16_t)0x001A)
#define VL53L4CD_RANGE_OFFSET_MM     					((uint16_t)0x001E)
#define VL53L4CD_INNER_OFFSET_MM     					((uint16_t)0x0020)
#define VL53L4CD_OUTER_OFFSET_MM     					((uint16_t)0x0022)
#define VL53L4CD_I2C_FAST_MODE_PLUS     				((uint16_t)0x002D)
#define VL53L4CD_GPIO_HV_MUX_CTRL      					((uint16_t)0x0030)
#define VL53L4CD_GPIO_TIO_HV_STATUS    					((uint16_t)0x0031)
#define VL53L4CD_SYSTEM_INTERRUPT  						((uint16_t)0x0046)
#define VL53L4CD_RANGE_CONFIG_A     					((uint16_t)0x005E)
#define VL53L4CD_RANGE_CONFIG_B      					((uint16_t)0x0061)
#define VL53L4CD_RANGE_CONFIG_SIGMA_THRESH     			((uint16_t)0x0064)
#define VL53L4CD_MIN_COUNT_RATE_RTN_LIMIT_MCPS    		((uint16_t)0x0066)
#define VL53L4CD_INTERMEASUREMENT_MS 					((uint16_t)0x006C)
#define VL53L4CD_THRESH_HIGH    						((uint16_t)0x0072)
#define VL53L4CD_THRESH_LOW     						((uint16_t)0x0074)
#define VL53L4CD_SYSTEM_INTERRUPT_CLEAR        			((uint16_t)0x0086)
#define VL53L4CD_SYSTEM_START     						((uint16_t)0x0087)
#define VL53L4CD_RESULT_RANGE_STATUS   					((uint16_t)0x0089)
#define VL53L4CD_RESULT_SPAD_NB   						((uint16_t)0x008C)
#define VL53L4CD_RESULT_SIGNAL_RATE   					((uint16_t)0x008E)
#define VL53L4CD_RESULT_AMBIENT_RATE   					((uint16_t)0x0090)
#define VL53L4CD_RESULT_SIGMA   						((uint16_t)0x0092)
#define VL53L4CD_RESULT_DISTANCE   						((uint16_t)0x0096)


#define VL53L4CD_RESULT_OSC_CALIBRATE_VAL      ((uint16_t)0x00DE)
#define VL53L4CD_FIRMWARE_SYSTEM_STATUS        ((uint16_t)0x00E5)
#define VL53L4CD_IDENTIFICATION_MODEL_ID       ((uint16_t)0x010F)

/**
 *  @brief defines Software Version
 */

typedef struct {
	uint8_t      major;    /*!< major number */
	uint8_t      minor;    /*!< minor number */
	uint8_t      build;    /*!< build number */
	uint32_t     revision; /*!< revision number */
} VL53L4CD_Version_t;

/**
 *  @brief Packed reading results type
 */

typedef struct {

	/* Status of measurements. If the status is equal to 0, the data are valid*/
	uint8_t range_status;
	/* Measured distance in millimeters */
	uint16_t distance_mm;
	/* Ambient noise in kcps */
	uint16_t ambient_rate_kcps;
	/* Ambient noise in kcps/SPAD */
	uint16_t ambient_per_spad_kcps;
	/* Measured signal of the target in kcps */
	uint16_t signal_rate_kcps;
	/* Measured signal of the target in kcps/SPAD */
	uint16_t signal_per_spad_kcps;
	/* Number of SPADs enabled */
	uint16_t number_of_spad;
	/* Estimated measurements std deviation in mm */
	uint16_t sigma_mm;
} VL53L4CD_ResultsData_t;


static const uint8_t VL53L4CD_DEFAULT_CONFIGURATION[] = {
  0x12, /* 0x2d : set bit 2 and 5 to 1 for fast plus mode (1MHz I2C),
   else don't touch */
  0x00, /* 0x2e : bit 0 if I2C pulled up at 1.8V, else set bit 0 to 1
   (pull up at AVDD) */
  0x00, /* 0x2f : bit 0 if GPIO pulled up at 1.8V, else set bit 0 to 1
  (pull up at AVDD) */
  0x11, /* 0x30 : set bit 4 to 0 for active high interrupt and 1 for active low
  (bits 3:0 must be 0x1), use SetInterruptPolarity() */
  0x02, /* 0x31 : bit 1 = interrupt depending on the polarity,
  use CheckForDataReady() */
  0x00, /* 0x32 : not user-modifiable */
  0x02, /* 0x33 : not user-modifiable */
  0x08, /* 0x34 : not user-modifiable */
  0x00, /* 0x35 : not user-modifiable */
  0x08, /* 0x36 : not user-modifiable */
  0x10, /* 0x37 : not user-modifiable */
  0x01, /* 0x38 : not user-modifiable */
  0x01, /* 0x39 : not user-modifiable */
  0x00, /* 0x3a : not user-modifiable */
  0x00, /* 0x3b : not user-modifiable */
  0x00, /* 0x3c : not user-modifiable */
  0x00, /* 0x3d : not user-modifiable */
  0xff, /* 0x3e : not user-modifiable */
  0x00, /* 0x3f : not user-modifiable */
  0x0F, /* 0x40 : not user-modifiable */
  0x00, /* 0x41 : not user-modifiable */
  0x00, /* 0x42 : not user-modifiable */
  0x00, /* 0x43 : not user-modifiable */
  0x00, /* 0x44 : not user-modifiable */
  0x00, /* 0x45 : not user-modifiable */
  0x20, /* 0x46 : interrupt configuration 0->level low detection, 1-> level high,
  2-> Out of window, 3->In window, 0x20-> New sample ready , TBC */
  0x0b, /* 0x47 : not user-modifiable */
  0x00, /* 0x48 : not user-modifiable */
  0x00, /* 0x49 : not user-modifiable */
  0x02, /* 0x4a : not user-modifiable */
  0x14, /* 0x4b : not user-modifiable */
  0x21, /* 0x4c : not user-modifiable */
  0x00, /* 0x4d : not user-modifiable */
  0x00, /* 0x4e : not user-modifiable */
  0x05, /* 0x4f : not user-modifiable */
  0x00, /* 0x50 : not user-modifiable */
  0x00, /* 0x51 : not user-modifiable */
  0x00, /* 0x52 : not user-modifiable */
  0x00, /* 0x53 : not user-modifiable */
  0xc8, /* 0x54 : not user-modifiable */
  0x00, /* 0x55 : not user-modifiable */
  0x00, /* 0x56 : not user-modifiable */
  0x38, /* 0x57 : not user-modifiable */
  0xff, /* 0x58 : not user-modifiable */
  0x01, /* 0x59 : not user-modifiable */
  0x00, /* 0x5a : not user-modifiable */
  0x08, /* 0x5b : not user-modifiable */
  0x00, /* 0x5c : not user-modifiable */
  0x00, /* 0x5d : not user-modifiable */
  0x01, /* 0x5e : not user-modifiable */
  0xcc, /* 0x5f : not user-modifiable */
  0x07, /* 0x60 : not user-modifiable */
  0x01, /* 0x61 : not user-modifiable */
  0xf1, /* 0x62 : not user-modifiable */
  0x05, /* 0x63 : not user-modifiable */
  0x00, /* 0x64 : Sigma threshold MSB (mm in 14.2 format for MSB+LSB),
   use SetSigmaThreshold(), default value 90 mm  */
  0xa0, /* 0x65 : Sigma threshold LSB */
  0x00, /* 0x66 : Min count Rate MSB (MCPS in 9.7 format for MSB+LSB),
   use SetSignalThreshold() */
  0x80, /* 0x67 : Min count Rate LSB */
  0x08, /* 0x68 : not user-modifiable */
  0x38, /* 0x69 : not user-modifiable */
  0x00, /* 0x6a : not user-modifiable */
  0x00, /* 0x6b : not user-modifiable */
  0x00, /* 0x6c : Intermeasurement period MSB, 32 bits register,
   use SetIntermeasurementInMs() */
  0x00, /* 0x6d : Intermeasurement period */
  0x0f, /* 0x6e : Intermeasurement period */
  0x89, /* 0x6f : Intermeasurement period LSB */
  0x00, /* 0x70 : not user-modifiable */
  0x00, /* 0x71 : not user-modifiable */
  0x00, /* 0x72 : distance threshold high MSB (in mm, MSB+LSB),
   use SetD:tanceThreshold() */
  0x00, /* 0x73 : distance threshold high LSB */
  0x00, /* 0x74 : distance threshold low MSB ( in mm, MSB+LSB),
   use SetD:tanceThreshold() */
  0x00, /* 0x75 : distance threshold low LSB */
  0x00, /* 0x76 : not user-modifiable */
  0x01, /* 0x77 : not user-modifiable */
  0x07, /* 0x78 : not user-modifiable */
  0x05, /* 0x79 : not user-modifiable */
  0x06, /* 0x7a : not user-modifiable */
  0x06, /* 0x7b : not user-modifiable */
  0x00, /* 0x7c : not user-modifiable */
  0x00, /* 0x7d : not user-modifiable */
  0x02, /* 0x7e : not user-modifiable */
  0xc7, /* 0x7f : not user-modifiable */
  0xff, /* 0x80 : not user-modifiable */
  0x9B, /* 0x81 : not user-modifiable */
  0x00, /* 0x82 : not user-modifiable */
  0x00, /* 0x83 : not user-modifiable */
  0x00, /* 0x84 : not user-modifiable */
  0x01, /* 0x85 : not user-modifiable */
  0x00, /* 0x86 : clear interrupt, use ClearInterrupt() */
  0x00  /* 0x87 : start ranging, use StartRanging() or StopRanging(),
   If you want an automatic start after VL53L4CD_init() call,
    put 0x40 in location 0x87 */
};


/* Paramètres à modifier */

#ifndef DEFAULT_I2C_BUFFER_LEN
  #ifdef BUFFER_LENGTH
    #define DEFAULT_I2C_BUFFER_LEN  BUFFER_LENGTH
  #else
    #define DEFAULT_I2C_BUFFER_LEN  32
  #endif
#endif
#define I2C_RELEASE_BUS_COUNT 1000U

#define DEFAULT_VL53L4CD_ID 0xEBAA
#define DEFAULT_VL53L4CD_ADDRESS 0x52
/**
 * @brief If the macro below is defined, the device will be programmed to run
 * with I2C Fast Mode Plus (up to 1MHz). Otherwise, default max value is 400kHz.
 */

/* #define VL53L4CD_I2C_FAST_MODE_PLUS */


class VL53L4CD {
  public:
    /** Constructor
     * @param[in] i2c device I2C to be used for communication
     * @param[in] xshut_pin pin to be used as component LPn
     * @param[in] address I2C address to be used for the sensor instance
     */
    VL53L4CD(int num);


    /** Destructor
     */
    ~VL53L4CD();


    /*** Interface Methods ***/

    /**
     * @brief Initialize the sensor with default values
     * @param (uint8_t) addr : New I2C address.
     * @return (VL53L4CD_Error) status : 0 if OK.
     */

    VL53L4CD_Error Init(void);

    /**
     * @brief Check the sensor ID with default ID
     * @param : none
     * @return (VL53L4CD_Error) status : 0 if OK.
     */

    VL53L4CD_Error CheckSensor(void);

    /**
     * @brief Get the distance  by LiDAR
     * @param : none
     * @return Distance : uint16_t in millimeter
     */

    uint16_t getDistance(void);


    /* Main APIs */
    /**
     * @brief This function programs the software driver version.
     * @param (VL53L4CD_Version_t) pVersion : Pointer of structure, containing the
     * software version.
     * @return (VL53L4CD_Error) status : 0 if SW version is OK.
     */

    VL53L4CD_Error GetSWVersion(
      VL53L4CD_Version_t *pVersion);


    /**
     * @brief This function sets a new I2C address to a sensor. It can be used for
     * example when multiple sensors share the same I2C bus.
     * @param (uint8_t) new_address : New I2C address.
     * @return (VL53L4CD_Error) status : 0 if I2C address has been correctly
     * programmed.
     */

    VL53L4CD_Error SetI2CAddress(
      uint8_t new_address);

    /**
     * @brief This function is used to get the sensor id of VL53L4CD. The sensor id
     * should be 0xEBAA.
     * @param (uint16_t) *p_id : Sensor id.
     * @return (VL53L4CD_Error) status : 0 if OK.
     */

    VL53L4CD_Error GetSensorId(
      uint16_t *p_id);

    /**
     * @brief This function is used to initialize the sensor.
     * @return (VL53L4CD_Error) status : 0 if init is OK.
     */

    VL53L4CD_Error SensorInit();

    /**
     * @brief This function clears the interrupt. It needs to be called after a
     * ranging data reading to arm the interrupt for the next data ready event.
     * @return (VL53L4CD_ERROR) status : 0 if OK.
     */

    VL53L4CD_Error ClearInterrupt();



    /**
     * @brief This function starts a ranging session. The ranging operation is
     * continuous. The clear interrupt has to be done after each get data to allow
     * the interrupt to raise when the next data is ready.
     * @return (VL53L4CD_Error) status : 0 if OK.
     */

    VL53L4CD_Error StartRanging();

    /**
     * @brief This function stops the ranging in progress.
     * @return (VL53L4CD_Error) status : 0 if OK.
     */

    VL53L4CD_Error StopRanging();

    /**
     * @brief This function check if a new data is available by polling a dedicated
     * register.
     * @param (uint8_t) *p_is_data_ready : Pointer containing a flag to know if a
     * data is ready : 0 = no data ready, 1 = data ready.
     * @return (VL53L4CD_Error) status : 0 if OK.
     */

    VL53L4CD_Error CheckForDataReady(
      uint8_t *p_is_data_ready);

    /**
     * @brief This function sets new range timing. Timing are composed of
     * TimingBudget and InterMeasurement. TimingBudget represents the timing during
     * VCSEL enabled, and InterMeasurement the time between two measurements.
     * The sensor can have different ranging mode depending of the configuration,
     * please refer to the user manual for more information.
     * @param (uint32_t) timing_budget_ms :  New timing budget in ms. Value can be
     * between 10ms and 200ms. Default is 50ms.
     * @param (uint32_t) inter_measurement_ms :  New inter-measurement in ms. If the
     * value is equal to 0, the ranging period is defined by the timing budget.
     * Otherwise, inter-measurement must be > timing budget. When all the timing
     * budget is consumed, the device goes in low power mode until inter-measurement
     * is done.
     * @return (uint8_t) status : 0 if OK.
     */

    VL53L4CD_Error SetRangeTiming(
      uint32_t timing_budget_ms,
      uint32_t inter_measurement_ms);

    /**
     * @brief This function gets the current range timing. Timing are composed of
     * TimingBudget and InterMeasurement. TimingBudget represents the timing during
     * VCSEL enabled, and InterMeasurement the time between two measurements.
     * The sensor can have different ranging mode depending of the configuration,
     * please refer to the user manual for more information.
     * @param (uint32_t) *p_timing_budget_ms :  Pointer containing the current
     * timing budget in ms.
     * @param (uint32_t) *p_inter_measurement_ms :  Pointer containing the current
     * inter-measurement in ms.
     * @return (uint8_t) status : 0 if OK.
     */

    VL53L4CD_Error GetRangeTiming(
      uint32_t *p_timing_budget_ms,
      uint32_t *p_inter_measurement_ms);

    /**
     * @brief This function gets the results reported by the sensor.
     * @param (VL53L4CD_Result_t) *pResult :  Pointer of structure, filled with the
     * ranging results.
     * @return (uint8_t) status : 0 if OK.
     */

    VL53L4CD_Error GetResult(VL53L4CD_ResultsData_t *pResult);

    /**
     * @brief This function sets a new offset correction in mm. Offset corresponds
     * to the difference in millimeters between real distance and measured distance.
     * @param (int16_t) OffsetValueInMm :  Offset value in millimeters. The minimum
     *  value is -1024mm and maximum is 1023mm.
     * @return (uint8_t) status : 0 if OK.
     */

    VL53L4CD_Error SetOffset(int16_t OffsetValueInMm);

    /**
     * @brief This function gets the current offset correction in mm. Offset
     * corresponds to the difference in millimeters between real distance and
     * measured distance.
     * @param (int16_t) OffsetValueInMm :  Offset value in millimeters. The minimum
     *  value is -1024mm and maximum is 1023mm.
     * @return (uint8_t) status : 0 if OK.
     */

    VL53L4CD_Error GetOffset(int16_t *Offset);

    /**
     * @brief This function sets a new Xtalk value in kcps. Xtalk represents the
     * correction to apply to the sensor when a protective coverglass is placed
     * at the top of the sensor.
     * @param (uint16_t) XtalkValueKcps : New xtalk value in kcps. The default
     * value is 0 kcps (no coverglass). Minimum is 0 kcps , and maximum is 128
     * kcps.
     * @return (VL53L4CD_Error) status : 0 if OK.
     */

    VL53L4CD_Error SetXtalk(uint16_t XtalkValueKcps);

    /**
     * @brief This function gets the current Xtalk value in kcps. Xtalk represents
     * the correction to apply to the sensor when a protective coverglass is placed
     * at the top of the sensor.
     * @param (uint16_t) p_xtalk_kcps : Pointer of current xtalk value in kcps.
     * @return (VL53L4CD_Error) status : 0 if OK.
     */

    VL53L4CD_Error GetXtalk(uint16_t *p_xtalk_kcps);

    


    /**
     * @brief This function sets a new signal threshold in kcps. If a
     * target has a lower signal as the programmed value, the result status in
     * structure 'VL53L4CD_Result_t' will be equal to 2.
     * @param (uint16_t) signal_kcps : New signal threshold in kcps. The default
     * value is 1024 kcps. Minimum is 0 kcps (no threshold), and maximum is 16384
     * kcps.
     * @return (VL53L4CD_Error) status : 0 if OK.
     */

    VL53L4CD_Error SetSignalThreshold(uint16_t signal_kcps);

    /**
     * @brief This function returns the current signal threshold in kcps. If a
     * target has a lower signal as the programmed value, the result status in
     * structure 'VL53L4CD_Result_t' will be equal to 2.
     * @param (uint16_t) *p_signal_kcps : Pointer of signal threshold in kcps.
     * @return (VL53L4CD_Error) status : 0 if OK.
     */

    VL53L4CD_Error GetSignalThreshold(
      uint16_t *p_signal_kcps);

    /**
     * @brief This function programs a new sigma threshold. The sigma corresponds to
     * the standard deviation of the returned pulse. If the computed sigma is above
     * the programmed value, the result status in structure 'VL53L4CD_Result_t'
     * will be equal to 1.
     * @param (uint16_t) sigma_mm : New sigma threshold in mm. The default value is
     * 15mm. Minimum is 0mm (not threshold), and maximum is 16383mm.
     * @return (VL53L4CD_Error) status : 0 if programming is or 255 if value is too
     * high.
     */

    VL53L4CD_Error SetSigmaThreshold(
      uint16_t  sigma_mm);

    /**
     * @brief This function gets the current sigma threshold. The sigma corresponds
     * to the standard deviation of the returned pulse. If the computed sigma is
     * above the programmed value, the result status in structure
     * 'VL53L4CD_Result_t' will be equal to 1.
     * @param (uint16_t) *p_sigma_mm : Current sigma threshold in mm.
     * @return (VL53L4CD_Error) status : 0 if programming is OK.
     */

    VL53L4CD_Error GetSigmaThreshold(
      uint16_t  *p_sigma_mm);

    /**
     * @brief This function can be called when the temperature might have changed by
     * more than 8 degrees Celsius. The function can only be used if the sensor is
     * not ranging, otherwise, the ranging needs to be stopped using function
     * 'VL53L4CD_StopRanging()'. After calling this function, the ranging can
     * restart normally.
     * @return (VL53L4CD_Error) status : 0 if update is OK.
     */

    VL53L4CD_Error StartTemperatureUpdate();

    /* Calibration APIs */

    /**
     * @brief This function can be used to perform an offset calibration. Offset
     * corresponds to the difference in millimeters between real distance and
     * measured distance. ST recommend to perform offset at 100m, on a grey17%
     * reflective target, but any other distance and reflectance can be used.
     * The function returns the offset value found and programs the offset
     * compensation into the device.
     * @param (int16_t) TargetDistInMm : Real distance between the sensor and the
     * target in millimeters. ST recommend 100mm. Min distance is 50mm and max is
     * 1000mm.
     * @param (int16_t) nb_samples : Number of samples (between 5 and 255). A higher
     * number of samples increases the accuracy, but it also takes more time. ST
     * recommend to use at least 10 samples.
     * @return (VL53L4CD_Error) status : 0 if OK, or 255 if something occurred (e.g
     * invalid nb of samples).
     */

    VL53L4CD_Error CalibrateOffset(
      int16_t TargetDistInMm,
      int16_t *p_measured_offset_mm,
      int16_t nb_samples);


    /**
     * @brief This function can be used to perform a Xtalk calibration. Xtalk
     * represents the correction to apply to the sensor when a protective coverglass
     * is placed at the top of the sensor. The distance for calibration depends of
     * the coverglass, it needs to be characterized. Please refer to the User Manual
     * for more information.
     * The function returns the Xtalk value found and programs the Xtalk
     * compensation into the device.
     * @param uint16_t) TargetDistInMm : Real distance between the sensor and the
     * target in millimeters. This distance needs to be characterized, as described
     * into the User Manual.
     * @param (int16_t) nb_samples : Number of samples (between 5 and 255). A higher
     * number of samples increases the accuracy, but it also takes more time. ST
     * recommend to use at least 10 samples.
     * @return (VL53L4CD_Error) status : 0 if OK, or 255 if something occurred (e.g
     * invalid nb of samples).
     */

    VL53L4CD_Error CalibrateXtalk(
      int16_t TargetDistInMm,
      uint16_t *p_measured_xtalk_kcps,
      int16_t nb_samples);

	VL53L4CD_ResultsData_t results;


  protected:

    /**
     * @brief Read 32 bits through I2C.
     */

    uint8_t RdDWord(uint16_t registerAddr, uint32_t *value);

    /**
     * @brief Read 16 bits through I2C.
     */

    uint8_t RdWord(uint16_t registerAddr, uint16_t *value);

    /**
     * @brief Read 8 bits through I2C.
     */

    uint8_t RdByte(uint16_t registerAddr, uint8_t *value);

    /**
     * @brief Write 8 bits through I2C.
     */

    uint8_t WrByte(uint16_t registerAddr, uint8_t value);

    /**
     * @brief Write 16 bits through I2C.
     */

    uint8_t WrWord(uint16_t RegisterAdress, uint16_t value);

    /**
     * @brief Write 32 bits through I2C.
     */

    uint8_t WrDWord(uint16_t RegisterAdress, uint32_t value);

    /**
     * @brief Wait during N milliseconds.
     */

    void WaitMs(uint32_t TimeMs);

    /**
    * @brief Send (read or write) multiple bytes through I2C.
    */


    uint8_t I2CSend(uint16_t RegisterAddress, uint8_t *buff, uint32_t size, char rw);


    /* Digital out pin */
    //GPIO_Type * xshut;
    //uint32_t xshut_pin_mask;

    I2C_Type * lidar_i2c;
    /* I2C address to use */
    uint16_t addr;
    int num; 		// lidar 1 : num = 1; lidar 2 : num = 2


	uint16_t sensor_id;

  private:
	void CreateHandle(void);
	void I2C_Init (void);
};


#endif /* MYDRIVERS_VL53L4CD_CLASS_H_ */
