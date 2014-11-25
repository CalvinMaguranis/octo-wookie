#ifndef __AUDIO_CHUNK_H
#define __AUDIO_CHUNK_H

#if defined(_WIN32) || defined(_WIN64)
	#pragma once
#endif

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

namespace ow
{
	class audio_chunk
	{
	public:
		audio_chunk() : chn_pref(-1), vol(128) {}

		audio_chunk(std::string chunk, int channel = -1) {
			load(chunk);
			chn_pref = channel;
		}

		audio_chunk(int channel) { 
			chn_pref = channel;
			c = Mix_GetChunk(channel); 
		}

		void load(std::string chunk) {
			free();
			c = Mix_LoadWAV(chunk.c_str());
		}

		void play(int loops=0) {
			if (c != NULL) {
				cur_chn = Mix_PlayChannel(chn_pref, c, loops);
			}
		}
		bool is_playing() { return Mix_Playing(cur_chn) > 0 ? true : false; }
		void stop() { Mix_HaltChannel(cur_chn); }
		void pause() { Mix_Pause(cur_chn); }
		bool is_paused() { return Mix_Paused(cur_chn) > 0 ? true : false; }
		void resume() { Mix_Resume(cur_chn); }

		void volume(int v) { Mix_VolumeChunk(c, v); }
		int get_volume() { return vol; }
		void channel(int channel) { 
			chn_pref = channel; 
			cur_chn = channel;
		}

	private:
		Mix_Chunk *c;
		int chn_pref;
		int cur_chn;

		int vol;

		void free() {
			if (c != NULL) {
				Mix_FreeChunk(c);
				c = NULL;
			}
			chn_pref = -1;
			cur_chn = 0;
		}

		~audio_chunk() { free(); }
	};

} // namespace ow

#endif // __AUDIO_CHUNK_H