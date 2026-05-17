"use strict";

let allocated = null;
let full_window_canvas = false;


function wasm_write_string_count(s, count, to_standard_error) {
    const u8 = js_string_from_cstring(s, count);
    js_write_to_console_buffer(u8, to_standard_error);
}

function wasm_debug_break() {
    debugger;
}

const js_exported_functions = {
    wasm_write_string_count,
    wasm_debug_break,
};

const imports = {
    env: new Proxy(js_exported_functions, {
        get(target, prop, receiver) {
            if (target.hasOwnProperty(prop)) {
                return target[prop];
            }

            return (...args) => { 
                console.error("Missing function: ", prop, args);
                throw new Error("Missing function: " + prop);
            };
        },
    }),
};

WebAssembly.instantiateStreaming(fetch("main.wasm"), imports).then((obj) => {
    allocated = obj.instance.exports.memory;
    const heap_base = obj.instance.exports.__heap_base.value;
    console.log("The heap starts at address: ", heap_base);

    // let screen_width  = document.documentElement.clientWidth;
    // let screen_height = document.documentElement.clientHeight;
    // console.log("Screen ", screen_width, "x", screen_height);

    // window.addEventListener("load", canvas_resize, false);
    window.addEventListener("resize", canvas_resize, false);


    const canvas = document.getElementById("game-canvas");
    const context_2d = canvas.getContext("2d");
    if (context_2d == null) {
        throw new Error("Could not create 2D context");
    }

    context_2d.fillStyle = "#FFFFFFFF";
    context_2d.fillRect(0, 0, canvas.width, canvas.height);

    let x0 = 0.1 * canvas.width;
    let y0 = 0.1 * canvas.height;
    let w  = canvas.width * 0.8;
    let h  = canvas.height * 0.8;

    context_2d.fillStyle = "#0000FFFF";
    context_2d.fillRect(x0, y0, w, h);


    obj.instance.exports.wasm_entry_point();
}).catch((err) => {
    console.error("Failed to load wasm file: ", err);
});
    
window.addEventListener("load", canvas_resize, false);


function canvas_resize() {
    const canvas = document.getElementById("game-canvas");
    
    if (full_window_canvas) {
        canvas.style.width  = window.innerWidth  + "px";
        canvas.style.height = window.innerHeight + "px";
    } else {
        let ratio = canvas.width / canvas.height;
        let canvas_height = window.innerHeight;
        let canvas_width  = canvas_height * ratio;

        if (canvas_width > window.innerWidth) {
            canvas_width  = window.innerWidth;
            canvas_height = canvas_width / ratio;
        }

        // console.log("Canvas: ", canvas_width, "x", canvas_height, "ratio: ", ratio);

        canvas.style.width  = canvas_width  + "px";
        canvas.style.height = canvas_height + "px";
    }
}



const text_decoder = new TextDecoder();
function js_string_from_cstring(pointer, length) {
    const u8 = new Uint8Array(allocated.buffer);
    const bytes = u8.subarray(Number(pointer), Number(pointer) + Number(length));
    return text_decoder.decode(bytes);
}


let console_buffer = "";
let console_buffer_is_standard_error;
let console_timeout;
const FLUSH_BUFFER_MS = 3;

function js_write_to_console_buffer(s, to_standard_error) {
    if (console_buffer && console_buffer_is_standard_error != to_standard_error) {
        flush_buffer();
    }

    console_buffer_is_standard_error = to_standard_error;
    const lines = s.split("\n");
    for (let i = 0; i < lines.length - 1; i++) {
        console_buffer += lines[i];
        flush_buffer();
    }

    console_buffer += lines[lines.length - 1];

    clearTimeout(console_timeout);
    if (console_buffer) {
        console_timeout = setTimeout(() => {
            flush_buffer();
        }, FLUSH_BUFFER_MS);
    }

    function flush_buffer() {
        if (!console_buffer) return;

        if (console_buffer_is_standard_error) {
            console.error(console_buffer);
        } else {
            console.log(console_buffer);
        }

        console_buffer = "";
    }
}