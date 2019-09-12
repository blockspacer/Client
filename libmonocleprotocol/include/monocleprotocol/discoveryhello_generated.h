// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_DISCOVERYHELLO_MONOCLE_H_
#define FLATBUFFERS_GENERATED_DISCOVERYHELLO_MONOCLE_H_

#include "flatbuffers/flatbuffers.h"

namespace monocle {

struct DiscoveryHello;

struct DiscoveryHello FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_ADDRESSES = 4,
    VT_SCOPES = 6
  };
  const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *addresses() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *>(VT_ADDRESSES);
  }
  const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *scopes() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *>(VT_SCOPES);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_ADDRESSES) &&
           verifier.VerifyVector(addresses()) &&
           verifier.VerifyVectorOfStrings(addresses()) &&
           VerifyOffset(verifier, VT_SCOPES) &&
           verifier.VerifyVector(scopes()) &&
           verifier.VerifyVectorOfStrings(scopes()) &&
           verifier.EndTable();
  }
};

struct DiscoveryHelloBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_addresses(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> addresses) {
    fbb_.AddOffset(DiscoveryHello::VT_ADDRESSES, addresses);
  }
  void add_scopes(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> scopes) {
    fbb_.AddOffset(DiscoveryHello::VT_SCOPES, scopes);
  }
  explicit DiscoveryHelloBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  DiscoveryHelloBuilder &operator=(const DiscoveryHelloBuilder &);
  flatbuffers::Offset<DiscoveryHello> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<DiscoveryHello>(end);
    return o;
  }
};

inline flatbuffers::Offset<DiscoveryHello> CreateDiscoveryHello(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> addresses = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> scopes = 0) {
  DiscoveryHelloBuilder builder_(_fbb);
  builder_.add_scopes(scopes);
  builder_.add_addresses(addresses);
  return builder_.Finish();
}

inline flatbuffers::Offset<DiscoveryHello> CreateDiscoveryHelloDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<flatbuffers::Offset<flatbuffers::String>> *addresses = nullptr,
    const std::vector<flatbuffers::Offset<flatbuffers::String>> *scopes = nullptr) {
  auto addresses__ = addresses ? _fbb.CreateVector<flatbuffers::Offset<flatbuffers::String>>(*addresses) : 0;
  auto scopes__ = scopes ? _fbb.CreateVector<flatbuffers::Offset<flatbuffers::String>>(*scopes) : 0;
  return monocle::CreateDiscoveryHello(
      _fbb,
      addresses__,
      scopes__);
}

}  // namespace monocle

#endif  // FLATBUFFERS_GENERATED_DISCOVERYHELLO_MONOCLE_H_