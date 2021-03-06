// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_RECEIVERCHANGED_MONOCLE_H_
#define FLATBUFFERS_GENERATED_RECEIVERCHANGED_MONOCLE_H_

#include "flatbuffers/flatbuffers.h"

#include "receivermode_generated.h"

namespace monocle {

struct ReceiverChanged;
struct ReceiverChangedBuilder;

struct ReceiverChanged FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef ReceiverChangedBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TOKEN = 4,
    VT_MODE = 6,
    VT_MEDIAURI = 8,
    VT_AUTOCREATED = 10,
    VT_USERNAME = 12,
    VT_PASSWORD = 14,
    VT_PARAMETERS = 16
  };
  uint64_t token() const {
    return GetField<uint64_t>(VT_TOKEN, 0);
  }
  monocle::ReceiverMode mode() const {
    return static_cast<monocle::ReceiverMode>(GetField<int8_t>(VT_MODE, 0));
  }
  const flatbuffers::String *mediauri() const {
    return GetPointer<const flatbuffers::String *>(VT_MEDIAURI);
  }
  bool autocreated() const {
    return GetField<uint8_t>(VT_AUTOCREATED, 0) != 0;
  }
  const flatbuffers::String *username() const {
    return GetPointer<const flatbuffers::String *>(VT_USERNAME);
  }
  const flatbuffers::String *password() const {
    return GetPointer<const flatbuffers::String *>(VT_PASSWORD);
  }
  const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *parameters() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *>(VT_PARAMETERS);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_TOKEN) &&
           VerifyField<int8_t>(verifier, VT_MODE) &&
           VerifyOffset(verifier, VT_MEDIAURI) &&
           verifier.VerifyString(mediauri()) &&
           VerifyField<uint8_t>(verifier, VT_AUTOCREATED) &&
           VerifyOffset(verifier, VT_USERNAME) &&
           verifier.VerifyString(username()) &&
           VerifyOffset(verifier, VT_PASSWORD) &&
           verifier.VerifyString(password()) &&
           VerifyOffset(verifier, VT_PARAMETERS) &&
           verifier.VerifyVector(parameters()) &&
           verifier.VerifyVectorOfStrings(parameters()) &&
           verifier.EndTable();
  }
};

struct ReceiverChangedBuilder {
  typedef ReceiverChanged Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_token(uint64_t token) {
    fbb_.AddElement<uint64_t>(ReceiverChanged::VT_TOKEN, token, 0);
  }
  void add_mode(monocle::ReceiverMode mode) {
    fbb_.AddElement<int8_t>(ReceiverChanged::VT_MODE, static_cast<int8_t>(mode), 0);
  }
  void add_mediauri(flatbuffers::Offset<flatbuffers::String> mediauri) {
    fbb_.AddOffset(ReceiverChanged::VT_MEDIAURI, mediauri);
  }
  void add_autocreated(bool autocreated) {
    fbb_.AddElement<uint8_t>(ReceiverChanged::VT_AUTOCREATED, static_cast<uint8_t>(autocreated), 0);
  }
  void add_username(flatbuffers::Offset<flatbuffers::String> username) {
    fbb_.AddOffset(ReceiverChanged::VT_USERNAME, username);
  }
  void add_password(flatbuffers::Offset<flatbuffers::String> password) {
    fbb_.AddOffset(ReceiverChanged::VT_PASSWORD, password);
  }
  void add_parameters(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> parameters) {
    fbb_.AddOffset(ReceiverChanged::VT_PARAMETERS, parameters);
  }
  explicit ReceiverChangedBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<ReceiverChanged> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<ReceiverChanged>(end);
    return o;
  }
};

inline flatbuffers::Offset<ReceiverChanged> CreateReceiverChanged(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t token = 0,
    monocle::ReceiverMode mode = monocle::ReceiverMode::AutoConnect,
    flatbuffers::Offset<flatbuffers::String> mediauri = 0,
    bool autocreated = false,
    flatbuffers::Offset<flatbuffers::String> username = 0,
    flatbuffers::Offset<flatbuffers::String> password = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> parameters = 0) {
  ReceiverChangedBuilder builder_(_fbb);
  builder_.add_token(token);
  builder_.add_parameters(parameters);
  builder_.add_password(password);
  builder_.add_username(username);
  builder_.add_mediauri(mediauri);
  builder_.add_autocreated(autocreated);
  builder_.add_mode(mode);
  return builder_.Finish();
}

inline flatbuffers::Offset<ReceiverChanged> CreateReceiverChangedDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t token = 0,
    monocle::ReceiverMode mode = monocle::ReceiverMode::AutoConnect,
    const char *mediauri = nullptr,
    bool autocreated = false,
    const char *username = nullptr,
    const char *password = nullptr,
    const std::vector<flatbuffers::Offset<flatbuffers::String>> *parameters = nullptr) {
  auto mediauri__ = mediauri ? _fbb.CreateString(mediauri) : 0;
  auto username__ = username ? _fbb.CreateString(username) : 0;
  auto password__ = password ? _fbb.CreateString(password) : 0;
  auto parameters__ = parameters ? _fbb.CreateVector<flatbuffers::Offset<flatbuffers::String>>(*parameters) : 0;
  return monocle::CreateReceiverChanged(
      _fbb,
      token,
      mode,
      mediauri__,
      autocreated,
      username__,
      password__,
      parameters__);
}

}  // namespace monocle

#endif  // FLATBUFFERS_GENERATED_RECEIVERCHANGED_MONOCLE_H_
