#include <string>
#include "emscripten/bind.h"
#include "emscripten/val.h"
#include "lodepng.h"

using namespace emscripten;

thread_local const val Uint8ClampedArray = val::global("Uint8ClampedArray");
thread_local const val ImageData = val::global("ImageData");

std::vector<unsigned char> to_vector(std::string const& str)
{
    return std::vector<unsigned char>(str.data(), str.data() + str.length() + 1);
}

val decode(std::string buffer) {
  auto bufferVec = to_vector(buffer);
  std::vector<unsigned char> image; //the raw pixels
  unsigned width, height;

  int error = lodepng::decode(image, width, height, bufferVec, LCT_RGBA, 8);

  if (error) {
    return val(error);
  }

  auto data = Uint8ClampedArray.new_(typed_memory_view(image.size(), &image[0]));
  auto js_result = ImageData.new_(data, width, height);

  return js_result;
}

EMSCRIPTEN_BINDINGS(my_module) {
  function("decode", &decode);
}
