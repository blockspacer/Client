// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_SUBSCRIBEHARDWARESTATSRESPONSE_MONOCLE_H_
#define FLATBUFFERS_GENERATED_SUBSCRIBEHARDWARESTATSRESPONSE_MONOCLE_H_

#include "flatbuffers/flatbuffers.h"

#include "diskstat_generated.h"
#include "hardwarestats_generated.h"

namespace monocle {

struct SubscribeHardwareStatsResponse;

struct SubscribeHardwareStatsResponse FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_CURRENTHARDWARESTATS = 4
  };
  const monocle::HardwareStats *currenthardwarestats() const {
    return GetPointer<const monocle::HardwareStats *>(VT_CURRENTHARDWARESTATS);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_CURRENTHARDWARESTATS) &&
           verifier.VerifyTable(currenthardwarestats()) &&
           verifier.EndTable();
  }
};

struct SubscribeHardwareStatsResponseBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_currenthardwarestats(flatbuffers::Offset<monocle::HardwareStats> currenthardwarestats) {
    fbb_.AddOffset(SubscribeHardwareStatsResponse::VT_CURRENTHARDWARESTATS, currenthardwarestats);
  }
  explicit SubscribeHardwareStatsResponseBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  SubscribeHardwareStatsResponseBuilder &operator=(const SubscribeHardwareStatsResponseBuilder &);
  flatbuffers::Offset<SubscribeHardwareStatsResponse> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<SubscribeHardwareStatsResponse>(end);
    return o;
  }
};

inline flatbuffers::Offset<SubscribeHardwareStatsResponse> CreateSubscribeHardwareStatsResponse(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<monocle::HardwareStats> currenthardwarestats = 0) {
  SubscribeHardwareStatsResponseBuilder builder_(_fbb);
  builder_.add_currenthardwarestats(currenthardwarestats);
  return builder_.Finish();
}

}  // namespace monocle

#endif  // FLATBUFFERS_GENERATED_SUBSCRIBEHARDWARESTATSRESPONSE_MONOCLE_H_