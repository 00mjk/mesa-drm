/* i810_drv.h -- Private header for the i810 driver -*- linux-c -*-
 * Created: Mon Dec 13 01:50:01 1999 by jhartmann@precisioninsight.com
 *
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors: Rickard E. (Rik) Faith <faith@precisioninsight.com>
 * 	    Jeff Hartmann <jhartmann@precisioninsight.com>
 *
 * $XFree86$
 */

#ifndef _I810_DRV_H_
#define _I810_DRV_H_
#include "i810_drm_public.h"

typedef struct _drm_i810_ring_buffer{
	int tail_mask;
	unsigned long Start;
	unsigned long End;
	unsigned long Size;
	u8 *virtual_start;
	int head;
	int tail;
	int space;
} drm_i810_ring_buffer_t;

typedef struct drm_i810_private {
   	int ring_map_idx;
   	int buffer_map_idx;

   	drm_i810_ring_buffer_t ring;
	drm_i810_sarea_t *sarea_priv;

      	unsigned long hw_status_page;
   	unsigned long counter;

   	atomic_t dispatch_lock;
      	atomic_t pending_bufs;
   	atomic_t in_flush;

} drm_i810_private_t;

				/* i810_drv.c */
extern int  i810_init(void);
extern void i810_cleanup(void);
extern int  i810_version(struct inode *inode, struct file *filp,
			  unsigned int cmd, unsigned long arg);
extern int  i810_open(struct inode *inode, struct file *filp);
extern int  i810_release(struct inode *inode, struct file *filp);
extern int  i810_ioctl(struct inode *inode, struct file *filp,
			unsigned int cmd, unsigned long arg);
extern int  i810_unlock(struct inode *inode, struct file *filp,
			 unsigned int cmd, unsigned long arg);

				/* i810_dma.c */
extern int  i810_dma_schedule(drm_device_t *dev, int locked);
extern int  i810_dma(struct inode *inode, struct file *filp,
		      unsigned int cmd, unsigned long arg);
extern int  i810_irq_install(drm_device_t *dev, int irq);
extern int  i810_irq_uninstall(drm_device_t *dev);
extern int  i810_control(struct inode *inode, struct file *filp,
			  unsigned int cmd, unsigned long arg);
extern int  i810_lock(struct inode *inode, struct file *filp,
		       unsigned int cmd, unsigned long arg);
extern int  i810_dma_init(struct inode *inode, struct file *filp,
			  unsigned int cmd, unsigned long arg);
extern int  i810_flush_ioctl(struct inode *inode, struct file *filp,
			     unsigned int cmd, unsigned long arg);

				/* i810_bufs.c */
extern int  i810_addbufs(struct inode *inode, struct file *filp, 
			unsigned int cmd, unsigned long arg);
extern int  i810_infobufs(struct inode *inode, struct file *filp, 
			 unsigned int cmd, unsigned long arg);
extern int  i810_markbufs(struct inode *inode, struct file *filp,
			 unsigned int cmd, unsigned long arg);
extern int  i810_freebufs(struct inode *inode, struct file *filp,
			 unsigned int cmd, unsigned long arg);
extern int  i810_mapbufs(struct inode *inode, struct file *filp,
			unsigned int cmd, unsigned long arg);
extern int  i810_addmap(struct inode *inode, struct file *filp,
		       unsigned int cmd, unsigned long arg);

				/* i810_context.c */
extern int  i810_resctx(struct inode *inode, struct file *filp,
		       unsigned int cmd, unsigned long arg);
extern int  i810_addctx(struct inode *inode, struct file *filp,
		       unsigned int cmd, unsigned long arg);
extern int  i810_modctx(struct inode *inode, struct file *filp,
		       unsigned int cmd, unsigned long arg);
extern int  i810_getctx(struct inode *inode, struct file *filp,
		       unsigned int cmd, unsigned long arg);
extern int  i810_switchctx(struct inode *inode, struct file *filp,
			  unsigned int cmd, unsigned long arg);
extern int  i810_newctx(struct inode *inode, struct file *filp,
		       unsigned int cmd, unsigned long arg);
extern int  i810_rmctx(struct inode *inode, struct file *filp,
		      unsigned int cmd, unsigned long arg);

extern int  i810_context_switch(drm_device_t *dev, int old, int new);
extern int  i810_context_switch_complete(drm_device_t *dev, int new);



#endif
