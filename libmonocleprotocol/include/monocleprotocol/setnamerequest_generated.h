// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_SETNAMEREQUEST_MONOCLE_H_
#define FLATBUFFERS_GENERATED_SETNAMEREQUEST_MONOCLE_H_

#include "flatbuffers/flatbuffers.h"

namespace monocle {

struct SetNameRequest;
struct SetNameRequestBuilder;

struct SetNameRequest FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef SetNameRequestBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4
  };
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           verifier.EndTable();
  }
};

struct SetNameRequestBuilder {
  typedef SetNameRequest Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(SetNameRequest::VT_NAME, name);
  }
  explicit SetNameRequestBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<SetNameRequest> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<SetNameRequest>(end);
    return o;
  }
};

inline flatbuffers::Offset<SetNameRequest> CreateSetNameRequest(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> name = 0) {
  SetNameRequestBuilder builder_(_fbb);
  builder_.add_name(name);
  return builder_.Finish();
}

inline flatbuffers::Offset<SetNameRequest> CreateSetNameRequestDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  return monocle::CreateSetNameRequest(
      _fbb,
      name__);
}

}  // namespace monocle

#endif  // FLATBUFFERS_GENERATED_SETNAMEREQUEST_MONOCLE_H_
