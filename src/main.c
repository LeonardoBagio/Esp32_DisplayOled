#include <driver/gpio.h>
#include <driver/spi_master.h>
#include <esp_log.h>
#include <stdio.h>
#include <string.h>
#include <u8g2.h>
#include "sdkconfig.h"
#include "u8g2_esp32_hal.h"

void app_main(void);
int controla_selecao(int);
char* primeiraLinha;
char* segundaLinha;
int selecao = 0;
u8g2_t u8g2; 

int controla_selecao(int selecao){
	if (selecao == 0){
		return 1;
	}

	if (selecao == 1){
		return 2;
	}

	if (selecao == 2){
		return 3;
	}

	return 0;
}

void app_main(void) {
	u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
	u8g2_esp32_hal.sda = 5;
	u8g2_esp32_hal.scl = 4;
	u8g2_esp32_hal_init(u8g2_esp32_hal);

	u8g2_Setup_ssd1306_i2c_128x32_univision_f(
		&u8g2,
		U8G2_R0,
		u8g2_esp32_i2c_byte_cb,
		u8g2_esp32_gpio_and_delay_cb); 
	u8x8_SetI2CAddress(&u8g2.u8x8, 0x78);
	u8g2_InitDisplay(&u8g2); 
	u8g2_SetPowerSave(&u8g2, 0); 
	u8g2_ClearBuffer(&u8g2);

	selecao = 0;

	while (true){
		if (selecao == 0){
			primeiraLinha = "DISPLAY";
			segundaLinha  = "OLED";
		}

		if (selecao == 1){
			primeiraLinha = "IOT";
			segundaLinha  = "APLICADA";
		}

		if (selecao == 2){
			primeiraLinha = "LEONARDO";
			segundaLinha  = "BAGIO";
		}

		if (selecao == 3){
			primeiraLinha = ":-)";
			segundaLinha  = "";
		}

		u8g2_SetFont(&u8g2, u8g2_font_ncenB12_tr);
		u8g2_DrawStr(&u8g2, 0, 15, primeiraLinha);
		u8g2_SendBuffer(&u8g2);
		u8g2_SetFont(&u8g2, u8g2_font_ncenB10_tr);
		u8g2_DrawStr(&u8g2, 0, 30, segundaLinha);
		u8g2_SendBuffer(&u8g2);

		vTaskDelay(3000 / portTICK_RATE_MS);
		u8g2_ClearBuffer(&u8g2);

		selecao = controla_selecao(selecao);
	}
}