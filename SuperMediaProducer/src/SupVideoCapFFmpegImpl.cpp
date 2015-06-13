//implment SupVideoCapFFmpegImpl
//andycai_sc@163.com

#include "SuperMediaProducer/SupVideoCapFFmpegImpl.h"

SupVideoCapFFmpegImpl::SupVideoCapFFmpegImpl(const std::string& videoFormat) :
SupVideoCaptureImpl(videoFormat), m_avFormatCtx(0), m_avInputFormat(0),m_avCodecCtx(0), m_avCodec(0),
m_swsCtx(0), m_videoIndex(-1), m_pictureHandler(0), m_captureActivity(this, &SupVideoCapFFmpegImpl::capturing)
{
}

SupVideoCapFFmpegImpl::~SupVideoCapFFmpegImpl()
{
}

bool SupVideoCapFFmpegImpl::open(const std::string& device)
{
    m_avInputFormat = av_find_input_format(m_videoFormat.c_str());

    if ((avformat_open_input(&m_avFormatCtx, device.c_str(), m_avInputFormat, 0) != 0) &&
        avformat_find_stream_info(m_avFormatCtx, NULL) < 0)
        return false;

    for(int i = 0; i< m_avFormatCtx->nb_streams; i++)
	{
		if (m_avFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			m_videoIndex = i;
		}
	}

	if (m_videoIndex < 0)
        return false;

    m_avCodecCtx = m_avFormatCtx->streams[m_videoIndex]->codec;
	m_avCodec = avcodec_find_decoder(m_avCodecCtx->codec_id);

	if (avcodec_open2(m_avCodecCtx, m_avCodec, NULL) < 0)
	{
		return false;
	}

	m_swsCtx = sws_getContext(m_avCodecCtx->width, m_avCodecCtx->height, m_avCodecCtx->pix_fmt, m_avCodecCtx->width, m_avCodecCtx->height, PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);


    return true;
}

void SupVideoCapFFmpegImpl::capture(SuperPictureHandler* pictureHandler)
{
    m_pictureHandler = pictureHandler;
    m_captureActivity.start();
}

void SupVideoCapFFmpegImpl::stop()
{
    m_captureActivity.stop();
    m_captureActivity.wait();
}

void SupVideoCapFFmpegImpl::capturing()
{
    AVPacket* avPacket = (AVPacket *)av_malloc(sizeof(AVPacket));
	AVFrame* avFrame = avcodec_alloc_frame();
	AVFrame* frameData = avcodec_alloc_frame();

	uint8_t *buffer = (uint8_t *)av_malloc(avpicture_get_size(PIX_FMT_YUV420P, m_avCodecCtx->width, m_avCodecCtx->height));
	avpicture_fill((AVPicture *)frameData, buffer, PIX_FMT_YUV420P, m_avCodecCtx->width, m_avCodecCtx->height);

	int gotPicture = 0;

    int pixSize = m_avCodecCtx->width * m_avCodecCtx->height;
	int yuvSize = pixSize * 3 / 2;
	char* picture = new char[yuvSize];

	while (!m_captureActivity.isStopped())
    {
        if (av_read_frame(m_avFormatCtx, avPacket) >= 0)
		{
			if (avPacket->stream_index == m_videoIndex)
			{
				if (avcodec_decode_video2(m_avCodecCtx, avFrame, &gotPicture, avPacket) <= 0)
				{
					av_free_packet(avPacket);
					continue;
				}

				if (gotPicture > 0)
				{
                    sws_scale(m_swsCtx, (const uint8_t* const*)avFrame->data, avFrame->linesize, 0, m_avCodecCtx->height, frameData->data, frameData->linesize);

					memcpy(picture, frameData->data[0], pixSize);
					memcpy(picture + pixSize, frameData->data[2], pixSize  / 4);
					memcpy(picture + pixSize * 5 / 4 , frameData->data[1], pixSize / 4);

					if (m_pictureHandler)
					{
                        m_pictureHandler->handlePicture(SuperPictureHandler::YUV420P, m_avCodecCtx->width, m_avCodecCtx->height, picture, yuvSize);
					}
                }
			}


			av_free_packet(avPacket);
		}
    }

    av_free(avPacket);
	avcodec_free_frame(&avFrame);

	delete[] picture;
}
