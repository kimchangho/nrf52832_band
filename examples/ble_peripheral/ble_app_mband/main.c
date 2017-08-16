#include "main.h"

/**@brief Application main function.
 */
struct bno055_accel_t accel_xyz;
struct bno055_mag_t mag_xyz;
struct bno055_gyro_t gyro_xyz;
struct bno055_euler_t euler_hrp;
struct bno055_euler_double_t d_euler_hpr;
struct bno055_gravity_t gravity_xyz;

float temp_pressure_lbs = 0; 
float temp_temperature_lbs = 0; 
float temp_asl_lbs  = 0;

const nrf_drv_timer_t TIMER2 = NRF_DRV_TIMER_INSTANCE(3);
/**
 * @brief Handler for timer events.
 */
void timer_led_event_handler(nrf_timer_event_t event_type, void* p_context)
{
	
    switch (event_type)
    {
        case NRF_TIMER_EVENT_COMPARE0:
            break;

        default:
            //Do nothing.
            break;
    }
}

void timer_init()
{
		uint32_t err_code = NRF_SUCCESS;
		uint32_t time_ticks;
	  nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;
    err_code = nrf_drv_timer_init(&TIMER2, &timer_cfg, timer_led_event_handler);
    APP_ERROR_CHECK(err_code);

    time_ticks = nrf_drv_timer_ms_to_ticks(&TIMER2, 1);

    nrf_drv_timer_extended_compare(
         &TIMER2, NRF_TIMER_CC_CHANNEL0, time_ticks, NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, true);

    nrf_drv_timer_enable(&TIMER2);
}

int main(void)
{
    uint32_t err_code;
    //bool erase_bonds;
		ble_stack_init();
    // Initialize.
    APP_TIMER_INIT(APP_TIMER_PRESCALER, APP_TIMER_OP_QUEUE_SIZE, false);
		twi_init();
    uart_init();
		gpio_init();
	
		saadc_init();
		saadc_sampling_event_init();
    saadc_sampling_event_enable();
	
		nrf_bno055_init();
		lps25hInit();
		lps25hSetEnabled(true);
		//buttons_leds_init(&erase_bonds);
    gap_params_init();
    services_init();
    advertising_init();
    conn_params_init();
    printf("\r\nUART Start!\r\n");
    err_code = ble_advertising_start(BLE_ADV_MODE_FAST);
		button_init();
		
		timer_init();
		
    APP_ERROR_CHECK(err_code);

    // Enter main loop.
    for (;;)
    {
      power_manage();
			
			//bno055_convert_double_euler_hpr_deg(&d_euler_hpr);
			//printf("%f\n", d_euler_hpr.h);
			//lps25hGetData(&temp_pressure_lbs, &temp_temperature_lbs, &temp_asl_lbs);
			//printf("%f\n", temp_asl_lbs);
			//nrf_delay_ms(10);
			if(device_state == DEVICE_ON)
			{
				nrf_gpio_pin_set(15);
			}
			else if(device_state == DEVICE_OFF)
			{
				nrf_gpio_pin_clear(15);
			}
			nrf_gpio_pin_set(15);
    }
}

void gpio_init()
{
	nrf_gpio_cfg_output(5);
	nrf_gpio_cfg_output(14);
	nrf_gpio_cfg_output(15);
	nrf_gpio_cfg_output(16);
	nrf_gpio_cfg_input(4, NRF_GPIO_PIN_NOPULL);
	nrf_gpio_cfg_input(9, NRF_GPIO_PIN_PULLDOWN);
}

/**
 * @}
 */
