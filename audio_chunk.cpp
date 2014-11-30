#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

#include "audio_chunk.hpp"

namespace ow
{
	audio_chunk::audio_chunk() : chn(-1), vol(128), c(NULL)
	{
	}

	audio_chunk::audio_chunk(std::string chunk, int channel) 
	{
		load(chunk);
		chn = channel;
		vol = 128;
	}

	audio_chunk::~audio_chunk()
	{
		free();
	}

	void audio_chunk::load(std::string chunk, int channel)
	{
		free();
		c = Mix_LoadWAV(chunk.c_str());
		chn = channel;
	}

	void audio_chunk::play(int loops)
	{
		if (c != NULL) {
			chn = Mix_PlayChannel(chn, c, loops);
		}
	}

	void audio_chunk::stop()
	{
		Mix_HaltChannel(chn);
	}

	void audio_chunk::pause()
	{
		Mix_Pause(chn);
	}


	void audio_chunk::resume()
	{
		Mix_Resume(chn);
	}

	void audio_chunk::volume(int v)
	{
		vol = v;
		Mix_VolumeChunk(c, v);
	}

	void audio_chunk::fade_in(int loops, int ms)
	{
		if (c != NULL) {
			Mix_FadeInChannel(chn, c, loops, ms);
		}
	}

	void audio_chunk::fade_out(int ms)
	{
		Mix_FadeOutChannel(chn, ms);
	}


	bool audio_chunk::playing()
	{
		return Mix_Playing(chn) > 0 ? true : false;
	}

	bool audio_chunk::paused()
	{
		return Mix_Paused(chn) > 0 ? true : false;
	}

	int audio_chunk::get_volume()
	{
		return vol;
	}

	Mix_Fading audio_chunk::get_fading_status()
	{
		return Mix_FadingChannel(chn);
	}

	void audio_chunk::channel(int channel)
	{
		chn = channel;
	}

	int audio_chunk::get_channel()
	{
		return chn;
	}

	void audio_chunk::free() 
	{
		if (c != NULL) {
			Mix_FreeChunk(c);
			c = NULL;
		}
		chn = -1;
	}

} // namespace ow