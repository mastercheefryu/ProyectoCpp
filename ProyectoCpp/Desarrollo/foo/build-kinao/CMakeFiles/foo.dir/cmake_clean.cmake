FILE(REMOVE_RECURSE
  "CMakeFiles/foo.dir/main.cpp.o"
  "sdk/bin/foo.pdb"
  "sdk/bin/foo"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang CXX)
  INCLUDE(CMakeFiles/foo.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
