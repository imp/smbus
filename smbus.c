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

/*
 * Solaris SMBus driver
 */

#include <sys/types.h>
#include <sys/cmn_err.h>
#include <sys/note.h>
#include <sys/conf.h>
#include <sys/devops.h>
#include <sys/modctl.h>
#include <sys/stat.h>
#include <sys/ddi.h>
#include <sys/sunddi.h>

#include "smbus.h"

#define	NT_SMBUS	"ddi_smbus"

typedef struct {
	dev_info_t	*dip;
} smbus_state_t;

static void *smbus_statep;


static int
smbus_open(dev_t *devp, int flag, int otyp, cred_t *cp)
{
	int		instance;
	smbus_state_t	*sp;

	instance = getminor(*devp);

	sp = ddi_get_soft_state(smbus_statep, instance);

	if (sp == NULL)
		return (ENXIO);

	if (instance == 0) {
		/* That is a control node */
		return (0);
	} else {
		/* That is LU node, meanwhile not supported */
		return (EINVAL);
	}
}


static int
smbus_close(dev_t dev, int flag, int otyp, cred_t *cp)
{
	int		instance;
	smbus_state_t	*sp;

	instance = getminor(dev);

	sp = ddi_get_soft_state(smbus_statep, instance);

	if (sp == NULL)
		return (ENXIO);

	if (instance == 0) {
		return (0);
	} else {
		return (0);
	}
}


static int
smbus_read(dev_t dev, struct uio *uio_p, cred_t *cp)
{
	int		instance;
	smbus_state_t	*sp;

	instance = getminor(dev);

	sp = ddi_get_soft_state(smbus_statep, instance);

	if (sp == NULL)
		return (ENXIO);

	return (0);
}


static int
smbus_write(dev_t dev, struct uio *uio_p, cred_t *cp)
{
	int		instance;
	smbus_state_t	*sp;

	instance = getminor(dev);

	sp = ddi_get_soft_state(smbus_statep, instance);

	if (sp == NULL)
		return (ENXIO);

	return (0);
}


static int
smbus_ioctl(dev_t dev, int cmd, intptr_t arg, int mode, cred_t *cp, int *rvp)
{
	int		instance;
	smbus_state_t	*sp;

	instance = getminor(dev);

	sp = ddi_get_soft_state(smbus_statep, instance);

	if (sp == NULL)
		return (ENXIO);

	return (0);
}

static struct cb_ops smbus_cb_ops = {
	.cb_open	= smbus_open,
	.cb_close	= smbus_close,
	.cb_strategy	= nodev,
	.cb_print	= nodev,
	.cb_dump	= nodev,
	.cb_read	= smbus_read,
	.cb_write	= smbus_write,
	.cb_ioctl	= smbus_ioctl,
	.cb_devmap	= nodev,
	.cb_mmap	= nodev,
	.cb_segmap	= nodev,
	.cb_chpoll	= nochpoll,
	.cb_prop_op	= ddi_prop_op,
	.cb_str		= NULL,
	.cb_flag	= D_NEW | D_MP | D_64BIT,
	.cb_rev		= CB_REV,
	.cb_aread	= nodev,
	.cb_awrite	= nodev
};

static int
smbus_getinfo(dev_info_t *dip, ddi_info_cmd_t cmd, void *arg, void **rp)
{
	int		rc;
	int		instance;
	smbus_state_t	*sp;

	instance = getminor((dev_t)arg);

	switch (cmd) {
	case DDI_INFO_DEVT2DEVINFO:
		sp = ddi_get_soft_state(smbus_statep, instance);
		if (sp != NULL) {
			*rp = sp->dip;
			rc = DDI_SUCCESS;
		} else {
			*rp = NULL;
			rc = DDI_FAILURE;
		}
		break;
	case DDI_INFO_DEVT2INSTANCE:
		*rp = (void *)(uintptr_t)instance;
		rc = DDI_SUCCESS;
		break;
	default:
		rc = DDI_FAILURE;
	}

	return (rc);
}

static int
smbus_attach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	smbus_state_t	*sp;
	int		instance;
	int		rc;

	switch (cmd) {
	case DDI_ATTACH:
		break;
	case DDI_RESUME:
	default:
		return (DDI_FAILURE);
	}

	instance = ddi_get_instance(dip);
	if (ddi_soft_state_zalloc(smbus_statep, instance) != DDI_SUCCESS) {
		return (DDI_FAILURE);
	}

	sp = ddi_get_soft_state(smbus_statep, instance);
	ASSERT(sp);

	sp->dip = dip;

	rc = ddi_create_minor_node(dip, "ctl", S_IFCHR, instance, NT_SMBUS, 0);

	if (rc != DDI_SUCCESS) {
		cmn_err(CE_WARN, "smbus_attach: failed to create minor node");
		return (DDI_FAILURE);
	}

	ddi_report_dev(dip);

	return (DDI_SUCCESS);
}

static int
smbus_detach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
	smbus_state_t	*sp;
	int		instance;

	switch (cmd) {
	case DDI_DETACH:
		break;
	case DDI_SUSPEND:
	default:
		return (DDI_FAILURE);
	}

	instance = ddi_get_instance(dip);
	sp = ddi_get_soft_state(smbus_statep, instance);

	ASSERT(sp);

	ddi_remove_minor_node(dip, 0);

	ddi_soft_state_free(smbus_statep, instance);

	return (DDI_SUCCESS);
}


static struct dev_ops smbus_dev_ops = {
	.devo_rev	= DEVO_REV,
	.devo_refcnt	= 0,
	.devo_getinfo	= smbus_getinfo,
	.devo_identify	= nulldev,
	.devo_probe	= nulldev,
	.devo_attach	= smbus_attach,
	.devo_detach	= smbus_detach,
	.devo_reset	= nodev,
	.devo_cb_ops	= &smbus_cb_ops,
	.devo_bus_ops	= NULL,
	.devo_power	= NULL,
	.devo_quiesce	= ddi_quiesce_not_supported
};


static struct modldrv smbus_modldrv = {
	.drv_modops	= &mod_driverops,
	.drv_linkinfo	= "SMBus driver v0",
	.drv_dev_ops	= &smbus_dev_ops
};

static struct modlinkage smbus_modlinkage = {
	.ml_rev		= MODREV_1,
	.ml_linkage	= {&smbus_modldrv, NULL, NULL, NULL}
};

/*
 * Loadable module entry points.
 */
int
_init(void)
{
	int error;

	error = ddi_soft_state_init(&smbus_statep, sizeof (smbus_state_t), 0);
	if (error != 0) {
		return (error);
	}
	error = mod_install(&smbus_modlinkage);
	if (error != 0) {
		ddi_soft_state_fini(&smbus_statep);
	}
	return (error);
}

int
_fini(void)
{
	int error;

	error = mod_remove(&smbus_modlinkage);
	if (error == 0) {
		ddi_soft_state_fini(&smbus_statep);
	}
	return (error);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&smbus_modlinkage, modinfop));
}
