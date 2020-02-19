// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_SUBSCRIBERESPONSE_MONOCLE_H_
#define FLATBUFFERS_GENERATED_SUBSCRIBERESPONSE_MONOCLE_H_

#include "flatbuffers/flatbuffers.h"

#include "codec_generated.h"
#include "codecindex_generated.h"
#include "file_generated.h"
#include "filemonitorstate_generated.h"
#include "filestate_generated.h"
#include "group_generated.h"
#include "index_generated.h"
#include "logmessage_generated.h"
#include "map_generated.h"
#include "mountpoint_generated.h"
#include "onvifuser_generated.h"
#include "onvifuserlevel_generated.h"
#include "receiver_generated.h"
#include "receivermode_generated.h"
#include "receiverstate_generated.h"
#include "recording_generated.h"
#include "recordingjob_generated.h"
#include "recordingjobsource_generated.h"
#include "recordingjobsourcetrack_generated.h"
#include "recordingjobsourcetype_generated.h"
#include "recordingjobstate_generated.h"
#include "recordingtrack_generated.h"
#include "severity_generated.h"
#include "token_generated.h"
#include "tracktype_generated.h"
#include "user_generated.h"
#include "version_generated.h"

namespace monocle {

struct SubscribeResponse;

struct SubscribeResponse FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4,
    VT_PUBLICKEY = 6,
    VT_ARCHITECTURE = 8,
    VT_OPERATINGSYSTEM = 10,
    VT_COMPILER = 12,
    VT_DATABASEPATH = 14,
    VT_VERSION = 16,
    VT_IDENTIFIER = 18,
    VT_ENVIRONMENTVARIABLES = 20,
    VT_COMMANDLINEVARIABLES = 22,
    VT_ONVIFUSERS = 24,
    VT_GROUPS = 26,
    VT_USERS = 28,
    VT_FILES = 30,
    VT_RECEIVERS = 32,
    VT_RECORDINGS = 34,
    VT_SERVERLOGMESSAGES = 36,
    VT_MAXRECORDINGS = 38,
    VT_MAPS = 40,
    VT_MOUNTPOINTS = 42,
    VT_LATITUDE = 44,
    VT_LONGITUDE = 46,
    VT_NUMCUDADEVICES = 48,
    VT_NUMCLDEVICES = 50,
    VT_MAXOBJECTDETECTORS = 52
  };
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  const flatbuffers::String *publickey() const {
    return GetPointer<const flatbuffers::String *>(VT_PUBLICKEY);
  }
  const flatbuffers::String *architecture() const {
    return GetPointer<const flatbuffers::String *>(VT_ARCHITECTURE);
  }
  int32_t operatingsystem() const {
    return GetField<int32_t>(VT_OPERATINGSYSTEM, 0);
  }
  const flatbuffers::String *compiler() const {
    return GetPointer<const flatbuffers::String *>(VT_COMPILER);
  }
  const flatbuffers::String *databasepath() const {
    return GetPointer<const flatbuffers::String *>(VT_DATABASEPATH);
  }
  const monocle::VERSION *version() const {
    return GetStruct<const monocle::VERSION *>(VT_VERSION);
  }
  uint64_t identifier() const {
    return GetField<uint64_t>(VT_IDENTIFIER, 0);
  }
  const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *environmentvariables() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *>(VT_ENVIRONMENTVARIABLES);
  }
  const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *commandlinevariables() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>> *>(VT_COMMANDLINEVARIABLES);
  }
  const flatbuffers::Vector<flatbuffers::Offset<monocle::ONVIFUser>> *onvifusers() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<monocle::ONVIFUser>> *>(VT_ONVIFUSERS);
  }
  const flatbuffers::Vector<flatbuffers::Offset<monocle::Group>> *groups() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<monocle::Group>> *>(VT_GROUPS);
  }
  const flatbuffers::Vector<flatbuffers::Offset<monocle::User>> *users() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<monocle::User>> *>(VT_USERS);
  }
  const flatbuffers::Vector<flatbuffers::Offset<monocle::File>> *files() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<monocle::File>> *>(VT_FILES);
  }
  const flatbuffers::Vector<flatbuffers::Offset<monocle::Receiver>> *receivers() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<monocle::Receiver>> *>(VT_RECEIVERS);
  }
  const flatbuffers::Vector<flatbuffers::Offset<monocle::Recording>> *recordings() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<monocle::Recording>> *>(VT_RECORDINGS);
  }
  const flatbuffers::Vector<flatbuffers::Offset<monocle::LogMessage>> *serverlogmessages() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<monocle::LogMessage>> *>(VT_SERVERLOGMESSAGES);
  }
  uint32_t maxrecordings() const {
    return GetField<uint32_t>(VT_MAXRECORDINGS, 0);
  }
  const flatbuffers::Vector<flatbuffers::Offset<monocle::Map>> *maps() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<monocle::Map>> *>(VT_MAPS);
  }
  const flatbuffers::Vector<flatbuffers::Offset<monocle::MountPoint>> *mountpoints() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<monocle::MountPoint>> *>(VT_MOUNTPOINTS);
  }
  const flatbuffers::String *latitude() const {
    return GetPointer<const flatbuffers::String *>(VT_LATITUDE);
  }
  const flatbuffers::String *longitude() const {
    return GetPointer<const flatbuffers::String *>(VT_LONGITUDE);
  }
  uint32_t numcudadevices() const {
    return GetField<uint32_t>(VT_NUMCUDADEVICES, 0);
  }
  uint32_t numcldevices() const {
    return GetField<uint32_t>(VT_NUMCLDEVICES, 0);
  }
  uint32_t maxobjectdetectors() const {
    return GetField<uint32_t>(VT_MAXOBJECTDETECTORS, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           VerifyOffset(verifier, VT_PUBLICKEY) &&
           verifier.VerifyString(publickey()) &&
           VerifyOffset(verifier, VT_ARCHITECTURE) &&
           verifier.VerifyString(architecture()) &&
           VerifyField<int32_t>(verifier, VT_OPERATINGSYSTEM) &&
           VerifyOffset(verifier, VT_COMPILER) &&
           verifier.VerifyString(compiler()) &&
           VerifyOffset(verifier, VT_DATABASEPATH) &&
           verifier.VerifyString(databasepath()) &&
           VerifyField<monocle::VERSION>(verifier, VT_VERSION) &&
           VerifyField<uint64_t>(verifier, VT_IDENTIFIER) &&
           VerifyOffset(verifier, VT_ENVIRONMENTVARIABLES) &&
           verifier.VerifyVector(environmentvariables()) &&
           verifier.VerifyVectorOfStrings(environmentvariables()) &&
           VerifyOffset(verifier, VT_COMMANDLINEVARIABLES) &&
           verifier.VerifyVector(commandlinevariables()) &&
           verifier.VerifyVectorOfStrings(commandlinevariables()) &&
           VerifyOffset(verifier, VT_ONVIFUSERS) &&
           verifier.VerifyVector(onvifusers()) &&
           verifier.VerifyVectorOfTables(onvifusers()) &&
           VerifyOffset(verifier, VT_GROUPS) &&
           verifier.VerifyVector(groups()) &&
           verifier.VerifyVectorOfTables(groups()) &&
           VerifyOffset(verifier, VT_USERS) &&
           verifier.VerifyVector(users()) &&
           verifier.VerifyVectorOfTables(users()) &&
           VerifyOffset(verifier, VT_FILES) &&
           verifier.VerifyVector(files()) &&
           verifier.VerifyVectorOfTables(files()) &&
           VerifyOffset(verifier, VT_RECEIVERS) &&
           verifier.VerifyVector(receivers()) &&
           verifier.VerifyVectorOfTables(receivers()) &&
           VerifyOffset(verifier, VT_RECORDINGS) &&
           verifier.VerifyVector(recordings()) &&
           verifier.VerifyVectorOfTables(recordings()) &&
           VerifyOffset(verifier, VT_SERVERLOGMESSAGES) &&
           verifier.VerifyVector(serverlogmessages()) &&
           verifier.VerifyVectorOfTables(serverlogmessages()) &&
           VerifyField<uint32_t>(verifier, VT_MAXRECORDINGS) &&
           VerifyOffset(verifier, VT_MAPS) &&
           verifier.VerifyVector(maps()) &&
           verifier.VerifyVectorOfTables(maps()) &&
           VerifyOffset(verifier, VT_MOUNTPOINTS) &&
           verifier.VerifyVector(mountpoints()) &&
           verifier.VerifyVectorOfTables(mountpoints()) &&
           VerifyOffset(verifier, VT_LATITUDE) &&
           verifier.VerifyString(latitude()) &&
           VerifyOffset(verifier, VT_LONGITUDE) &&
           verifier.VerifyString(longitude()) &&
           VerifyField<uint32_t>(verifier, VT_NUMCUDADEVICES) &&
           VerifyField<uint32_t>(verifier, VT_NUMCLDEVICES) &&
           VerifyField<uint32_t>(verifier, VT_MAXOBJECTDETECTORS) &&
           verifier.EndTable();
  }
};

