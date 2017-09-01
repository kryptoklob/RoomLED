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

uint8_t loading_index = 0;
uint8_t old_mode;

void loading_bar_pal() {

  // Fill up to loading_bar_index with gradient  
  for (int k = 0; k < loading_index; k++) {
    leds[k] 		    = CHSV(this_hue, this_sat, this_bright);
    leds[STRANDLEN - k - 1] = CHSV(this_hue, this_sat, this_bright); 	
  }

  loading_index++;

  if ( loading_index == (STRANDLEN/2 + 20) ) { 
   led_mode = old_mode;
   if ( led_mode == 39 ) { led_mode = 0; }
  }
}

#endif
