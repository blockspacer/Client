// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_REMOVETRACKREQUEST_MONOCLE_H_
#define FLATBUFFERS_GENERATED_REMOVETRACKREQUEST_MONOCLE_H_

#include "flatbuffers/flatbuffers.h"

namespace monocle {

struct RemoveTrackRequest;

struct RemoveTrackRequest FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_RECORDINGTOKEN = 4,
    VT_ID = 6
  };
  uint64_t recordingtoken() const {
    return GetField<uint64_t>(VT_RECORDINGTOKEN, 0);
  }
  uint32_t id() const {
    return GetField<uint32_t>(VT_ID, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_RECORDINGTOKEN) &&
           VerifyField<uint32_t>(verifier, VT_ID) &&
           verifier.EndTable();
  }
};

struct RemoveTrackRequestBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_recordingtoken(uint64_t recordingtoken) {
    fbb_.AddElement<uint64_t>(RemoveTrackRequest::VT_RECORDINGTOKEN, recordingtoken, 0);
  }
  void add_id(uint32_t id) {
    fbb_.AddElement<uint32_t>(RemoveTrackRequest::VT_ID, id, 0);
  }
  explicit RemoveTrackRequestBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  RemoveTrackRequestBuilder &operator=(const RemoveTrackRequestBuilder &);
  flatbuffers::Offset<RemoveTrackRequest> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<RemoveTrackRequest>(end);
    return o;
  }
};

inline flatbuffers::Offset<RemoveTrackRequest> CreateRemoveTrackRequest(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t recordingtoken = 0,
    uint32_t id = 0) {
  RemoveTrackRequestBuilder builder_(_fbb);
  builder_.add_recordingtoken(recordingtoken);
  builder_.add_id(id);
  return builder_.Finish();
}

}  // namespace monocle

#endif  // FLATBUFFERS_GENERATED_REMOVETRACKREQUEST_MONOCLE_H_