struct SubscribeResponseBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(SubscribeResponse::VT_NAME, name);
  }
  void add_publickey(flatbuffers::Offset<flatbuffers::String> publickey) {
    fbb_.AddOffset(SubscribeResponse::VT_PUBLICKEY, publickey);
  }
  void add_architecture(flatbuffers::Offset<flatbuffers::String> architecture) {
    fbb_.AddOffset(SubscribeResponse::VT_ARCHITECTURE, architecture);
  }
  void add_operatingsystem(int32_t operatingsystem) {
    fbb_.AddElement<int32_t>(SubscribeResponse::VT_OPERATINGSYSTEM, operatingsystem, 0);
  }
  void add_compiler(flatbuffers::Offset<flatbuffers::String> compiler) {
    fbb_.AddOffset(SubscribeResponse::VT_COMPILER, compiler);
  }
  void add_databasepath(flatbuffers::Offset<flatbuffers::String> databasepath) {
    fbb_.AddOffset(SubscribeResponse::VT_DATABASEPATH, databasepath);
  }
  void add_version(const monocle::VERSION *version) {
    fbb_.AddStruct(SubscribeResponse::VT_VERSION, version);
  }
  void add_identifier(uint64_t identifier) {
    fbb_.AddElement<uint64_t>(SubscribeResponse::VT_IDENTIFIER, identifier, 0);
  }
  void add_environmentvariables(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> environmentvariables) {
    fbb_.AddOffset(SubscribeResponse::VT_ENVIRONMENTVARIABLES, environmentvariables);
  }
  void add_commandlinevariables(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> commandlinevariables) {
    fbb_.AddOffset(SubscribeResponse::VT_COMMANDLINEVARIABLES, commandlinevariables);
  }
  void add_onvifusers(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<monocle::ONVIFUser>>> onvifusers) {
    fbb_.AddOffset(SubscribeResponse::VT_ONVIFUSERS, onvifusers);
  }
  void add_groups(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<monocle::Group>>> groups) {
    fbb_.AddOffset(SubscribeResponse::VT_GROUPS, groups);
  }
  void add_users(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<monocle::User>>> users) {
    fbb_.AddOffset(SubscribeResponse::VT_USERS, users);
  }
  void add_files(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<monocle::File>>> files) {
    fbb_.AddOffset(SubscribeResponse::VT_FILES, files);
  }
  void add_receivers(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<monocle::Receiver>>> receivers) {
    fbb_.AddOffset(SubscribeResponse::VT_RECEIVERS, receivers);
  }
  void add_recordings(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<monocle::Recording>>> recordings) {
    fbb_.AddOffset(SubscribeResponse::VT_RECORDINGS, recordings);
  }
  void add_serverlogmessages(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<monocle::LogMessage>>> serverlogmessages) {
    fbb_.AddOffset(SubscribeResponse::VT_SERVERLOGMESSAGES, serverlogmessages);
  }
  void add_maxrecordings(uint32_t maxrecordings) {
    fbb_.AddElement<uint32_t>(SubscribeResponse::VT_MAXRECORDINGS, maxrecordings, 0);
  }
  void add_maps(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<monocle::Map>>> maps) {
    fbb_.AddOffset(SubscribeResponse::VT_MAPS, maps);
  }
  void add_mountpoints(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<monocle::MountPoint>>> mountpoints) {
    fbb_.AddOffset(SubscribeResponse::VT_MOUNTPOINTS, mountpoints);
  }
  void add_latitude(flatbuffers::Offset<flatbuffers::String> latitude) {
    fbb_.AddOffset(SubscribeResponse::VT_LATITUDE, latitude);
  }
  void add_longitude(flatbuffers::Offset<flatbuffers::String> longitude) {
    fbb_.AddOffset(SubscribeResponse::VT_LONGITUDE, longitude);
  }
  void add_numcudadevices(uint32_t numcudadevices) {
    fbb_.AddElement<uint32_t>(SubscribeResponse::VT_NUMCUDADEVICES, numcudadevices, 0);
  }
  void add_numcldevices(uint32_t numcldevices) {
    fbb_.AddElement<uint32_t>(SubscribeResponse::VT_NUMCLDEVICES, numcldevices, 0);
  }
  void add_maxobjectdetectors(uint32_t maxobjectdetectors) {
    fbb_.AddElement<uint32_t>(SubscribeResponse::VT_MAXOBJECTDETECTORS, maxobjectdetectors, 0);
  }
  explicit SubscribeResponseBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  SubscribeResponseBuilder &operator=(const SubscribeResponseBuilder &);
  flatbuffers::Offset<SubscribeResponse> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<SubscribeResponse>(end);
    return o;
  }
};

