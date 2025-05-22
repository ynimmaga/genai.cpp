# genai.cpp
A repository to standardize GenAI pipeline interfaces and allow different backends to implement their own optimized methods

## Project Structure

genai.cpp/
├── pipelines/                # Core pipeline interface
│   ├── text2text_pipeline.hpp  # Abstract base class and factory
│   └── text2text_pipeline.cpp  # Factory implementation
├── backends/                 # Backend-specific implementations
│   ├── onnx/
│   │   ├── ort_genai.h           # (Mocked) ONNX GenAI C API header
│   │   ├── onnx_text_pipeline.hpp
│   │   └── onnx_text_pipeline.cpp
│   └── openvino/
│       ├── ov_genai.h            # (Mocked) OpenVINO GenAI C API header
│       ├── openvino_text_pipeline.hpp
│       └── openvino_text_pipeline.cpp
├── examples/                 # Example usage
│   └── main.cpp
├── cmake/                    # CMake helper modules
│   ├── FindOrtGenAI.cmake      # (Mocked) CMake find module for ONNX GenAI lib
│   └── FindOvGenAI.cmake       # (Mocked) CMake find module for OpenVINO GenAI lib
├── CMakeLists.txt            # Root CMake build script
└── README.md                 # This file



## Core Components

* **`Text2TextPipeline` (in `pipelines/`)**: An abstract base class defining the interface for text generation. It includes a pure virtual `operator()` for performing inference and a factory function `create_pipeline` to instantiate specific backend implementations.
* **`ORTText2TextPipeline` (in `backends/onnx/`)**: A concrete implementation for the ONNX Runtime backend. It uses a mocked `ort_genai.h` API (inspired by `image_a63089.png`) for its operations.
* **`OVText2TextPipeline` (in `backends/openvino/`)**: A concrete implementation for an OpenVINO backend. It uses a mocked `ov_genai.h` API, designed conceptually parallel to the ONNX one.
* **Mocked GenAI Headers (`ort_genai.h`, `ov_genai.h`)**: These files simulate the C-style API that a real GenAI SDK might provide for interacting with models, tokenizers, and generators.
* **`create_pipeline` Factory**: Allows easy instantiation of a desired pipeline backend (`ONNXRuntime` or `OpenVINO`) by specifying the `BackendType`, model path, and device.

## Building the Project

This project uses CMake for building.

### Prerequisites

* A C++17 compatible compiler (e.g., GCC, Clang, MSVC)
* CMake (version 3.15 or newer)

### Build Steps (Conceptual)

1.  **Clone the repository / Create the files**:
    Ensure all files and directories are created as specified.

2.  **Configure with CMake**:
    Open a terminal or command prompt in the root directory (`genai_pipeline_project/`).
    ```bash
    mkdir build
    cd build
    cmake ..
    ```

3.  **Build the project**:
    ```bash
    cmake --build .
    ```
   
    This will compile the pipeline libraries and the example executable (`genai_example`).

## Running the Example

After a successful build, the example executable will be located in the `build` directory (or a subdirectory like `build/Debug` or `build/examples/` depending on your CMake generator and setup).

```bash
./genai_example

