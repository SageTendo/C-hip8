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
 * Handles the sound event for the Chip8 speaker system
 * First checks if the sound timer has reached 0.
 * If so, play the sound.
 * 
 * @param c8 The Chip8 instance
 */
void handle_sound(Chip8 *c8) {
  if (c8->sound_timer == 0) {
    PauseSound(c8->sfx);
    return;
  }

  if (!IsSoundPlaying(c8->sfx))
    PlaySound(c8->sfx);
  else
    ResumeSound(c8->sfx);
}

/**
 * Closes the Chip8 speaker system
 * First unload the SFX Sound.
 * Lastly, closes the audio device.
 * 
 * @param c8 The Chip8 instance
 */
void close_speaker(Chip8 *c8) {
  StopSound(c8->sfx);
  UnloadSound(c8->sfx);
  CloseAudioDevice();
}