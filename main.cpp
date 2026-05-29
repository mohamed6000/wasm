// #define NB_STRIP_GENERAL_PREFIX
// #include "nb.h"

#include <stdint.h>

#if defined(__wasm__) || defined(__wasm) || defined(__wasm32__) || defined(__wasm32) || defined(__wasm64__)
#define OS_WASM 1
#endif

#if defined(__wasm64__) || defined(__wasm64)
#define ARCH_WASM64 1
#elif defined(__wasm32__) || defined(__wasm32)
#define ARCH_WASM32 1
#endif

#ifndef ARCH_WASM64
#define ARCH_WASM64 0
#endif

#ifndef ARCH_WASM32
#define ARCH_WASM32 0
#endif


extern "C" {

// https://developer.mozilla.org/en-US/docs/Web/API/WebGL_API/Constants

// WebGL constants.

// Clearing buffers
#define WEBGL_DEPTH_BUFFER_BIT   0x00000100
#define WEBGL_STENCIL_BUFFER_BIT 0x00000400
#define WEBGL_COLOR_BUFFER_BIT   0x00004000

// Rendering primitives
#define WEBGL_POINTS          0x0000
#define WEBGL_LINES           0x0001
#define WEBGL_LINE_LOOP       0x0002
#define WEBGL_LINE_STRIP      0x0003
#define WEBGL_TRIANGLES       0x0004
#define WEBGL_TRIANGLE_STRIP  0x0005
#define WEBGL_TRIANGLE_FAN    0x0006

// Blending modes
#define WEBGL_ZERO  0
#define WEBGL_ONE   1
#define WEBGL_SRC_COLOR                0x0300
#define WEBGL_ONE_MINUS_SRC_COLOR      0x0301
#define WEBGL_SRC_ALPHA                0x0302
#define WEBGL_ONE_MINUS_SRC_ALPHA      0x0303
#define WEBGL_DST_ALPHA                0x0304
#define WEBGL_ONE_MINUS_DST_ALPHA      0x0305
#define WEBGL_DST_COLOR                0x0306
#define WEBGL_ONE_MINUS_DST_COLOR      0x0307
#define WEBGL_SRC_ALPHA_SATURATE       0x0308
#define WEBGL_CONSTANT_COLOR           0x8001
#define WEBGL_ONE_MINUS_CONSTANT_COLOR 0x8002
#define WEBGL_CONSTANT_ALPHA           0x8003
#define WEBGL_ONE_MINUS_CONSTANT_ALPHA 0x8004

// Blending equations
#define WEBGL_FUNC_ADD              0x8006
#define WEBGL_FUNC_SUBTRACT         0x800A
#define WEBGL_FUNC_REVERSE_SUBTRACT 0x800B

// Getting GL parameter information
#define WEBGL_BLEND_EQUATION  0x8009
#define WEBGL_BLEND_EQUATION_RGB  0x8009
#define WEBGL_BLEND_EQUATION_ALPHA    0x883D
#define WEBGL_BLEND_DST_RGB   0x80C8
#define WEBGL_BLEND_SRC_RGB   0x80C9
#define WEBGL_BLEND_DST_ALPHA     0x80CA
#define WEBGL_BLEND_SRC_ALPHA     0x80CB
#define WEBGL_BLEND_COLOR     0x8005
#define WEBGL_ARRAY_BUFFER_BINDING    0x8894
#define WEBGL_ELEMENT_ARRAY_BUFFER_BINDING    0x8895
#define WEBGL_LINE_WIDTH  0x0B21
#define WEBGL_ALIASED_POINT_SIZE_RANGE    0x846D
#define WEBGL_ALIASED_LINE_WIDTH_RANGE    0x846E
#define WEBGL_CULL_FACE_MODE  0x0B45
#define WEBGL_FRONT_FACE  0x0B46
#define WEBGL_DEPTH_RANGE     0x0B70
#define WEBGL_DEPTH_WRITEMASK     0x0B72
#define WEBGL_DEPTH_CLEAR_VALUE   0x0B73
#define WEBGL_DEPTH_FUNC  0x0B74
#define WEBGL_STENCIL_CLEAR_VALUE     0x0B91
#define WEBGL_STENCIL_FUNC    0x0B92
#define WEBGL_STENCIL_FAIL    0x0B94
#define WEBGL_STENCIL_PASS_DEPTH_FAIL     0x0B95
#define WEBGL_STENCIL_PASS_DEPTH_PASS     0x0B96
#define WEBGL_STENCIL_REF     0x0B97
#define WEBGL_STENCIL_VALUE_MASK  0x0B93  
#define WEBGL_STENCIL_WRITEMASK   0x0B98  
#define WEBGL_STENCIL_BACK_FUNC   0x8800  
#define WEBGL_STENCIL_BACK_FAIL   0x8801  
#define WEBGL_STENCIL_BACK_PASS_DEPTH_FAIL    0x8802  
#define WEBGL_STENCIL_BACK_PASS_DEPTH_PASS    0x8803  
#define WEBGL_STENCIL_BACK_REF    0x8CA3  
#define WEBGL_STENCIL_BACK_VALUE_MASK     0x8CA4  
#define WEBGL_STENCIL_BACK_WRITEMASK  0x8CA5  
#define WEBGL_VIEWPORT    0x0BA2
#define WEBGL_SCISSOR_BOX     0x0C10
#define WEBGL_COLOR_CLEAR_VALUE   0x0C22  
#define WEBGL_COLOR_WRITEMASK     0x0C23  
#define WEBGL_UNPACK_ALIGNMENT    0x0CF5  
#define WEBGL_PACK_ALIGNMENT  0x0D05  
#define WEBGL_MAX_TEXTURE_SIZE    0x0D33  
#define WEBGL_MAX_VIEWPORT_DIMS   0x0D3A  
#define WEBGL_SUBPIXEL_BITS   0x0D50  
#define WEBGL_RED_BITS    0x0D52  
#define WEBGL_GREEN_BITS  0x0D53  
#define WEBGL_BLUE_BITS   0x0D54  
#define WEBGL_ALPHA_BITS  0x0D55  
#define WEBGL_DEPTH_BITS  0x0D56  
#define WEBGL_STENCIL_BITS    0x0D57  
#define WEBGL_POLYGON_OFFSET_UNITS    0x2A00  
#define WEBGL_POLYGON_OFFSET_FACTOR   0x8038  
#define WEBGL_TEXTURE_BINDING_2D  0x8069  
#define WEBGL_SAMPLE_BUFFERS  0x80A8  
#define WEBGL_SAMPLES     0x80A9  
#define WEBGL_SAMPLE_COVERAGE_VALUE   0x80AA  
#define WEBGL_SAMPLE_COVERAGE_INVERT  0x80AB  
#define WEBGL_COMPRESSED_TEXTURE_FORMATS  0x86A3  
#define WEBGL_VENDOR  0x1F00  
#define WEBGL_RENDERER    0x1F01  
#define WEBGL_VERSION     0x1F02  
#define WEBGL_IMPLEMENTATION_COLOR_READ_TYPE  0x8B9A  
#define WEBGL_IMPLEMENTATION_COLOR_READ_FORMAT    0x8B9B  
#define WEBGL_BROWSER_DEFAULT_WEBGL   0x9244

// Buffers
#define WEBGL_STATIC_DRAW          0x88E4
#define WEBGL_STREAM_DRAW          0x88E0
#define WEBGL_DYNAMIC_DRAW         0x88E8
#define WEBGL_ARRAY_BUFFER         0x8892
#define WEBGL_ELEMENT_ARRAY_BUFFER 0x8893
#define WEBGL_BUFFER_SIZE          0x8764
#define WEBGL_BUFFER_USAGE         0x8765

// Vertex attributes
#define WEBGL_CURRENT_VERTEX_ATTRIB               0x8626
#define WEBGL_VERTEX_ATTRIB_ARRAY_ENABLED         0x8622  
#define WEBGL_VERTEX_ATTRIB_ARRAY_SIZE            0x8623  
#define WEBGL_VERTEX_ATTRIB_ARRAY_STRIDE          0x8624  
#define WEBGL_VERTEX_ATTRIB_ARRAY_TYPE            0x8625  
#define WEBGL_VERTEX_ATTRIB_ARRAY_NORMALIZED      0x886A  
#define WEBGL_VERTEX_ATTRIB_ARRAY_POINTER         0x8645  
#define WEBGL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING  0x889F  

// Culling
#define WEBGL_CULL_FACE      0x0B44
#define WEBGL_FRONT          0x0404
#define WEBGL_BACK           0x0405
#define WEBGL_FRONT_AND_BACK 0x0408

// Enabling and disabling
#define WEBGL_BLEND                    0x0BE2
#define WEBGL_DEPTH_TEST               0x0B71
#define WEBGL_DITHER                   0x0BD0
#define WEBGL_POLYGON_OFFSET_FILL      0x8037
#define WEBGL_SAMPLE_ALPHA_TO_COVERAGE 0x809E
#define WEBGL_SAMPLE_COVERAGE          0x80A0
#define WEBGL_SCISSOR_TEST             0x0C11
#define WEBGL_STENCIL_TEST             0x0B90

// Errors
#define WEBGL_NO_ERROR 0
#define WEBGL_INVALID_ENUM       0x0500
#define WEBGL_INVALID_VALUE      0x0501
#define WEBGL_INVALID_OPERATION  0x0502
#define WEBGL_OUT_OF_MEMORY      0x0505
#define WEBGL_CONTEXT_LOST_WEBGL 0x9242

// Front face directions
#define WEBGL_CW  0x0900
#define WEBGL_CCW 0x0901

// Hints
#define WEBGL_DONT_CARE            0x1100
#define WEBGL_FASTEST              0x1101
#define WEBGL_NICEST               0x1102
#define WEBGL_GENERATE_MIPMAP_HINT 0x8192

// Data types
#define WEBGL_BYTE            0x1400  
#define WEBGL_UNSIGNED_BYTE   0x1401  
#define WEBGL_SHORT           0x1402  
#define WEBGL_UNSIGNED_SHORT  0x1403  
#define WEBGL_INT             0x1404  
#define WEBGL_UNSIGNED_INT    0x1405  
#define WEBGL_FLOAT           0x1406

// Pixel formats
#define WEBGL_DEPTH_COMPONENT 0x1902  
#define WEBGL_ALPHA           0x1906  
#define WEBGL_RGB             0x1907  
#define WEBGL_RGBA            0x1908  
#define WEBGL_LUMINANCE       0x1909  
#define WEBGL_LUMINANCE_ALPHA 0x190A

// Pixel types
#define WEBGL_UNSIGNED_BYTE           0x1401  
#define WEBGL_UNSIGNED_SHORT_4_4_4_4  0x8033  
#define WEBGL_UNSIGNED_SHORT_5_5_5_1  0x8034  
#define WEBGL_UNSIGNED_SHORT_5_6_5    0x8363

// Shaders
#define WEBGL_FRAGMENT_SHADER     0x8B30
#define WEBGL_VERTEX_SHADER   0x8B31
#define WEBGL_COMPILE_STATUS  0x8B81
#define WEBGL_DELETE_STATUS   0x8B80
#define WEBGL_LINK_STATUS     0x8B82
#define WEBGL_VALIDATE_STATUS     0x8B83
#define WEBGL_ATTACHED_SHADERS    0x8B85
#define WEBGL_ACTIVE_ATTRIBUTES   0x8B89
#define WEBGL_ACTIVE_UNIFORMS     0x8B86
#define WEBGL_MAX_VERTEX_ATTRIBS  0x8869
#define WEBGL_MAX_VERTEX_UNIFORM_VECTORS  0x8DFB  
#define WEBGL_MAX_VARYING_VECTORS     0x8DFC  
#define WEBGL_MAX_COMBINED_TEXTURE_IMAGE_UNITS    0x8B4D  
#define WEBGL_MAX_VERTEX_TEXTURE_IMAGE_UNITS  0x8B4C  
#define WEBGL_MAX_TEXTURE_IMAGE_UNITS     0x8872
#define WEBGL_MAX_FRAGMENT_UNIFORM_VECTORS    0x8DFD  
#define WEBGL_SHADER_TYPE     0x8B4F  
#define WEBGL_SHADING_LANGUAGE_VERSION    0x8B8C  
#define WEBGL_CURRENT_PROGRAM     0x8B8D  

// Depth or stencil tests
#define WEBGL_NEVER    0x0200
#define WEBGL_LESS     0x0201
#define WEBGL_EQUAL    0x0202
#define WEBGL_LEQUAL   0x0203
#define WEBGL_GREATER  0x0204
#define WEBGL_NOTEQUAL 0x0205
#define WEBGL_GEQUAL   0x0206
#define WEBGL_ALWAYS   0x0207

// Stencil actions
#define WEBGL_KEEP        0x1E00  
#define WEBGL_REPLACE     0x1E01  
#define WEBGL_INCR        0x1E02  
#define WEBGL_DECR        0x1E03  
#define WEBGL_INVERT      0x150A  
#define WEBGL_INCR_WRAP   0x8507  
#define WEBGL_DECR_WRAP   0x8508

// Textures
#define WEBGL_NEAREST     0x2600  
#define WEBGL_LINEAR  0x2601  
#define WEBGL_NEAREST_MIPMAP_NEAREST  0x2700  
#define WEBGL_LINEAR_MIPMAP_NEAREST   0x2701  
#define WEBGL_NEAREST_MIPMAP_LINEAR   0x2702  
#define WEBGL_LINEAR_MIPMAP_LINEAR    0x2703  
#define WEBGL_TEXTURE_MAG_FILTER  0x2800  
#define WEBGL_TEXTURE_MIN_FILTER  0x2801  
#define WEBGL_TEXTURE_WRAP_S  0x2802  
#define WEBGL_TEXTURE_WRAP_T  0x2803  
#define WEBGL_TEXTURE_2D  0x0DE1  
#define WEBGL_TEXTURE     0x1702  
#define WEBGL_TEXTURE_CUBE_MAP    0x8513  
#define WEBGL_TEXTURE_BINDING_CUBE_MAP    0x8514  
#define WEBGL_TEXTURE_CUBE_MAP_POSITIVE_X     0x8515  
#define WEBGL_TEXTURE_CUBE_MAP_NEGATIVE_X     0x8516  
#define WEBGL_TEXTURE_CUBE_MAP_POSITIVE_Y     0x8517  
#define WEBGL_TEXTURE_CUBE_MAP_NEGATIVE_Y     0x8518  
#define WEBGL_TEXTURE_CUBE_MAP_POSITIVE_Z     0x8519  
#define WEBGL_TEXTURE_CUBE_MAP_NEGATIVE_Z     0x851A  
#define WEBGL_MAX_CUBE_MAP_TEXTURE_SIZE   0x851C  

/* TEXTURE0 - 31   0x84C0 - 0x84DF     A texture unit. */
#define WEBGL_TEXTURE0 0x84C0

#define WEBGL_ACTIVE_TEXTURE  0x84E0
#define WEBGL_REPEAT          0x2901  
#define WEBGL_CLAMP_TO_EDGE   0x812F  
#define WEBGL_MIRRORED_REPEAT 0x8370

// Uniform types
#define WEBGL_FLOAT_VEC2      0x8B50  
#define WEBGL_FLOAT_VEC3      0x8B51  
#define WEBGL_FLOAT_VEC4      0x8B52  
#define WEBGL_INT_VEC2        0x8B53  
#define WEBGL_INT_VEC3        0x8B54  
#define WEBGL_INT_VEC4        0x8B55  
#define WEBGL_BOOL            0x8B56  
#define WEBGL_BOOL_VEC2       0x8B57  
#define WEBGL_BOOL_VEC3       0x8B58  
#define WEBGL_BOOL_VEC4       0x8B59  
#define WEBGL_FLOAT_MAT2      0x8B5A  
#define WEBGL_FLOAT_MAT3      0x8B5B  
#define WEBGL_FLOAT_MAT4      0x8B5C  
#define WEBGL_SAMPLER_2D      0x8B5E  
#define WEBGL_SAMPLER_CUBE    0x8B60

// Shader precision-specified types
#define WEBGL_LOW_FLOAT    0x8DF0  
#define WEBGL_MEDIUM_FLOAT 0x8DF1  
#define WEBGL_HIGH_FLOAT   0x8DF2  
#define WEBGL_LOW_INT      0x8DF3  
#define WEBGL_MEDIUM_INT   0x8DF4  
#define WEBGL_HIGH_INT     0x8DF5

// Framebuffers and renderbuffers
#define WEBGL_FRAMEBUFFER     0x8D40  
#define WEBGL_RENDERBUFFER    0x8D41  
#define WEBGL_RGBA4   0x8056  
#define WEBGL_RGB5_A1     0x8057  
#define WEBGL_RGB565  0x8D62  
#define WEBGL_DEPTH_COMPONENT16   0x81A5  
#define WEBGL_STENCIL_INDEX8  0x8D48  
#define WEBGL_DEPTH_STENCIL   0x84F9  
#define WEBGL_RENDERBUFFER_WIDTH  0x8D42  
#define WEBGL_RENDERBUFFER_HEIGHT     0x8D43  
#define WEBGL_RENDERBUFFER_INTERNAL_FORMAT    0x8D44  
#define WEBGL_RENDERBUFFER_RED_SIZE   0x8D50  
#define WEBGL_RENDERBUFFER_GREEN_SIZE     0x8D51  
#define WEBGL_RENDERBUFFER_BLUE_SIZE  0x8D52  
#define WEBGL_RENDERBUFFER_ALPHA_SIZE     0x8D53  
#define WEBGL_RENDERBUFFER_DEPTH_SIZE     0x8D54  
#define WEBGL_RENDERBUFFER_STENCIL_SIZE   0x8D55  
#define WEBGL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE  0x8CD0  
#define WEBGL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME  0x8CD1  
#define WEBGL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL    0x8CD2  
#define WEBGL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE    0x8CD3  
#define WEBGL_COLOR_ATTACHMENT0   0x8CE0  
#define WEBGL_DEPTH_ATTACHMENT    0x8D00  
#define WEBGL_STENCIL_ATTACHMENT  0x8D20  
#define WEBGL_DEPTH_STENCIL_ATTACHMENT    0x821A  
#define WEBGL_NONE    0   
#define WEBGL_FRAMEBUFFER_COMPLETE    0x8CD5  
#define WEBGL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT   0x8CD6  
#define WEBGL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT   0x8CD7  
#define WEBGL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS   0x8CD9  
#define WEBGL_FRAMEBUFFER_UNSUPPORTED     0x8CDD  
#define WEBGL_FRAMEBUFFER_BINDING     0x8CA6  
#define WEBGL_RENDERBUFFER_BINDING    0x8CA7  
#define WEBGL_MAX_RENDERBUFFER_SIZE   0x84E8  
#define WEBGL_INVALID_FRAMEBUFFER_OPERATION   0x0506

// Pixel storage modes
#define WEBGL_UNPACK_FLIP_Y_WEBGL     0x9240  
#define WEBGL_UNPACK_PREMULTIPLY_ALPHA_WEBGL  0x9241  
#define WEBGL_UNPACK_COLORSPACE_CONVERSION_WEBGL  0x9243


// WebGL extensions constants.

// ANGLE_instanced_arrays
#define WEBGL_VERTEX_ATTRIB_ARRAY_DIVISOR_ANGLE   0x88FE

// WEBGL_debug_renderer_info
#define WEBGL_UNMASKED_VENDOR_WEBGL   0x9245
#define WEBGL_UNMASKED_RENDERER_WEBGL 0x9246

// EXT_texture_filter_anisotropic
#define WEBGL_MAX_TEXTURE_MAX_ANISOTROPY_EXT  0x84FF
#define WEBGL_TEXTURE_MAX_ANISOTROPY_EXT      0x84FE  

// WEBGL_compressed_texture_s3tc
#define WEBGL_COMPRESSED_RGB_S3TC_DXT1_EXT    0x83F0
#define WEBGL_COMPRESSED_RGBA_S3TC_DXT1_EXT   0x83F1
#define WEBGL_COMPRESSED_RGBA_S3TC_DXT3_EXT   0x83F2
#define WEBGL_COMPRESSED_RGBA_S3TC_DXT5_EXT   0x83F3

// WEBGL_compressed_texture_etc
#define WEBGL_COMPRESSED_R11_EAC  0x9270
#define WEBGL_COMPRESSED_SIGNED_R11_EAC   0x9271
#define WEBGL_COMPRESSED_RG11_EAC     0x9272
#define WEBGL_COMPRESSED_SIGNED_RG11_EAC  0x9273
#define WEBGL_COMPRESSED_RGB8_ETC2    0x9274
#define WEBGL_COMPRESSED_RGBA8_ETC2_EAC   0x9275
#define WEBGL_COMPRESSED_SRGB8_ETC2   0x9276
#define WEBGL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC    0x9277
#define WEBGL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2    0x9278
#define WEBGL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2   0x9279

// WEBGL_compressed_texture_pvrtc
#define WEBGL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG     0x8C00
#define WEBGL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG    0x8C02
#define WEBGL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG     0x8C01
#define WEBGL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG    0x8C03

// WEBGL_compressed_texture_etc1
#define WEBGL_COMPRESSED_RGB_ETC1_WEBGL   0x8D64

// WEBGL_depth_texture
#define WEBGL_UNSIGNED_INT_24_8_WEBGL     0x84FA

// OES_texture_half_float
#define WEBGL_HALF_FLOAT_OES  0x8D61

// WEBGL_color_buffer_float
#define WEBGL_RGBA32F_EXT     0x8814
#define WEBGL_RGB32F_EXT  0x8815
#define WEBGL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE_EXT   0x8211  
#define WEBGL_UNSIGNED_NORMALIZED_EXT     0x8C17  

// EXT_blend_minmax
#define WEBGL_MIN_EXT     0x8007
#define WEBGL_MAX_EXT     0x8008

// EXT_sRGB
#define WEBGL_SRGB_EXT    0x8C40
#define WEBGL_SRGB_ALPHA_EXT  0x8C42
#define WEBGL_SRGB8_ALPHA8_EXT    0x8C43
#define WEBGL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT   0x8210

// OES_standard_derivatives
#define FRAGMENT_SHADER_DERIVATIVE_HINT_OES 0x8B8B

// WEBGL_draw_buffers
#define WEBGL_COLOR_ATTACHMENT0_WEBGL     0x8CE0
#define WEBGL_COLOR_ATTACHMENT1_WEBGL     0x8CE1
#define WEBGL_COLOR_ATTACHMENT2_WEBGL     0x8CE2
#define WEBGL_COLOR_ATTACHMENT3_WEBGL     0x8CE3
#define WEBGL_COLOR_ATTACHMENT4_WEBGL     0x8CE4
#define WEBGL_COLOR_ATTACHMENT5_WEBGL     0x8CE5
#define WEBGL_COLOR_ATTACHMENT6_WEBGL     0x8CE6
#define WEBGL_COLOR_ATTACHMENT7_WEBGL     0x8CE7
#define WEBGL_COLOR_ATTACHMENT8_WEBGL     0x8CE8
#define WEBGL_COLOR_ATTACHMENT9_WEBGL     0x8CE9
#define WEBGL_COLOR_ATTACHMENT10_WEBGL    0x8CEA
#define WEBGL_COLOR_ATTACHMENT11_WEBGL    0x8CEB
#define WEBGL_COLOR_ATTACHMENT12_WEBGL    0x8CEC
#define WEBGL_COLOR_ATTACHMENT13_WEBGL    0x8CED
#define WEBGL_COLOR_ATTACHMENT14_WEBGL    0x8CEE
#define WEBGL_COLOR_ATTACHMENT15_WEBGL    0x8CEF
#define WEBGL_DRAW_BUFFER0_WEBGL  0x8825
#define WEBGL_DRAW_BUFFER1_WEBGL  0x8826
#define WEBGL_DRAW_BUFFER2_WEBGL  0x8827
#define WEBGL_DRAW_BUFFER3_WEBGL  0x8828
#define WEBGL_DRAW_BUFFER4_WEBGL  0x8829
#define WEBGL_DRAW_BUFFER5_WEBGL  0x882A
#define WEBGL_DRAW_BUFFER6_WEBGL  0x882B
#define WEBGL_DRAW_BUFFER7_WEBGL  0x882C
#define WEBGL_DRAW_BUFFER8_WEBGL  0x882D
#define WEBGL_DRAW_BUFFER9_WEBGL  0x882E
#define WEBGL_DRAW_BUFFER10_WEBGL     0x882F
#define WEBGL_DRAW_BUFFER11_WEBGL     0x8830
#define WEBGL_DRAW_BUFFER12_WEBGL     0x8831
#define WEBGL_DRAW_BUFFER13_WEBGL     0x8832
#define WEBGL_DRAW_BUFFER14_WEBGL     0x8833
#define WEBGL_DRAW_BUFFER15_WEBGL     0x8834
#define WEBGL_MAX_COLOR_ATTACHMENTS_WEBGL     0x8CDF
#define WEBGL_MAX_DRAW_BUFFERS_WEBGL  0x8824

// OES_vertex_array_object
#define WEBGL_VERTEX_ARRAY_BINDING_OES    0x85B5

// EXT_disjoint_timer_query
#define WEBGL_QUERY_COUNTER_BITS_EXT  0x8864
#define WEBGL_CURRENT_QUERY_EXT   0x8865
#define WEBGL_QUERY_RESULT_EXT    0x8866
#define WEBGL_QUERY_RESULT_AVAILABLE_EXT  0x8867
#define WEBGL_TIME_ELAPSED_EXT    0x88BF
#define WEBGL_TIMESTAMP_EXT   0x8E28
#define WEBGL_GPU_DISJOINT_EXT    0x8FBB



// WebGL types.

// WebGL 1 types.
typedef unsigned long GLenum;
typedef bool GLboolean;
typedef unsigned long GLbitfield;
typedef char GLbyte;
typedef short GLshort;
typedef long GLint;
typedef long GLsizei;
typedef long long GLintptr;
typedef long long GLsizeiptr;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned long GLuint;
typedef float GLfloat;
typedef float GLclampf;

// WebGL 2 types.
typedef long long GLint64;

// WebGL extensions types.
typedef unsigned long long GLuint64EXT;

// WebGL functions.
void webglClearColor(float r, float g, float b, float a);
void webglClear(int clear_flags);

void webglActiveTexture(GLuint tex);
void webglAttachShader(GLuint program, GLuint shader);
void webglClearDepth(GLclampf depth);
void webglClearStencil(GLint s);
void webglColorMask(bool r, bool g, bool b, bool a);
void webglCompileShader(GLuint shader);
GLuint webglCreateBuffer(void);
GLuint webglCreateFramebuffer(void);

bool webglIsExtensionSupported(const char *name_pointer, int name_count);
int webglGetError(void);
void webglGetWebGLVersion(unsigned int *major, unsigned int *minor);
void webglGetESVersion(unsigned int *major, unsigned int *minor);
int webglDrawingBufferWidth(void);
int webglDrawingBufferHeight(void);



extern void wasm_write_string_count(const char *s, int count, bool to_standard_error);

extern void wasm_debug_break(void);

extern void wasm_entry_point_set(void (*entry)(float));

extern float wasm_canvas_get_width(void);
extern float wasm_canvas_get_height(void);
extern void wasm_canvas_get_size(float result_pointer[2]);

extern void context2d_clear_render_target(float r, float g, float b, float a);

extern void context2d_draw_quad(float x0, float y0, float x1, float y1, float r, float g, float b, float a);

#define STRINGIFY(x) STRINGIFY2(x)
#define STRINGIFY2(x) #x

#define basic_assert(expr) do { \
    if (!(expr)) { \
        wasm_write_string("Assertion Failure: " STRINGIFY(expr) " at " __FILE__ ":" STRINGIFY(__LINE__) "\n", true); \
        wasm_debug_break(); \
    } \
} while (0)

