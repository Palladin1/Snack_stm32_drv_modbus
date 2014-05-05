#if 0
#include <stdio.h>

#include <stm32f10x.h>

#include "spi.h"

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
static void RCC_Configuration(void)
{
    /* Enable SPI_SPI_MASTER clock and GPIO clock */
    RCC_APB2PeriphClockCmd(SPI_MASTER_GPIO_CLK | SPI_MASTER_CLK | RCC_APB2Periph_AFIO, ENABLE);
}

/**
  * @brief  Configures the different GPIO ports.
  * @param  None
  * @retval None
  */
static void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Configure SCK and MOSI pins as Alternate Function Push Pull */
    GPIO_InitStructure.GPIO_Pin = SPI_MASTER_PIN_SCK | SPI_MASTER_PIN_MOSI;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(SPI_MASTER_GPIO, &GPIO_InitStructure);

    /* Configure MISO pin as Input Floating */
    GPIO_InitStructure.GPIO_Pin = SPI_MASTER_PIN_MISO;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(SPI_MASTER_GPIO, &GPIO_InitStructure);

    /* Configure CS pin */
    GPIO_InitStructure.GPIO_Pin = SPI_MASTER_PIN_CS;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(SPI_MASTER_GPIO, &GPIO_InitStructure);

    GPIO_SetBits(SPI_MASTER_GPIO, SPI_MASTER_PIN_CS);

}

int spi_master_xfer(SPI_TypeDef *SPIx, uint8_t *tx, int tx_len, uint8_t *rx, int rx_len)
{
    SPI_InitTypeDef SPI_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;

    DMA_Cmd(DMA1_Channel2, DISABLE);
    DMA_Cmd(DMA1_Channel3, DISABLE);

    SPI_Cmd(SPIx, DISABLE);
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI_MASTER, &SPI_InitStructure);
    SPI_Cmd(SPIx, ENABLE);

    if (tx != NULL) {
        DMA_DeInit(DMA1_Channel3);
        DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(SPIx->DR));
        DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)tx;
        DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
        DMA_InitStructure.DMA_BufferSize = tx_len;
        DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
        DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
        DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
        DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
        DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
        DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
        DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
        DMA_Init(DMA1_Channel3, &DMA_InitStructure);
    } else {
        DMA_DeInit(DMA1_Channel3);
    }

    if (rx != NULL) {
        DMA_DeInit(DMA1_Channel2);
        DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(SPIx->DR));
        DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)rx;
        DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
        DMA_InitStructure.DMA_BufferSize = rx_len;
        DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
        DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
        DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
        DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
        DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
        DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
        DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
        DMA_Init(DMA1_Channel2, &DMA_InitStructure);
    } else {
        DMA_DeInit(DMA1_Channel2);
    }

//    SPI_CalculateCRC(SPIx, DISABLE);
//    SPI_GetCRC(SPIx, SPI_CRC_Rx);
//    SPI_CalculateCRC(SPIx, ENABLE);
    (void)SPI_I2S_ReceiveData(SPIx);
    SPI_I2S_ClearFlag(SPIx, SPI_I2S_FLAG_RXNE);
    SPI_I2S_ClearFlag(SPIx, SPI_I2S_FLAG_TXE);

    DMA_ClearFlag(DMA1_FLAG_TC2 | DMA1_FLAG_TE2);
    DMA_ClearFlag(DMA1_FLAG_TC3 | DMA1_FLAG_TE3);

    if (rx != NULL)
        DMA_Cmd(DMA1_Channel2, ENABLE);
    if (rx != NULL)
        DMA_Cmd(DMA1_Channel3, ENABLE);

    /* Transfer complete */
    while (!DMA_GetFlagStatus(DMA1_FLAG_TC2));
    while (!DMA_GetFlagStatus(DMA1_FLAG_TC3));

    /* Wait for SPI_MASTER data reception: CRC transmitted by SPI_SLAVE */
//    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);
//    if ((SPI_I2S_GetFlagStatus(SPIx, SPI_FLAG_CRCERR)) != RESET)
//    {
//        return -1;
//    }
    return 0;
}

void spi_init(void)
{
    SPI_InitTypeDef SPI_InitStructure;

    RCC_Configuration();

    GPIO_Configuration();

    /* SPI_MASTER configuration */
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI_MASTER, &SPI_InitStructure);

    /* Enable SPI_MASTER DMA TX request */
    SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
    /* Enable SPI_MASTER DMA RX request */
    SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Rx, ENABLE);

    /* Enable SPI_MASTER */
    SPI_Cmd(SPI_MASTER, ENABLE);
}

u8 SPI_WriteByte(SPI_TypeDef *SPIx, u8 data)
{
    u8 Data = 0;

    /* Wait until the transmit buffer is empty */
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);
    /* Send the byte */
    SPI_I2S_SendData(SPIx, data);

    /* Wait until a data is received */
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
    /* Get the received data */
    Data = SPI_I2S_ReceiveData(SPIx);

    /* Return the shifted data */
    return Data;
}
#endif
