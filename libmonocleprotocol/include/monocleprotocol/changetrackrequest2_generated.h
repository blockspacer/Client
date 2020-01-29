// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_CHANGETRACKREQUEST2_MONOCLE_H_
#define FLATBUFFERS_GENERATED_CHANGETRACKREQUEST2_MONOCLE_H_

#include "flatbuffers/flatbuffers.h"

#include "tracktype_generated.h"

namespace monocle {

struct ChangeTrackRequest2;

struct ChangeTrackRequest2 FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_RECORDINGTOKEN = 4,
    VT_RECORDINGJOBTOKEN = 6,
    VT_DESCRIPTION = 8,
    VT_FIXEDFILES = 10,
    VT_DIGITALSIGNING = 12,
    VT_ENCRYPT = 14,
    VT_FLUSHFREQUENCY = 16,
    VT_FILES = 18,
    VT_MEDIAURI = 20,
    VT_USERNAME = 22,
    VT_PASSWORD = 24,
    VT_RECEIVERPARAMETERS = 26,
    VT_SOURCEPARAMETERS = 28,
    VT_OBJECTDETECTORSOURCEPARAMETERS = 30
  };
  uint64_t recordingtoken() const {
    return GetField<uint64_t>(VT_RECORDINGTOKEN, 0);
  }
  uint64_t recordingjobtoken() const {
    return GetField<uint64_t>(VT_RECORDINGJOBTOKEN, 0);
  }
  const flatbuffers::String *description() const {
    return GetPointer<const flatbuffers::String *>(VT_DESCRIPTION);
  }
  bool fixedfiles() const {
    return GetField<uint8_t>(VT_FIXEDFILES, 0) != 0;
  }
  bool digitalsigning() const {
    return GetField<uint8_t>(VT_DIGITALSIGNING, 0) != 0;
  }
  bool encrypt() const {
    return GetField<uint8_t>(VT_ENCRYPT, 0) != 0;
  }
  uint32_t flushfrequency() const {
    return GetField<uint32_t>(VT_FLUSHFREQUENCY, 0);
  }
  const flatbuffers::Vector<uint64_t> *files() const {
    return GetPointer<const flatbuffers::Vector<uint64_t> *>(VT_FILES);
  }
  const flatbuffers::String *mediauri() const {
    return GetPointer<const flatbuffers::String *>(VT_MEDIAURI);
  }
  const flatbuffers::String *username() const {
    return GetPointer<const flatbuffers::String *>(VT_USERNAME);
  }
  const flatbuffers::String *password() const {
    return GetPointer<const flatbuffers::String *>(VT_PASSWORD);
  }
  const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *receiverparameters() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *>(VT_RECEIVERPARAMETERS);
  }
  const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *sourceparameters() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *>(VT_SOURCEPARAMETERS);
  }
  const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *objectdetectorsourceparameters() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *>(VT_OBJECTDETECTORSOURCEPARAMETERS);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_RECORDINGTOKEN) &&
           VerifyField<uint64_t>(verifier, VT_RECORDINGJOBTOKEN) &&
           VerifyOffset(verifier, VT_DESCRIPTION) &&
           verifier.VerifyString(description()) &&
           VerifyField<uint8_t>(verifier, VT_FIXEDFILES) &&
           VerifyField<uint8_t>(verifier, VT_DIGITALSIGNING) &&
           VerifyField<uint8_t>(verifier, VT_ENCRYPT) &&
           VerifyField<uint32_t>(verifier, VT_FLUSHFREQUENCY) &&
           VerifyOffset(verifier, VT_FILES) &&
           verifier.VerifyVector(files()) &&
           VerifyOffset(verifier, VT_MEDIAURI) &&
           verifier.VerifyString(mediauri()) &&
           VerifyOffset(verifier, VT_USERNAME) &&
           verifier.VerifyString(username()) &&
           VerifyOffset(verifier, VT_PASSWORD) &&
           verifier.VerifyString(password()) &&
           VerifyOffset(verifier, VT_RECEIVERPARAMETERS) &&
           verifier.VerifyVector(receiverparameters()) &&
           verifier.VerifyVectorOfStrings(receiverparameters()) &&
           VerifyOffset(verifier, VT_SOURCEPARAMETERS) &&
           verifier.VerifyVector(sourceparameters()) &&
           verifier.VerifyVectorOfStrings(sourceparameters()) &&
           VerifyOffset(verifier, VT_OBJECTDETECTORSOURCEPARAMETERS) &&
           verifier.VerifyVector(objectdetectorsourceparameters()) &&
           verifier.VerifyVectorOfStrings(objectdetectorsourceparameters()) &&
           verifier.EndTable();
  }
};

