add_executable(sigmf main.cc)
target_compile_features(sigmf PRIVATE cxx_std_23)
set_target_properties(sigmf PROPERTIES CXX_EXTENSIONS OFF)

find_package(Matplot++ CONFIG REQUIRED)
target_link_libraries(sigmf PRIVATE Matplot++::cimg Matplot++::matplot)
install(TARGETS sigmf RUNTIME DESTINATION .)
