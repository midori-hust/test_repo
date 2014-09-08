#include <stdio.h>
#include <string.h>
#include "jrb.h"
#include "fields.h"

int revcomp(Jval k1, Jval k2)
{
  return -strcmp(k1.s, k2.s);
}

main()
{
  JRB b;
  JRB bn;
  IS is;

  is = new_inputstruct(NULL);
  b = make_jrb();

  while (get_line(is) >= 0) {
    (void) jrb_insert_gen(b, new_jval_s(strdup(is->text1)), 
                               new_jval_v(NULL), revcomp);
  }

  jrb_traverse(bn, b) {
    printf("%s", jval_s(bn->key));
  }
}