#ifndef __AUDIO_MUSIC_H
#define __AUDIO_MUSIC_H

#pragma once

namespace ow
{
	class audio_music
	{
	public:
		audio_music();
		audio_music(std::string music);

		void load(std::string music);

		void play(int loops = -1);
		void stop();
		void pause();
		void rewind();
		void resume();
		void volume(const int v);
		
		void fade_in(const int loops, const int ms);
		void fade_out(const int ms);
		
		bool playing();
		bool paused();

		Mix_MusicType get_type();
		Mix_Fading get_fading_status();
		int get_volume();

	private:
		Mix_Music *m;
		Mix_MusicType t;
		int vol;

		void free();

		~audio_music();
	};

} // namespace ow

#endif // __AUDIO_MUSIC_H