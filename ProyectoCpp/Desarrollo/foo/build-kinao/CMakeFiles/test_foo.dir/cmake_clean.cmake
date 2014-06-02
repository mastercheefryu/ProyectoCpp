FILE(REMOVE_RECURSE
  "CMakeFiles/test_foo.dir/test.cpp.o"
  "sdk/bin/test_foo.pdb"
  "sdk/bin/test_foo"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang CXX)
  INCLUDE(CMakeFiles/test_foo.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
