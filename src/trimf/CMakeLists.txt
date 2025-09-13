add_executable(trimf main.cc)
target_compile_features(trimf PRIVATE cxx_std_23)
set_target_properties(trimf PROPERTIES CXX_EXTENSIONS OFF)

find_package(Matplot++ CONFIG REQUIRED)
target_link_libraries(trimf PRIVATE Matplot++::cimg Matplot++::matplot)