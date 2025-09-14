add_executable(fuzzy-complements main.cc)
target_compile_features(fuzzy-complements PRIVATE cxx_std_23)
set_target_properties(fuzzy-complements PROPERTIES CXX_EXTENSIONS OFF)

find_package(Matplot++ CONFIG REQUIRED)
target_link_libraries(fuzzy-complements PRIVATE Matplot++::cimg Matplot++::matplot)
install(TARGETS fuzzy-complements RUNTIME DESTINATION .)