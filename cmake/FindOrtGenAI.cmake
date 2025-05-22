# Mock FindOrtGenAI.cmake
# In a real scenario, this would locate the ONNX Runtime GenAI headers and libraries.

message(STATUS "Looking for OrtGenAI (mocked)")

# Set placeholder paths - these would be found by CMake in a real setup
set(ORT_GENAI_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/backends/onnx") # Points to our mock header
set(ORT_GENAI_LIBRARIES "ort_genai_mock_lib") # Placeholder library name

if(ORT_GENAI_INCLUDE_DIRS AND EXISTS "${ORT_GENAI_INCLUDE_DIRS}/ort_genai.h")
    set(OrtGenAI_FOUND TRUE)
    message(STATUS "Found OrtGenAI (mocked): TRUE")
    message(STATUS "  OrtGenAI_INCLUDE_DIRS: ${ORT_GENAI_INCLUDE_DIRS}")
    message(STATUS "  OrtGenAI_LIBRARIES: ${ORT_GENAI_LIBRARIES}")
else()
    set(OrtGenAI_FOUND FALSE)
    message(STATUS "Found OrtGenAI (mocked): FALSE - Mock header not found where expected.")
endif()

if(OrtGenAI_FOUND)
    if(NOT TARGET OrtGenAI::ort_genai)
        add_library(OrtGenAI::ort_genai INTERFACE IMPORTED)
        set_target_properties(OrtGenAI::ort_genai PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${ORT_GENAI_INCLUDE_DIRS}")
        # In a real scenario, you'd also set INTERFACE_LINK_LIBRARIES
        # add_library(ort_genai_mock_lib STATIC IMPORTED) # if it were a real lib
        # set_property(TARGET ort_genai_mock_lib PROPERTY IMPORTED_LOCATION "/path/to/libort_genai.a")
        # target_link_libraries(OrtGenAI::ort_genai INTERFACE ort_genai_mock_lib)
    endif()
endif()
