/*

  m2.h
  
  Overall header file

  
  m2tklib = Mini Interative Interface Toolkit Library
  
  Copyright (C) 2011  olikraus@gmail.com

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.


  
   /usr/lib/avr/include/avr/pgmspace.h
   
*/

#ifndef _M2_H
#define _M2_H


#include <stddef.h>
#include <stdint.h>

/* this macro controlles the use debug output */
/* #define M2_USE_DBG_SHOW */



/* this macro controlles the use of the the PGM memory */

#ifdef __AVR__
#define M2_AVR_PGM
#endif

/*
    M2_AVR_PGM
      Overall switch for activating PROGMEM 
      Defined, if __AVR__ has been defined
    M2_AVR_OPT_ROM
      controlls the use of Progmem space for any option strings
      Not defined 
*/

#define M2_FRAME_AT_END

#if defined(M2_AVR_PGM)
#include "avr/pgmspace.h"
#define M2_PROGMEM PROGMEM
#define M2_SECTION_PROGMEM __attribute__((section(".progmem.data")))
//#define M2_AVR_OPT_ROM
#else
#define M2_PROGMEM
#define M2_SECTION_PROGMEM
#endif

#ifdef __GNUC__
#define M2_NOINLINE __attribute__((noinline))
#else
#define M2_NOINLINE
#endif

/* M2_ATOMIC_BLOCK */ 
#ifdef __AVR__
#include <util/atomic.h>
#define M2_ATOMIC_BLOCK ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
#endif

#ifndef M2_ATOMIC_BLOCK
#define M2_ATOMIC_BLOCK
#endif 


