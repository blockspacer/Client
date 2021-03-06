// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_REMOVERECEIVERREQUEST_MONOCLE_H_
#define FLATBUFFERS_GENERATED_REMOVERECEIVERREQUEST_MONOCLE_H_

#include "flatbuffers/flatbuffers.h"

namespace monocle {

struct RemoveReceiverRequest;
struct RemoveReceiverRequestBuilder;

struct RemoveReceiverRequest FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef RemoveReceiverRequestBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TOKEN = 4
  };
  uint64_t token() const {
    return GetField<uint64_t>(VT_TOKEN, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_TOKEN) &&
           verifier.EndTable();
  }
};

struct RemoveReceiverRequestBuilder {
  typedef RemoveReceiverRequest Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_token(uint64_t token) {
    fbb_.AddElement<uint64_t>(RemoveReceiverRequest::VT_TOKEN, token, 0);
  }
  explicit RemoveReceiverRequestBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<RemoveReceiverRequest> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<RemoveReceiverRequest>(end);
    return o;
  }
};

inline flatbuffers::Offset<RemoveReceiverRequest> CreateRemoveReceiverRequest(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t token = 0) {
  RemoveReceiverRequestBuilder builder_(_fbb);
  builder_.add_token(token);
  return builder_.Finish();
}

}  // namespace monocle

#endif  // FLATBUFFERS_GENERATED_REMOVERECEIVERREQUEST_MONOCLE_H_
