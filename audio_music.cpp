#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

#include "audio_music.hpp"

namespace ow
{
	audio_music::audio_music() : vol(128), t(MUS_NONE)
	{
	}

	audio_music::audio_music(std::string music) 
	{
		load(music);
	}

	audio_music::~audio_music()
	{
		free();
	}

	void audio_music::load(std::string music)
	{
		free();
		m = Mix_LoadMUS(music.c_str());
		t = get_type();
	}

	void audio_music::play(int loops)
	{
		if (m != NULL) {
			Mix_PlayMusic(m, loops);
		}
	}

	void audio_music::stop()
	{
		Mix_HaltMusic();
	}

	void audio_music::pause()
	{
		Mix_PauseMusic();
	}
	
	void audio_music::rewind() 
	{
		Mix_RewindMusic();
	}

	void audio_music::resume()
	{
		Mix_ResumeMusic();
	}

	void audio_music::volume(const int v)
	{
		vol = v;
		Mix_VolumeMusic(v);
	}
	
	void audio_music::fade_in(const int loops, const int ms)
	{
		if (m != NULL) {
			Mix_FadeInMusic(m, loops, ms);
		}
	}
	
	void audio_music::fade_out(const int ms)
	{
		Mix_FadeOutMusic(ms);
	}
	
	bool audio_music::playing()
	{
		return Mix_PlayingMusic() > 0 ? true : false;
	}
	
	bool audio_music::paused()
	{
		return Mix_PausedMusic() > 0 ? true : false;
	}

	Mix_MusicType audio_music::get_type()
	{
		return t;
	}
	
	Mix_Fading audio_music::get_fading_status()
	{
		return Mix_FadingMusic();
	}
	
	int audio_music::get_volume()
	{
		return vol;
	}


	void audio_music::free() 
	{
		if (m != NULL) {
			Mix_FreeMusic(m);
			m = NULL;
		}
	}

} // namespace ow