#include <stdio.h>
#include <string.h>
#include "jrb.h"
#include "fields.h"

main()
{
  JRB b;
  JRB bn;
  IS is;

  is = new_inputstruct(NULL);
  b = make_jrb();

  while (get_line(is) >= 0) {
    if (jrb_find_str(b, is->text1) == NULL) {
      (void) jrb_insert_str(b, strdup(is->text1), new_jval_v(NULL));
    }
  }

  jrb_traverse(bn, b) {
    printf("%s", jval_s(bn->key));
  }
}