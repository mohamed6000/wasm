'use strict';

let allocated = null;

function wasm_write_string_count(s, count, to_standard_error) {
    const u8 = js_string_from_cstring(s, count);

    if (to_standard_error) {
        console.error(u8);
    } else {
        console.log(u8);
    }
}

const imports = {
    env: {
        wasm_write_string_count,
    }
};

(async () => {
    const wasm = WebAssembly.instantiateStreaming(fetch("main.wasm"), imports).then((obj) => {
            allocated = obj.instance.exports.memory;
            obj.instance.exports.wasm_entry_point();
        }).catch((err) => {
            console.error("Failed to load wasm file: ", err);
        });
})();


const text_decoder = new TextDecoder();
function js_string_from_cstring(pointer, length) {
    const u8 = new Uint8Array(allocated.buffer);
    const bytes = u8.subarray(Number(pointer), Number(pointer) + Number(length));
    return text_decoder.decode(bytes);
}