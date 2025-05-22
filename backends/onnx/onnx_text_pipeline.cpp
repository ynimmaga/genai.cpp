#include "onnx_text_pipeline.hpp"
#include <iostream>
#include <vector> // Required for std::vector

ORTText2TextPipeline::ORTText2TextPipeline(const std::string& model_path, const std::string& device)
    : model_path_(model_path), device_(device) {
    std::cout << "Initializing ORTText2TextPipeline..." << std::endl;
    std::cout << "  Model Path: " << model_path_ << std::endl;
    std::cout << "  Device: " << device_ << std::endl;

    // auto config = OgaConfig::Create(model_path.c_str());
    config_ = Oga::Config::Create(model_path.c_str());
    config_->append_provider(device_); // Example: "cpu", "cuda", etc.

    // model = OgaModel::Create(*config);
    model_ = Oga::Model::Create(*config_);

    // tokenizer = OgaTokenizer::Create(*model);
    tokenizer_ = Oga::Tokenizer::Create(*model_);

    // params = OgaGeneratorParams::Create(*model);
    params_ = Oga::GeneratorParams::Create(*model_);
    params_->SetSearchOption("max_length", 1024); // As per image

    // generator = OgaGenerator::Create(*model, *params);
    generator_ = Oga::Generator::Create(*model_, *params_);

    std::cout << "ORTText2TextPipeline initialized." << std::endl;
}

ORTText2TextPipeline::~ORTText2TextPipeline() {
    std::cout << "Destroying ORTText2TextPipeline..." << std::endl;
    // Smart pointers will handle deallocation
}

GenerationResult ORTText2TextPipeline::operator()(const std::string& input) {
    std::cout << "ORTText2TextPipeline generating for input: \"" << input << "\"" << std::endl;

    // auto seq = OgaSequences::Create(); // Not clear how OgaSequences is used with ApplyChatTemplate from image
                                       // Assuming ApplyChatTemplate returns the sequence directly or modifies a passed-in one.
                                       // For mock, let's assume it returns the needed sequence directly.
    std::vector<int> encoded_input_tokens; // Placeholder for token_ids
    // tokenizer->Encode(tokenizer->ApplyChatTemplate("", input.c_str(), true).c_str(), *seq);
    // The image shows: tokenizer->Encode(tokenizer->ApplyChatTemplate("", input.c_str(), true),c_str(), *seq);
    // This looks a bit off. Let's interpret ApplyChatTemplate as producing tokens directly or a string to be encoded.
    // Let's go with the interpretation from image_a63089.png which is:
    // auto seq = OgaSequences::Create(); // this seems to be a container for sequences
    // tokenizer->Encode(tokenizer->ApplyChatTemplate("", input.c_str(), true),c_str(), *seq); // this line is complex
    // generator->AppendTokenSequences(*seq);

    // Simplified mock based on image:
    // The image's Encode line is complex. A more typical flow:
    // 1. Apply chat template (if any) to input string -> processed_input_string
    // 2. Encode processed_input_string -> token_ids
    // Re-interpreting the image line: `tokenizer->Encode(tokenizer->ApplyChatTemplate("", input.c_str(), true).c_str(), *seq);`
    // This seems like ApplyChatTemplate returns a string, which is then encoded.
    // Or ApplyChatTemplate directly provides tokens. The `*seq` argument to Encode is also unusual if it's not an output param.

    // Let's follow the image structure more directly for the mock:
    // auto seq_obj = Oga::Sequences::Create(); // Assuming this is how 'seq' is obtained
    // The image has: tokenizer->Encode(tokenizer->ApplyChatTemplate("", input.c_str(), true),c_str(), *seq);
    // Let's assume ApplyChatTemplate provides the tokens and they are then given to the generator
    std::vector<int> templated_tokens = tokenizer_->ApplyChatTemplate("", input.c_str(), true, encoded_input_tokens); // Mocked to return tokens

    generator_->AppendTokenSequences(templated_tokens); // `templated_tokens` is our `*seq` equivalent here

    std::string output_str;
    std::vector<int> full_decoded_sequence;

    while (!generator_->IsDone()) {
        generator_->GenerateNextToken();
        const std::vector<int>& sequence_data_batch = generator_->GetSequenceData(0); // Get data for the first (and only) sequence
        if (!sequence_data_batch.empty()) {
            int tok = sequence_data_batch.back(); // Get the last token (the new one)
            full_decoded_sequence.push_back(tok); // Collect all generated tokens
        }
    }
    output_str = tokenizer_->Decode(full_decoded_sequence);

    GenerationResult result;
    result.text = output_str;
    std::cout << "ORTText2TextPipeline generation complete. Output: " << result.text << std::endl;
    return result;
}

BackendType ORTText2TextPipeline::get_backend_type() const {
    return BackendType::ONNXRuntime;
}
