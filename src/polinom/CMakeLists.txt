add_executable(polinom main.cc)
target_compile_features(polinom PRIVATE cxx_std_23)
set_target_properties(polinom PROPERTIES CXX_EXTENSIONS OFF)

find_package(Matplot++ CONFIG REQUIRED)
target_link_libraries(polinom PRIVATE Matplot++::cimg Matplot++::matplot)
install(TARGETS polinom RUNTIME DESTINATION .)