#ifdef __cplusplus
extern "C" {
#endif


/*==============================================================*/
/* Forward declarations */

/* generic element pointer */
typedef struct _m2_el_fnfmt_struct m2_el_fnfmt_t;
typedef m2_el_fnfmt_t *m2_el_fnfmt_p;
  
  
/* toplevel API */
typedef struct _m2_struct m2_t;
typedef struct _m2_struct *m2_p;

/* tree navigation structure */
typedef struct _m2_nav_struct m2_nav_t;
typedef struct _m2_nav_struct *m2_nav_p;

/* argument for the element (=widget) callback procedures */
typedef struct _m2_el_fnarg m2_el_fnarg_t;
typedef struct _m2_el_fnarg *m2_el_fnarg_p;

typedef struct _m2_gfx_arg m2_gfx_arg_t;
typedef struct _m2_gfx_arg *m2_gfx_arg_p;


/* event handler (callback procedure) */
typedef uint8_t (*m2_eh_fnptr)(m2_p ep, uint8_t msg, uint8_t arg);

/* event source (callback procedure) */
typedef uint8_t (*m2_es_fnptr)(m2_p ep, uint8_t msg);

/* graphics handler (callback procedure) */
typedef uint8_t (*m2_gfx_fnptr)(m2_gfx_arg_p arg);

/* element callback procedure */
typedef uint8_t (*m2_el_fnptr)(m2_el_fnarg_p fn_arg);

/* button, elinfo callback procedure */
typedef void (*m2_button_fnptr)(m2_el_fnarg_p fnarg);

/* generic rom pointers */
typedef void m2_rom_void M2_PROGMEM;
typedef char m2_rom_char M2_PROGMEM;

typedef const m2_rom_void *m2_rom_void_p;
typedef const m2_rom_char *m2_rom_char_p;
typedef const m2_rom_char m2_rom_char_t;

#if defined(M2_AVR_OPT_ROM)
typedef const m2_rom_char *m2_opt_p;
#else
typedef const char *m2_opt_p;
#endif

/*==============================================================*/
/* m2tklib Toplevel API */


/* object interface */
void m2_InitM2(m2_p m2, m2_rom_void_p element, m2_es_fnptr es, m2_eh_fnptr eh, m2_gfx_fnptr gh) M2_NOINLINE;	/* m2obj.c */
void m2_CheckKeyM2(m2_p m2) M2_NOINLINE;
uint8_t m2_HandleKeyM2(m2_p m2) M2_NOINLINE;													/* m2obj.c */
void m2_DrawM2(m2_p m2) M2_NOINLINE;													/* m2draw.c */
void m2_SetFontM2(m2_p m2, uint8_t font_idx, const void *font_ptr) M2_NOINLINE;					/* m2obj.c */
void m2_SetEventSourceHandlerM2(m2_p m2, m2_es_fnptr es) M2_NOINLINE;						/* m2obj.c */
void m2_SetRootM2(m2_p m2, m2_rom_void_p element) M2_NOINLINE;								/* m2obj.c */
m2_rom_void_p m2_GetRootM2(m2_p m2) M2_NOINLINE;										/* m2obj.c */
void m2_ClearM2(m2_p m2);
void m2_SetGraphicsHandlerM2(m2_p m2, m2_gfx_fnptr gh);

/* simplified interface */
extern m2_t m2_global_object;
void m2_Init(m2_rom_void_p element, m2_es_fnptr es, m2_eh_fnptr eh, m2_gfx_fnptr gh);
void m2_CheckKey(void);
uint8_t m2_HandleKey(void);
void m2_Draw(void);
void m2_SetKey(uint8_t key);
void m2_SetFont(uint8_t font_idx, const void *font_ptr);
void m2_InitEventSource(void);
void m2_SetRoot(m2_rom_void_p element);
m2_rom_void_p m2_GetRoot(void);
void m2_Clear(void);
void m2_SetGraphicsHandler(m2_gfx_fnptr gh);


void m2_MessageFn(const char *text, const char *button, m2_button_fnptr fn);
void m2_MessageB2Fn(const char *text, const char *button1, m2_button_fnptr fn1, const char *button2, m2_button_fnptr fn2);


extern uint8_t m2_is_frame_draw_at_end;									/* m2draw.c */
extern m2_el_fnfmt_t m2_null_element M2_SECTION_PROGMEM;					/* m2null.c */

/*==============================================================*/
/* Arguments for m2_Init() */

/* event sources */
uint8_t m2_es_sdl(m2_p ep, uint8_t msg);		/* m2ghsdl.c: SDL Event Source */
//uint8_t m2_es_arduino(m2_p ep, uint8_t msg);			/* m2esarduino.c */

uint8_t m2_es_SL(m2_p ep, uint8_t msg);			/* m2esSL.c */

/* event handler */
uint8_t m2_eh_2bd(m2_p ep, uint8_t msg, uint8_t arg);		/* m2eh2bd.c 2 Button Handler with data entry mode SELECT, NEXT */
uint8_t m2_eh_2bs(m2_p ep, uint8_t msg, uint8_t arg);		/* m2eh2bs.c simplified 2 Button Handler SELECT, NEXT */
uint8_t m2_eh_4bd(m2_p ep, uint8_t msg, uint8_t arg);		/* m2eh4bd.c */		
uint8_t m2_eh_4bs(m2_p ep, uint8_t msg, uint8_t arg);		/* m2eh4bs.c simplified 4 Button Handler SELECT, EXIT, PREV, NEXT */
uint8_t m2_eh_6bs(m2_p ep, uint8_t msg, uint8_t arg);		/* m2eh6bs.c simplified 6 Button Handler SELECT, EXIT, PREV, NEXT, DATA_UP, DATA_DOWN */

/* graphics handler */
uint8_t m2_gh_dummy(m2_gfx_arg_p arg);
uint8_t m2_gh_sdl(m2_gfx_arg_p arg);					/* m2ghsdl.c: SDL Graphics Handler */


/*==============================================================*/
/* Macro Definitions */

#define M2_PSTR(s) s

/* Define the maximum depth of  the menu tree */
#define M2_DEPTH_MAX 7

/* Key values */
#define M2_KEY_NONE 0
#define M2_KEY_SELECT 1
#define M2_KEY_EXIT 2
#define M2_KEY_NEXT 3
#define M2_KEY_PREV 4
#define M2_KEY_DATA_UP 5
#define M2_KEY_DATA_DOWN 6
#define M2_KEY_REFRESH 7

#define M2_KEY_CNT 7

/* mark key as event */
/* if the EVENT bit is set, then the key is directly passed to the queue */
/* if the EVENT bit is not set, then it is assumed, that this value has to be debounced */
/* this is only important for the event source */
#define M2_KEY_EVENT_MASK (64)
#define M2_KEY_EVENT(k) ((k)|M2_KEY_EVENT_MASK)
#define M2_IS_KEY_EVENT(k) ((k)&M2_KEY_EVENT_MASK)

/* Messages to the element callback procedures, see documentation */
#define M2_EL_MSG_GET_LIST_LEN 2
#define M2_EL_MSG_GET_LIST_ELEMENT 3
#define M2_EL_MSG_GET_LIST_BOX 4
#define M2_EL_MSG_GET_OPT 5
#define M2_EL_MSG_IS_AUTO_SKIP 15
#define M2_EL_MSG_IS_READ_ONLY 16
#define M2_EL_MSG_GET_HEIGHT 17
#define M2_EL_MSG_GET_WIDTH 18
#define M2_EL_MSG_IS_DATA_ENTRY 20
#define M2_EL_MSG_DATA_UP 21
#define M2_EL_MSG_DATA_DOWN 22
#define M2_EL_MSG_DATA_SET_U8 23
#define M2_EL_MSG_SELECT 30
#define M2_EL_MSG_NEW_FOCUS 31
#define M2_EL_MSG_SHOW 40
#if defined(M2_USE_DBG_SHOW)
#define M2_EL_MSG_DBG_SHOW 41
#endif
/* currently disabled
#define M2_EL_MSG_POST_SHOW 42
*/

/* Messages to the graphics subsystem */
#define M2_GFX_MSG_INIT 							0
#define M2_GFX_MSG_START 							1
#define M2_GFX_MSG_END 							2
#define M2_GFX_MSG_DRAW_HLINE 					3
#define M2_GFX_MSG_DRAW_VLINE 						4
#define M2_GFX_MSG_DRAW_BOX 						5
#define M2_GFX_MSG_DRAW_TEXT 						6
#define M2_GFX_MSG_DRAW_TEXT_P 					7
#define M2_GFX_MSG_DRAW_NORMAL_NO_FOCUS			8
#define M2_GFX_MSG_DRAW_NORMAL_FOCUS 				9
#define M2_GFX_MSG_DRAW_NORMAL_PARENT_FOCUS		10
#define M2_GFX_MSG_DRAW_SMALL_FOCUS 				11
#define M2_GFX_MSG_DRAW_NORMAL_DATA_ENTRY 			12
#define M2_GFX_MSG_DRAW_SMALL_DATA_ENTRY 			13
#define M2_GFX_MSG_DRAW_GO_UP 					14
#define M2_GFX_MSG_DRAW_ICON 						15
#define M2_GFX_MSG_DRAW_VERTICAL_SCROLL_BAR		16
#define M2_GFX_MSG_GET_TEXT_WIDTH 					17
#define M2_GFX_MSG_GET_TEXT_WIDTH_P 				18
#define M2_GFX_MSG_GET_CHAR_WIDTH 					19	
#define M2_GFX_MSG_GET_CHAR_HEIGHT 				20
#define M2_GFX_MSG_GET_NORMAL_BORDER_HEIGHT 		21
#define M2_GFX_MSG_GET_NORMAL_BORDER_WIDTH 		22
#define M2_GFX_MSG_GET_NORMAL_BORDER_X_OFFSET 		23
#define M2_GFX_MSG_GET_NORMAL_BORDER_Y_OFFSET 		24
#define M2_GFX_MSG_GET_SMALL_BORDER_HEIGHT 		25
#define M2_GFX_MSG_GET_SMALL_BORDER_WIDTH 			26
#define M2_GFX_MSG_GET_SMALL_BORDER_X_OFFSET 		27
#define M2_GFX_MSG_GET_SMALL_BORDER_Y_OFFSET 		28
#define M2_GFX_MSG_GET_READONLY_BORDER_HEIGHT 		29
#define M2_GFX_MSG_GET_READONLY_BORDER_WIDTH 		30
#define M2_GFX_MSG_GET_READONLY_BORDER_X_OFFSET 	31
#define M2_GFX_MSG_GET_READONLY_BORDER_Y_OFFSET 	32
#define M2_GFX_MSG_GET_LIST_OVERLAP_HEIGHT 			33
#define M2_GFX_MSG_GET_LIST_OVERLAP_WIDTH 			34
#define M2_GFX_MSG_GET_ICON_HEIGHT 				35
#define M2_GFX_MSG_GET_ICON_WIDTH 					36
#define M2_GFX_MSG_IS_FRAME_DRAW_AT_END			37
#define M2_GFX_MSG_SET_FONT						38
#define M2_GFX_MSG_GET_DISPLAY_WIDTH				39
#define M2_GFX_MSG_GET_DISPLAY_HEIGHT				40

/*==============================================================*/
/* object function */
/* M2_FN = Menu Field Notification Message */

struct _m2_el_fnarg
{
  m2_rom_void_p element;	/* pointer to the current element */
  uint8_t msg;				/* message M2_EL_MSG_xxx */
  uint8_t arg;				/* depends on message */
  void *data;  				/* depends on message */
  m2_nav_p nav;			/* reference to navigation object */
};
#define M2_EL_FN_DEF(name) uint8_t name(m2_el_fnarg_p fn_arg)







/*==============================================================*/
uint8_t m2_rom_low_level_get_byte(m2_rom_void_p ptr) M2_NOINLINE;									/* m2rom.c */
void m2_rom_low_level_copy(void *dest, m2_rom_void_p src, uint8_t cnt) M2_NOINLINE;					/* m2rom.c */
uint8_t m2_rom_get_u8(m2_rom_void_p base, uint8_t offset) M2_NOINLINE;								/* m2rom.c */
uint32_t m2_rom_get_u32(m2_rom_void_p base, uint8_t offset) M2_NOINLINE;							/* m2rom.c */
m2_rom_void_p m2_rom_get_rom_ptr(m2_rom_void_p base, uint8_t offset) M2_NOINLINE;					/* m2rom.c */
void *m2_rom_get_ram_ptr(m2_rom_void_p base, uint8_t offset) M2_NOINLINE;							/* m2rom.c */
m2_el_fnptr m2_rom_get_el_fnptr(m2_rom_void_p base) M2_NOINLINE;									/* m2rom.c */
m2_el_fnptr m2_rom_get_fnptr(m2_rom_void_p base, uint8_t offset) M2_NOINLINE;							/* m2rom.c */
m2_rom_void_p m2_rom_get_ptr_list_rom_ptr(m2_rom_void_p base, uint8_t idx) M2_NOINLINE;				/* m2rom.c */
/*==============================================================*/
/* option string */
#define M2_OPT_NOT_FOUND 255
uint8_t m2_opt_get_val(m2_rom_char_p str, char cmd) M2_NOINLINE;									/* m2opt.c */
uint8_t m2_opt_get_val_zero_default(m2_rom_char_p str, char cmd) M2_NOINLINE;						/* m2opt.c */
uint8_t m2_opt_get_val_any_default(m2_rom_char_p str, char cmd, uint8_t default_value) M2_NOINLINE;		/* m2opt.c */


/*==============================================================*/
uint8_t m2_GetKeyFromQueue(m2_p m2);														/* m2key.c */
void m2_PutKeyIntoQueue(m2_p m2, uint8_t key_code);												/* m2key.c */
void m2_SetDetectedKey(m2_p m2, uint8_t key_code);												/* m2key.c */


/*==============================================================*/

/* combo box (callback procedure) */
typedef const char *(*m2_get_str_fnptr)(uint8_t idx);

/*==============================================================*/

/* strlist element (callback procedure) */
typedef const char *(*m2_strlist_cb_fnptr)(uint8_t idx, uint8_t msg);

#define M2_STRLIST_MSG_GET_STR 101
#define M2_STRLIST_MSG_SELECT 102

/*==============================================================*/
/* list of elements */
/* M2_LIST(rgb_list) = { &red_el, &green_el, &blue_el }; */

#define M2_LIST(list) const void *list[] M2_SECTION_PROGMEM 

/*==============================================================*/
/* elements */
/* the first st ructure member is always the element callback function */
/* the base element. all other elementes are derived from this structure */
struct _m2_el_fnfmt_struct
{
  m2_el_fnptr fn;		/* fn must be the first member of the struct */
  m2_rom_char_p fmt; 	/* hmmm.... format options are located in ram */
};
/* see above 
typedef struct _m2_el_fnfmt_struct m2_el_fnfmt_t;
typedef m2_el_fnfmt_t *m2_el_fnfmt_p;
*/

/* do not used this element procedure directly! */
/* it is more an abstract base class procedure... */
M2_EL_FN_DEF(m2_el_fnfmt_fn);


struct _m2_el_space_struct
{
  m2_el_fnfmt_t ff;
};
typedef struct _m2_el_space_struct m2_el_space_t;
typedef m2_el_space_t *m2_el_space_p;

M2_EL_FN_DEF(m2_el_space_fn);

#define M2_SPACE(el,fmt) m2_el_space_t el M2_SECTION_PROGMEM = { { m2_el_space_fn, (fmt) } }
#define M2_EXTERN_SPACE(el) extern m2_el_space_t el



struct _m2_el_strptr_struct
{
  m2_el_fnfmt_t ff;
  const char **strptr;
};
typedef struct _m2_el_strptr_struct m2_el_strptr_t;
typedef m2_el_strptr_t *m2_el_strptr_p;

M2_EL_FN_DEF(m2_el_strptr_fn);

M2_EL_FN_DEF(m2_el_labelptr_fn);
#define M2_LABELPTR(el,fmt,strptr) m2_el_strptr_t el M2_SECTION_PROGMEM = { { m2_el_labelptr_fn, (fmt) }, (strptr) }
#define M2_EXTERN_LABELPTR(el) extern m2_el_strptr_t el

struct _m2_el_buttonptr_struct
{
  m2_el_strptr_t el_strptr;
  m2_button_fnptr button_callback;
};
typedef struct _m2_el_buttonptr_struct m2_el_buttonptr_t;
typedef m2_el_buttonptr_t *m2_el_buttonptr_p;

M2_EL_FN_DEF(m2_el_buttonptr_fn);
#define M2_BUTTONPTR(el, fmt,strptr,callback) m2_el_buttonptr_t el M2_SECTION_PROGMEM = { { { m2_el_buttonptr_fn, (fmt) }, (strptr) },  (callback)  }
#define M2_EXTERN_BUTTONPTR(el) extern m2_el_buttonptr_t el


struct _m2_el_str_struct
{
  m2_el_fnfmt_t ff;
  const char *str;
};
typedef struct _m2_el_str_struct m2_el_str_t;
typedef m2_el_str_t *m2_el_str_p;

M2_EL_FN_DEF(m2_el_str_fn);
M2_EL_FN_DEF(m2_el_str_up_fn);
#define M2_STR_UP(el,fmt,str) m2_el_str_t el M2_SECTION_PROGMEM = { { m2_el_str_up_fn, (fmt) }, (str) }
#define M2_EXTERN_STR_UP(el) extern m2_el_str_t el

M2_EL_FN_DEF(m2_el_label_fn);
#define M2_LABEL(el,fmt,str) m2_el_str_t el M2_SECTION_PROGMEM = { { m2_el_label_fn, (fmt) }, (str) }
#define M2_EXTERN_LABEL(el) extern m2_el_str_t el

M2_EL_FN_DEF(m2_el_labelp_fn);
#define M2_LABELP(el,fmt,str) m2_el_str_t el M2_SECTION_PROGMEM = { { m2_el_labelp_fn, (fmt) }, (str) }
#define M2_EXTERN_LABELP(el) extern m2_el_str_t el


struct _m2_el_root_struct
{
  m2_el_str_t el_str;
  m2_rom_void_p element;
};
typedef struct _m2_el_root_struct m2_el_root_t;
typedef m2_el_root_t *m2_el_root_p;

M2_EL_FN_DEF(m2_el_root_fn);
#define M2_ROOT(el, fmt, str, element) m2_el_root_t el M2_SECTION_PROGMEM = { { { m2_el_root_fn, (fmt) }, (str) },  (element)  }
#define M2_EXTERN_ROOT(el) extern m2_el_root_t el

struct _m2_el_button_struct
{
  m2_el_str_t el_str;
  m2_button_fnptr button_callback;
};
typedef struct _m2_el_button_struct m2_el_button_t;
typedef m2_el_button_t *m2_el_button_p;

M2_EL_FN_DEF(m2_el_button_fn);
#define M2_BUTTON(el, fmt, str, callback) m2_el_button_t el M2_SECTION_PROGMEM = { { { m2_el_button_fn, (fmt) }, (str) },  (callback)  }
#define M2_EXTERN_BUTTON(el) extern m2_el_button_t el


struct _m2_el_u8_struct
{
  m2_el_fnfmt_t ff;
  uint8_t min;
  uint8_t max;
  uint8_t *val;		/* data, which should be modified */
};
typedef struct _m2_el_u8_struct m2_el_u8_t;
typedef m2_el_u8_t *m2_el_u8_p;

M2_EL_FN_DEF(m2_el_u8base_fn);												/* m2elu8base.c */
M2_EL_FN_DEF(m2_el_u8num_fn);
#define M2_U8NUM(el,fmt,min,max,variable) m2_el_u8_t el M2_SECTION_PROGMEM = { { m2_el_u8num_fn, (fmt) }, (min), (max), (variable) }
#define M2_EXTERN_U8NUM(el) extern m2_el_u8_t el
M2_EL_FN_DEF(m2_el_u8hs_fn);
#define M2_U8HS(el,fmt,min,max,variable) m2_el_u8_t el M2_SECTION_PROGMEM = { { m2_el_u8hs_fn, (fmt) }, (min), (max), (variable) }
#define M2_EXTERN_U8HS(el) extern m2_el_u8_t el



struct _m2_el_list_struct
{
  m2_el_fnfmt_t ff;
  uint8_t len;
  m2_rom_void_p *el_list;	/* Because we use M2_SECTION_PROGMEM, there is no type checking for PROGMEM */
};
typedef struct _m2_el_list_struct m2_el_list_t;
typedef m2_el_list_t *m2_el_list_p;

M2_EL_FN_DEF(m2_el_vlist_fn);
M2_EL_FN_DEF(m2_el_hlist_fn);
M2_EL_FN_DEF(m2_el_gridlist_fn);
M2_EL_FN_DEF(m2_el_xylist_fn);

#define M2_VLIST(el,fmt,list) m2_el_list_t el M2_SECTION_PROGMEM = { { m2_el_vlist_fn, (fmt) } , sizeof(list)/sizeof(*(list)), (list) }
#define M2_HLIST(el,fmt,list) m2_el_list_t el M2_SECTION_PROGMEM = { { m2_el_hlist_fn, (fmt) } , sizeof(list)/sizeof(*(list)), (list) }
#define M2_GRIDLIST(el,fmt,list) m2_el_list_t el M2_SECTION_PROGMEM = { { m2_el_gridlist_fn, (fmt) } , sizeof(list)/sizeof(*(list)), (list) }
#define M2_XYLIST(el,fmt,list) m2_el_list_t el M2_SECTION_PROGMEM = { { m2_el_xylist_fn, (fmt) } , sizeof(list)/sizeof(*(list)), (list) }

#define M2_EXTERN_VLIST(el) extern m2_el_list_t el
#define M2_EXTERN_HLIST(el) extern m2_el_list_t el
#define M2_EXTERN_GRIDLIST(el) extern m2_el_list_t el
#define M2_EXTERN_XYLIST(el) extern m2_el_list_t el

uint8_t m2_calc_vlist_height_overlap_correction(uint8_t height, uint8_t cnt) M2_NOINLINE; /* m2ellistv.c */


struct _m2_el_text_struct
{
  m2_el_fnfmt_t ff;
  char *text;
  uint8_t len;
};
typedef struct _m2_el_text_struct m2_el_text_t;
typedef m2_el_text_t *m2_el_text_p;

M2_EL_FN_DEF(m2_el_text_fn);
#define M2_TEXT(el,fmt,text,len) m2_el_text_t el M2_SECTION_PROGMEM = { { m2_el_text_fn, (fmt) }, (text), (len) }
#define M2_EXTERN_TEXT(el) extern m2_el_text_t el

struct _m2_el_u32_struct
{
  m2_el_fnfmt_t ff;
  uint32_t *val;
};
typedef struct _m2_el_u32_struct m2_el_u32_t;
typedef m2_el_u32_t *m2_el_u32_p;

M2_EL_FN_DEF(m2_el_u32_fn);
#define M2_U32NUM(el,fmt,variable) m2_el_u32_t el M2_SECTION_PROGMEM = { { m2_el_u32_fn, (fmt) }, (variable) }
#define M2_EXTERN_U32NUM(el) extern m2_el_u32_t el

struct _m2_el_align_struct
{
  m2_el_fnfmt_t ff;
  m2_rom_void_p element;
};
typedef struct _m2_el_align_struct m2_el_align_t;
typedef m2_el_align_t *m2_el_align_p;

M2_EL_FN_DEF(m2_el_align_fn);
#define M2_ALIGN(el, fmt, element) m2_el_align_t el M2_SECTION_PROGMEM = {{ m2_el_align_fn, (fmt) }, (element) }
#define M2_EXTERN_ALIGN(el) extern m2_el_align_t el

/* used for toggle and radio buttons */
struct _m2_el_setval_struct
{
  m2_el_fnfmt_t ff;
  uint8_t *val;
};
typedef struct _m2_el_setval_struct m2_el_setval_t;
typedef m2_el_setval_t *m2_el_setval_p;

M2_EL_FN_DEF(m2_el_setval_fn);
M2_EL_FN_DEF(m2_el_toggle_fn);
#define M2_TOGGLE(el,fmt,variable) m2_el_setval_t el M2_SECTION_PROGMEM = { { m2_el_toggle_fn, (fmt) }, (variable) }
#define M2_EXTERN_TOGGLE(el) extern m2_el_setval_t el

M2_EL_FN_DEF(m2_el_radio_fn);
#define M2_RADIO(el,fmt,variable) m2_el_setval_t el M2_SECTION_PROGMEM = { { m2_el_radio_fn, (fmt) }, (variable) }
#define M2_EXTERN_RADIO(el) extern m2_el_setval_t el


struct _m2_el_combo_struct
{
  m2_el_setval_t setval;
  uint8_t cnt;
  m2_get_str_fnptr get_str_fnptr;
};
typedef struct _m2_el_combo_struct m2_el_combo_t;
typedef m2_el_combo_t *m2_el_combo_p;

M2_EL_FN_DEF(m2_el_combo_fn);
#define M2_COMBO(el,fmt,variable,cnt,fnptr) m2_el_combo_t el M2_SECTION_PROGMEM = { { { m2_el_combo_fn, (fmt) }, (variable) }, (cnt), (fnptr) }
#define M2_EXTERN_COMBO(el) extern m2_el_combo_t el

uint8_t m2_el_combo_get_len(m2_el_fnarg_p fn_arg) M2_NOINLINE;
m2_get_str_fnptr m2_el_combo_get_str_fnptr(m2_el_fnarg_p fn_arg) M2_NOINLINE;
const char *m2_el_combo_get_str(m2_el_fnarg_p fn_arg, uint8_t idx) M2_NOINLINE;
uint8_t m2_el_combo_get_max_len_idx(m2_el_fnarg_p fn_arg) M2_NOINLINE;

/* slbase.c */

struct _m2_el_slbase_struct
{
  m2_el_fnfmt_t ff;
  uint8_t *top;		/* index number of the top most line, which is visible */
  uint8_t *len;		/* total number of lines */
};
typedef struct _m2_el_slbase_struct m2_el_slbase_t;
typedef m2_el_slbase_t *m2_el_slbase_p;

M2_EL_FN_DEF(m2_el_vsb_fn);
#define M2_VSB(el,fmt,first,cnt) m2_el_slbase_t el M2_SECTION_PROGMEM = { { m2_el_vsb_fn, (fmt) }, (first), (cnt) }
#define M2_EXTERN_VSB(el) extern m2_el_slbase_t el

struct _m2_el_strlist_struct
{
  m2_el_slbase_t slbase;
  m2_strlist_cb_fnptr strlist_cb_fnptr;
};
typedef struct _m2_el_strlist_struct m2_el_strlist_t;
typedef m2_el_strlist_t *m2_el_strlist_p;

M2_EL_FN_DEF(m2_el_strlist_fn);
#define M2_STRLIST(el,fmt,first,cnt,fnptr) m2_el_strlist_t el M2_SECTION_PROGMEM = { { { m2_el_strlist_fn, (fmt) }, (first), (cnt) }, (fnptr) }
#define M2_EXTERN_STRLIST(el) extern m2_el_strlist_t el


struct _m2_el_infobase_struct
{
  m2_el_slbase_t slbase;
  m2_button_fnptr select_callback;
};
typedef struct _m2_el_infobase_struct m2_el_infobase_t;
typedef m2_el_infobase_t *m2_el_infobase_p;


struct _m2_el_info_struct
{
  m2_el_infobase_t infobase;
  const char *info_str;
};
typedef struct _m2_el_info_struct m2_el_info_t;
typedef m2_el_info_t *m2_el_info_p;

struct _m2_el_infop_struct
{
  m2_el_infobase_t infobase;
  m2_rom_char_p info_str;
};
typedef struct _m2_el_infop_struct m2_el_infop_t;
typedef m2_el_infop_t *m2_el_infop_p;

M2_EL_FN_DEF(m2_el_info_fn);
#define M2_INFO(el,fmt,first,cnt,str,cb) m2_el_info_t el M2_SECTION_PROGMEM = { { { { m2_el_info_fn, (fmt) }, (first), (cnt) }, (cb)}, (str) }
#define M2_EXTERN_INFO(el) extern m2_el_info_t el

M2_EL_FN_DEF(m2_el_infop_fn);
#define M2_INFOP(el,fmt,first,cnt,str,cb) m2_el_infop_t el M2_SECTION_PROGMEM = { { { { m2_el_infop_fn, (fmt) }, (first), (cnt) }, (cb)}, (str) }
#define M2_EXTERN_INFOP(el) extern m2_el_infop_t el

/*==============================================================*/
/* m2nav....c */

struct _m2_nav_struct
{
  /* stores pointers to nested elements */
#ifdef __unix__
  m2_el_fnfmt_p element_list[M2_DEPTH_MAX];
#else
  m2_rom_void_p element_list[M2_DEPTH_MAX];
#endif
  
  /* local copy of the element fmt structure, automatically updated */
  /* probably only used because of the attrib value */
  /* not required, the "go up" functionality has been replaced by m2_el_str_up_fn
  m2_fmt_t fmt;
 */
  
  /* if the corresponding element at the same depth is a container, then */
  /* this array contains the index of the current child */
  uint8_t pos[M2_DEPTH_MAX];
  
  /* the current depth */
  /* 0: the nav structure is empty and there are no elements (array el is empty) */
  /* 1: there is one element at array position 0 (el[0]), "next" is not possible, because there is no parent */
  /* 2: el[0] and el[1] are valid, e[0] is the parent and pos[0] is the child position */
  uint8_t depth;

  /* is data entry mode active */
  /* only used for event handlers which need a separate data entry mode */
  /* however, this is information is also passed to the drawing functions */
  /* do not confuse this with m2_nav_is_data_entry(), which checks the */
  /* basic ability of an element to switch to data entry */
  uint8_t is_data_entry_active;
  
  /* can be set to change the root node of the tree */
  m2_rom_void_p new_root_element;
};


m2_rom_void_p m2_nav_get_current_element(m2_nav_p nav) M2_NOINLINE;	/* m2navutl.c */
m2_rom_void_p m2_nav_get_parent_element(m2_nav_p nav) M2_NOINLINE;	/* m2navutl.c */
void m2_nav_prepare_fn_arg_current_element(m2_nav_p nav) M2_NOINLINE; /* m2navutl.c */
void m2_nav_prepare_fn_arg_parent_element(m2_nav_p nav) M2_NOINLINE;  /* m2navutl.c */

void m2_nav_send_new_focus(m2_nav_p nav) M2_NOINLINE;			/* m2navutl.c */
uint8_t m2_nav_is_read_only(m2_nav_p nav) M2_NOINLINE;			/* m2navutl.c */
uint8_t m2_nav_is_auto_skip(m2_nav_p nav) M2_NOINLINE;			/* m2navutl.c */
uint8_t m2_nav_is_parent_auto_skip(m2_nav_p nav) M2_NOINLINE;		/* m2navutl.c */
uint8_t m2_nav_get_list_len(m2_nav_p nav) M2_NOINLINE;			/* m2navutl.c */
uint8_t m2_nav_get_parent_list_len(m2_nav_p nav) M2_NOINLINE;			/* m2navutl.c */
void m2_nav_load_child(m2_nav_p nav, uint8_t pos) M2_NOINLINE;	/* m2navutl.c */
uint8_t m2_nav_is_data_entry(m2_nav_p nav) M2_NOINLINE;			/* m2navutl.c */
uint8_t m2_nav_get_child_pos(m2_nav_p nav) M2_NOINLINE;		/* m2navutl.c */


void m2_nav_init(m2_nav_p nav,  m2_rom_void_p element) M2_NOINLINE; /* m2navinit.c */

void m2_nav_set_root(m2_nav_p nav,  m2_rom_void_p element) M2_NOINLINE; 	/* m2navroot.c */
/*void m2_nav_set_root(m2_nav_p nav,  m2_attrib_element_p ae);*/	/* m2navroot.c */
uint8_t m2_nav_check_and_assign_new_root(m2_nav_p nav) M2_NOINLINE;		/* m2navroot.c */


uint8_t m2_nav_up(m2_nav_p nav) M2_NOINLINE;							/* m2navupdn.c */
uint8_t m2_nav_down(m2_nav_p nav, uint8_t is_msg) M2_NOINLINE;			/* m2navupdn.c */
uint8_t m2_nav_do_auto_up(m2_nav_p nav) M2_NOINLINE;					/* m2navupdn.c */
uint8_t m2_nav_do_auto_down(m2_nav_p nav) M2_NOINLINE;				/* m2navupdn.c */

uint8_t m2_nav_prev(m2_nav_p nav) M2_NOINLINE;						/* m2navprev.c */
uint8_t m2_nav_next(m2_nav_p nav) M2_NOINLINE;						/* m2navnext.c */
uint8_t m2_nav_first(m2_nav_p nav) M2_NOINLINE;						/* m2navfirst.c */
uint8_t m2_nav_last(m2_nav_p nav) M2_NOINLINE;						/* m2navlast.c */
uint8_t m2_nav_data_up(m2_nav_p nav) M2_NOINLINE;						/* m2navdataup.c */
uint8_t m2_nav_data_down(m2_nav_p nav) M2_NOINLINE;					/* m2navdatadn.c */


uint8_t m2_el_parent_get_font(m2_nav_p nav) M2_NOINLINE;				/* m2elsubutl.c */


/*==============================================================*/
/* graphics structs */

/* position */
struct _m2_pos_struct
{
  uint8_t x;
  uint8_t y;
};
typedef struct _m2_pos_struct m2_pos_t;
typedef struct _m2_pos_struct *m2_pos_p;

/* parent child box, used as argument for M2_EL_MSG_GET_LIST_BOX */
struct _m2_pcbox_struct
{
  /* M2_EL_MSG_GET_LIST_BOX: "p" should be read only */
  m2_pos_t p;
  /* M2_EL_MSG_GET_LIST_BOX: "c" should be filled with suitable values */
  m2_pos_t c;
};
typedef struct _m2_pcbox_struct m2_pcbox_t;
typedef struct _m2_pcbox_struct *m2_pcbox_p;


/*==============================================================*/
/* Event Processing, */


/* must be power of 2 */
#define M2_KEY_QUEUE_LEN 4
struct _m2_struct
{
  m2_nav_t nav;		/* current focus */
  m2_eh_fnptr eh;		/* event handler, processes a key pressed event */
  m2_es_fnptr es;		/* event source, produces and returnes an event */
  m2_gfx_fnptr gh;		/* graphics handler */
  uint8_t forced_key; 	/* additional key, which will be processed by the next call to m2_Step() */
  uint8_t is_frame_draw_at_end;
  
  /* internal values for the debounce algorithm */
  uint8_t detected_key_code;
  uint8_t detected_key_timer;
  uint8_t debounce_state; 
  /* result from the debounce algorithm */
  //uint8_t pressed_key_code;
  
  /* key queue */
  uint8_t key_queue_array[M2_KEY_QUEUE_LEN];
  uint8_t key_queue_pos;
  uint8_t key_queue_len;
};

#define M2_DEBOUNCE_STATE_WAIT_FOR_KEY_PRESS 	0
#define M2_DEBOUNCE_STATE_PRESS				1
#define M2_DEBOUNCE_STATE_WAIT_FOR_KEY_RELEASE	2
#define M2_DEBOUNCE_STATE_RELEASE				3


m2_nav_p m2_get_nav(m2_p m2);											/* m2utl.c */


/* messages for the event handler callback procedure */
#define M2_EP_MSG_SELECT M2_KEY_SELECT
#define M2_EP_MSG_NEXT M2_KEY_NEXT
#define M2_EP_MSG_PREV M2_KEY_PREV
#define M2_EP_MSG_EXIT M2_KEY_EXIT
#define M2_EP_MSG_DATA_UP M2_KEY_DATA_UP
#define M2_EP_MSG_DATA_DOWN M2_KEY_DATA_DOWN

/* messages for the event source callback procedure */
/* request to return a key value */
/* option 1: no EVENT bit set: return an unbounced raw value from the hardware */
/* option 2: EVENT bit set: Suppress debounce and pass this event directly to the event queue */

#define M2_ES_MSG_GET_KEY 0
/* first call to the event source handler is this message */
#define M2_ES_MSG_INIT 1


/*==============================================================*/
uint8_t m2_nav_user_up(m2_nav_p nav) M2_NOINLINE;						/* m2usrupdn.c */
uint8_t m2_nav_user_down(m2_nav_p nav, uint8_t is_msg) M2_NOINLINE;		/* m2usrupdn.c */
uint8_t m2_nav_user_prev(m2_nav_p nav) M2_NOINLINE;					/* m2usrprev.c */
uint8_t m2_nav_user_first(m2_nav_p nav) M2_NOINLINE;						/* m2usrsnext.c */
uint8_t m2_nav_user_next(m2_nav_p nav) M2_NOINLINE;					/* m2usrsnext.c */



/*==============================================================*/
/* mnufnarg.c */
/* Note: These functions are not reentrant: Do not use within field functions */
void m2_fn_arg_clear(void) M2_NOINLINE;
void m2_fn_arg_set_element(m2_rom_void_p element) M2_NOINLINE;
void m2_fn_arg_set_arg_data(uint8_t arg, void *data) M2_NOINLINE;
void m2_fn_arg_set_pos(uint8_t pos) M2_NOINLINE;
void m2_fn_arg_set_nav(m2_nav_p nav) M2_NOINLINE;
uint8_t m2_fn_arg_call(uint8_t msg) M2_NOINLINE;

/* Reentrant procedures */
uint8_t m2_fn_get_width(m2_rom_void_p element) M2_NOINLINE;								/* m2fnarg.c */
uint8_t m2_fn_get_height(m2_rom_void_p element) M2_NOINLINE;								/* m2fnarg.c */

/*==============================================================*/
/* m2ellistbase.c list base functions*/
uint8_t m2_el_list_get_len(m2_el_fnarg_p fn_arg) M2_NOINLINE;									/* m2ellistbase.c */
uint8_t m2_el_list_get_len_by_element(m2_rom_void_p element) M2_NOINLINE;						/* m2ellistbase.c */
m2_rom_void_p m2_el_list_get_child(m2_rom_void_p element, uint8_t idx) M2_NOINLINE;			/* m2ellistbase.c */
uint8_t m2_el_list_get_child_size(m2_rom_void_p element, uint8_t is_height, uint8_t idx) M2_NOINLINE;	/* m2ellistbase.c */
uint8_t m2_el_list_opt_get_val_zero_default(m2_rom_void_p element, char cmd) M2_NOINLINE;			/* m2ellistbase.c */
uint8_t m2_el_listbase_fn(m2_el_fnarg_p fn_arg) M2_NOINLINE;									/* m2ellistbase.c */

uint8_t m2_el_calc_child_fn(m2_rom_void_p element, uint8_t start, uint8_t end, uint8_t is_height, uint8_t is_sum) M2_NOINLINE;	/* m2ellistcalc.c */
uint8_t m2_expand_direction(m2_rom_void_p element, uint8_t in, uint8_t optchar) M2_NOINLINE;						/* m2ellistcalc.c */

/*==============================================================*/
uint8_t m2_el_u8_get_max(m2_el_fnarg_p fn_arg) M2_NOINLINE;								/* m2elu8base.c */
uint8_t m2_el_u8_get_min(m2_el_fnarg_p fn_arg) M2_NOINLINE;								/* m2elu8base.c */
uint8_t *m2_el_u8_get_val_ptr(m2_el_fnarg_p fn_arg) M2_NOINLINE;							/* m2elu8base.c */


/*==============================================================*/
char *m2_el_str_get_str(m2_el_fnarg_p fn_arg) M2_NOINLINE;									/* m2elstr.c */

/*==============================================================*/
char *m2_el_strptr_get_str(m2_el_fnarg_p fn_arg) M2_NOINLINE;									/* m2elstrptr.c */



/*==============================================================*/
m2_rom_char_p m2_el_fnfmt_get_fmt_by_element(m2_rom_void_p element) M2_NOINLINE;			/* m2elfnfmt.c */
m2_rom_char_p m2_el_fnfmt_get_fmt(const m2_el_fnarg_p fn_arg) M2_NOINLINE;					/* m2elfnfmt.c */
uint8_t m2_el_fmfmt_opt_get_val_zero_default(const m2_el_fnarg_p fn_arg, uint8_t c) M2_NOINLINE;		/* m2elfnfmt.c */
uint8_t m2_el_fmfmt_opt_get_val_any_default(const m2_el_fnarg_p fn_arg, uint8_t c, uint8_t default_value);	/* m2elfnfmt.c */
uint8_t m2_el_fmfmt_opt_get_val_any_by_element(m2_rom_void_p element, uint8_t c, uint8_t default_value); /* m2elfnfmt.c */
uint8_t m2_el_fmfmt_opt_get_a_one_default(const m2_el_fnarg_p fn_arg) M2_NOINLINE;					/* m2elfnfmt.c */
uint8_t m2_el_fmfmt_get_font(const m2_el_fnarg_p fn_arg) M2_NOINLINE;							/* m2elfnfmt.c */
uint8_t m2_el_fmfmt_get_font_by_element(m2_rom_void_p element) M2_NOINLINE;						/* m2elfnfmt.c */

uint8_t m2_opt_get_hH(m2_rom_char_p str) M2_NOINLINE;									/* m2elfnfmt.c */
uint8_t m2_el_fnfmt_get_hH(const m2_el_fnarg_p fn_arg) M2_NOINLINE;							/* m2elfnfmt.c */
uint8_t m2_el_fnfmt_get_hH_by_element(m2_rom_void_p element) M2_NOINLINE;					/* m2elfnfmt.c */
uint8_t m2_opt_get_wW(m2_rom_char_p str) M2_NOINLINE;									/* m2elfnfmt.c */
uint8_t m2_el_fnfmt_get_wW(const m2_el_fnarg_p fn_arg) M2_NOINLINE;						/* m2elfnfmt.c */
uint8_t m2_el_fnfmt_get_wW_by_element(m2_rom_void_p element) M2_NOINLINE;					/* m2elfnfmt.c */


/*==============================================================*/
#define M2_EL_SLBASE_ILLEGAL 255

uint8_t *m2_el_slbase_get_len_ptr(m2_rom_void_p element) M2_NOINLINE;						/* m2elslbase.c */
uint8_t m2_el_slbase_get_len(m2_rom_void_p element) M2_NOINLINE;							/* m2elslbase.c */
uint8_t *m2_el_slbase_get_top_ptr(m2_rom_void_p element) M2_NOINLINE;						/* m2elslbase.c */
uint8_t m2_el_slbase_get_top(m2_rom_void_p element) M2_NOINLINE;							/* m2elslbase.c */
uint8_t m2_el_slbase_get_visible_lines(m2_rom_void_p element) M2_NOINLINE;					/* m2elslbase.c */
uint8_t m2_el_slbase_get_visible_pos(m2_rom_void_p element, uint8_t idx) M2_NOINLINE;			/* m2elslbase.c */
uint8_t m2_el_slbase_calc_height(m2_rom_void_p element) M2_NOINLINE;						/* m2elslbase.c */
uint8_t m2_el_slbase_calc_width(m2_rom_void_p element) M2_NOINLINE;						/* m2elslbase.c */
void m2_el_slbase_adjust_top_to_focus(m2_rom_void_p element, uint8_t pos) M2_NOINLINE;			/* m2elslbase.c */
void m2_el_slbase_adjust_top_to_cnt(m2_rom_void_p element) M2_NOINLINE;						/* m2elslbase.c */
uint8_t m2_el_slbase_calc_box(m2_rom_void_p el_slbase, uint8_t idx, m2_pcbox_p data);			/* m2elslbase.c */
void m2_el_slbase_show(m2_el_fnarg_p fn_arg, const char *s);								/* m2elslbase.c */

/*==============================================================*/
uint8_t *m2_el_setval_get_val_ptr(m2_el_fnarg_p fn_arg) M2_NOINLINE;							/* m2elsetval.c */


/*==============================================================*/
/* helper procedures for the graphics handler */
uint8_t m2_utl_sb_get_slider_height(uint8_t height, uint8_t total, uint8_t visible);					/* m2elsb.c */
uint8_t m2_utl_sb_get_slider_position(uint8_t height, uint8_t slider, uint8_t total, uint8_t visible, uint8_t top); /* m2elsb.c */

/*==============================================================*/
/* m2gfx.c */

struct _m2_gfx_arg
{
  uint8_t msg;
  uint8_t x;
  uint8_t y;
  uint8_t w;
  uint8_t h;
  uint8_t font;
  uint8_t icon;
  uint8_t total;		/* scroll bar: total number of items */
  uint8_t top;		/* scroll bar: topmost item (first visible item) 0 .. total-visible*/
  uint8_t visible;	/* scroll bar: number of visible items 0 .. total-1 */
  const char *s;
};



void m2_gfx_init(m2_gfx_fnptr fnptr);
void m2_gfx_start(m2_gfx_fnptr fnptr);
void m2_gfx_hline(uint8_t x0, uint8_t y0, uint8_t w);
void m2_gfx_vline(uint8_t x0, uint8_t y0, uint8_t h);
void m2_gfx_box(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h);

void m2_gfx_text(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, uint8_t font, const char *s);
void m2_gfx_text_p(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, uint8_t font, const char *s);

void m2_gfx_normal_no_focus(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, uint8_t font);
void m2_gfx_normal_focus(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, uint8_t font);
/* used only of there is also a small focus */
void m2_gfx_normal_parent_focus(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, uint8_t font);
void m2_gfx_small_focus(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, uint8_t font);
void m2_gfx_normal_data_entry(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, uint8_t font);
void m2_gfx_small_data_entry(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, uint8_t font);
void m2_gfx_go_up(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, uint8_t font);

uint8_t m2_gfx_get_text_width(uint8_t font, const char *s);				/* used for lables and buttons */
uint8_t m2_gfx_get_text_width_p(uint8_t font, const char *s);
uint8_t m2_gfx_get_char_width(uint8_t font);			
uint8_t m2_gfx_get_char_height(uint8_t font);

uint8_t m2_gfx_add_normal_border_height(uint8_t font, uint8_t height);
uint8_t m2_gfx_add_normal_border_width(uint8_t font, uint8_t width);
uint8_t m2_gfx_add_normal_border_x(uint8_t font, uint8_t x);
uint8_t m2_gfx_add_normal_border_y(uint8_t font, uint8_t y);

uint8_t m2_gfx_add_small_border_height(uint8_t font, uint8_t height);
uint8_t m2_gfx_add_small_border_width(uint8_t font, uint8_t width);
uint8_t m2_gfx_add_small_border_x(uint8_t font, uint8_t x);
uint8_t m2_gfx_add_small_border_y(uint8_t font, uint8_t y);

uint8_t m2_gfx_add_readonly_border_height(uint8_t font, uint8_t height);
uint8_t m2_gfx_add_readonly_border_width(uint8_t font, uint8_t width);
uint8_t m2_gfx_add_readonly_border_x(uint8_t font, uint8_t x);
uint8_t m2_gfx_add_readonly_border_y(uint8_t font, uint8_t y);

uint8_t m2_gfx_get_list_overlap_height(void);
uint8_t m2_gfx_get_list_overlap_width(void);

/* ACTIVE and INACTIVE icons must have the same dimension, */
/* this means m2_gfx_get_icon_xxx must return the same values for ACTIVE and INACTIVE */
#define M2_ICON_TOGGLE_ACTIVE 1
#define M2_ICON_TOGGLE_INACTIVE 2 
#define M2_ICON_RADIO_ACTIVE 3
#define M2_ICON_RADIO_INACTIVE 4

void m2_gfx_draw_icon(uint8_t x0, uint8_t y0, uint8_t font, uint8_t icon_number);
uint8_t m2_gfx_get_icon_height(uint8_t font, uint8_t icon_number);
uint8_t m2_gfx_get_icon_width(uint8_t font, uint8_t icon_number);

uint8_t m2_gfx_is_frame_draw_at_end(void);

void m2_gfx_end(void);
void m2_gfx_set_font(m2_gfx_fnptr fnptr, uint8_t font_idx, const void *font_ptr);

uint8_t m2_gfx_get_display_width(void);
uint8_t m2_gfx_get_display_height(void);


/*==============================================================*/

void m2_gfx_draw_text_add_normal_border_offset(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, uint8_t font, const char *s); /* m2gfxutl.c */
void m2_gfx_draw_text_add_small_border_offset(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, uint8_t font, const char *s); /* m2gfxutl.c */
void m2_gfx_draw_text_add_readonly_border_offset(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, uint8_t font, const char *s); /* m2gfxutl.c */
void m2_gfx_draw_text_p_add_readonly_border_offset(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, uint8_t font, const char *s); /* m2gfxutl.c */

void m2_gfx_draw_vertical_scroll_bar(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, uint8_t total, uint8_t top, uint8_t visible);


void m2_gfx_draw_icon_add_normal_border_offset(uint8_t x0, uint8_t y0, uint8_t font, uint8_t icon_number) M2_NOINLINE;	/* m2gfxutl.c */
uint8_t m2_gfx_get_char_height_with_small_border(uint8_t font) M2_NOINLINE;											/* m2gfxutl.c */
uint8_t m2_gfx_get_char_width_with_small_border(uint8_t font) M2_NOINLINE;											/* m2gfxutl.c */
uint8_t m2_gfx_get_char_height_with_normal_border(uint8_t font) M2_NOINLINE;											/* m2gfxutl.c */
uint8_t m2_gfx_get_char_width_with_normal_border(uint8_t font) M2_NOINLINE;											/* m2gfxutl.c */


/*==============================================================*/
void m2_SetPin(uint8_t key, uint8_t pin);				/* m2pin.c */
uint8_t m2_GetPin(uint8_t key);						/* m2pin.c */
uint8_t m2_IsPinAssigned(uint8_t key);					/* m2pin.c */


/*==============================================================*/
uint8_t m2_align_get_max_height(m2_el_fnarg_p fn_arg, uint8_t size);		/* m2align.c */
uint8_t m2_align_get_max_width(m2_el_fnarg_p fn_arg, uint8_t size);		/* m2align.c */



#ifdef __cplusplus
}
#endif


#endif /* _M2_H */

