#ifndef MATRIX_PAL_H
#define MATRIX_PAL_H


/* Usage - matrix_pal();
 *  
 *  This is one of the few routines I have with pixel counting.
 *  
 *  
 * current_palette, target_palette
 * this_rot
 * this_index
 * bg_clr
 * bg_bri
 * this_dir
 * this_bright
 */

void matrix_pal() {                                           // One line matrix

  if (this_rot) this_index++;                                   // Increase palette index to change colours on the fly
  
  if (random8(90) > 80) {
    if (this_dir == 0)
      leds[0] = ColorFromPalette(current_palette, this_index, this_bright, current_blending); 
    else
      leds[NUM_LEDS_PER_STRIP-1] = ColorFromPalette( current_palette, this_index, this_bright, current_blending);
  } else {
    if (this_dir == 0)
      leds[0] = CHSV(bg_clr, this_sat, bg_bri); 
    else
      leds[NUM_LEDS_PER_STRIP-1] = CHSV(bg_clr, this_sat, bg_bri);
  }

  if (this_dir == 0) {
    for (int i = NUM_LEDS_PER_STRIP-1; i >0 ; i-- ) leds[i] = leds[i-1];
  } else {
    for (int i = 0; i < NUM_LEDS_PER_STRIP-1 ; i++ ) leds[i] = leds[i+1];
  }

} // matrix_pal()


#endif