void wasm_write_string(const char *s, bool to_standard_error = false) {
    const char *it = s;

    while (*it++);

    int count = it - 1 - s;

    wasm_write_string_count(s, count, to_standard_error);
}

void write_integer(int64_t x) {
    char rev[256];
    char buf[256];
    int count = 0;
    bool is_negative = false;

    if (x == 0) {
        wasm_write_string_count("0", 1, false);
        return;
    } 

    if (x < 0) {
        x = -x;
        is_negative = true;
    }

    while (x) {
        int64_t d = x % 10;
        rev[count++] = (char)('0' + d);

        x /= 10;
    }

    char *it = buf;
    if (is_negative) {
        *it++ = '-';
    }

    for (int i = count-1; i >= 0; --i) {
        *it++ = rev[i];
    }

    *it = 0;

    wasm_write_string_count(buf, (int)(it-buf), false);
}

int add(int a, int b) {
    return a + b;
}


extern unsigned char __heap_base;

static unsigned char *bump_pointer = &__heap_base;

typedef unsigned long size_t;

void *basic_malloc(size_t size) {
    void *result = bump_pointer;
    bump_pointer += size;
    return result;
}

void basic_free(void *mem) {
    (void)(mem);
}

int main(void);

__attribute((export_name("_start")))
void _start(void) {
    main();
}

}



