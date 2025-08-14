#include "Sound.h"

#include "../FrameCore/Log.h"

#include <sndfile.h>
#include <AL/al.h>

namespace Frame {

	CSound::CSound(const char * filename, bool stereoToMono_ifItIsStereo) {
		SF_INFO sfInfo {};
		sfInfo.format = 0;
		SNDFILE * sndFile = sf_open(filename, SFM_READ, & sfInfo);

		if(!sndFile) {
			Log::Log(Log::ELevel::Error, "Failed to open sound file %s. Error message: %s", filename, sf_strerror(sndFile));
			return;
		}

		alGenBuffers(1, & m_bufferId);
		if(ALenum error = alGetError(); error != AL_NO_ERROR) {
			Log::Log(Log::ELevel::Error, "Sound file %s: Failed to generate OpenAL buffer: %s", filename, alGetString(error));
			return;
		}

		int format = 0;
		switch(sfInfo.channels) {
		case 1:
			format = AL_FORMAT_MONO16;
			break;
		case 2:
			format = AL_FORMAT_STEREO16;
			break;
		}

		if(!format) {
			Log::Log(Log::ELevel::Error, "Failed to open sound file %s. Unknown channels: %d", filename, sfInfo.channels);
			return;
		}

		sf_count_t totalSamples = sfInfo.frames * sfInfo.channels;
		short * data = new short[totalSamples] {};

		sf_count_t readCount = sf_read_short(sndFile, data, totalSamples);
		if(readCount != totalSamples) {
			Log::Log(Log::ELevel::Error, "Sound file %s: Failed to read all frames: read %ld/%ld", filename, readCount, totalSamples);
		}

		int channels = sfInfo.channels;

		// 立体声转单声道
		// Stereo to Mono
		if(stereoToMono_ifItIsStereo && format == AL_FORMAT_STEREO16) {
			totalSamples /= 2;
			short * monoData = new short[totalSamples];
			for(sf_count_t i = 0; i < totalSamples; i++) {
				int mixed = (data[i * 2] + data[i * 2 + 1]) / 2;
				monoData[i] = static_cast<short>(mixed);
			}
			delete[] data;
			data = monoData;
			format = AL_FORMAT_MONO16;
			channels = 1;
		}

		alBufferData(m_bufferId, format, data, static_cast<ALsizei>(sfInfo.frames * channels * sizeof(* data)), sfInfo.samplerate);
		if(ALenum error = alGetError(); error != AL_NO_ERROR) {
			Log::Log(Log::ELevel::Error, "Sound file %s: Failed to fill OpenAL buffer: %s", filename, alGetString(error));
		}
		
		sf_close(sndFile);
		delete[] data;
	}

	CSound::~CSound() {
		alDeleteBuffers(1, & m_bufferId);
	}

}