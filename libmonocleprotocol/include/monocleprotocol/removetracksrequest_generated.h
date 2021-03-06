// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_REMOVETRACKSREQUEST_MONOCLE_H_
#define FLATBUFFERS_GENERATED_REMOVETRACKSREQUEST_MONOCLE_H_

#include "flatbuffers/flatbuffers.h"

namespace monocle {

struct RemoveTracksRequest;
struct RemoveTracksRequestBuilder;

struct RemoveTracksRequest FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef RemoveTracksRequestBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_RECORDINGTOKEN = 4,
    VT_IDS = 6
  };
  uint64_t recordingtoken() const {
    return GetField<uint64_t>(VT_RECORDINGTOKEN, 0);
  }
  const flatbuffers::Vector<uint32_t> *ids() const {
    return GetPointer<const flatbuffers::Vector<uint32_t> *>(VT_IDS);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_RECORDINGTOKEN) &&
           VerifyOffset(verifier, VT_IDS) &&
           verifier.VerifyVector(ids()) &&
           verifier.EndTable();
  }
};

struct RemoveTracksRequestBuilder {
  typedef RemoveTracksRequest Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_recordingtoken(uint64_t recordingtoken) {
    fbb_.AddElement<uint64_t>(RemoveTracksRequest::VT_RECORDINGTOKEN, recordingtoken, 0);
  }
  void add_ids(flatbuffers::Offset<flatbuffers::Vector<uint32_t>> ids) {
    fbb_.AddOffset(RemoveTracksRequest::VT_IDS, ids);
  }
  explicit RemoveTracksRequestBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<RemoveTracksRequest> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<RemoveTracksRequest>(end);
    return o;
  }
};

inline flatbuffers::Offset<RemoveTracksRequest> CreateRemoveTracksRequest(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t recordingtoken = 0,
    flatbuffers::Offset<flatbuffers::Vector<uint32_t>> ids = 0) {
  RemoveTracksRequestBuilder builder_(_fbb);
  builder_.add_recordingtoken(recordingtoken);
  builder_.add_ids(ids);
  return builder_.Finish();
}

inline flatbuffers::Offset<RemoveTracksRequest> CreateRemoveTracksRequestDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t recordingtoken = 0,
    const std::vector<uint32_t> *ids = nullptr) {
  auto ids__ = ids ? _fbb.CreateVector<uint32_t>(*ids) : 0;
  return monocle::CreateRemoveTracksRequest(
      _fbb,
      recordingtoken,
      ids__);
}

}  // namespace monocle

#endif  // FLATBUFFERS_GENERATED_REMOVETRACKSREQUEST_MONOCLE_H_
