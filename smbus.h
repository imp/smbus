/*
 * This file and its contents are supplied under the terms of the
 * Common Development and Distribution License ("CDDL"), version 1.0.
 * You may only use this file in accordance with the terms of version
 * 1.0 of the CDDL.
 *
 * A full copy of the text of the CDDL should have accompanied this
 * source.  A copy of the CDDL is also available via the Internet at
 * http://www.illumos.org/license/CDDL.
 */

/*
 * Copyright 2011 Grigale Ltd.  All rights reserved.
 */

#ifndef _SMBUS_H
#define	_SMBUS_H

/*
 * SMBus I/O and Memory Mapped I/O Register definitions.
 */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * SMBus I/O and Memory Mapped I/O Register Address Map definitions.
 */
#define	SMBUS_HST_STS		0x00	/* Host Status */
#define	SMBUS_HST_CNT		0x02	/* Host Control */
#define	SMBUS_HST_CMD		0x03	/* Host Command */
#define	SMBUS_XMIT_SLVA		0x04	/* Transmit Slave Address */
#define	SMBUS_HST_D0		0x05	/* Host Data 0 */
#define	SMBUS_HST_D1		0x06	/* Host Data 1 */
#define	SMBUS_HOST_BLOCK_DB	0x07	/* Host block Data Byte */
#define	SMBUS_PEC		0x08	/* Packet Error Check */
#define	SMBUS_RCV_SLVA		0x09	/* Receive Slave Address */
#define	SMBUS_SLV_DATA		0x0a	/* Receive Slave Data */
#define	SMBUS_AUX_STS		0x0c	/* Auxiliary Status */
#define	SMBUS_AUX_CTL		0x0d	/* Auxiliary Control */
#define	SMBUS_SMLINK_PIN_CTL	0x0e	/* SMLink Pin Control */
#define	SMBUS_SMBUS_PIN_CTL	0x0f	/* SMBus Pin Control */
#define	SMBUS_SLV_STS		0x10	/* Slave Status */
#define	SMBUS_SLV_CMD		0x11	/* Slave Command */
#define	SMBUS_NOTIFY_DADDR	0x14	/* Notify Device Address */
#define	SMBUS_NOTIFY_DLOW	0x16	/* Notify Data Low Byte */
#define	SMBUS_NOTIFY_DHIGH	0x17	/* Notify Data High Byte */

/*
 * Host Status Register bits
 *
 * All status bits are set by hardware and cleared by the software writing
 * a one to the particular bit position. Writing a 0 to any bit position
 * has no effect.
 */

#define	HST_STS_DS		0x80	/* Byte Done Status */
#define	HST_STS_INUSE_STS	0x40	/* In Use Semaphore */
#define	HST_STS_SMBALERT_STS	0x20	/* In Use Semaphore */
#define	HST_STS_FAILED		0x10	/* In Use Semaphore */
#define	HST_STS_BUS_ERR		0x08	/* In Use Semaphore */
#define	HST_STS_DEV_ERR		0x04	/* In Use Semaphore */
#define	HST_STS_INTR		0x02	/* In Use Semaphore */
#define	HST_STS_HOST_BUSY	0x01	/* In Use Semaphore */

/*
 * Host Control Register bits
 *
 * A read to this register will clear the byte pointer of thw 32-byte buffer
 */

#define	HST_CNT_PEC_EN		0x80
#define	HST_CNT_START		0x40
#define	HST_CNT_LAST_BYTE	0x20
#define	HST_CNT_SMB_CMD_MASK	0x1c
#define	HST_CNT_SMB_CMD_QUICK		0x00
#define	HST_CNT_SMB_CMD_BYTE		0x04
#define	HST_CNT_SMB_CMD_BYTE_DATA	0x08
#define	HST_CNT_SMB_CMD_WORD_DATA	0x0c
#define	HST_CNT_SMB_CMD_PROCESS_CALL	0x10
#define	HST_CNT_SMB_CMD_BLOCK		0x14
#define	HST_CNT_SMB_CMD_I2C_READ	0x18
#define	HST_CNT_SMB_CMD_BLOCK_PROCESS	0x1c
#define	HST_CNT_KILL		0x02
#define	HST_CNT_INTREN		0x01


/*
 * Transmit Slave Address Register
 */

#define	XMIT_SLVA_ADDR_MASK	0xFE
#define	XMIT_SLVA_RW_MASK	0x01
#define	XMIT_SLVA_READ		0x01
#define	XMIT_SLVA_WRITE		0x00

/*
 * Auxiliary Status Register bits
 */
#define	AUX_STS_STCO		0x02
#define	AUX_STS_CRCE		0x01

/*
 * Auxiliary Control Register bits
 */
#define	AUX_CTL_E32B		0x02
#define	AUX_CTL_AAC		0x01

#ifdef __cplusplus
}
#endif

#endif /* SMBUS_H */
