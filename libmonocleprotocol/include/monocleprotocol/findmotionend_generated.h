// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_FINDMOTIONEND_MONOCLE_H_
#define FLATBUFFERS_GENERATED_FINDMOTIONEND_MONOCLE_H_

#include "flatbuffers/flatbuffers.h"

namespace monocle {

struct FindMotionEnd;

struct FindMotionEnd FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TOKEN = 4,
    VT_RET = 6
  };
  uint64_t token() const {
    return GetField<uint64_t>(VT_TOKEN, 0);
  }
  uint64_t ret() const {
    return GetField<uint64_t>(VT_RET, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_TOKEN) &&
           VerifyField<uint64_t>(verifier, VT_RET) &&
           verifier.EndTable();
  }
};

struct FindMotionEndBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_token(uint64_t token) {
    fbb_.AddElement<uint64_t>(FindMotionEnd::VT_TOKEN, token, 0);
  }
  void add_ret(uint64_t ret) {
    fbb_.AddElement<uint64_t>(FindMotionEnd::VT_RET, ret, 0);
  }
  explicit FindMotionEndBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  FindMotionEndBuilder &operator=(const FindMotionEndBuilder &);
  flatbuffers::Offset<FindMotionEnd> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FindMotionEnd>(end);
    return o;
  }
};

inline flatbuffers::Offset<FindMotionEnd> CreateFindMotionEnd(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t token = 0,
    uint64_t ret = 0) {
  FindMotionEndBuilder builder_(_fbb);
  builder_.add_ret(ret);
  builder_.add_token(token);
  return builder_.Finish();
}

}  // namespace monocle

#endif  // FLATBUFFERS_GENERATED_FINDMOTIONEND_MONOCLE_H_