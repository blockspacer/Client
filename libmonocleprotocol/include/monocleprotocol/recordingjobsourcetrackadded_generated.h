// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_RECORDINGJOBSOURCETRACKADDED_MONOCLE_H_
#define FLATBUFFERS_GENERATED_RECORDINGJOBSOURCETRACKADDED_MONOCLE_H_

#include "flatbuffers/flatbuffers.h"

#include "recordingjobstate_generated.h"

namespace monocle {

struct RecordingJobSourceTrackAdded;

struct RecordingJobSourceTrackAdded FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_RECORDINGTOKEN = 4,
    VT_RECORDINGJOBTOKEN = 6,
    VT_RECORDINGJOBSOURCETOKEN = 8,
    VT_RECORDINGJOBSOURCETRACKTOKEN = 10,
    VT_RECORDINGTRACKID = 12,
    VT_PARAMETERS = 14,
    VT_STATE = 16,
    VT_ERROR = 18,
    VT_ACTIVEPARAMETERS = 20
  };
  uint64_t recordingtoken() const {
    return GetField<uint64_t>(VT_RECORDINGTOKEN, 0);
  }
  uint64_t recordingjobtoken() const {
    return GetField<uint64_t>(VT_RECORDINGJOBTOKEN, 0);
  }
  uint64_t recordingjobsourcetoken() const {
    return GetField<uint64_t>(VT_RECORDINGJOBSOURCETOKEN, 0);
  }
  uint64_t recordingjobsourcetracktoken() const {
    return GetField<uint64_t>(VT_RECORDINGJOBSOURCETRACKTOKEN, 0);
  }
  uint32_t recordingtrackid() const {
    return GetField<uint32_t>(VT_RECORDINGTRACKID, 0);
  }
  const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *parameters() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *>(VT_PARAMETERS);
  }
  monocle::RecordingJobState state() const {
    return static_cast<monocle::RecordingJobState>(GetField<int8_t>(VT_STATE, 0));
  }
  const flatbuffers::String *error() const {
    return GetPointer<const flatbuffers::String *>(VT_ERROR);
  }
  const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *activeparameters() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *>(VT_ACTIVEPARAMETERS);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_RECORDINGTOKEN) &&
           VerifyField<uint64_t>(verifier, VT_RECORDINGJOBTOKEN) &&
           VerifyField<uint64_t>(verifier, VT_RECORDINGJOBSOURCETOKEN) &&
           VerifyField<uint64_t>(verifier, VT_RECORDINGJOBSOURCETRACKTOKEN) &&
           VerifyField<uint32_t>(verifier, VT_RECORDINGTRACKID) &&
           VerifyOffset(verifier, VT_PARAMETERS) &&
           verifier.VerifyVector(parameters()) &&
           verifier.VerifyVectorOfStrings(parameters()) &&
           VerifyField<int8_t>(verifier, VT_STATE) &&
           VerifyOffset(verifier, VT_ERROR) &&
           verifier.VerifyString(error()) &&
           VerifyOffset(verifier, VT_ACTIVEPARAMETERS) &&
           verifier.VerifyVector(activeparameters()) &&
           verifier.VerifyVectorOfStrings(activeparameters()) &&
           verifier.EndTable();
  }
};

struct RecordingJobSourceTrackAddedBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_recordingtoken(uint64_t recordingtoken) {
    fbb_.AddElement<uint64_t>(RecordingJobSourceTrackAdded::VT_RECORDINGTOKEN, recordingtoken, 0);
  }
  void add_recordingjobtoken(uint64_t recordingjobtoken) {
    fbb_.AddElement<uint64_t>(RecordingJobSourceTrackAdded::VT_RECORDINGJOBTOKEN, recordingjobtoken, 0);
  }
  void add_recordingjobsourcetoken(uint64_t recordingjobsourcetoken) {
    fbb_.AddElement<uint64_t>(RecordingJobSourceTrackAdded::VT_RECORDINGJOBSOURCETOKEN, recordingjobsourcetoken, 0);
  }
  void add_recordingjobsourcetracktoken(uint64_t recordingjobsourcetracktoken) {
    fbb_.AddElement<uint64_t>(RecordingJobSourceTrackAdded::VT_RECORDINGJOBSOURCETRACKTOKEN, recordingjobsourcetracktoken, 0);
  }
  void add_recordingtrackid(uint32_t recordingtrackid) {
    fbb_.AddElement<uint32_t>(RecordingJobSourceTrackAdded::VT_RECORDINGTRACKID, recordingtrackid, 0);
  }
  void add_parameters(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> parameters) {
    fbb_.AddOffset(RecordingJobSourceTrackAdded::VT_PARAMETERS, parameters);
  }
  void add_state(monocle::RecordingJobState state) {
    fbb_.AddElement<int8_t>(RecordingJobSourceTrackAdded::VT_STATE, static_cast<int8_t>(state), 0);
  }
  void add_error(flatbuffers::Offset<flatbuffers::String> error) {
    fbb_.AddOffset(RecordingJobSourceTrackAdded::VT_ERROR, error);
  }
  void add_activeparameters(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> activeparameters) {
    fbb_.AddOffset(RecordingJobSourceTrackAdded::VT_ACTIVEPARAMETERS, activeparameters);
  }
  explicit RecordingJobSourceTrackAddedBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  RecordingJobSourceTrackAddedBuilder &operator=(const RecordingJobSourceTrackAddedBuilder &);
  flatbuffers::Offset<RecordingJobSourceTrackAdded> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<RecordingJobSourceTrackAdded>(end);
    return o;
  }
};

inline flatbuffers::Offset<RecordingJobSourceTrackAdded> CreateRecordingJobSourceTrackAdded(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t recordingtoken = 0,
    uint64_t recordingjobtoken = 0,
    uint64_t recordingjobsourcetoken = 0,
    uint64_t recordingjobsourcetracktoken = 0,
    uint32_t recordingtrackid = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> parameters = 0,
    monocle::RecordingJobState state = monocle::RecordingJobState::Idle,
    flatbuffers::Offset<flatbuffers::String> error = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> activeparameters = 0) {
  RecordingJobSourceTrackAddedBuilder builder_(_fbb);
  builder_.add_recordingjobsourcetracktoken(recordingjobsourcetracktoken);
  builder_.add_recordingjobsourcetoken(recordingjobsourcetoken);
  builder_.add_recordingjobtoken(recordingjobtoken);
  builder_.add_recordingtoken(recordingtoken);
  builder_.add_activeparameters(activeparameters);
  builder_.add_error(error);
  builder_.add_parameters(parameters);
  builder_.add_recordingtrackid(recordingtrackid);
  builder_.add_state(state);
  return builder_.Finish();
}

inline flatbuffers::Offset<RecordingJobSourceTrackAdded> CreateRecordingJobSourceTrackAddedDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t recordingtoken = 0,
    uint64_t recordingjobtoken = 0,
    uint64_t recordingjobsourcetoken = 0,
    uint64_t recordingjobsourcetracktoken = 0,
    uint32_t recordingtrackid = 0,
    const std::vector<flatbuffers::Offset<flatbuffers::String>> *parameters = nullptr,
    monocle::RecordingJobState state = monocle::RecordingJobState::Idle,
    const char *error = nullptr,
    const std::vector<flatbuffers::Offset<flatbuffers::String>> *activeparameters = nullptr) {
  auto parameters__ = parameters ? _fbb.CreateVector<flatbuffers::Offset<flatbuffers::String>>(*parameters) : 0;
  auto error__ = error ? _fbb.CreateString(error) : 0;
  auto activeparameters__ = activeparameters ? _fbb.CreateVector<flatbuffers::Offset<flatbuffers::String>>(*activeparameters) : 0;
  return monocle::CreateRecordingJobSourceTrackAdded(
      _fbb,
      recordingtoken,
      recordingjobtoken,
      recordingjobsourcetoken,
      recordingjobsourcetracktoken,
      recordingtrackid,
      parameters__,
      state,
      error__,
      activeparameters__);
}

}  // namespace monocle

#endif  // FLATBUFFERS_GENERATED_RECORDINGJOBSOURCETRACKADDED_MONOCLE_H_
