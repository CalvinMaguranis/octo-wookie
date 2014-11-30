#ifndef __AUDIO_CHUNK_H
#define __AUDIO_CHUNK_H

#pragma once

namespace ow
{
	class audio_chunk
	{
	public:
		audio_chunk();
		audio_chunk(std::string chunk, int channel = -1);

		void load(std::string chunk, int channel = -1);

		void play(int loops = 0);
		void stop();
		void pause();
		void resume();
		void volume(int v);
		void channel(int channel);

		void fade_in(int loops, int ms);
		void fade_out(int ms);

		bool playing();
		bool paused();

		
		int get_volume();
		Mix_Fading get_fading_status();
		int get_channel();

	private:
		Mix_Chunk *c;
		int chn;
		int vol;

		void free();

		~audio_chunk();
	};

} // namespace ow

#endif // __AUDIO_CHUNK_H