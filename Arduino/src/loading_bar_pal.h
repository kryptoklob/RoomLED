#ifndef LOADING_BAR_PAL_H
#define LOADING_BAR_PAL_H

/* Gradient loading bar.
 * Starts slow, speeds up near the middle and ends fast.
 * Uses palletes.
 *
 * Modifiers:
 *  - this_dir
 *  - this_bright
 *  - this_cutoff
 *  - this_rot
 *  - current_palette
 *  - bg_clr
 */

uint8_t loading_index;

void loading_bar_pal() {

  // Fill up to loading_bar_index with gradient  
  
  for (int k = 0; k < loading_index; k++) {
    int this_bright = qsubd(cubicwave8(( k * all_freq ) + this_phase ), this_cutoff);
    leds[k] = CHSV( bg_clr, 255, bg_bri);
    leds[k] += ColorFromPalette(current_palette, this_index, this_bright, current_blending);
    this_index += this_rot;
  }
 
  loading_index++;
  if ( loading_index == STRANDLEN ) { led_mode = default_mode; }
}

#endif
