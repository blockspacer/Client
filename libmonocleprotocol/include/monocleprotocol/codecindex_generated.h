// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_CODECINDEX_MONOCLE_H_
#define FLATBUFFERS_GENERATED_CODECINDEX_MONOCLE_H_

#include "flatbuffers/flatbuffers.h"

#include "codec_generated.h"

namespace monocle {

struct CodecIndex;

struct CodecIndex FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_ID = 4,
    VT_CODEC = 6,
    VT_PARAMETERS = 8,
    VT_TIMESTAMP = 10
  };
  uint64_t id() const {
    return GetField<uint64_t>(VT_ID, 0);
  }
  monocle::Codec codec() const {
    return static_cast<monocle::Codec>(GetField<int8_t>(VT_CODEC, 0));
  }
  const flatbuffers::String *parameters() const {
    return GetPointer<const flatbuffers::String *>(VT_PARAMETERS);
  }
  uint64_t timestamp() const {
    return GetField<uint64_t>(VT_TIMESTAMP, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_ID) &&
           VerifyField<int8_t>(verifier, VT_CODEC) &&
           VerifyOffset(verifier, VT_PARAMETERS) &&
           verifier.VerifyString(parameters()) &&
           VerifyField<uint64_t>(verifier, VT_TIMESTAMP) &&
           verifier.EndTable();
  }
};

struct CodecIndexBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_id(uint64_t id) {
    fbb_.AddElement<uint64_t>(CodecIndex::VT_ID, id, 0);
  }
  void add_codec(monocle::Codec codec) {
    fbb_.AddElement<int8_t>(CodecIndex::VT_CODEC, static_cast<int8_t>(codec), 0);
  }
  void add_parameters(flatbuffers::Offset<flatbuffers::String> parameters) {
    fbb_.AddOffset(CodecIndex::VT_PARAMETERS, parameters);
  }
  void add_timestamp(uint64_t timestamp) {
    fbb_.AddElement<uint64_t>(CodecIndex::VT_TIMESTAMP, timestamp, 0);
  }
  explicit CodecIndexBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  CodecIndexBuilder &operator=(const CodecIndexBuilder &);
  flatbuffers::Offset<CodecIndex> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<CodecIndex>(end);
    return o;
  }
};

inline flatbuffers::Offset<CodecIndex> CreateCodecIndex(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t id = 0,
    monocle::Codec codec = monocle::Codec::METADATA,
    flatbuffers::Offset<flatbuffers::String> parameters = 0,
    uint64_t timestamp = 0) {
  CodecIndexBuilder builder_(_fbb);
  builder_.add_timestamp(timestamp);
  builder_.add_id(id);
  builder_.add_parameters(parameters);
  builder_.add_codec(codec);
  return builder_.Finish();
}

inline flatbuffers::Offset<CodecIndex> CreateCodecIndexDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t id = 0,
    monocle::Codec codec = monocle::Codec::METADATA,
    const char *parameters = nullptr,
    uint64_t timestamp = 0) {
  auto parameters__ = parameters ? _fbb.CreateString(parameters) : 0;
  return monocle::CreateCodecIndex(
      _fbb,
      id,
      codec,
      parameters__,
      timestamp);
}

}  // namespace monocle

#endif  // FLATBUFFERS_GENERATED_CODECINDEX_MONOCLE_H_
