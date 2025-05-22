#include "pipelines/text2text_pipeline.hpp"
#include <iostream>
#include <vector>
#include <stdexcept> // For std::exception

void run_pipeline_example(BackendType backend_type, const std::string& model_name_or_path) {
    std::cout << "\n=====================================================" << std::endl;
    std::cout << "Running example for backend: "
              << (backend_type == BackendType::ONNXRuntime ? "ONNXRuntime" : "OpenVINO")
              << " with model: " << model_name_or_path << std::endl;
    std::cout << "=====================================================" << std::endl;

    try {
        std::shared_ptr<Text2TextPipeline> pipeline = create_pipeline(
            backend_type,
            model_name_or_path,
            "CPU" // Using CPU for this example
        );

        if (!pipeline) {
            std::cerr << "Failed to create the pipeline!" << std::endl;
            return;
        }

        std::cout << "\nPipeline created. Backend type: "
                  << (pipeline->get_backend_type() == BackendType::ONNXRuntime ? "ONNXRuntime" : "OpenVINO")
                  << std::endl;

        std::vector<std::string> prompts = {
            "Hello, what is the weather like?",
            "Explain the concept of a Large Language Model."
        };

        for (const auto& prompt : prompts) {
            std::cout << "\n---> Input Prompt: \"" << prompt << "\"" << std::endl;
            GenerationResult gen_result = (*pipeline)(prompt);
            std::cout << "---> Generated Output: \"" << gen_result.text << "\"" << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error during pipeline execution: " << e.what() << std::endl;
    }
    std::cout << "--- Example Run Finished ---\n" << std::endl;
}

int main() {
    std::cout << "Starting GenAI Pipeline Examples...\n" << std::endl;

    // Example with ONNXRuntime backend
    run_pipeline_example(BackendType::ONNXRuntime, "dummy_model_files/model.onnx");

    // Example with OpenVINO backend
    run_pipeline_example(BackendType::OpenVINO, "dummy_model_files/model.xml");

    std::cout << "All GenAI Pipeline Examples Complete." << std::endl;

    return 0;
}
