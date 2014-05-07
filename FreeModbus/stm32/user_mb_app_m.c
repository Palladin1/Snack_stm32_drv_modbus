/*
 * FreeModbus Libary: user callback functions and buffer define in master mode
 * Copyright (C) 2013 Armink <armink.ztl@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: user_mb_app_m.c,v 1.60 2013/11/23 11:49:05 Armink $
 */
#include "user_mb_app.h"

/*-----------------------Master mode use these variables----------------------*/
#if MB_MASTER_RTU_ENABLED > 0 || MB_MASTER_ASCII_ENABLED > 0
//Master mode:DiscreteInputs variables
USHORT   usMDiscInStart                             = M_DISCRETE_INPUT_START;
#if      M_DISCRETE_INPUT_NDISCRETES%8
UCHAR    ucMDiscInBuf[MB_MASTER_TOTAL_SLAVE_NUM][M_DISCRETE_INPUT_NDISCRETES/8+1];
#else
UCHAR    ucMDiscInBuf[MB_MASTER_TOTAL_SLAVE_NUM][M_DISCRETE_INPUT_NDISCRETES/8];
#endif
//Master mode:Coils variables
USHORT   usMCoilStart                               = M_COIL_START;
#if      M_COIL_NCOILS%8
UCHAR    ucMCoilBuf[MB_MASTER_TOTAL_SLAVE_NUM][M_COIL_NCOILS/8+1];
#else
UCHAR    ucMCoilBuf[MB_MASTER_TOTAL_SLAVE_NUM][M_COIL_NCOILS/8];
#endif
//Master mode:InputRegister variables
USHORT   usMRegInStart                              = M_REG_INPUT_START;
USHORT   usMRegInBuf[MB_MASTER_TOTAL_SLAVE_NUM][M_REG_INPUT_NREGS];
//Master mode:HoldingRegister variables
USHORT   usMRegHoldStart                            = M_REG_HOLDING_START;
USHORT   usMRegHoldBuf[MB_MASTER_TOTAL_SLAVE_NUM][M_REG_HOLDING_NREGS];

