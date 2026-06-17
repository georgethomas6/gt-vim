#include <stdlib.h>

typedef struct edit_buff edit_buff_t;

edit_buff_t *init(int start_size);

void nuke(edit_buff_t *);
