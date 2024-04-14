
project(Practichka_18 VERSION ${VERSION_PROJECT}
    LANGUAGES ${LANGUAGES_PROJECT})


add_executable(Practichka_18
    src/main.cpp
    include/ExceotionError.hpp
)

target_link_libraries(Practichka_18 PRIVATE CPPON_lib)