//******************************����Ĵ����ص�����**********************************
//��������: eMBErrorCode eMBMasterRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
//��    ��������Ĵ�����صĹ��ܣ�������������
//��ڲ�����pucRegBuffer : �ص�������Modbus�Ĵ����ĵ�ǰֵд��Ļ�����
//			usAddress    : �Ĵ�������ʼ��ַ������Ĵ����ĵ�ַ��Χ��1-65535��
//			usNRegs      : �Ĵ�������
//���ڲ�����eMBErrorCode : ������������صĴ�����
//��    ע��Editor��Armink 2013-11-25    Company: BXXJS
//**********************************************************************************
eMBErrorCode
eMBMasterRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    USHORT          iRegIndex;
    USHORT *        pusRegInputBuf;
    UCHAR           REG_INPUT_START;
    UCHAR           REG_INPUT_NREGS;
    UCHAR           usRegInStart;

	pusRegInputBuf = usMRegInBuf[ucMBMasterGetDestAddress() - 1];
	REG_INPUT_START = M_REG_INPUT_START;
	REG_INPUT_NREGS = M_REG_INPUT_NREGS;
	usRegInStart = usMRegInStart;

	usAddress--;//FreeModbus���ܺ������Ѿ���1��Ϊ��֤�뻺�����׵�ַһ�£��ʼ�1
    if( ( usAddress >= REG_INPUT_START )
        && ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
    {
        iRegIndex = usAddress - usRegInStart;
        while( usNRegs > 0 )
        {
			pusRegInputBuf[iRegIndex] = *pucRegBuffer++ << 8;
			pusRegInputBuf[iRegIndex] |= *pucRegBuffer++;
            iRegIndex++;
            usNRegs--;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }

    return eStatus;
}
//******************************���ּĴ����ص�����**********************************
//��������: eMBErrorCode eMBMasterRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
//��    �������ּĴ�����صĹ��ܣ�������������д������д��
//��ڲ�����pucRegBuffer : �����Ҫ�����û��Ĵ�����ֵ���������������ָ���µļĴ�����ֵ��
//                         ���Э��ջ��֪����ǰ����ֵ���ص��������뽫��ǰֵд�����������
//			usAddress    : �Ĵ�������ʼ��ַ��
//			usNRegs      : �Ĵ�������
//          eMode        : ����ò���ΪeMBRegisterMode::MB_REG_WRITE���û���Ӧ����ֵ����pucRegBuffer�еõ����¡�
//                         ����ò���ΪeMBRegisterMode::MB_REG_READ���û���Ҫ����ǰ��Ӧ�����ݴ洢��pucRegBuffer��
//���ڲ�����eMBErrorCode : ������������صĴ�����
//��    ע��Editor��Armink 2013-11-25    Company: BXXJS
//**********************************************************************************
eMBErrorCode
eMBMasterRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    USHORT          iRegIndex;
    USHORT *        pusRegHoldingBuf;
    UCHAR           REG_HOLDING_START;
    UCHAR           REG_HOLDING_NREGS;
    UCHAR           usRegHoldStart;

	pusRegHoldingBuf = usMRegHoldBuf[ucMBMasterGetDestAddress() - 1];
	REG_HOLDING_START = M_REG_HOLDING_START;
	REG_HOLDING_NREGS = M_REG_HOLDING_NREGS;
	usRegHoldStart = usMRegHoldStart;
	//If mode is read,the master will wirte the received date to bufffer.
	eMode = MB_REG_WRITE;

	usAddress--;//FreeModbus���ܺ������Ѿ���1��Ϊ��֤�뻺�����׵�ַһ�£��ʼ�1
    if( ( usAddress >= REG_HOLDING_START ) &&
        ( usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS ) )
    {
        iRegIndex = usAddress - usRegHoldStart;
        switch ( eMode )
        {
            /* Pass current register values to the protocol stack. */
        case MB_REG_READ:
            while( usNRegs > 0 )
            {
				*pucRegBuffer++ = ( unsigned char )( pusRegHoldingBuf[iRegIndex] >> 8 );
				*pucRegBuffer++ = ( unsigned char )( pusRegHoldingBuf[iRegIndex] & 0xFF );
                iRegIndex++;
                usNRegs--;
            }
            break;

            /* Update current register values with new values from the
             * protocol stack. */
        case MB_REG_WRITE:
            while( usNRegs > 0 )
            {
                pusRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;
                pusRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;
                iRegIndex++;
                usNRegs--;
            }
            break;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }
    return eStatus;
}
//****************************��Ȧ״̬�Ĵ����ص�����********************************
//��������: eMBErrorCode eMBMasterRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
//��    ������Ȧ״̬�Ĵ�����صĹ��ܣ�������������д������д��
//��ڲ�����pucRegBuffer : λ���һ���ֽڣ���ʼ�Ĵ�����Ӧ��λ���ڸ��ֽ�pucRegBuffer�����λLSB��
//                         ����ص�����Ҫд�����������û���õ�����Ȧ�����粻��8��һ�����Ȧ״̬����Ӧ��λ����ֵ��������λ0��
//			usAddress    : ��һ����Ȧ��ַ��
//			usNCoils     : �������Ȧ����
//          eMode        ������ò���ΪeMBRegisterMode::MB_REG_WRITE���û���Ӧ����ֵ����pucRegBuffer�еõ����¡�
//                         ����ò���ΪeMBRegisterMode::MB_REG_READ���û���Ҫ����ǰ��Ӧ�����ݴ洢��pucRegBuffer��
//���ڲ�����eMBErrorCode : ������������صĴ�����
//��    ע��Editor��Armink 2013-11-25    Company: BXXJS
//**********************************************************************************
eMBErrorCode
eMBMasterRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    USHORT          iRegIndex , iRegBitIndex , iNReg;
	UCHAR *         pucCoilBuf;
    UCHAR           COIL_START;
    UCHAR           COIL_NCOILS;
    UCHAR           usCoilStart;
    iNReg =  usNCoils / 8 + 1;        //ռ�üĴ�������

	pucCoilBuf = ucMCoilBuf[ucMBMasterGetDestAddress() - 1];
	COIL_START = M_COIL_START;
	COIL_NCOILS = M_COIL_NCOILS;
	usCoilStart = usMCoilStart;
	//If mode is read,the master will wirte the received date to bufffer.
	eMode = MB_REG_WRITE;

	usAddress--;//FreeModbus���ܺ������Ѿ���1��Ϊ��֤�뻺�����׵�ַһ�£��ʼ�1
	if( ( usAddress >= COIL_START ) &&
        ( usAddress + usNCoils <= COIL_START + COIL_NCOILS ) )
    {
        iRegIndex    = ( int )( usAddress - usCoilStart ) / 8 ;    //ÿ���Ĵ�����8��
		iRegBitIndex = ( int )( usAddress - usCoilStart ) % 8 ;	   //����ڼĴ����ڲ���λ��ַ
        switch ( eMode )
        {
            /* Pass current coil values to the protocol stack. */
        case MB_REG_READ:
            while( iNReg > 0 )
            {
				*pucRegBuffer++ = xMBUtilGetBits(&pucCoilBuf[iRegIndex++] , iRegBitIndex , 8);
                iNReg --;
            }
			pucRegBuffer --;
			usNCoils = usNCoils % 8;                        //���µ���Ȧ��	
			*pucRegBuffer = *pucRegBuffer <<(8 - usNCoils); //��λ����
			*pucRegBuffer = *pucRegBuffer >>(8 - usNCoils);
            break;

            /* Update current coil values with new values from the
             * protocol stack. */
        case MB_REG_WRITE:
            while(iNReg > 1)									 //���������������������
            {
				xMBUtilSetBits(&pucCoilBuf[iRegIndex++] , iRegBitIndex  , 8 , *pucRegBuffer++);
                iNReg--;
            }
			usNCoils = usNCoils % 8;                            //���µ���Ȧ��
			if (usNCoils != 0)                                  //xMBUtilSetBits���� �ڲ���λ����Ϊ0ʱ����bug
			{
				xMBUtilSetBits(&pucCoilBuf[iRegIndex++], iRegBitIndex, usNCoils,
						*pucRegBuffer++);
			}
			break;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }
    return eStatus;
}
//****************************��ɢ����Ĵ����ص�����********************************
//��������: eMBErrorCode eMBMasterRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
//��    ������ɢ����Ĵ�����صĹ��ܣ�������������
//��ڲ�����pucRegBuffer : �õ�ǰ����Ȧ���ݸ�������Ĵ�������ʼ�Ĵ�����Ӧ��λ���ڸ��ֽ�pucRegBuffer�����λLSB��
//                         ����ص�����Ҫд�����������û���õ�����Ȧ�����粻��8��һ�����Ȧ״̬����Ӧ��λ����ֵ��������Ϊ0��
//			usAddress    : ��ɢ�������ʼ��ַ
//			usNDiscrete  : ��ɢ���������
//���ڲ�����eMBErrorCode : ������������صĴ�����
//��    ע��Editor��Armink 2013-11-25    Company: BXXJS
//**********************************************************************************
eMBErrorCode
eMBMasterRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
    eMBErrorCode    eStatus = MB_ENOERR;
	USHORT          iRegIndex , iRegBitIndex , iNReg;
	UCHAR *         pucDiscreteInputBuf;
    UCHAR           DISCRETE_INPUT_START;
    UCHAR           DISCRETE_INPUT_NDISCRETES;
    UCHAR           usDiscreteInputStart;
	iNReg =  usNDiscrete / 8 + 1;        //ռ�üĴ�������

	pucDiscreteInputBuf = ucMDiscInBuf[ucMBMasterGetDestAddress() - 1];
	DISCRETE_INPUT_START = M_DISCRETE_INPUT_START;
	DISCRETE_INPUT_NDISCRETES = M_DISCRETE_INPUT_NDISCRETES;
	usDiscreteInputStart = usMDiscInStart;

	usAddress--;//FreeModbus���ܺ������Ѿ���1��Ϊ��֤�뻺�����׵�ַһ�£��ʼ�1
    if( ( usAddress >= DISCRETE_INPUT_START )
        && ( usAddress + usNDiscrete <= DISCRETE_INPUT_START + DISCRETE_INPUT_NDISCRETES ) )
    {
        iRegIndex    = ( int )( usAddress - usDiscreteInputStart ) / 8 ;    //ÿ���Ĵ�����8��
		iRegBitIndex = ( int )( usAddress - usDiscreteInputStart ) % 8 ;	   //����ڼĴ����ڲ���λ��ַ

		/* Update current coil values with new values from the
		 * protocol stack. */
		while (iNReg > 1) //���������������������
		{
			xMBUtilSetBits(&pucDiscreteInputBuf[iRegIndex++], iRegBitIndex, 8,
					*pucRegBuffer++);
			iNReg--;
		}
		usNDiscrete = usNDiscrete % 8; //���µ���Ȧ��
		if (usNDiscrete != 0) //xMBUtilSetBits���� �ڲ���λ����Ϊ0ʱ����bug
		{
			xMBUtilSetBits(&pucDiscreteInputBuf[iRegIndex++], iRegBitIndex,
					usNDiscrete, *pucRegBuffer++);
		}
    }
    else
    {
        eStatus = MB_ENOREG;
    }

    return eStatus;
}
#endif