inline flatbuffers::Offset<SubscribeResponse> CreateSubscribeResponse(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> name = 0,
    flatbuffers::Offset<flatbuffers::String> publickey = 0,
    flatbuffers::Offset<flatbuffers::String> architecture = 0,
    int32_t operatingsystem = 0,
    flatbuffers::Offset<flatbuffers::String> compiler = 0,
    flatbuffers::Offset<flatbuffers::String> databasepath = 0,
    const monocle::VERSION *version = 0,
    uint64_t identifier = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> environmentvariables = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> commandlinevariables = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<monocle::ONVIFUser>>> onvifusers = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<monocle::Group>>> groups = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<monocle::User>>> users = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<monocle::File>>> files = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<monocle::Receiver>>> receivers = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<monocle::Recording>>> recordings = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<monocle::LogMessage>>> serverlogmessages = 0,
    uint32_t maxrecordings = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<monocle::Map>>> maps = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<monocle::MountPoint>>> mountpoints = 0,
    flatbuffers::Offset<flatbuffers::String> latitude = 0,
    flatbuffers::Offset<flatbuffers::String> longitude = 0,
    uint32_t numcudadevices = 0,
    uint32_t numcldevices = 0,
    uint32_t maxobjectdetectors = 0) {
  SubscribeResponseBuilder builder_(_fbb);
  builder_.add_identifier(identifier);
  builder_.add_maxobjectdetectors(maxobjectdetectors);
  builder_.add_numcldevices(numcldevices);
  builder_.add_numcudadevices(numcudadevices);
  builder_.add_longitude(longitude);
  builder_.add_latitude(latitude);
  builder_.add_mountpoints(mountpoints);
  builder_.add_maps(maps);
  builder_.add_maxrecordings(maxrecordings);
  builder_.add_serverlogmessages(serverlogmessages);
  builder_.add_recordings(recordings);
  builder_.add_receivers(receivers);
  builder_.add_files(files);
  builder_.add_users(users);
  builder_.add_groups(groups);
  builder_.add_onvifusers(onvifusers);
  builder_.add_commandlinevariables(commandlinevariables);
  builder_.add_environmentvariables(environmentvariables);
  builder_.add_version(version);
  builder_.add_databasepath(databasepath);
  builder_.add_compiler(compiler);
  builder_.add_operatingsystem(operatingsystem);
  builder_.add_architecture(architecture);
  builder_.add_publickey(publickey);
  builder_.add_name(name);
  return builder_.Finish();
}

