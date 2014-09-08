#include <stdio.h>
#include <string.h>
#include "jrb.h"
#include "fields.h"

int compare(Jval k1, Jval k2)
{
  int i1, i2;

  i1 = atoi(k1.s);
  i2 = atoi(k2.s);

  if (i1 > i2) return 1;
  if (i1 < i2) return -1;
  return strcmp(k1.s, k2.s);
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
                               new_jval_v(NULL), compare);
  }

  jrb_traverse(bn, b) {
    printf("%s", jval_s(bn->key));
  }
}