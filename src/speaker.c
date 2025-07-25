#include "speaker.h"

/**
 * Initialises the Chip8 speaker system
 * First initialise the audio device which will play sound.
 * Lastly, loads the SFX resource file and pass it to the Chip8 instance.
 * 
 * @param c8 The Chip8 instance
 */
void init_speaker(Chip8 *c8) {
  InitAudioDevice();
   c8->sfx = LoadSound(SFX);
}

/**
 * Closes the Chip8 speaker system
 * First unload the SFX Sound.
 * Lastly, closes the audio device.
 * 
 * @param c8 The Chip8 instance
 */
void close_speaker(Chip8 *c8) {
  UnloadSound(c8->sfx);
  CloseAudioDevice();
}