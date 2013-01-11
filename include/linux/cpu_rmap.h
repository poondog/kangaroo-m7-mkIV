/*
 * cpu_rmap.c: CPU affinity reverse-map support
 * Copyright 2011 Solarflare Communications Inc.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, incorporated herein by reference.
 */

#include <linux/cpumask.h>
#include <linux/gfp.h>
#include <linux/slab.h>
#include <linux/kref.h>

struct cpu_rmap {
	struct kref	refcount;
	u16		size, used;
	void		**obj;
	struct {
		u16	index;
		u16	dist;
	}		near[0];
};
#define CPU_RMAP_DIST_INF 0xffff

extern struct cpu_rmap *alloc_cpu_rmap(unsigned int size, gfp_t flags);

extern int cpu_rmap_put(struct cpu_rmap *rmap);

extern int cpu_rmap_add(struct cpu_rmap *rmap, void *obj);
extern int cpu_rmap_update(struct cpu_rmap *rmap, u16 index,
			   const struct cpumask *affinity);

static inline u16 cpu_rmap_lookup_index(struct cpu_rmap *rmap, unsigned int cpu)
{
	return rmap->near[cpu].index;
}

static inline void *cpu_rmap_lookup_obj(struct cpu_rmap *rmap, unsigned int cpu)
{
	return rmap->obj[rmap->near[cpu].index];
}

#ifdef CONFIG_GENERIC_HARDIRQS

static inline struct cpu_rmap *alloc_irq_cpu_rmap(unsigned int size)
{
	return alloc_cpu_rmap(size, GFP_KERNEL);
}
extern void free_irq_cpu_rmap(struct cpu_rmap *rmap);

extern int irq_cpu_rmap_add(struct cpu_rmap *rmap, int irq);

#endif
