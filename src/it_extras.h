#ifndef LIBXMP_IT_EXTRAS_H
#define LIBXMP_IT_EXTRAS_H

#define IT_EXTRAS_MAGIC 0xfc99c286

/* We're using extras support to store IT sustain loop data. This will be moved
 * to the main data structures in the next major release.
 */
struct it_sample_extra {
	int sus_lps;
	int sus_lpe;
};

struct it_module_extras {
	uint32 magic;
	struct it_sample_extra *xsmp;	/* IT extra sample fields */
};

#define IT_MODULE_EXTRAS(x) ((struct it_module_extras *)(x).extra)
#define HAS_IT_MODULE_EXTRAS(x) \
	(IT_MODULE_EXTRAS(x) != NULL && \
	 IT_MODULE_EXTRAS(x)->magic == IT_EXTRAS_MAGIC)

int it_new_module_extras(struct module_data *);
void it_release_module_extras(struct module_data *);

#endif
