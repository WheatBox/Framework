#include <FrameAsset/Sound.h>

#include <FrameCore/Log.h>

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

		size_t dataSize = sfInfo.frames * sfInfo.channels * sizeof(short);
		short * data = new short[dataSize] {};
		sf_read_short(sndFile, data, sfInfo.frames);

		// 立体声转单声道
		// Stereo to Mono
		if(stereoToMono_ifItIsStereo && format == AL_FORMAT_STEREO16) {
			dataSize /= 2;
			for(size_t i = 0; i < dataSize; i++) {
				data[i] = data[i * 2] / 2 + data[i * 2 + 1] / 2;
			}
			format = AL_FORMAT_MONO16;
		}

		alBufferData(m_bufferId, format, data, static_cast<ALsizei>(dataSize), sfInfo.samplerate);
		
		sf_close(sndFile);
		delete[] data;
	}

	CSound::~CSound() {
		alDeleteBuffers(1, & m_bufferId);
	}

}