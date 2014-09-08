#include <stdio.h>
#include <string.h>
#include "jrb.h"
#include "fields.h"

main()
{
  JRB level_1, level_2;
  JRB bn, bn2;
  IS is;

  is = new_inputstruct(NULL);
  level_1 = make_jrb();

  while (get_line(is) >= 0) {
    bn = jrb_find_int(level_1, atoi(is->text1));
    if (bn == NULL) {
      bn = jrb_insert_int(level_1, atoi(is->text1), 
                               new_jval_v((void *)make_jrb()));
    }
    level_2 = (JRB ) jval_v(bn->val);
    jrb_insert_str(level_2, strdup(is->text1), new_jval_v(NULL));
  }

  jrb_traverse(bn, level_1) {
    level_2 = (JRB ) jval_v(bn->val);
    jrb_traverse(bn2, level_2) {
      printf("%s", bn2->key.s);
    }
  }
}