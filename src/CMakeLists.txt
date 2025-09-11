add_executable(main main.cc)
target_compile_features(main PRIVATE cxx_std_20)
set_target_properties(main PROPERTIES CXX_EXTENSIONS OFF)

find_package(Matplot++ CONFIG REQUIRED)
target_link_libraries(main PRIVATE Matplot++::cimg Matplot++::matplot)
