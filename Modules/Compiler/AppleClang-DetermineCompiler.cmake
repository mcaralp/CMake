
set(_compiler_id_pp_test "defined(__clang__) && defined(__apple_build_version__)")

include("${CMAKE_CURRENT_LIST_DIR}/Clang-DetermineCompilerInternal.cmake")

set(_compiler_id_version_compute "${_compiler_id_version_compute}
# define COMPILER_VERSION_TWEAK DEC(__apple_build_version__)")
