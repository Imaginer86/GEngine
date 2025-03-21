#pragma once

/*! @defgroup keys Keyboard keys
 *  @brief Keyboard key IDs.
 *
 *  See [key input](@ref input_key) for how these are used.
 *
 *  These key codes are inspired by the _USB HID Usage Tables v1.12_ (p. 53-60),
 *  but re-arranged to map to 7-bit ASCII for printable keys (function keys are
 *  put in the 256+ range).
 *
 *  The naming of the key codes follow these rules:
 *   - The US keyboard layout is used
 *   - Names of printable alpha-numeric characters are used (e.g. "A", "R",
 *     "3", etc.)
 *   - For non-alphanumeric characters, Unicode:ish names are used (e.g.
 *     "COMMA", "LEFT_SQUARE_BRACKET", etc.). Note that some names do not
 *     correspond to the Unicode standard (usually for brevity)
 *   - Keys that lack a clear US mapping are named "WORLD_x"
 *   - For non-printable keys, custom names are used (e.g. "F4",
 *     "BACKSPACE", etc.)
 *
 *  @ingroup input
 *  @{
 */

 /* The unknown key */
#define G_KEY_UNKNOWN            -1

/* Printable keys */
#define G_KEY_SPACE              32
#define G_KEY_APOSTROPHE         39  /* ' */
#define G_KEY_COMMA              44  /* , */
#define G_KEY_MINUS              45  /* - */
#define G_KEY_PERIOD             46  /* . */
#define G_KEY_SLASH              47  /* / */
#define G_KEY_0                  48
#define G_KEY_1                  49
#define G_KEY_2                  50
#define G_KEY_3                  51
#define G_KEY_4                  52
#define G_KEY_5                  53
#define G_KEY_6                  54
#define G_KEY_7                  55
#define G_KEY_8                  56
#define G_KEY_9                  57
#define G_KEY_SEMICOLON          59  /* ; */
#define G_KEY_EQUAL              61  /* = */
#define G_KEY_A                  65
#define G_KEY_B                  66
#define G_KEY_C                  67
#define G_KEY_D                  68
#define G_KEY_E                  69
#define G_KEY_F                  70
#define G_KEY_G                  71
#define G_KEY_H                  72
#define G_KEY_I                  73
#define G_KEY_J                  74
#define G_KEY_K                  75
#define G_KEY_L                  76
#define G_KEY_M                  77
#define G_KEY_N                  78
#define G_KEY_O                  79
#define G_KEY_P                  80
#define G_KEY_Q                  81
#define G_KEY_R                  82
#define G_KEY_S                  83
#define G_KEY_T                  84
#define G_KEY_U                  85
#define G_KEY_V                  86
#define G_KEY_W                  87
#define G_KEY_X                  88
#define G_KEY_Y                  89
#define G_KEY_Z                  90
#define G_KEY_LEFT_BRACKET       91  /* [ */
#define G_KEY_BACKSLASH          92  /* \ */
#define G_KEY_RIGHT_BRACKET      93  /* ] */
#define G_KEY_GRAVE_ACCENT       96  /* ` */
#define G_KEY_WORLD_1            161 /* non-US #1 */
#define G_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define G_KEY_ESCAPE             256
#define G_KEY_ENTER              257
#define G_KEY_TAB                258
#define G_KEY_BACKSPACE          259
#define G_KEY_INSERT             260
#define G_KEY_DELETE             261
#define G_KEY_RIGHT              262
#define G_KEY_LEFT               263
#define G_KEY_DOWN               264
#define G_KEY_UP                 265
#define G_KEY_PAGE_UP            266
#define G_KEY_PAGE_DOWN          267
#define G_KEY_HOME               268
#define G_KEY_END                269
#define G_KEY_CAPS_LOCK          280
#define G_KEY_SCROLL_LOCK        281
#define G_KEY_NUM_LOCK           282
#define G_KEY_PRINT_SCREEN       283
#define G_KEY_PAUSE              284
#define G_KEY_F1                 290
#define G_KEY_F2                 291
#define G_KEY_F3                 292
#define G_KEY_F4                 293
#define G_KEY_F5                 294
#define G_KEY_F6                 295
#define G_KEY_F7                 296
#define G_KEY_F8                 297
#define G_KEY_F9                 298
#define G_KEY_F10                299
#define G_KEY_F11                300
#define G_KEY_F12                301
#define G_KEY_F13                302
#define G_KEY_F14                303
#define G_KEY_F15                304
#define G_KEY_F16                305
#define G_KEY_F17                306
#define G_KEY_F18                307
#define G_KEY_F19                308
#define G_KEY_F20                309
#define G_KEY_F21                310
#define G_KEY_F22                311
#define G_KEY_F23                312
#define G_KEY_F24                313
#define G_KEY_F25                314
#define G_KEY_KP_0               320
#define G_KEY_KP_1               321
#define G_KEY_KP_2               322
#define G_KEY_KP_3               323
#define G_KEY_KP_4               324
#define G_KEY_KP_5               325
#define G_KEY_KP_6               326
#define G_KEY_KP_7               327
#define G_KEY_KP_8               328
#define G_KEY_KP_9               329
#define G_KEY_KP_DECIMAL         330
#define G_KEY_KP_DIVIDE          331
#define G_KEY_KP_MULTIPLY        332
#define G_KEY_KP_SUBTRACT        333
#define G_KEY_KP_ADD             334
#define G_KEY_KP_ENTER           335
#define G_KEY_KP_EQUAL           336
#define G_KEY_LEFT_SHIFT         340
#define G_KEY_LEFT_CONTROL       341
#define G_KEY_LEFT_ALT           342
#define G_KEY_LEFT_SUPER         343
#define G_KEY_RIGHT_SHIFT        344
#define G_KEY_RIGHT_CONTROL      345
#define G_KEY_RIGHT_ALT          346
#define G_KEY_RIGHT_SUPER        347
#define G_KEY_MENU               348

#define G_KEY_LAST               G_KEY_MENU

class Input
{
public:
	bool Init(void* window_);
};
