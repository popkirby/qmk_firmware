/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

enum {
    _DEFAULT = 0,
    _LOWER,
    _RAISE,
    _MOUSE,
    _SCROLL,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [_DEFAULT] = LAYOUT_universal(
    KC_TAB         , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                        KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_MINUS   ,
    LCTL_T(KC_ESC) , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                        KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_QUOT  ,
    KC_LSFT        , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                                        KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_RSFT  ,
                KC_LALT,KC_LGUI,LGUI_T(KC_TAB)     ,LT(_LOWER,KC_SPC),LT(_SCROLL,KC_ESC),                  KC_BSPC,LT(_RAISE,KC_ENT), RCTL_T(KC_LNG4),     KC_RALT  , KC_PSCR
  ),

  [_LOWER] = LAYOUT_universal(
    _______  ,  KC_EXLM   , KC_AT      , KC_HASH    , KC_DLR     , KC_PERC   ,                                      KC_CIRC  , KC_AMPR     , KC_ASTR    , KC_LPRN    , KC_RPRN   , KC_TILD   ,
    _______  ,  _______   , KC_MS_BTN2 , KC_MS_BTN3 , KC_MS_BTN1 , _______   ,                                      KC_MINS  , KC_EQUAL    , KC_BSLS    , KC_LBRC   , KC_RBRC  , _______   ,
    _______  ,  _______   , _______    , _______    , _______    , _______   ,                                   S(KC_MINS)  , S(KC_EQUAL) , S(KC_BSLS) , S(KC_LBRC)  , S(KC_RBRC)  , _______  ,
                  _______  , _______ , _______  ,         _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),

  [_RAISE] = LAYOUT_universal(
    _______  ,KC_1, KC_2     , KC_3    , KC_4     , KC_5  ,                                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  , KC_GRAVE  ,
    _______  ,KC_F1, KC_F2     , KC_F3    , KC_F4     , KC_F5 ,                                         KC_LEFT  , KC_DOWN  , KC_UP, KC_RIGHT  , KC_COLON  , KC_DQT  ,
    _______  ,KC_F6, KC_F7     , KC_F8    , KC_F9     ,KC_F10,                                        S(KC_MINS),_______, KC_LNG1   ,KC_LNG2,_______,_______,
                  _______     , _______  , _______  ,         _______  , _______  ,                   _______   , _______  , _______       , _______  , _______
  ),

  [_MOUSE] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______ , _______ , _______  ,
    _______  , _______  , KC_MS_BTN2  , KC_MS_BTN3   , KC_MS_BTN1  , _______ ,                                        _______  , _______  , _______  , _______ , _______  , _______  ,
    _______ , _______  , _______  , _______  , _______  , _______ ,                                        _______  , _______ , _______ , _______  , _______  , _______ ,
                  _______    , _______  , _______  ,        _______  , _______  ,                   _______  , _______  , _______       , _______  , KC_MS_BTN1
  ),

  [_SCROLL] = LAYOUT_universal(
    RGB_TOG  , _______  , _______  , _______  , _______  , _______  ,                                        RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , KC_MS_BTN2  , KC_MS_BTN3   , KC_MS_BTN1  , SCRL_DVI ,                                        RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , SCRL_DVD ,                                        CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , _______  , KBC_SAVE ,
                  QK_RBT    , KBC_RST  , _______  ,        _______  , _______  ,                   _______  , _______  , _______       , KBC_RST  , QK_RBT
  ),
};
// clang-format on

const rgblight_segment_t PROGMEM _default_layer[] = {};
const rgblight_segment_t PROGMEM _lower_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_PURPLE});
const rgblight_segment_t PROGMEM _raise_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_CYAN});
const rgblight_segment_t PROGMEM _mouse_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_ORANGE});
const rgblight_segment_t PROGMEM _scroll_layer[]  = RGBLIGHT_LAYER_SEGMENTS({0, RGBLED_NUM, HSV_GREEN});

const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(_default_layer, _lower_layer, _raise_layer, _mouse_layer, _scroll_layer);

void keyboard_post_init_user() {
    rgblight_layers = my_rgb_layers;
}

#define DEFINE_RGBLIGHT_LAYER(__state, __layer) rgblight_set_layer_state(__layer, layer_state_cmp(__state, __layer))

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == _SCROLL);

    DEFINE_RGBLIGHT_LAYER(state, _LOWER);
    DEFINE_RGBLIGHT_LAYER(state, _RAISE);
    DEFINE_RGBLIGHT_LAYER(state, _MOUSE);
    DEFINE_RGBLIGHT_LAYER(state, _SCROLL);

    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
}
#endif

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);
}
#endif

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_ESC):
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(_LOWER, KC_SPC):
        case LT(_SCROLL, KC_ESC):
        case LT(_RAISE, KC_ENT):
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}
