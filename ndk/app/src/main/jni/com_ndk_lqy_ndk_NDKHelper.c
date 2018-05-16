//
// Created by 罗秋雨 on 2018/5/11.
//

#include "com_ndk_lqy_ndk_NDKHelper.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/dict.h"
#include "libavutil/mathematics.h"
#include "libavutil/mem.h"

JNIEXPORT jint JNICALL Java_com_lqy_test_NDKHelper_convert
        (JNIEnv *env, jobject thiz, jstring mp4, jstring ts) {
    int res = 0;
    int videoStreamIndex = -1;
    int audioStreamIndex = -1;
    AVBitStreamFilterContext* filterContext = 0;

    const char* strInputMediaFileName = (*env)->GetStringUTFChars(env, mp4, 0);
    const char* strOutMediaFileName = (*env)->GetStringUTFChars(env, ts, 0);;

    av_register_all();
    avformat_network_init();
    avcodec_register_all();

    AVFormatContext* pFormatContext = 0;
    res = avformat_open_input(&pFormatContext, strInputMediaFileName, 0, 0);
    if(res != 0){
        LOGE("avformat_open_input res < 0");
        return res;
    }
    res = avformat_find_stream_info(pFormatContext, 0);
    if(res < 0){
        LOGE("avformat_find_stream_info res < 0");
        return res;
    }

    av_dump_format(pFormatContext, -1, strInputMediaFileName, 0);
    for(int i = 0; i < pFormatContext->nb_streams; i++){
        if(pFormatContext->streams[i]->codec->codec_type == 0){
            videoStreamIndex = i;
        } else if(pFormatContext->streams[i]->codec->codec_type == 1){
            audioStreamIndex = i;
        }
    }

    if(strstr(pFormatContext->iformat->name, "flv") != 0 ||
            strstr(pFormatContext->iformat->name, "mp4") != 0 ||
            strstr(pFormatContext->iformat->name, "mov") != 0){
        if(pFormatContext->streams[videoStreamIndex]->codec->codec_id == 28){
            filterContext = av_bitstream_filter_init("h264_mp4toannexb");
        } else {
            LOGE("av_bitstream_filter_init not init");
            return -1;
        }
    }

    AVFormatContext* pOutFormatContext = 0;
    avformat_alloc_output_context2(&pOutFormatContext, 0, 0, strOutMediaFileName);
    if(pOutFormatContext == 0){
        LOGE("avformat_alloc_output_context2 error");
        return -1;
    }
    AVOutputFormat* avOutputFormat = pOutFormatContext->oformat;

    if((avOutputFormat->flags & 1) == 0){
        AVIOContext* avioContext = 0;
        if(avio_open(&avioContext, strOutMediaFileName, 2) < 0){
            LOGE("avio_open res < 0");
            return -1;
        }
        pOutFormatContext->pb = avioContext;
    }

    AVStream* audioOutStream = 0;
    if(audioStreamIndex != -1){
        AVStream* inStream = 0;
        AVStream* outStream = 0;
        AVCodecContext* outCodecContext = 0;

        outStream = avformat_new_stream(pOutFormatContext, 0);
        if(outStream == 0){
            LOGE("audio avformat_new_stream res < 0");
            return -1;
        }

        inStream = pFormatContext->streams[audioStreamIndex];
        outStream->id = pOutFormatContext->nb_streams - 1;
        outCodecContext = outStream->codec;
        outStream->time_base = inStream->time_base;

        res = avcodec_copy_context(outStream->codec, inStream->codec);
        if(res < 0){
            LOGE("audio avcodec_copy_context res < 0");
            return res;
        }

        outCodecContext->codec_tag = 0;
        if((64 & pOutFormatContext->oformat->flags) != 0){
            outCodecContext->flags = (outCodecContext->flags | 4194304);
        }

        audioOutStream = outStream;
    }

    AVStream* videoOutStream = 0;
    if(videoStreamIndex != -1){
        AVStream* inStream = 0;
        AVStream* outStream = 0;
        AVCodecContext* outCodecContext = 0;

        outStream = avformat_new_stream(pOutFormatContext, 0);
        if(outStream == 0){
            LOGE("video avformat_new_stream res < 0");
            return -1;
        }

        inStream = pFormatContext->streams[videoStreamIndex];
        outStream->id = pOutFormatContext->nb_streams - 1;
        outCodecContext = outStream->codec;
        outStream->time_base = inStream->time_base;

        res = avcodec_copy_context(outStream->codec, inStream->codec);
        if(res < 0){
            LOGE("video avcodec_copy_context res < 0");
            return res;
        }

        outCodecContext->codec_tag = 0;
        if((64 & pOutFormatContext->oformat->flags) != 0){
            outCodecContext->flags = (outCodecContext->flags | 4194304);
        }

        videoOutStream = outStream;
    }

    av_dump_format(pOutFormatContext, 0, strOutMediaFileName, 1);
    res = avformat_write_header(pOutFormatContext, 0);
    if(res != 0){
        LOGE("avformat_write_header res != 0");
        return res;
    }

    AVPacket packet;
    av_init_packet(&packet);

    int decodeDone = 0;
    do{
        decodeDone = av_read_frame(pFormatContext, &packet);
        if(decodeDone < 0){
            LOGE("av_read_frame res < 0, all frame execute");
            break;
        }

        if(av_dup_packet(&packet) < 0){
            av_packet_unref(&packet);
            LOGE("av_dup_packet pass one frame");
            continue;
        }

        if(packet.pts < packet.dts){
            packet.pts = packet.dts;
        }

        if(packet.stream_index == videoStreamIndex){
            packet.pts = av_rescale_q_rnd(packet.pts, pFormatContext->streams[videoStreamIndex]->time_base, videoOutStream->time_base, 5);
            packet.dts = av_rescale_q_rnd(packet.dts, pFormatContext->streams[videoStreamIndex]->time_base, videoOutStream->time_base, 5);
            packet.duration = (int)av_rescale_q(packet.duration, pFormatContext->streams[videoStreamIndex]->time_base, videoOutStream->time_base);
            packet.stream_index = 1;
        } else if(packet.stream_index == audioStreamIndex){
            packet.pts = av_rescale_q_rnd(packet.pts, pFormatContext->streams[audioStreamIndex]->time_base, audioOutStream->time_base, 5);
            packet.dts = av_rescale_q_rnd(packet.dts, pFormatContext->streams[audioStreamIndex]->time_base, audioOutStream->time_base, 5);
            packet.duration = (int)av_rescale_q(packet.duration, pFormatContext->streams[audioStreamIndex]->time_base, audioOutStream->time_base);
            packet.stream_index = 0;
        }
        res = av_interleaved_write_frame(pOutFormatContext, &packet);
        if(res < 0){
            LOGE("av_interleaved_write_frame could not write one frame of stream");
        }
        av_packet_unref(&packet);
    } while (decodeDone == 0);

    res = av_write_trailer(pOutFormatContext);
    if(res < 0){
        LOGE("av_write_trailer res < 0");
        return res;
    }

    avio_flush(pOutFormatContext->pb);
    avio_close(pOutFormatContext->pb);

    if(filterContext != 0){
        av_bitstream_filter_close(filterContext);
        filterContext = 0;
    }

    av_free(pOutFormatContext);
    av_free(pFormatContext);
    LOGE("convert finish");
    return 0;
}