#include QMK_KEYBOARD_H
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
// Layer shorthand
#define _BL 0
#define _LW 1
#define _RS 2
#define _DT 3

#undef OLED_FONT_WIDTH
#define OLED_FONT_WIDTH 10

enum layer_keycodes {
    QWERTY = SAFE_RANGE, LOWER, RAISE, DOTA
};

bool dota_layer = false;
bool tap = false;

static uint16_t dota_timer, lower_timer, raise_timer;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_BL] = LAYOUT_ortho_4x12(
   KC_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_MINS,        KC_EQL, KC_6, KC_7,  KC_8,     KC_9, KC_0,   KC_BSPC,  \
   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_HOME,        KC_END, KC_Y, KC_U,  KC_I,     KC_O, KC_P,   KC_BSLS,  \
   KC_GRV,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC,        KC_RBRC,  KC_H, KC_J,  KC_K,     KC_L, KC_SCLN,KC_QUOT,  \
   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_RPRN,        KC_LT,  KC_N, KC_M,  KC_COMMA, KC_DOT ,KC_SLSH,KC_RSFT,  \
   KC_LCPO, KC_PSCR, KC_LGUI, KC_LALT, KC_LCTL, LOWER,   KC_DEL,         KC_ENT, RAISE, KC_RALT, KC_LEFT,   KC_DOWN, KC_UP,KC_RGHT\
),

[_LW] = LAYOUT_ortho_4x12(
   DOTA,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,   KC_MINS,        KC_EQL, KC_F6, KC_F7,  KC_F8,     KC_F9, KC_F10,   KC_BSPC,  \
   KC_TAB,KC_Q,    KC_UP,   KC_E,    KC_R,    KC_T,    KC_HOME,        KC_END, KC_Y, KC_P7,  KC_P8,  KC_P9, KC_P,   KC_BSLS,  \
   KC_ESC,KC_LEFT, KC_DOWN, KC_RGHT, KC_F,    KC_G,    KC_LBRC,        KC_RBRC,  KC_H, KC_P4,  KC_P5,KC_P6, KC_SCLN,KC_QUOT,  \
   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,    KC_RPRN,        KC_LT,  KC_N, KC_P1,  KC_P2, KC_P3 ,KC_SLSH,KC_RSFT,  \
   KC_LCPO, KC_PSCR, KC_LGUI, KC_LALT, KC_LCTL, LOWER,   KC_DEL,         KC_ENT, RAISE, KC_RALT, KC_P0,   KC_DOWN, KC_UP,KC_RGHT\
),

[_RS] = LAYOUT_ortho_4x12(
   DOTA,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    LOWER, KC_X,KC_X, \
   KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,KC_X,KC_X,  \
   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,KC_X,KC_X,  \
   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,KC_X,KC_X,  \
   KC_LCTL,  KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,KC_X,KC_X  \
),
[_DT] = LAYOUT_ortho_4x12(
   DOTA,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_F1, KC_DEL, KC_6,  KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,  \
   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_ENT, KC_DEL, KC_Y,  KC_U,    KC_I,    KC_O,    KC_P,    LOWER,  \
   KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_Y,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,KC_X,KC_LPRN,  \
   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_M,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,KC_X,KC_RPRN,  \
   KC_LCTL,  KC_LGUI, KC_LALT, KC_B,  KC_LALT,  KC_SPC,  KC_C,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, RAISE,LOWER\
)
};

void matrix_init_user(void) {
    oled_on();
    oled_clear();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case LOWER:
      if(record->event.pressed){
        lower_timer = timer_read();
        layer_on(_LW);
        tap=false;
      }else{
        layer_off(_LW);
        //if I release  the layer key without pressing any other key,
        //the tap flag will still be false
        if((tap==false)&&(timer_elapsed(lower_timer) < TAPPING_TERM)){
            tap_code(KC_SPC);
        }
      }
      return false;
      break;
    case RAISE:
      if(record->event.pressed){
        raise_timer = timer_read();
        layer_on(_RS);
        tap=false;
      }else{
        layer_off(_RS);
        //if I release  the layer key without pressing any other key,
        //the tap flag will still be false
        if((tap==false)&&(timer_elapsed(raise_timer) < TAPPING_TERM)){
            tap_code(KC_SPC);
        }
      }
      return false;
      break;

    case DOTA:
      if(record->event.pressed){
        dota_timer = timer_read();
        if(!dota_layer){
            dota_layer=true;
            layer_on(_DT);
        }else{
            tap_code(KC_ESC);
        }
      }else{
        if (timer_elapsed(dota_timer) > TAPPING_TERM*2) {  
            dota_layer=false;
            layer_off(_DT) ;
        }
      }
      return false;
      break;

    default:
        tap = true;//if tap something, tap is true
      break;
    }
  return true;
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;  // flips the display 180 degrees if offhand
}

#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {
  // Host Keyboard Layer Status
  if (is_keyboard_master()) {
      oled_write_P(PSTR("-----\nlayer\n-----\n"), false);
      switch (biton32(layer_state)) {
        case _BL:
          oled_write_P(PSTR("  D\n  E\n  F\n  A\n  U\n  L\n  T"), false);
          break;
        case _LW:
          oled_write_P(PSTR("  L\n  O\n  W\n  E\n  R\n   \n   "), false);
          break;
        case _RS:
          oled_write_P(PSTR("  R\n  A\n  I\n  S\n  E\n   \n   "), false);
          break;
        case _DT:
          oled_write_P(PSTR("DOTA\nDOTA\nDOTA"), false);
          //nder_logo(); 
          break;
          // Or use the write_ln shortcut over adding '\n' to the end of your string
        default:
          oled_clear();
          break;
      }
  }else{
         oled_write_P(PSTR(" ___ \n|[_]|\n|+ ;|\n`---'"), false);
  }
}

  // Host Keyboard LED Status
//  uint8_t led_usb_state = host_keyboard_leds();
  //oled_write_P(led_usb_state & (1<<USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
  //oled_write_P(led_usb_state & (1<<USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
  //oled_write_P(led_usb_state & (1<<USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
#endif