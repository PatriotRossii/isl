cmake_minimum_required(VERSION 3.16)
project(isl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(PREBUILT_MODULE_PATH ${CMAKE_BINARY_DIR}/modules)

set(PROJECT_SOURCE_DIR src)

function(add_module name)
    file(MAKE_DIRECTORY ${PREBUILT_MODULE_PATH})
    add_custom_target(${name}.pcm
            COMMAND
                ${CMAKE_CXX_COMPILER}
                -std=c++20
                -stdlib=libc++
                -fmodules
                -c
                ${CMAKE_CURRENT_SOURCE_DIR}/${ARGN}
                -Xclang -emit-module-interface
                -o ${PREBUILT_MODULE_PATH}/${name}.pcm
                -fprebuilt-module-path=${PREBUILT_MODULE_PATH}
            )
endfunction()

add_module(initializer_list ${PROJECT_SOURCE_DIR}/initializer_list/initializer_list.cpp)

add_module(type_traits ${PROJECT_SOURCE_DIR}/type_traits/type_traits.cpp)
add_module(utility ${PROJECT_SOURCE_DIR}/utility/utility.cpp)

add_module(functional ${PROJECT_SOURCE_DIR}/functional/functional.cpp)
add_module(tuple ${PROJECT_SOURCE_DIR}/tuple/tuple.cpp)

add_module(array ${PROJECT_SOURCE_DIR}/array/array.cpp)
