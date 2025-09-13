add_executable(trapmf main.cc)
target_compile_features(trapmf PRIVATE cxx_std_23)
set_target_properties(trapmf PROPERTIES CXX_EXTENSIONS OFF)

find_package(Matplot++ CONFIG REQUIRED)
target_link_libraries(trapmf PRIVATE Matplot++::cimg Matplot++::matplot)