void update_2d(float dt) {
    static float x = 0;

    context2d_clear_render_target(1,1,1,1);

    float size[2];
    wasm_canvas_get_size(size);

    float w = size[0];
    float h = size[1];

    float x0 = w * 0.1f;
    float y0 = h * 0.1f;
    float x1 = w * 0.9f;
    float y1 = h * 0.9f;
    context2d_draw_quad(x0, y0, x1, y1, 0,0,1,1);
    
    x += 100 * dt;
    context2d_draw_quad(x, 10, x+10, 20, 1,0,0,1);
}

void update(float dt) {
    webglClearColor(0.3, 0.0, 0.3, 1);
    webglClear(WEBGL_COLOR_BUFFER_BIT);

    float back_buffer_width  = webglDrawingBufferWidth();
    float back_buffer_height = webglDrawingBufferHeight();
}

int main(void) {
    #if OS_WASM
    wasm_write_string("WASM platform\n", false);
#endif

#if ARCH_WASM32
    wasm_write_string("WASM32\n", false);
#elif ARCH_WASM32
    wasm_write_string("WASM64\n", false);
#endif

    // Address 0 is valid for WASM runtime.
    // So we compile with -fsanitize=undefined -fsanitize-trap for clang.
    // int *pointer = 0;
    // *pointer = 0xFF;

    char *p = (char *)basic_malloc(12+1);
    __builtin_memset(p, 0, 13);

    char msg[] = "Hello friend";
    for (int i = 0; i < 12; ++i) {
        p[i] = msg[i];
    }

    wasm_write_string(p, false);
    wasm_write_string("\n", false);

    basic_free(p);

    if (webglIsExtensionSupported("EXT_sRGB", sizeof("EXT_sRGB")-1))
        wasm_write_string("EXT_sRGB\n", false);

    if (webglGetError())
        wasm_write_string("WebGL error!", false);

    unsigned int major, minor;
    webglGetWebGLVersion(&major, &minor);

    wasm_write_string("WebGL Major: ");
    write_integer(major);
    wasm_write_string(", ");
    wasm_write_string("Minor: ");
    write_integer(minor);
    wasm_write_string("\n");

    webglGetESVersion(&major, &minor);

    wasm_write_string("OpenGL ES Major: ");
    write_integer(major);
    wasm_write_string(", ");
    wasm_write_string("Minor: ");
    write_integer(minor);
    wasm_write_string("\n");

    webglActiveTexture(WEBGL_TEXTURE0);

    wasm_entry_point_set(update);

    return 0;
}



// #define NB_IMPLEMENTATION
// #include "nb.h"