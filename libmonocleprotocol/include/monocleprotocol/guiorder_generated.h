// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_GUIORDER_MONOCLE_H_
#define FLATBUFFERS_GENERATED_GUIORDER_MONOCLE_H_

#include "flatbuffers/flatbuffers.h"

namespace monocle {

struct GuiOrder;
struct GuiOrderBuilder;

struct GuiOrder FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef GuiOrderBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TOKEN = 4,
    VT_ORDER = 6
  };
  uint64_t token() const {
    return GetField<uint64_t>(VT_TOKEN, 0);
  }
  uint64_t order() const {
    return GetField<uint64_t>(VT_ORDER, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_TOKEN) &&
           VerifyField<uint64_t>(verifier, VT_ORDER) &&
           verifier.EndTable();
  }
};

struct GuiOrderBuilder {
  typedef GuiOrder Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_token(uint64_t token) {
    fbb_.AddElement<uint64_t>(GuiOrder::VT_TOKEN, token, 0);
  }
  void add_order(uint64_t order) {
    fbb_.AddElement<uint64_t>(GuiOrder::VT_ORDER, order, 0);
  }
  explicit GuiOrderBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<GuiOrder> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<GuiOrder>(end);
    return o;
  }
};

inline flatbuffers::Offset<GuiOrder> CreateGuiOrder(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t token = 0,
    uint64_t order = 0) {
  GuiOrderBuilder builder_(_fbb);
  builder_.add_order(order);
  builder_.add_token(token);
  return builder_.Finish();
}

}  // namespace monocle

#endif  // FLATBUFFERS_GENERATED_GUIORDER_MONOCLE_H_
