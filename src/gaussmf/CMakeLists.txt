add_executable(gaussmf main.cc)
target_compile_features(gaussmf PRIVATE cxx_std_23)
set_target_properties(gaussmf PROPERTIES CXX_EXTENSIONS OFF)

find_package(Matplot++ CONFIG REQUIRED)
target_link_libraries(gaussmf PRIVATE Matplot++::cimg Matplot++::matplot)