/* mga_drm_public.h -- Public header for the Matrox g200/g400 driver -*- linux-c -*-
 * Created: Tue Jan 25 01:50:01 1999 by jhartmann@precisioninsight.com
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
 * Authors: Jeff Hartmann <jhartmann@precisioninsight.com>
 *          Keith Whitwell <keithw@precisioninsight.com>
 *
 * $XFree86: xc/programs/Xserver/hw/xfree86/os-support/linux/drm/kernel/mga_drm_public.h,v 1.1 2000/02/11 17:26:07 dawes Exp $
 */

#ifndef _MGA_DRM_PUBLIC_H_
#define _MGA_DRM_PUBLIC_H_

#define MGA_F  0x1		/* fog */
#define MGA_A  0x2		/* alpha */
#define MGA_S  0x4		/* specular */
#define MGA_T2 0x8		/* multitexture */

#define MGA_WARP_TGZ            0
#define MGA_WARP_TGZF           (MGA_F)
#define MGA_WARP_TGZA           (MGA_A)
#define MGA_WARP_TGZAF          (MGA_F|MGA_A)
#define MGA_WARP_TGZS           (MGA_S)
#define MGA_WARP_TGZSF          (MGA_S|MGA_F)
#define MGA_WARP_TGZSA          (MGA_S|MGA_A)
#define MGA_WARP_TGZSAF         (MGA_S|MGA_F|MGA_A)
#define MGA_WARP_T2GZ           (MGA_T2)
#define MGA_WARP_T2GZF          (MGA_T2|MGA_F)
#define MGA_WARP_T2GZA          (MGA_T2|MGA_A)
#define MGA_WARP_T2GZAF         (MGA_T2|MGA_A|MGA_F)
#define MGA_WARP_T2GZS          (MGA_T2|MGA_S)
#define MGA_WARP_T2GZSF         (MGA_T2|MGA_S|MGA_F)
#define MGA_WARP_T2GZSA         (MGA_T2|MGA_S|MGA_A)
#define MGA_WARP_T2GZSAF        (MGA_T2|MGA_S|MGA_F|MGA_A)

#define MGA_MAX_G400_PIPES 16
#define MGA_MAX_G200_PIPES  8	/* no multitex */

#define MGA_MAX_WARP_PIPES MGA_MAX_G400_PIPES

#define MGA_CARD_TYPE_G200 1
#define MGA_CARD_TYPE_G400 2


typedef struct _drm_mga_warp_index {
   	int installed;
   	unsigned long phys_addr;
   	int size;
} mgaWarpIndex;

typedef struct drm_mga_init {
   	enum { 
	   	MGA_INIT_DMA = 0x01,
	       	MGA_CLEANUP_DMA = 0x02
	} func;
   	int reserved_map_agpstart;
   	int reserved_map_idx;
   	int buffer_map_idx;
   	int sarea_priv_offset;
   	int primary_size;
   	int warp_ucode_size;
   	int frontOffset;
   	int backOffset;
   	int depthOffset;
   	int textureOffset;
   	int textureSize;
        int agpTextureOffset;
        int agpTextureSize;
   	int cpp;
   	int stride;
   	int sgram;
	int chipset;
   	mgaWarpIndex WarpIndex[MGA_MAX_WARP_PIPES];
	int mAccess;
} drm_mga_init_t;

typedef struct _xf86drmClipRectRec {
   	unsigned short x1;
   	unsigned short y1;
   	unsigned short x2;
   	unsigned short y2;
} xf86drmClipRectRec;

#define MGA_FRONT   0x1
#define MGA_BACK    0x2
#define MGA_DEPTH   0x4


/* 3d state excluding texture units:
 */
#define MGA_CTXREG_DSTORG   0	/* validated */
#define MGA_CTXREG_MACCESS  1	
#define MGA_CTXREG_PLNWT    2	
#define MGA_CTXREG_DWGCTL    3	
#define MGA_CTXREG_ALPHACTRL 4
#define MGA_CTXREG_FOGCOLOR  5
#define MGA_CTXREG_WFLAG     6
#define MGA_CTXREG_TDUAL0    7
#define MGA_CTXREG_TDUAL1    8
#define MGA_CTXREG_FCOL      9
#define MGA_CTX_SETUP_SIZE   10

/* 2d state
 */
#define MGA_2DREG_PITCH 	0
#define MGA_2D_SETUP_SIZE 	1

/* Each texture unit has a state:
 */
#define MGA_TEXREG_CTL        0
#define MGA_TEXREG_CTL2       1
#define MGA_TEXREG_FILTER     2
#define MGA_TEXREG_BORDERCOL  3
#define MGA_TEXREG_ORG        4 /* validated */
#define MGA_TEXREG_ORG1       5
#define MGA_TEXREG_ORG2       6
#define MGA_TEXREG_ORG3       7
#define MGA_TEXREG_ORG4       8
#define MGA_TEXREG_WIDTH      9
#define MGA_TEXREG_HEIGHT     10
#define MGA_TEX_SETUP_SIZE    11

/* What needs to be changed for the current vertex dma buffer?
 */