struct ChangeTrackRequest2Builder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_recordingtoken(uint64_t recordingtoken) {
    fbb_.AddElement<uint64_t>(ChangeTrackRequest2::VT_RECORDINGTOKEN, recordingtoken, 0);
  }
  void add_recordingjobtoken(uint64_t recordingjobtoken) {
    fbb_.AddElement<uint64_t>(ChangeTrackRequest2::VT_RECORDINGJOBTOKEN, recordingjobtoken, 0);
  }
  void add_description(flatbuffers::Offset<flatbuffers::String> description) {
    fbb_.AddOffset(ChangeTrackRequest2::VT_DESCRIPTION, description);
  }
  void add_fixedfiles(bool fixedfiles) {
    fbb_.AddElement<uint8_t>(ChangeTrackRequest2::VT_FIXEDFILES, static_cast<uint8_t>(fixedfiles), 0);
  }
  void add_digitalsigning(bool digitalsigning) {
    fbb_.AddElement<uint8_t>(ChangeTrackRequest2::VT_DIGITALSIGNING, static_cast<uint8_t>(digitalsigning), 0);
  }
  void add_encrypt(bool encrypt) {
    fbb_.AddElement<uint8_t>(ChangeTrackRequest2::VT_ENCRYPT, static_cast<uint8_t>(encrypt), 0);
  }
  void add_flushfrequency(uint32_t flushfrequency) {
    fbb_.AddElement<uint32_t>(ChangeTrackRequest2::VT_FLUSHFREQUENCY, flushfrequency, 0);
  }
  void add_files(flatbuffers::Offset<flatbuffers::Vector<uint64_t>> files) {
    fbb_.AddOffset(ChangeTrackRequest2::VT_FILES, files);
  }
  void add_mediauri(flatbuffers::Offset<flatbuffers::String> mediauri) {
    fbb_.AddOffset(ChangeTrackRequest2::VT_MEDIAURI, mediauri);
  }
  void add_username(flatbuffers::Offset<flatbuffers::String> username) {
    fbb_.AddOffset(ChangeTrackRequest2::VT_USERNAME, username);
  }
  void add_password(flatbuffers::Offset<flatbuffers::String> password) {
    fbb_.AddOffset(ChangeTrackRequest2::VT_PASSWORD, password);
  }
  void add_receiverparameters(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> receiverparameters) {
    fbb_.AddOffset(ChangeTrackRequest2::VT_RECEIVERPARAMETERS, receiverparameters);
  }
  void add_sourceparameters(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> sourceparameters) {
    fbb_.AddOffset(ChangeTrackRequest2::VT_SOURCEPARAMETERS, sourceparameters);
  }
  void add_objectdetectorsourceparameters(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> objectdetectorsourceparameters) {
    fbb_.AddOffset(ChangeTrackRequest2::VT_OBJECTDETECTORSOURCEPARAMETERS, objectdetectorsourceparameters);
  }
  explicit ChangeTrackRequest2Builder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ChangeTrackRequest2Builder &operator=(const ChangeTrackRequest2Builder &);
  flatbuffers::Offset<ChangeTrackRequest2> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<ChangeTrackRequest2>(end);
    return o;
  }
};

