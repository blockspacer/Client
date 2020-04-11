// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_CHANGEGROUPREQUEST_MONOCLE_H_
#define FLATBUFFERS_GENERATED_CHANGEGROUPREQUEST_MONOCLE_H_

#include "flatbuffers/flatbuffers.h"

namespace monocle {

struct ChangeGroupRequest;
struct ChangeGroupRequestBuilder;

struct ChangeGroupRequest FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef ChangeGroupRequestBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TOKEN = 4,
    VT_NAME = 6,
    VT_MANAGEUSERS = 8,
    VT_MANAGERECORDINGS = 10,
    VT_ALLRECORDINGS = 12,
    VT_RECORDINGS = 14,
    VT_MANAGEMAPS = 16,
    VT_MANAGEDEVICE = 18
  };
  uint64_t token() const {
    return GetField<uint64_t>(VT_TOKEN, 0);
  }
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  bool manageusers() const {
    return GetField<uint8_t>(VT_MANAGEUSERS, 0) != 0;
  }
  bool managerecordings() const {
    return GetField<uint8_t>(VT_MANAGERECORDINGS, 0) != 0;
  }
  bool allrecordings() const {
    return GetField<uint8_t>(VT_ALLRECORDINGS, 0) != 0;
  }
  const flatbuffers::Vector<uint64_t> *recordings() const {
    return GetPointer<const flatbuffers::Vector<uint64_t> *>(VT_RECORDINGS);
  }
  bool managemaps() const {
    return GetField<uint8_t>(VT_MANAGEMAPS, 0) != 0;
  }
  bool managedevice() const {
    return GetField<uint8_t>(VT_MANAGEDEVICE, 0) != 0;
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_TOKEN) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyField<uint8_t>(verifier, VT_MANAGEUSERS) &&
           VerifyField<uint8_t>(verifier, VT_MANAGERECORDINGS) &&
           VerifyField<uint8_t>(verifier, VT_ALLRECORDINGS) &&
           VerifyOffset(verifier, VT_RECORDINGS) &&
           verifier.VerifyVector(recordings()) &&
           VerifyField<uint8_t>(verifier, VT_MANAGEMAPS) &&
           VerifyField<uint8_t>(verifier, VT_MANAGEDEVICE) &&
           verifier.EndTable();
  }
};

struct ChangeGroupRequestBuilder {
  typedef ChangeGroupRequest Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_token(uint64_t token) {
    fbb_.AddElement<uint64_t>(ChangeGroupRequest::VT_TOKEN, token, 0);
  }
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(ChangeGroupRequest::VT_NAME, name);
  }
  void add_manageusers(bool manageusers) {
    fbb_.AddElement<uint8_t>(ChangeGroupRequest::VT_MANAGEUSERS, static_cast<uint8_t>(manageusers), 0);
  }
  void add_managerecordings(bool managerecordings) {
    fbb_.AddElement<uint8_t>(ChangeGroupRequest::VT_MANAGERECORDINGS, static_cast<uint8_t>(managerecordings), 0);
  }
  void add_allrecordings(bool allrecordings) {
    fbb_.AddElement<uint8_t>(ChangeGroupRequest::VT_ALLRECORDINGS, static_cast<uint8_t>(allrecordings), 0);
  }
  void add_recordings(flatbuffers::Offset<flatbuffers::Vector<uint64_t>> recordings) {
    fbb_.AddOffset(ChangeGroupRequest::VT_RECORDINGS, recordings);
  }
  void add_managemaps(bool managemaps) {
    fbb_.AddElement<uint8_t>(ChangeGroupRequest::VT_MANAGEMAPS, static_cast<uint8_t>(managemaps), 0);
  }
  void add_managedevice(bool managedevice) {
    fbb_.AddElement<uint8_t>(ChangeGroupRequest::VT_MANAGEDEVICE, static_cast<uint8_t>(managedevice), 0);
  }
  explicit ChangeGroupRequestBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<ChangeGroupRequest> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<ChangeGroupRequest>(end);
    return o;
  }
};

inline flatbuffers::Offset<ChangeGroupRequest> CreateChangeGroupRequest(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t token = 0,
    flatbuffers::Offset<flatbuffers::String> name = 0,
    bool manageusers = false,
    bool managerecordings = false,
    bool allrecordings = false,
    flatbuffers::Offset<flatbuffers::Vector<uint64_t>> recordings = 0,
    bool managemaps = false,
    bool managedevice = false) {
  ChangeGroupRequestBuilder builder_(_fbb);
  builder_.add_token(token);
  builder_.add_recordings(recordings);
  builder_.add_name(name);
  builder_.add_managedevice(managedevice);
  builder_.add_managemaps(managemaps);
  builder_.add_allrecordings(allrecordings);
  builder_.add_managerecordings(managerecordings);
  builder_.add_manageusers(manageusers);
  return builder_.Finish();
}

inline flatbuffers::Offset<ChangeGroupRequest> CreateChangeGroupRequestDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t token = 0,
    const char *name = nullptr,
    bool manageusers = false,
    bool managerecordings = false,
    bool allrecordings = false,
    const std::vector<uint64_t> *recordings = nullptr,
    bool managemaps = false,
    bool managedevice = false) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  auto recordings__ = recordings ? _fbb.CreateVector<uint64_t>(*recordings) : 0;
  return monocle::CreateChangeGroupRequest(
      _fbb,
      token,
      name__,
      manageusers,
      managerecordings,
      allrecordings,
      recordings__,
      managemaps,
      managedevice);
}

}  // namespace monocle

#endif  // FLATBUFFERS_GENERATED_CHANGEGROUPREQUEST_MONOCLE_H_
