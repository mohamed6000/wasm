"use strict";

let allocated = null;
let full_window_canvas = false;
let canvas = null;
let ctx = null;
let entry_point_function = null;
let wasm_exports = null;
let gl = null;
let webgl_last_error = null;

const webgl_state = {
    programs: [],
    shaders: [],
    buffers: [],
    framebuffers: [],
    counter: 0,
};



function webgl_init(canvas_id) {
    canvas = document.getElementById(canvas_id);
    if (!canvas) {
        const elements = document.getElementsByTagName("canvas");
        if (elements && elements.length) {
            canvas = elements[0];
        }
    }

    if (!canvas) {
        console.error("Failed to query a canvas element");
        return;
    }

    const context_settings = {
        alpha: true,
        antialias: true,
        depth: true,
        stencil: false,
        premultipliedAlpha: true,
        preserveDrawingBuffer: false,
        powerPreference: "default", // "high-performance", "low-power"
        failIfMajorPerformanceCaveat: false,
    };
    gl = canvas.getContext("webgl", context_settings) || canvas.getContext("experimental-webgl", context_settings);

    if (!gl) {
        console.error("Failed to init WebGL");
    }

    console.log("[WebGL] Initialized WebGL.");
    console.log("[WebGL] API Version:", gl.getParameter(0x1F02));
    console.log("[WebGL] GLSL Version:", gl.getParameter(gl.SHADING_LANGUAGE_VERSION));
    console.log("[WebGL] Drawing buffer size", gl.drawingBufferWidth, "x", gl.drawingBufferHeight);
    console.log("[WebGL] Drawing buffer color space:", gl.drawingBufferColorSpace);
    console.log(gl.getContextAttributes());
    console.log(gl.getSupportedExtensions());
}

function webglIsExtensionSupported(name_pointer, name_count) {
    let u8 = js_string_from_cstring(name_pointer, name_count);
    let extensions = gl.getSupportedExtensions();
    return extensions.indexOf(u8) !== -1;
}

function js_record_last_error(error_code) {
    webgl_last_error || (webgl_last_error = error_code);
}

function webgl_get_new_id(table) {
    for (var ret = webgl_state.counter++, i = table.length; i < ret; ++i) {
        table[i] = null;
    }
    return ret;
}

function webglGetError() {
    let e = webgl_last_error;
    js_record_last_error(0);
    if (e) return e;

    return gl.getError();
}

function webglGetWebGLVersion(major_pointer, minor_pointer) {
    let version = gl.getParameter(0x1F02);
    let memory_view = new Uint32Array(allocated.buffer);

    if (version.indexOf("WebGL 2.0") !== -1) {
        memory_view[major_pointer >> 2] = 2;
        memory_view[minor_pointer >> 2] = 0;
        return;
    }

    memory_view[major_pointer >> 2] = 1;
    memory_view[minor_pointer >> 2] = 0;
}

function webglGetESVersion(major_pointer, minor_pointer) {
    let version = gl.getParameter(0x1F02);
    let memory_view = new Uint32Array(allocated.buffer);

    if (version.indexOf("OpenGL ES 3.0") !== -1) {
        memory_view[major_pointer >> 2] = 3;
        memory_view[minor_pointer >> 2] = 0;
        return;
    }

    memory_view[major_pointer >> 2] = 2;
    memory_view[minor_pointer >> 2] = 0;
}

function webglDrawingBufferWidth() {
    return gl.drawingBufferWidth;
}

function webglDrawingBufferHeight() {
    return gl.drawingBufferHeight;
}

function webglClearColor(r, g, b, a) {
    gl.clearColor(r, g, b, a);
}

function webglClear(clear_flag) {
    gl.clear(clear_flag);
}

function webglActiveTexture(tex) {
    gl.activeTexture(tex);
}

function webglAttachShader(program, shader) {
    gl.attachShader(webgl_state.programs[program], webgl_state.shaders[shader]);
}

function webglClearDepth(depth) {
    gl.clearDepth(depth);
}

function webglClearStencil(s) {
    gl.clearStencil(s);
}

