// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_USERADDED_MONOCLE_H_
#define FLATBUFFERS_GENERATED_USERADDED_MONOCLE_H_

#include "flatbuffers/flatbuffers.h"

namespace monocle {

struct UserAdded;

struct UserAdded FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TOKEN = 4,
    VT_USERNAME = 6,
    VT_DIGEST = 8,
    VT_GROUP = 10
  };
  uint64_t token() const {
    return GetField<uint64_t>(VT_TOKEN, 0);
  }
  const flatbuffers::String *username() const {
    return GetPointer<const flatbuffers::String *>(VT_USERNAME);
  }
  const flatbuffers::String *digest() const {
    return GetPointer<const flatbuffers::String *>(VT_DIGEST);
  }
  uint64_t group() const {
    return GetField<uint64_t>(VT_GROUP, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_TOKEN) &&
           VerifyOffset(verifier, VT_USERNAME) &&
           verifier.VerifyString(username()) &&
           VerifyOffset(verifier, VT_DIGEST) &&
           verifier.VerifyString(digest()) &&
           VerifyField<uint64_t>(verifier, VT_GROUP) &&
           verifier.EndTable();
  }
};

struct UserAddedBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_token(uint64_t token) {
    fbb_.AddElement<uint64_t>(UserAdded::VT_TOKEN, token, 0);
  }
  void add_username(flatbuffers::Offset<flatbuffers::String> username) {
    fbb_.AddOffset(UserAdded::VT_USERNAME, username);
  }
  void add_digest(flatbuffers::Offset<flatbuffers::String> digest) {
    fbb_.AddOffset(UserAdded::VT_DIGEST, digest);
  }
  void add_group(uint64_t group) {
    fbb_.AddElement<uint64_t>(UserAdded::VT_GROUP, group, 0);
  }
  explicit UserAddedBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  UserAddedBuilder &operator=(const UserAddedBuilder &);
  flatbuffers::Offset<UserAdded> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<UserAdded>(end);
    return o;
  }
};

inline flatbuffers::Offset<UserAdded> CreateUserAdded(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t token = 0,
    flatbuffers::Offset<flatbuffers::String> username = 0,
    flatbuffers::Offset<flatbuffers::String> digest = 0,
    uint64_t group = 0) {
  UserAddedBuilder builder_(_fbb);
  builder_.add_group(group);
  builder_.add_token(token);
  builder_.add_digest(digest);
  builder_.add_username(username);
  return builder_.Finish();
}

inline flatbuffers::Offset<UserAdded> CreateUserAddedDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t token = 0,
    const char *username = nullptr,
    const char *digest = nullptr,
    uint64_t group = 0) {
  auto username__ = username ? _fbb.CreateString(username) : 0;
  auto digest__ = digest ? _fbb.CreateString(digest) : 0;
  return monocle::CreateUserAdded(
      _fbb,
      token,
      username__,
      digest__,
      group);
}

}  // namespace monocle

#endif  // FLATBUFFERS_GENERATED_USERADDED_MONOCLE_H_