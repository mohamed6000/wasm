"use strict";

let allocated = null;
let full_window_canvas = false;
let canvas = null;
let ctx = null;


function context2d_init(canvas_id) {
    canvas = document.getElementById(canvas_id);
    ctx = canvas.getContext("2d");
    if (ctx == null) {
        throw new Error("Could not create 2D context");
    }
}

function context2d_clear_render_target(r, g, b, a) {
    ctx.fillStyle = "rgba(" + (r*255) + "," + (g*255) + "," + (b*255) + "," + a + ")";
    ctx.fillRect(0, 0, canvas.width, canvas.height);
}

function context2d_draw_quad(x0, y0, x1, y1, r, g, b, a) {
    ctx.fillStyle = "rgba(" + (r*255) + "," + (g*255) + "," + (b*255) + "," + a + ")";
    ctx.fillRect(x0, y0, x1-x0, y1-y0);
}


function wasm_canvas_get_width() {
    return canvas.width;
}

function wasm_canvas_get_height() {
    return canvas.height;
}

function wasm_canvas_get_size(result_ptr) {
    new Float32Array(allocated.buffer, result_ptr, 2).set([canvas.width, canvas.height]);
}

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
    wasm_canvas_get_width,
    wasm_canvas_get_height,
    wasm_canvas_get_size,
    context2d_clear_render_target,
    context2d_draw_quad,
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
    const wasm = obj.instance;
    allocated = wasm.exports.memory;
    const heap_base = wasm.exports.__heap_base.value;
    console.log("The heap starts at address: ", heap_base);

    // let screen_width  = document.documentElement.clientWidth;
    // let screen_height = document.documentElement.clientHeight;
    // console.log("Screen ", screen_width, "x", screen_height);

    // window.addEventListener("load", canvas_resize, false);
    window.addEventListener("resize", canvas_resize, false);


    context2d_init("game-canvas");


    obj.instance.exports.wasm_entry_point();


    // Main loop.
    if (wasm.exports.process_one_frame) {
        let last_time = undefined;

        function loop(timestamp) {
            if (last_time == undefined) {
                last_time = timestamp;
            }

            const dt = (timestamp - last_time) * 0.001;
            last_time = timestamp;

            if (!wasm.exports.process_one_frame(dt)) {
                // @Todo: cleanup...
                return;
            }

            window.requestAnimationFrame(loop);
        }

        // Kick-start the main loop.
        window.requestAnimationFrame(loop);
    }

    // @Todo: cleanup...
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