/* mach64_drm.h -- Public header for the mach64 driver -*- linux-c -*-
 * Created: Thu Nov 30 20:04:32 2000 by gareth@valinux.com
 *
 * Copyright 2000 Gareth Hughes
 * All Rights Reserved.
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
 * GARETH HUGHES BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Gareth Hughes <gareth@valinux.com>
 */

#ifndef __MACH64_DRM_H__
#define __MACH64_DRM_H__


/* WARNING: If you change any of these defines, make sure to change the
 * defines in the Xserver file (xf86drmMach64.h)
 */
#ifndef __MACH64_DEFINES__
#define __MACH64_DEFINES__

/* What needs to be changed for the current vertex buffer?
 * GH: We're going to be pedantic about this.  We want the card to do as
 * little as possible, so let's avoid having it fetch a whole bunch of
 * register values that don't change all that often, if at all.
 */
#define MACH64_UPLOAD_DST_OFF_PITCH	0x0001
#define MACH64_UPLOAD_Z_OFF_PITCH	0x0002
#define MACH64_UPLOAD_Z_ALPHA_CNTL	0x0004
#define MACH64_UPLOAD_SCALE_3D_CNTL	0x0008
#define MACH64_UPLOAD_DP_FOG_CLR	0x0010
#define MACH64_UPLOAD_DP_WRITE_MASK	0x0020
#define MACH64_UPLOAD_DP_PIX_WIDTH	0x0040
#define MACH64_UPLOAD_SETUP_CNTL	0x0080
#define MACH64_UPLOAD_MISC		0x0100
#define MACH64_UPLOAD_TEXTURE		0x0200
#define MACH64_UPLOAD_TEX0IMAGE		0x0400
#define MACH64_UPLOAD_TEX1IMAGE		0x0800
#define MACH64_UPLOAD_CLIPRECTS		0x1000 /* handled client-side */
#define MACH64_UPLOAD_CONTEXT		0x00ff
#define MACH64_UPLOAD_ALL		0x1fff

#define MACH64_FRONT			0x1
#define MACH64_BACK			0x2
#define MACH64_DEPTH			0x4

/* Keep these small for testing.
 */
#define MACH64_NR_SAREA_CLIPRECTS	8

/* WARNING: If you change any of these defines, make sure to change the
 * defines in the Xserver file (mach64_sarea.h)
 */
#define MACH64_CARD_HEAP		0
#define MACH64_AGP_HEAP			1
#define MACH64_NR_TEX_HEAPS		2
#define MACH64_NR_TEX_REGIONS		64
#define MACH64_LOG_TEX_GRANULARITY	16

#define MACH64_TEX_MAXLEVELS		1

#endif /* __MACH64_SAREA_DEFINES__ */

typedef struct {
	unsigned int dst_off_pitch;

	unsigned int z_off_pitch;
	unsigned int z_cntl;
	unsigned int alpha_tst_cntl;

	unsigned int scale_3d_cntl;

	unsigned int sc_left_right;
	unsigned int sc_top_bottom;

	unsigned int dp_fog_clr;
	unsigned int dp_write_mask;
	unsigned int dp_pix_width;
	unsigned int dp_mix;
	unsigned int dp_src;

	unsigned int clr_cmp_cntl;
	unsigned int gui_traj_cntl;

	unsigned int setup_cntl;

	unsigned int tex_size_pitch;
	unsigned int tex_cntl;
	unsigned int secondary_tex_off;
	unsigned int tex_offset;
} drm_mach64_context_regs_t;

typedef struct drm_mach64_tex_region {
	unsigned char next, prev;
	unsigned char in_use;
	int age;
} drm_mach64_tex_region_t;

typedef struct drm_mach64_sarea {
	/* The channel for communication of state information to the kernel
	 * on firing a vertex dma buffer.
	 */
	drm_mach64_context_regs_t context_state;
	unsigned int dirty;
	unsigned int vertsize;

	/* The current cliprects, or a subset thereof.
	 */
	drm_clip_rect_t boxes[MACH64_NR_SAREA_CLIPRECTS];
	unsigned int nbox;

	/* Counters for client-side throttling of rendering clients.
	 */
	unsigned int last_frame;
	unsigned int last_dispatch;

	/* Texture memory LRU.
	 */
	drm_mach64_tex_region_t tex_list[MACH64_NR_TEX_HEAPS]
					[MACH64_NR_TEX_REGIONS+1];
	int tex_age[MACH64_NR_TEX_HEAPS];
	int ctx_owner;
} drm_mach64_sarea_t;



typedef struct drm_mach64_init {
	enum {
		MACH64_INIT_DMA = 0x01,
		MACH64_CLEANUP_DMA = 0x02
	} func;

	unsigned int sarea_priv_offset;
	int is_pci;

	unsigned int fb_bpp;
	unsigned int front_offset, front_pitch;
	unsigned int back_offset, back_pitch;

	unsigned int depth_bpp;
	unsigned int depth_offset, depth_pitch;
	unsigned int span_offset;

	unsigned int fb_offset;
	unsigned int mmio_offset;
	unsigned int buffers_offset;
	unsigned int agp_textures_offset;
} drm_mach64_init_t;

typedef struct drm_mach64_clear {
	unsigned int flags;
	int x, y, w, h;
	unsigned int clear_color;
	unsigned int clear_depth;
} drm_mach64_clear_t;

typedef struct drm_mach64_vertex {
	int prim;
	int idx;			/* Index of vertex buffer */
	int count;			/* Number of vertices in buffer */
	int discard;			/* Client finished with buffer? */
} drm_mach64_vertex_t;

#endif
