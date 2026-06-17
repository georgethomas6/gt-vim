#include "../include/edit_buff.h"
#include <stdlib.h>

/*
 * Declaration for edit_buff_t
 * Container for all edits made
 * */
struct edit_buff {
  struct node *buff;
  unsigned int MAX;
  unsigned int size;
};

struct node {
  size_t byte;       // character
  unsigned int next; // where the next letter resides
};

int resize(struct edit_buff *);

/*
 * Function initializes an edit_buff_t
 * This function allocates memory; nuke must be called prior to program exit
 */
edit_buff_t *init(int start_size) {
  struct edit_buff *e_buff;
  if ((e_buff = malloc(sizeof(struct edit_buff))) == NULL) {
    return nullptr;
  };

  if ((e_buff->buff = malloc(sizeof(struct node) * start_size)) == NULL) {
    free(e_buff);
    return nullptr;
  }

  e_buff->MAX = start_size;
  e_buff->size = 0;

  return e_buff;
}

/*
 * Function frees all memory allocated by init function
 */
void nuke(edit_buff_t *e_buff) {
  free(e_buff->buff);
  free(e_buff);
  e_buff = nullptr;
}

/*
 * Function resizes buffer in e_buff
 * returns 0 on success, and < 0 on error
 */
int resize(struct edit_buff *e_buff) {
  e_buff->MAX *= 2;
  if ((realloc(e_buff->buff, sizeof(struct node) * e_buff->MAX)) == NULL) {
    return -1;
  };
  return 0;
}