inline flatbuffers::Offset<ChangeTrackRequest2> CreateChangeTrackRequest2(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t recordingtoken = 0,
    uint64_t recordingjobtoken = 0,
    flatbuffers::Offset<flatbuffers::String> description = 0,
    bool fixedfiles = false,
    bool digitalsigning = false,
    bool encrypt = false,
    uint32_t flushfrequency = 0,
    flatbuffers::Offset<flatbuffers::Vector<uint64_t>> files = 0,
    flatbuffers::Offset<flatbuffers::String> mediauri = 0,
    flatbuffers::Offset<flatbuffers::String> username = 0,
    flatbuffers::Offset<flatbuffers::String> password = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> receiverparameters = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> sourceparameters = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> objectdetectorsourceparameters = 0) {
  ChangeTrackRequest2Builder builder_(_fbb);
  builder_.add_recordingjobtoken(recordingjobtoken);
  builder_.add_recordingtoken(recordingtoken);
  builder_.add_objectdetectorsourceparameters(objectdetectorsourceparameters);
  builder_.add_sourceparameters(sourceparameters);
  builder_.add_receiverparameters(receiverparameters);
  builder_.add_password(password);
  builder_.add_username(username);
  builder_.add_mediauri(mediauri);
  builder_.add_files(files);
  builder_.add_flushfrequency(flushfrequency);
  builder_.add_description(description);
  builder_.add_encrypt(encrypt);
  builder_.add_digitalsigning(digitalsigning);
  builder_.add_fixedfiles(fixedfiles);
  return builder_.Finish();
}

inline flatbuffers::Offset<ChangeTrackRequest2> CreateChangeTrackRequest2Direct(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t recordingtoken = 0,
    uint64_t recordingjobtoken = 0,
    const char *description = nullptr,
    bool fixedfiles = false,
    bool digitalsigning = false,
    bool encrypt = false,
    uint32_t flushfrequency = 0,
    const std::vector<uint64_t> *files = nullptr,
    const char *mediauri = nullptr,
    const char *username = nullptr,
    const char *password = nullptr,
    const std::vector<flatbuffers::Offset<flatbuffers::String>> *receiverparameters = nullptr,
    const std::vector<flatbuffers::Offset<flatbuffers::String>> *sourceparameters = nullptr,
    const std::vector<flatbuffers::Offset<flatbuffers::String>> *objectdetectorsourceparameters = nullptr) {
  auto description__ = description ? _fbb.CreateString(description) : 0;
  auto files__ = files ? _fbb.CreateVector<uint64_t>(*files) : 0;
  auto mediauri__ = mediauri ? _fbb.CreateString(mediauri) : 0;
  auto username__ = username ? _fbb.CreateString(username) : 0;
  auto password__ = password ? _fbb.CreateString(password) : 0;
  auto receiverparameters__ = receiverparameters ? _fbb.CreateVector<flatbuffers::Offset<flatbuffers::String>>(*receiverparameters) : 0;
  auto sourceparameters__ = sourceparameters ? _fbb.CreateVector<flatbuffers::Offset<flatbuffers::String>>(*sourceparameters) : 0;
  auto objectdetectorsourceparameters__ = objectdetectorsourceparameters ? _fbb.CreateVector<flatbuffers::Offset<flatbuffers::String>>(*objectdetectorsourceparameters) : 0;
  return monocle::CreateChangeTrackRequest2(
      _fbb,
      recordingtoken,
      recordingjobtoken,
      description__,
      fixedfiles,
      digitalsigning,
      encrypt,
      flushfrequency,
      files__,
      mediauri__,
      username__,
      password__,
      receiverparameters__,
      sourceparameters__,
      objectdetectorsourceparameters__);
}

}  // namespace monocle

#endif  // FLATBUFFERS_GENERATED_CHANGETRACKREQUEST2_MONOCLE_H_
