#include "sram.h"

SRAM_HandleTypeDef g_sram_handler;

void SRAM_Init(void)
{
    GPIO_InitTypeDef           GPIO_Initure;
    FSMC_NORSRAM_TimingTypeDef fsmc_readwritetim;

    SRAM_CS_GPIO_CLK_ENABLE();     // Enable clock for SRAM_CS pin
    SRAM_WR_GPIO_CLK_ENABLE();     // Enable clock for SRAM_WR pin
    SRAM_RD_GPIO_CLK_ENABLE();     // Enable clock for SRAM_RD pin
    __HAL_RCC_FSMC_CLK_ENABLE();   // Enable clock for FSMC
    __HAL_RCC_GPIOD_CLK_ENABLE();  // Enable clock for GPIOD
    __HAL_RCC_GPIOE_CLK_ENABLE();  // Enable clock for GPIOE
    __HAL_RCC_GPIOF_CLK_ENABLE();  // Enable clock for GPIOF
    __HAL_RCC_GPIOG_CLK_ENABLE();  // Enable clock for GPIOG

    // Initialize SRAM_CS pin
    GPIO_Initure.Pin   = SRAM_CS_GPIO_PIN;
    GPIO_Initure.Mode  = GPIO_MODE_AF_PP;
    GPIO_Initure.Pull  = GPIO_PULLUP;
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SRAM_CS_GPIO_PORT, &GPIO_Initure);  // Set SRAM_CS pin mode

    // Initialize SRAM_WR pin
    GPIO_Initure.Pin = SRAM_WR_GPIO_PIN;
    HAL_GPIO_Init(SRAM_WR_GPIO_PORT, &GPIO_Initure);  // Set SRAM_WR pin mode

    // Initialize SRAM_RD pin
    GPIO_Initure.Pin = SRAM_RD_GPIO_PIN;
    HAL_GPIO_Init(SRAM_RD_GPIO_PORT, &GPIO_Initure);  // Set SRAM_RD pin mode

    // Initialize GPIO pins PD0,1,4,5,8~15
    GPIO_Initure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_Initure.Mode  = GPIO_MODE_AF_PP;       // Push-pull alternate function
    GPIO_Initure.Pull  = GPIO_PULLUP;           // Pull-up
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;  // High speed
    HAL_GPIO_Init(GPIOD, &GPIO_Initure);

    // Initialize GPIO pins PE0,1,7~15
    GPIO_Initure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOE, &GPIO_Initure);

    // Initialize GPIO pins PF0~5,12~15
    GPIO_Initure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOF, &GPIO_Initure);

    // Initialize GPIO pins PG0~5
    GPIO_Initure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
    HAL_GPIO_Init(GPIOG, &GPIO_Initure);

    g_sram_handler.Instance = FSMC_NORSRAM_DEVICE;
    g_sram_handler.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;

    g_sram_handler.Init.NSBank             = (SRAM_FSMC_NEX == 1)   ? FSMC_NORSRAM_BANK1
                                             : (SRAM_FSMC_NEX == 2) ? FSMC_NORSRAM_BANK2
                                             : (SRAM_FSMC_NEX == 3) ? FSMC_NORSRAM_BANK3
                                                                    : FSMC_NORSRAM_BANK4;  // Select FSMC_NE1~4 based on configuration
    g_sram_handler.Init.DataAddressMux     = FSMC_DATA_ADDRESS_MUX_DISABLE;                // Address/data lines not multiplexed
    g_sram_handler.Init.MemoryType         = FSMC_MEMORY_TYPE_SRAM;                        // SRAM
    g_sram_handler.Init.MemoryDataWidth    = FSMC_NORSRAM_MEM_BUS_WIDTH_16;                // 16-bit data width
    g_sram_handler.Init.BurstAccessMode    = FSMC_BURST_ACCESS_MODE_DISABLE;               // Disable burst access mode
    g_sram_handler.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;                // Wait signal polarity, valid in burst mode
    g_sram_handler.Init.WaitSignalActive   = FSMC_WAIT_TIMING_BEFORE_WS;                   // Wait signal activation timing
    g_sram_handler.Init.WriteOperation     = FSMC_WRITE_OPERATION_ENABLE;                  // Enable write operation
    g_sram_handler.Init.WaitSignal         = FSMC_WAIT_SIGNAL_DISABLE;                     // Disable wait signal
    g_sram_handler.Init.ExtendedMode       = FSMC_EXTENDED_MODE_DISABLE;                   // Same timing for read/write
    g_sram_handler.Init.AsynchronousWait   = FSMC_ASYNCHRONOUS_WAIT_DISABLE;               // Disable asynchronous wait
    g_sram_handler.Init.WriteBurst         = FSMC_WRITE_BURST_DISABLE;                     // Disable burst write
    // FSMC read timing control register
    fsmc_readwritetim.AddressSetupTime      = 0x00;  // Address setup time (ADDSET) is 1 HCLK 1/72M=13.8ns
    fsmc_readwritetim.AddressHoldTime       = 0x00;  // Address hold time (ADDHLD) not used in mode A
    fsmc_readwritetim.DataSetupTime         = 0x01;  // Data setup time is 2 HCLK=2*13.8=27.8ns
    fsmc_readwritetim.BusTurnAroundDuration = 0X00;
    fsmc_readwritetim.AccessMode            = FSMC_ACCESS_MODE_A;  // Mode A
    HAL_SRAM_Init(&g_sram_handler, &fsmc_readwritetim, &fsmc_readwritetim);
}

/**
 * @description: Write specified length of data to the specified address of SRAM
 * @param {uint8_t} *pbuf, data storage area
 * @param {uint32_t} addr, address to start writing (up to 32bit)
 * @param {uint32_t} datalen, Number of bytes to write (up to 32 bits)
 * @return {*}
 */
void SRAM_Write(uint8_t *pbuf, uint32_t addr, uint32_t datalen)
{
    for(; datalen != 0; datalen--)
    {
        *(volatile uint8_t *)(SRAM_BASE_ADDR + addr) = *pbuf;
        addr++;
        pbuf++;
    }
}

/**
 * @description:  Read specified length of data from the specified address of SRAM
 * @param {uint8_t} *pbuf, data storage area
 * @param {uint32_t} addr, address to start reading (up to 32bit)
 * @param {uint32_t} datalen, Number of bytes to reading (up to 32 bits)
 * @return {*}
 */
void SRAM_Read(uint8_t *pbuf, uint32_t addr, uint32_t datalen)
{
    for(; datalen != 0; datalen--)
    {
        *pbuf++ = *(volatile uint8_t *)(SRAM_BASE_ADDR + addr);
        addr++;
    }
}

uint8_t SRAM_Test_Read(uint32_t addr)
{
    uint8_t data;
    SRAM_Read(&data, addr, 1);
    return data;
}

void SRAM_Test_Write(uint32_t addr, uint8_t data)
{
    SRAM_Write(&data, addr, 1);
}