inline flatbuffers::Offset<SubscribeResponse> CreateSubscribeResponseDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr,
    const char *publickey = nullptr,
    const char *architecture = nullptr,
    int32_t operatingsystem = 0,
    const char *compiler = nullptr,
    const char *databasepath = nullptr,
    const monocle::VERSION *version = 0,
    uint64_t identifier = 0,
    const std::vector<flatbuffers::Offset<flatbuffers::String>> *environmentvariables = nullptr,
    const std::vector<flatbuffers::Offset<flatbuffers::String>> *commandlinevariables = nullptr,
    const std::vector<flatbuffers::Offset<monocle::ONVIFUser>> *onvifusers = nullptr,
    const std::vector<flatbuffers::Offset<monocle::Group>> *groups = nullptr,
    const std::vector<flatbuffers::Offset<monocle::User>> *users = nullptr,
    const std::vector<flatbuffers::Offset<monocle::File>> *files = nullptr,
    const std::vector<flatbuffers::Offset<monocle::Receiver>> *receivers = nullptr,
    const std::vector<flatbuffers::Offset<monocle::Recording>> *recordings = nullptr,
    const std::vector<flatbuffers::Offset<monocle::LogMessage>> *serverlogmessages = nullptr,
    uint32_t maxrecordings = 0,
    const std::vector<flatbuffers::Offset<monocle::Map>> *maps = nullptr,
    const std::vector<flatbuffers::Offset<monocle::MountPoint>> *mountpoints = nullptr,
    const char *latitude = nullptr,
    const char *longitude = nullptr,
    uint32_t numcudadevices = 0,
    uint32_t numcldevices = 0,
    uint32_t maxobjectdetectors = 0) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  auto publickey__ = publickey ? _fbb.CreateString(publickey) : 0;
  auto architecture__ = architecture ? _fbb.CreateString(architecture) : 0;
  auto compiler__ = compiler ? _fbb.CreateString(compiler) : 0;
  auto databasepath__ = databasepath ? _fbb.CreateString(databasepath) : 0;
  auto environmentvariables__ = environmentvariables ? _fbb.CreateVector<flatbuffers::Offset<flatbuffers::String>>(*environmentvariables) : 0;
  auto commandlinevariables__ = commandlinevariables ? _fbb.CreateVector<flatbuffers::Offset<flatbuffers::String>>(*commandlinevariables) : 0;
  auto onvifusers__ = onvifusers ? _fbb.CreateVector<flatbuffers::Offset<monocle::ONVIFUser>>(*onvifusers) : 0;
  auto groups__ = groups ? _fbb.CreateVector<flatbuffers::Offset<monocle::Group>>(*groups) : 0;
  auto users__ = users ? _fbb.CreateVector<flatbuffers::Offset<monocle::User>>(*users) : 0;
  auto files__ = files ? _fbb.CreateVector<flatbuffers::Offset<monocle::File>>(*files) : 0;
  auto receivers__ = receivers ? _fbb.CreateVector<flatbuffers::Offset<monocle::Receiver>>(*receivers) : 0;
  auto recordings__ = recordings ? _fbb.CreateVector<flatbuffers::Offset<monocle::Recording>>(*recordings) : 0;
  auto serverlogmessages__ = serverlogmessages ? _fbb.CreateVector<flatbuffers::Offset<monocle::LogMessage>>(*serverlogmessages) : 0;
  auto maps__ = maps ? _fbb.CreateVector<flatbuffers::Offset<monocle::Map>>(*maps) : 0;
  auto mountpoints__ = mountpoints ? _fbb.CreateVector<flatbuffers::Offset<monocle::MountPoint>>(*mountpoints) : 0;
  auto latitude__ = latitude ? _fbb.CreateString(latitude) : 0;
  auto longitude__ = longitude ? _fbb.CreateString(longitude) : 0;
  return monocle::CreateSubscribeResponse(
      _fbb,
      name__,
      publickey__,
      architecture__,
      operatingsystem,
      compiler__,
      databasepath__,
      version,
      identifier,
      environmentvariables__,
      commandlinevariables__,
      onvifusers__,
      groups__,
      users__,
      files__,
      receivers__,
      recordings__,
      serverlogmessages__,
      maxrecordings,
      maps__,
      mountpoints__,
      latitude__,
      longitude__,
      numcudadevices,
      numcldevices,
      maxobjectdetectors);
}

}  // namespace monocle

#endif  // FLATBUFFERS_GENERATED_SUBSCRIBERESPONSE_MONOCLE_H_
