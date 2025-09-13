add_executable(gbellmf main.cc)
target_compile_features(gbellmf PRIVATE cxx_std_23)
set_target_properties(gbellmf PROPERTIES CXX_EXTENSIONS OFF)

find_package(Matplot++ CONFIG REQUIRED)
target_link_libraries(gbellmf PRIVATE Matplot++::cimg Matplot++::matplot)
install(TARGETS gbellmf RUNTIME DESTINATION .)
