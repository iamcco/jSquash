CODEC_URL := https://github.com/lvandeve/lodepng/archive/refs/heads/master.zip
CODEC_DIR := node_modules/lodepng
ENVIRONMENT = web,worker

OUT_JS := dec/png_dec.js
OUT_WASM := $(OUT_JS:.js=.wasm)

.PHONY: all clean

all: $(OUT_JS)

# Define dependencies for all variations of build artifacts.
$(filter dec/%,$(OUT_JS)): dec/png_dec.cpp

%.js: $(CODEC_DIR)/lodepng.cpp
	$(CXX) \
		-I $(CODEC_DIR) \
		${CXXFLAGS} \
		${LDFLAGS} \
		--bind \
		-s ENVIRONMENT=$(ENVIRONMENT) \
		-s EXPORT_ES6=1 \
		-s DYNAMIC_EXECUTION=0 \
		-s MODULARIZE=1 \
		-o $@ \
		$+

$(CODEC_DIR):
	mkdir -p $@
	curl -sL $(CODEC_URL) --output ./lodepng.zip
	unzip -j ./lodepng.zip -d $(CODEC_DIR)

clean:
	$(RM) $(OUT_JS) $(OUT_WASM)
