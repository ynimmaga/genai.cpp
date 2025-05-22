#ifndef TEXT2TEXT_PIPELINE_HPP
#define TEXT2TEXT_PIPELINE_HPP

#include <string>
#include <memory> // For std::shared_ptr
#include <vector> // For potential future use

// Enum to specify the backend for the pipeline
enum class BackendType {
    OpenVINO,
    ONNXRuntime
};

// Struct to hold the result of a generation operation
struct GenerationResult {
    std::string text;
    // Could include other metadata like scores, tokens, etc.
};

// Abstract base class for a Text2Text Pipeline
class Text2TextPipeline {
public:
    virtual ~Text2TextPipeline() = default;

    // Pure virtual function for the generation operation
    // Takes a string prompt as input and returns a GenerationResult
    virtual GenerationResult operator()(const std::string& input) = 0;

    virtual BackendType get_backend_type() const = 0;
};

// Factory function to create instances of the Text2TextPipeline
std::shared_ptr<Text2TextPipeline> create_pipeline(
    BackendType backend,
    const std::string& model_path,
    const std::string& device = "CPU"); // Default device CPU

#endif // TEXT2TEXT_PIPELINE_HPP
