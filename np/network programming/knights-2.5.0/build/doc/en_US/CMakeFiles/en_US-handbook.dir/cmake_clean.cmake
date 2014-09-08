FILE(REMOVE_RECURSE
  "CMakeFiles/en_US-handbook"
  "index.cache.bz2"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/en_US-handbook.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
