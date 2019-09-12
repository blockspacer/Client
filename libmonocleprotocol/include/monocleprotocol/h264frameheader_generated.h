// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_H264FRAMEHEADER_MONOCLE_H_
#define FLATBUFFERS_GENERATED_H264FRAMEHEADER_MONOCLE_H_

#include "flatbuffers/flatbuffers.h"

namespace monocle {

struct H264FrameHeader;

struct H264FrameHeader FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TOKEN = 4,
    VT_PLAYREQUESTINDEX = 6,
    VT_CODECINDEX = 8,
    VT_MARKER = 10,
    VT_TIMESTAMP = 12,
    VT_SEQUENCENUM = 14,
    VT_PROGRESS = 16,
    VT_SIGNATURE = 18,
    VT_OFFSETS = 20
  };
  uint64_t token() const {
    return GetField<uint64_t>(VT_TOKEN, 0);
  }
  uint64_t playrequestindex() const {
    return GetField<uint64_t>(VT_PLAYREQUESTINDEX, 0);
  }
  uint64_t codecindex() const {
    return GetField<uint64_t>(VT_CODECINDEX, 0);
  }
  bool marker() const {
    return GetField<uint8_t>(VT_MARKER, 0) != 0;
  }
  uint64_t timestamp() const {
    return GetField<uint64_t>(VT_TIMESTAMP, 0);
  }
  int64_t sequencenum() const {
    return GetField<int64_t>(VT_SEQUENCENUM, 0);
  }
  float progress() const {
    return GetField<float>(VT_PROGRESS, 0.0f);
  }
  const flatbuffers::Vector<uint8_t> *signature() const {
    return GetPointer<const flatbuffers::Vector<uint8_t> *>(VT_SIGNATURE);
  }
  const flatbuffers::Vector<uint32_t> *offsets() const {
    return GetPointer<const flatbuffers::Vector<uint32_t> *>(VT_OFFSETS);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_TOKEN) &&
           VerifyField<uint64_t>(verifier, VT_PLAYREQUESTINDEX) &&
           VerifyField<uint64_t>(verifier, VT_CODECINDEX) &&
           VerifyField<uint8_t>(verifier, VT_MARKER) &&
           VerifyField<uint64_t>(verifier, VT_TIMESTAMP) &&
           VerifyField<int64_t>(verifier, VT_SEQUENCENUM) &&
           VerifyField<float>(verifier, VT_PROGRESS) &&
           VerifyOffset(verifier, VT_SIGNATURE) &&
           verifier.VerifyVector(signature()) &&
           VerifyOffset(verifier, VT_OFFSETS) &&
           verifier.VerifyVector(offsets()) &&
           verifier.EndTable();
  }
};

struct H264FrameHeaderBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_token(uint64_t token) {
    fbb_.AddElement<uint64_t>(H264FrameHeader::VT_TOKEN, token, 0);
  }
  void add_playrequestindex(uint64_t playrequestindex) {
    fbb_.AddElement<uint64_t>(H264FrameHeader::VT_PLAYREQUESTINDEX, playrequestindex, 0);
  }
  void add_codecindex(uint64_t codecindex) {
    fbb_.AddElement<uint64_t>(H264FrameHeader::VT_CODECINDEX, codecindex, 0);
  }
  void add_marker(bool marker) {
    fbb_.AddElement<uint8_t>(H264FrameHeader::VT_MARKER, static_cast<uint8_t>(marker), 0);
  }
  void add_timestamp(uint64_t timestamp) {
    fbb_.AddElement<uint64_t>(H264FrameHeader::VT_TIMESTAMP, timestamp, 0);
  }
  void add_sequencenum(int64_t sequencenum) {
    fbb_.AddElement<int64_t>(H264FrameHeader::VT_SEQUENCENUM, sequencenum, 0);
  }
  void add_progress(float progress) {
    fbb_.AddElement<float>(H264FrameHeader::VT_PROGRESS, progress, 0.0f);
  }
  void add_signature(flatbuffers::Offset<flatbuffers::Vector<uint8_t>> signature) {
    fbb_.AddOffset(H264FrameHeader::VT_SIGNATURE, signature);
  }
  void add_offsets(flatbuffers::Offset<flatbuffers::Vector<uint32_t>> offsets) {
    fbb_.AddOffset(H264FrameHeader::VT_OFFSETS, offsets);
  }
  explicit H264FrameHeaderBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  H264FrameHeaderBuilder &operator=(const H264FrameHeaderBuilder &);
  flatbuffers::Offset<H264FrameHeader> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<H264FrameHeader>(end);
    return o;
  }
};

inline flatbuffers::Offset<H264FrameHeader> CreateH264FrameHeader(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t token = 0,
    uint64_t playrequestindex = 0,
    uint64_t codecindex = 0,
    bool marker = false,
    uint64_t timestamp = 0,
    int64_t sequencenum = 0,
    float progress = 0.0f,
    flatbuffers::Offset<flatbuffers::Vector<uint8_t>> signature = 0,
    flatbuffers::Offset<flatbuffers::Vector<uint32_t>> offsets = 0) {
  H264FrameHeaderBuilder builder_(_fbb);
  builder_.add_sequencenum(sequencenum);
  builder_.add_timestamp(timestamp);
  builder_.add_codecindex(codecindex);
  builder_.add_playrequestindex(playrequestindex);
  builder_.add_token(token);
  builder_.add_offsets(offsets);
  builder_.add_signature(signature);
  builder_.add_progress(progress);
  builder_.add_marker(marker);
  return builder_.Finish();
}

inline flatbuffers::Offset<H264FrameHeader> CreateH264FrameHeaderDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t token = 0,
    uint64_t playrequestindex = 0,
    uint64_t codecindex = 0,
    bool marker = false,
    uint64_t timestamp = 0,
    int64_t sequencenum = 0,
    float progress = 0.0f,
    const std::vector<uint8_t> *signature = nullptr,
    const std::vector<uint32_t> *offsets = nullptr) {
  auto signature__ = signature ? _fbb.CreateVector<uint8_t>(*signature) : 0;
  auto offsets__ = offsets ? _fbb.CreateVector<uint32_t>(*offsets) : 0;
  return monocle::CreateH264FrameHeader(
      _fbb,
      token,
      playrequestindex,
      codecindex,
      marker,
      timestamp,
      sequencenum,
      progress,
      signature__,
      offsets__);
}

}  // namespace monocle

#endif  // FLATBUFFERS_GENERATED_H264FRAMEHEADER_MONOCLE_H_