add_executable(probabilistic-interpretation main.cc)
target_compile_features(probabilistic-interpretation PRIVATE cxx_std_23)
set_target_properties(probabilistic-interpretation PROPERTIES CXX_EXTENSIONS OFF)

find_package(Matplot++ CONFIG REQUIRED)
target_link_libraries(probabilistic-interpretation PRIVATE Matplot++::cimg Matplot++::matplot)
install(TARGETS probabilistic-interpretation RUNTIME DESTINATION .)