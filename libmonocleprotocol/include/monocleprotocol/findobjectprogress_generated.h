// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_FINDOBJECTPROGRESS_MONOCLE_H_
#define FLATBUFFERS_GENERATED_FINDOBJECTPROGRESS_MONOCLE_H_

#include "flatbuffers/flatbuffers.h"

namespace monocle {

struct FindObjectProgress;
struct FindObjectProgressBuilder;

struct FindObjectProgress FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FindObjectProgressBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TOKEN = 4,
    VT_PROGRESS = 6
  };
  uint64_t token() const {
    return GetField<uint64_t>(VT_TOKEN, 0);
  }
  float progress() const {
    return GetField<float>(VT_PROGRESS, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_TOKEN) &&
           VerifyField<float>(verifier, VT_PROGRESS) &&
           verifier.EndTable();
  }
};

struct FindObjectProgressBuilder {
  typedef FindObjectProgress Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_token(uint64_t token) {
    fbb_.AddElement<uint64_t>(FindObjectProgress::VT_TOKEN, token, 0);
  }
  void add_progress(float progress) {
    fbb_.AddElement<float>(FindObjectProgress::VT_PROGRESS, progress, 0.0f);
  }
  explicit FindObjectProgressBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FindObjectProgress> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FindObjectProgress>(end);
    return o;
  }
};

inline flatbuffers::Offset<FindObjectProgress> CreateFindObjectProgress(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t token = 0,
    float progress = 0.0f) {
  FindObjectProgressBuilder builder_(_fbb);
  builder_.add_token(token);
  builder_.add_progress(progress);
  return builder_.Finish();
}

}  // namespace monocle

#endif  // FLATBUFFERS_GENERATED_FINDOBJECTPROGRESS_MONOCLE_H_
