cmake_minimum_required(VERSION 3.15)
project(GenAIPipelineProject CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the module path for custom Find scripts
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# --- Global Include Directory ---
# This allows #include "pipelines/text2text_pipeline.hpp" etc. from anywhere
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


# --- Pipeline Interface Library ---
add_library(genai_pipeline_interface
    pipelines/text2text_pipeline.hpp
    pipelines/text2text_pipeline.cpp
)
target_include_directories(genai_pipeline_interface PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include> # For potential installation
)


# --- ONNX Backend ---
find_package(OrtGenAI REQUIRED) # Uses cmake/FindOrtGenAI.cmake

add_library(genai_onnx_backend
    backends/onnx/onnx_text_pipeline.hpp
    backends/onnx/onnx_text_pipeline.cpp
    # backends/onnx/ort_genai.h # Header only, included via OrtGenAI::ort_genai
)
target_link_libraries(genai_onnx_backend PUBLIC
    genai_pipeline_interface
    OrtGenAI::ort_genai # Links against the mocked (or real) OrtGenAI
)
target_include_directories(genai_onnx_backend PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)


# --- OpenVINO Backend ---
find_package(OvGenAI REQUIRED) # Uses cmake/FindOvGenAI.cmake

add_library(genai_openvino_backend
    backends/openvino/openvino_text_pipeline.hpp
    backends/openvino/openvino_text_pipeline.cpp
    # backends/openvino/ov_genai.h # Header only, included via OvGenAI::ov_genai
)
target_link_libraries(genai_openvino_backend PUBLIC
    genai_pipeline_interface
    OvGenAI::ov_genai # Links against the mocked (or real) OvGenAI
)
target_include_directories(genai_openvino_backend PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)


# --- Example Executable ---
add_executable(genai_example examples/main.cpp)
target_link_libraries(genai_example PRIVATE
    genai_pipeline_interface # For create_pipeline & base classes
    genai_onnx_backend       # For linking concrete ONNX pipeline
    genai_openvino_backend   # For linking concrete OpenVINO pipeline
)
target_include_directories(genai_example PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# --- Standard Install Rules (Optional) ---
# include(GNUInstallDirs)
# install(TARGETS genai_pipeline_interface genai_onnx_backend genai_openvino_backend genai_example
#     EXPORT GenAIPipelineProjectTargets
#     ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )
# install(DIRECTORY pipelines/ backends/ # Add relevant headers
#     DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/GenAIPipelineProject
#     FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h"
# )

# Print some info
message(STATUS "Project Source Directory: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "Project Binary Directory: ${CMAKE_BINARY_DIR}")