function webglColorMask(r, g, b, a) {
    gl.colorMask(!!r, !!g, !!b, !!a);
}

function webglCompileShader(shader) {
    gl.compileShader(webgl_state.shaders[shader]);
}

function webglCreateBuffer() {
    let buffer = gl.createBuffer();
    if (!buffer) {
        js_record_last_error(1282);
        return 0;
    }

    let id = webgl_get_new_id(webgl_state.buffers);
    buffer.name = id;
    webgl_state.buffers[id] = buffer;
    return id;
}

function webglCreateFramebuffer() {
    let buffer = gl.createFramebuffer();
    let id = webgl_get_new_id(webgl_state.framebuffers);
    buffer.name = id;
    webgl_state.framebuffers[id] = buffer;
    return id;
}



function context2d_init(canvas_id) {
    canvas = document.getElementById(canvas_id);
    if (!canvas) {
        const elements = document.getElementsByTagName("canvas");
        if (elements && elements.length) {
            canvas = elements[0];
        }
    }

    if (!canvas) {
        console.error("Failed to query a canvas element");
        return;
    }

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

function wasm_entry_point_set(entry) {
    entry_point_function = wasm_exports.__indirect_function_table.get(entry);
}

function wasm_write_string_count(s, count, to_standard_error) {
    const u8 = js_string_from_cstring(s, count);
    js_write_to_console_buffer(u8, to_standard_error);
}

function wasm_debug_break() {
    debugger;
}

const js_exported_functions = {
    wasm_entry_point_set,
    wasm_write_string_count,
    wasm_debug_break,
    wasm_canvas_get_width,
    wasm_canvas_get_height,
    wasm_canvas_get_size,
    
    context2d_clear_render_target,
    context2d_draw_quad,

    webglIsExtensionSupported,
    webglGetError,
    webglGetWebGLVersion,
    webglGetESVersion,
    webglDrawingBufferWidth,
    webglDrawingBufferHeight,
    webglClearColor,
    webglClear,
    webglActiveTexture,
    webglAttachShader,
    webglClearDepth,
    webglClearStencil,
    webglColorMask,
    webglCompileShader,
    webglCreateBuffer,
    webglCreateFramebuffer,
};

const imports = {
    env: new Proxy(js_exported_functions, {
        get(target, prop, receiver) {
            if (target.hasOwnProperty(prop)) {
                return target[prop];
            }

            return (...args) => { 
                console.error("Missing function: ", prop, args, "Did you forget to add it to the imports?");
                throw new Error("Missing function: " + prop);
            };
        },
    }),
};

WebAssembly.instantiateStreaming(fetch("main.wasm"), imports).then((obj) => {
    const wasm = obj.instance;
    wasm_exports = wasm.exports;
    allocated = wasm.exports.memory;
    const heap_base = wasm.exports.__heap_base.value;
    console.log("The heap starts at address: ", heap_base);

    // let screen_width  = document.documentElement.clientWidth;
    // let screen_height = document.documentElement.clientHeight;
    // console.log("Screen ", screen_width, "x", screen_height);

    // window.addEventListener("load", canvas_resize, false);
    window.addEventListener("resize", canvas_resize, false);


    // context2d_init("game-canvas");
    webgl_init();
    
    if (canvas) {
        canvas.addEventListener("contextmenu", (e) => {
            e.preventDefault();
        }, false);
        canvas.addEventListener("keydown", (e) => {
            e.preventDefault();
        }, false);
        canvas.addEventListener("mousedown", (e) => {
            e.target.focus();
        }, false);
    }


    if (wasm.exports._start) {
        wasm.exports._start();
    }


    // Main loop.
    if (entry_point_function) {
        let last_time = undefined;
        let dt        = undefined;

        function next_frame(timestamp) {
            dt = (timestamp - last_time) * 0.001;
            last_time = timestamp;

            entry_point_function(dt);
            window.requestAnimationFrame(next_frame);
        }

        // Kick-start the main loop.
        window.requestAnimationFrame((timestamp) => {
            last_time = timestamp;
            window.requestAnimationFrame(next_frame);
        });
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