#define MGA_UPLOAD_CTX        0x1
#define MGA_UPLOAD_TEX0       0x2
#define MGA_UPLOAD_TEX1       0x4
#define MGA_UPLOAD_PIPE       0x8
#define MGA_UPLOAD_TEX0IMAGE  0x10
#define MGA_UPLOAD_TEX1IMAGE  0x20
#define MGA_UPLOAD_2D 	      0x40
#define MGA_WAIT_AGE          0x80 /* handled client-side */
#define MGA_UPLOAD_CLIPRECTS  0x100 /* handled client-side */
#define MGA_DMA_FLUSH	      0x200 /* set when someone gets the lock
                                       quiescent */


/* 64 buffers of 16k each, total 1 meg.
 */
#define MGA_DMA_BUF_ORDER     14
#define MGA_DMA_BUF_SZ        (1<<MGA_DMA_BUF_ORDER)
#define MGA_DMA_BUF_NR        63


/* Keep these small for testing.
 */
#define MGA_NR_SAREA_CLIPRECTS 8



/* 2 heaps (1 for card, 1 for agp), each divided into upto 128
 * regions, subject to a minimum region size of (1<<16) == 64k. 
 *
 * Clients may subdivide regions internally, but when sharing between
 * clients, the region size is the minimum granularity. 
 */
#define MGA_CARD_HEAP 0
#define MGA_AGP_HEAP  1
#define MGA_NR_TEX_HEAPS 2
#define MGA_NR_TEX_REGIONS 16
#define MGA_LOG_MIN_TEX_REGION_SIZE 16

typedef struct {
	unsigned char next, prev;	
	unsigned char in_use;	
	int age;			
} mgaTexRegion;



typedef struct 
{
	/* The channel for communication of state information to the kernel
	 * on firing a vertex dma buffer.
	 */
   	unsigned int ContextState[MGA_CTX_SETUP_SIZE];
   	unsigned int ServerState[MGA_2D_SETUP_SIZE];
   	unsigned int TexState[2][MGA_TEX_SETUP_SIZE];
   	unsigned int WarpPipe;
   	unsigned int dirty;

   	unsigned int nbox;
   	xf86drmClipRectRec boxes[MGA_NR_SAREA_CLIPRECTS];


	/* Information about the most recently used 3d drawable.  The
	 * client fills in the req_* fields, the server fills in the 
	 * exported_ fields and puts the cliprects into boxes, above.
	 *
	 * The client clears the exported_drawable field before
	 * clobbering the boxes data.
	 */
        unsigned int req_drawable;	 /* the X drawable id */
	unsigned int req_draw_buffer;	 /* MGA_FRONT or MGA_BACK */

        unsigned int exported_drawable;	 
	unsigned int exported_index; 
        unsigned int exported_stamp;	
        unsigned int exported_buffers;	 
        unsigned int exported_nfront;
        unsigned int exported_nback;
	int exported_back_x, exported_front_x, exported_w;	
	int exported_back_y, exported_front_y, exported_h;
   	xf86drmClipRectRec exported_boxes[MGA_NR_SAREA_CLIPRECTS];
   
	/* Counters for aging textures and for client-side throttling.
	 */
        int last_enqueue;	/* last time a buffer was enqueued */
	int last_dispatch;	/* age of the most recently dispatched buffer */
	int last_quiescent;     /*  */


	/* LRU lists for texture memory in agp space and on the card
	 */
	mgaTexRegion texList[MGA_NR_TEX_HEAPS][MGA_NR_TEX_REGIONS+1];	
	unsigned int texAge[MGA_NR_TEX_HEAPS];	      
	
	/* Mechanism to validate card state.
	 */
   	int ctxOwner;		


} drm_mga_sarea_t;	


/* Device specific ioctls:
 */
typedef struct {
   	int idx;
	int clear_color;
	int clear_depth;
	int flags;
} drm_mga_clear_t;

typedef struct {
   	int idx;
} drm_mga_swap_t;

typedef struct {
	unsigned int destOrg;
	int idx;
	int length;
} drm_mga_iload_t;


/* These may be placeholders if we have more cliprects than
 * MGA_NR_SAREA_CLIPRECTS.  In that case, idx != real_idx; idx is
 * the number of a bogus buffer, real_idx is the real buffer to be
 * rendered multiple times.  
 *
 * This is a hack to work around assumptions built into the drm, and
 * may shortly be removed.
 */
typedef struct {
   	int idx;		/* buffer to queue and free on completion */
   	int real_idx;		/* buffer to execute */
	int real_used;		/* buf->used in for real buffer */
	int discard;		/*  */
} drm_mga_vertex_t;


#define DRM_IOCTL_MGA_INIT    DRM_IOW( 0x40, drm_mga_init_t)
#define DRM_IOCTL_MGA_SWAP    DRM_IOW( 0x41, drm_mga_swap_t)
#define DRM_IOCTL_MGA_CLEAR   DRM_IOW( 0x42, drm_mga_clear_t)
#define DRM_IOCTL_MGA_ILOAD   DRM_IOW( 0x43, drm_mga_iload_t)
#define DRM_IOCTL_MGA_VERTEX  DRM_IOW( 0x44, drm_mga_vertex_t)
#define DRM_IOCTL_MGA_FLUSH   DRM_IOW( 0x45, drm_lock_t )

#endif
