#pragma once

#include "fmt/entis/common/decoder.h"
#include "fmt/entis/audio/common.h"

namespace au {
namespace fmt {
namespace entis {
namespace audio {

    class LossyAudioDecoder final : public AudioDecoderImpl
    {
    public:
        LossyAudioDecoder(const MioHeader &header);
        ~LossyAudioDecoder();

        virtual bstr process_chunk(const MioChunk &chunk) override;

    private:
        struct Priv;
        std::unique_ptr<Priv> p;
    };

} } } }