add_executable(gauss2mf main.cc)
target_compile_features(gauss2mf PRIVATE cxx_std_23)
set_target_properties(gauss2mf PROPERTIES CXX_EXTENSIONS OFF)

find_package(Matplot++ CONFIG REQUIRED)
target_link_libraries(gauss2mf PRIVATE Matplot++::cimg Matplot++::matplot)
install(TARGETS gauss2mf RUNTIME DESTINATION .)
