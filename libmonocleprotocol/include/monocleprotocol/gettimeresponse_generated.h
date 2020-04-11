// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_GETTIMERESPONSE_MONOCLE_H_
#define FLATBUFFERS_GENERATED_GETTIMERESPONSE_MONOCLE_H_

#include "flatbuffers/flatbuffers.h"

namespace monocle {

struct GetTimeResponse;
struct GetTimeResponseBuilder;

struct GetTimeResponse FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef GetTimeResponseBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_UTCTIME = 4
  };
  uint64_t utctime() const {
    return GetField<uint64_t>(VT_UTCTIME, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_UTCTIME) &&
           verifier.EndTable();
  }
};

struct GetTimeResponseBuilder {
  typedef GetTimeResponse Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_utctime(uint64_t utctime) {
    fbb_.AddElement<uint64_t>(GetTimeResponse::VT_UTCTIME, utctime, 0);
  }
  explicit GetTimeResponseBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<GetTimeResponse> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<GetTimeResponse>(end);
    return o;
  }
};

inline flatbuffers::Offset<GetTimeResponse> CreateGetTimeResponse(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t utctime = 0) {
  GetTimeResponseBuilder builder_(_fbb);
  builder_.add_utctime(utctime);
  return builder_.Finish();
}

}  // namespace monocle

#endif  // FLATBUFFERS_GENERATED_GETTIMERESPONSE_MONOCLE_H_
