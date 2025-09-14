add_executable(minmax main.cc)
target_compile_features(minmax PRIVATE cxx_std_23)
set_target_properties(minmax PROPERTIES CXX_EXTENSIONS OFF)

find_package(Matplot++ CONFIG REQUIRED)
target_link_libraries(minmax PRIVATE Matplot++::cimg Matplot++::matplot)
install(TARGETS minmax RUNTIME DESTINATION .)
