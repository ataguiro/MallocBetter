export DYLD_LIBRARY_PATH=.
export DYLD_INSERT_LIBRARIES=test.so
export DYLD_FORCE_FLAT_NAMESPACE=1
$@
