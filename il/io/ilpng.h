#ifndef IL_ILPNG_H
#define IL_ILPNG_H

#include "il.h"

void save_array2ui8_to_png(array2ui8 *m, const char *file);

void load_png_to_array3ui8(array3ui8 *m, const char *file);
void save_array3ui8_to_png(array3ui8 *m, const char *file);

#endif //IL_ILPNG_H
