// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_GETRECORDINGREQUEST_MONOCLE_H_
#define FLATBUFFERS_GENERATED_GETRECORDINGREQUEST_MONOCLE_H_

#include "flatbuffers/flatbuffers.h"

namespace monocle {

struct GetRecordingRequest;
struct GetRecordingRequestBuilder;

struct GetRecordingRequest FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef GetRecordingRequestBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_RECORDINGTOKEN = 4
  };
  uint64_t recordingtoken() const {
    return GetField<uint64_t>(VT_RECORDINGTOKEN, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_RECORDINGTOKEN) &&
           verifier.EndTable();
  }
};

struct GetRecordingRequestBuilder {
  typedef GetRecordingRequest Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_recordingtoken(uint64_t recordingtoken) {
    fbb_.AddElement<uint64_t>(GetRecordingRequest::VT_RECORDINGTOKEN, recordingtoken, 0);
  }
  explicit GetRecordingRequestBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<GetRecordingRequest> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<GetRecordingRequest>(end);
    return o;
  }
};

inline flatbuffers::Offset<GetRecordingRequest> CreateGetRecordingRequest(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t recordingtoken = 0) {
  GetRecordingRequestBuilder builder_(_fbb);
  builder_.add_recordingtoken(recordingtoken);
  return builder_.Finish();
}

}  // namespace monocle

#endif  // FLATBUFFERS_GENERATED_GETRECORDINGREQUEST_MONOCLE_H_
