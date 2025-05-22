#include "openvino_text_pipeline.hpp"
#include <iostream>
#include <vector>

OVText2TextPipeline::OVText2TextPipeline(const std::string& model_path, const std::string& device)
    : model_path_(model_path), device_(device) {
    std::cout << "Initializing OVText2TextPipeline..." << std::endl;
    std::cout << "  Model Path: " << model_path_ << std::endl;
    std::cout << "  Device: " << device_ << std::endl;

    config_ = Ova::Config::Create(model_path.c_str());
    config_->set_device(device_);

    model_ = Ova::Model::Create(*config_);
    tokenizer_ = Ova::Tokenizer::Create(*model_);
    params_ = Ova::GeneratorParams::Create(*model_);
    params_->SetSearchOption("max_new_tokens", 256); // Example search option

    generator_ = Ova::Generator::Create(*model_, *params_);

    std::cout << "OVText2TextPipeline initialized." << std::endl;
}

OVText2TextPipeline::~OVText2TextPipeline() {
    std::cout << "Destroying OVText2TextPipeline..." << std::endl;
}

GenerationResult OVText2TextPipeline::operator()(const std::string& input) {
    std::cout << "OVText2TextPipeline generating for input: \"" << input << "\"" << std::endl;

    std::string processed_input = tokenizer_->ApplyChatTemplate("", input);
    std::vector<int> token_ids = tokenizer_->Encode(processed_input);

    generator_->SetInputTokens(token_ids);

    std::vector<int> generated_tokens;
    while (!generator_->IsDone()) {
        int next_token = generator_->GenerateNextToken();
        if (next_token != -1) { // Assuming -1 is an end/invalid token
            generated_tokens.push_back(next_token);
        } else {
            break; // Should be handled by IsDone, but good for safety
        }
    }

    GenerationResult result;
    result.text = tokenizer_->Decode(generated_tokens);
    std::cout << "OVText2TextPipeline generation complete. Output: " << result.text << std::endl;
    return result;
}

BackendType OVText2TextPipeline::get_backend_type() const {
    return BackendType::OpenVINO;
}
