#ifndef DWT_H
#define DWT_H

#define    DWT_CYCCNT    *(volatile uint32_t*)0xE0001004
#define    DWT_CONTROL   *(volatile uint32_t*)0xE0001000
#define    SCB_DEMCR     *(volatile uint32_t*)0xE000EDFC
	
volatile uint32_t count_tic = 0;
volatile uint32_t delta_time = 0;

void delay_micros(uint32_t us)
{
    uint32_t us_count_tic =  us * (SystemCoreClock / 1000000); // �������� ���-�� ������ �� 1 ��� � �������� �� ���� ��������
    DWT->CYCCNT = 0U; // �������� �������
    while(DWT->CYCCNT < us_count_tic)
			__NOP();
}

void DWT_start_timer()
{
		SCB_DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;// ��������� ������������ DWT
		DWT_CONTROL|= DWT_CTRL_CYCCNTENA_Msk; // �������� �������
		DWT_CYCCNT = 0;// �������� �������	
}

void DWT_stop_timer()
{
		delta_time = DWT_CYCCNT - count_tic;
		count_tic = DWT_CYCCNT; // ���-�� ������
		//snprintf(str, 16, "Takt %lu\n", count_tic);
		//HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), 1000);
}

#endif //DWT