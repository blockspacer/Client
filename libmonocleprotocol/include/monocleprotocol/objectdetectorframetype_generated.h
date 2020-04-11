// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_OBJECTDETECTORFRAMETYPE_MONOCLE_H_
#define FLATBUFFERS_GENERATED_OBJECTDETECTORFRAMETYPE_MONOCLE_H_

#include "flatbuffers/flatbuffers.h"

namespace monocle {

enum class ObjectDetectorFrameType : uint16_t {
  OBJECT_DETECTION = 1,
  OBJECT_RESET_MARKER = 2,
  MIN = OBJECT_DETECTION,
  MAX = OBJECT_RESET_MARKER
};

inline const ObjectDetectorFrameType (&EnumValuesObjectDetectorFrameType())[2] {
  static const ObjectDetectorFrameType values[] = {
    ObjectDetectorFrameType::OBJECT_DETECTION,
    ObjectDetectorFrameType::OBJECT_RESET_MARKER
  };
  return values;
}

inline const char * const *EnumNamesObjectDetectorFrameType() {
  static const char * const names[3] = {
    "OBJECT_DETECTION",
    "OBJECT_RESET_MARKER",
    nullptr
  };
  return names;
}

inline const char *EnumNameObjectDetectorFrameType(ObjectDetectorFrameType e) {
  if (flatbuffers::IsOutRange(e, ObjectDetectorFrameType::OBJECT_DETECTION, ObjectDetectorFrameType::OBJECT_RESET_MARKER)) return "";
  const size_t index = static_cast<size_t>(e) - static_cast<size_t>(ObjectDetectorFrameType::OBJECT_DETECTION);
  return EnumNamesObjectDetectorFrameType()[index];
}

}  // namespace monocle

#endif  // FLATBUFFERS_GENERATED_OBJECTDETECTORFRAMETYPE_MONOCLE_H_
