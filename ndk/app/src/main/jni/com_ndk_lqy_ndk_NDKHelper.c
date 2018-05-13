//
// Created by 罗秋雨 on 2018/5/11.
//

#include "com_ndk_lqy_ndk_NDKHelper.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/dict.h"
#include "libavutil/mathematics.h"
#include "libavutil/mem.h"

#define TAG "jni" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

JNIEXPORT jint JNICALL Java_com_lqy_test_NDKHelper_test
        (JNIEnv *env, jobject thiz, jint codecID) {
    AVCodec *codec = 0;
    av_register_all();//该函数在所有基于ffmpeg的应用程序中几乎都是第一个被调用的。只有调用了该函数，才能使用复用器，编码器等
    codec = avcodec_find_decoder(
            codecID);//通过code ID查找一个已经注册的音视频编码器。H264的codecID是28，所以我们java那边传28下来如果检测到H264注册过了这边codec就不为空，返回0
    if (codec != 0) {
        return 0;
    } else {
        return -1;
    }
}

JNIEXPORT jint JNICALL Java_com_lqy_test_NDKHelper_convert
        (JNIEnv *env, jobject thiz, jstring mp4, jstring ts) {
//    int res = 0;
//    int videoStreamIndex = -1;
//    int audioStreamIndex = -1;
//    AVBitStreamFilterContext* filterContext = 0;
//
//    LOGD("------------------->1");
//    const char* strInputMediaFileName = (*env)->GetStringUTFChars(env, mp4, 0);
//    const char* strOutMediaFileName = (*env)->GetStringUTFChars(env, ts, 0);;
//
//    LOGD("------------------->2");
//    av_register_all();
//    avformat_network_init();
//    avcodec_register_all();
//
//    LOGD("------------------->3");
//    AVFormatContext* pFormatContext = 0;
//    res = avformat_open_input(&pFormatContext, strInputMediaFileName, 0, 0);
//    if(res != 0){
//        return res;
//    }
//    res = avformat_find_stream_info(pFormatContext, 0);
//    if(res < 0){
//        return res;
//    }
//
//    LOGD("------------------->4 0");
//    av_dump_format(pFormatContext, -1, strInputMediaFileName, 0);
//    for(int i = 0; i < pFormatContext->nb_streams; i++){
//        if(pFormatContext->streams[i]->codec->codec_type == 0){
//            videoStreamIndex = i;
//            LOGD("------------------->4 1");
//        } else if(pFormatContext->streams[i]->codec->codec_type == 1){
//            audioStreamIndex = i;
//            LOGD("------------------->4 2");
//        }
//        LOGD("------------------->4 3");
//    }
//
//    LOGD("------------------->5 0");
//    if(strstr(pFormatContext->iformat->name, "flv") != 0 ||
//            strstr(pFormatContext->iformat->name, "mp4") != 0 ||
//            strstr(pFormatContext->iformat->name, "mov") != 0){
//        LOGD("------------------->5 1");
//        if(pFormatContext->streams[videoStreamIndex]->codec->codec_id == 28){
//            LOGD("------------------->5 2");
//            filterContext = av_bitstream_filter_init("h264_mp4toannexb");
//        } else {
//            return -1;
//        }
//    }
//
//    LOGD("------------------->6");
//    AVFormatContext* pOutFormatContext = 0;
//    avformat_alloc_output_context2(&pOutFormatContext, 0, "mp4", strOutMediaFileName);
//    if(pOutFormatContext == 0){
//        return -1;
//    }
//    AVOutputFormat* avOutputFormat = pOutFormatContext->oformat;
//
//    LOGD("------------------->7 0");
//    if((avOutputFormat->flags & 1) == 0){
//        LOGD("------------------->7 1");
//        AVIOContext* avioContext = 0;
//        if(avio_open(&avioContext, strOutMediaFileName, 2) < 0){
//            return -1;
//        }
//        pOutFormatContext->pb = avioContext;
//        LOGD("------------------->7 2");
//    }
//
//    LOGD("------------------->8");
//    AVStream* audioOutStream = 0;
//    if(audioStreamIndex != -1){
//        AVStream* inStream = 0;
//        AVStream* outStream = 0;
//        AVCodecContext* outCodecContext = 0;
//
//        outStream = avformat_new_stream(pOutFormatContext, 0);
//        if(outStream == 0){
//            return -1;
//        }
//
//        inStream = pFormatContext->streams[audioStreamIndex];
//        outStream->id = pOutFormatContext->nb_streams - 1;
//        outCodecContext = outStream->codec;
//        outStream->time_base = inStream->time_base;
//
//        res = avcodec_copy_context(outStream->codec, inStream->codec);
//        if(res < 0){
//            return res;
//        }
//
//        outCodecContext->codec_tag = 0;
//        if((64 & pOutFormatContext->oformat->flags) != 0){
//            outCodecContext->flags = (outCodecContext->flags | 4194304);
//        }
//
//        audioOutStream = outStream;
//    }
//    LOGD("------------------->9");
//
//    AVStream* videoOutStream = 0;
//    if(videoStreamIndex != -1){
//        AVStream* inStream = 0;
//        AVStream* outStream = 0;
//        AVCodecContext* outCodecContext = 0;
//
//        outStream = avformat_new_stream(pOutFormatContext, 0);
//        if(outStream == 0){
//            return -1;
//        }
//
//        inStream = pFormatContext->streams[videoStreamIndex];
//        outStream->id = pOutFormatContext->nb_streams - 1;
//        outCodecContext = outStream->codec;
//        outStream->time_base = inStream->time_base;
//
//        res = avcodec_copy_context(outStream->codec, inStream->codec);
//        if(res < 0){
//            return res;
//        }
//
//        outCodecContext->codec_tag = 0;
//        if((64 & pOutFormatContext->oformat->flags) != 0){
//            outCodecContext->flags = (outCodecContext->flags | 4194304);
//        }
//
//        videoOutStream = outStream;
//    }
//    LOGD("------------------->10");
//
//    av_dump_format(pOutFormatContext, 0, strOutMediaFileName, 1);
//    res = avformat_write_header(pOutFormatContext, 0);
//    if(res != 0){
//        return res;
//    }
//    LOGD("------------------->11");
//
//    AVPacket packet;
//    av_init_packet(&packet);
//    LOGD("------------------->12 0");
//
//    int decodeDone = 0;
//    do{
//        decodeDone = av_read_frame(pFormatContext, &packet);
//        if(decodeDone < 0){
//            LOGD("------------------->12 1");
//            break;
//        }
//
//        if(av_dup_packet(&packet) < 0){
//            av_packet_unref(&packet);
//            LOGD("------------------->12 2");
//            break;
//        }
//
//        if(packet.pts < packet.dts){
//            packet.pts = packet.dts;
//        }
//
//        if(packet.stream_index == videoStreamIndex){
//            packet.pts = av_rescale_q_rnd(packet.pts, pFormatContext->streams[videoStreamIndex]->time_base, videoOutStream->time_base, 5);
//            packet.dts = av_rescale_q_rnd(packet.dts, pFormatContext->streams[videoStreamIndex]->time_base, videoOutStream->time_base, 5);
//
//            packet.duration = (int)av_rescale_q(packet.duration, pFormatContext->streams[videoStreamIndex]->time_base, videoOutStream->time_base);
//            packet.stream_index = 1;
//        } else if(packet.stream_index == audioStreamIndex){
//            packet.pts = av_rescale_q_rnd(packet.pts, pFormatContext->streams[audioStreamIndex]->time_base, audioOutStream->time_base, 5);
//            packet.dts = av_rescale_q_rnd(packet.dts, pFormatContext->streams[audioStreamIndex]->time_base, audioOutStream->time_base, 5);
//
//            packet.duration = (int)av_rescale_q(packet.duration, pFormatContext->streams[audioStreamIndex]->time_base, audioOutStream->time_base);
//            packet.stream_index = 0;
//        }
//
//        res = av_interleaved_write_frame(pOutFormatContext, 0);
//        if(res < 0){
//            LOGD("Warning: Could not write one frame of stream\n");
//        }
//        av_packet_unref(&packet);
//    } while (decodeDone == 0);
//    LOGD("------------------->13");
//
//    res = av_write_trailer(pOutFormatContext);
//    if(res < 0){
//        return res;
//    }
//    LOGD("------------------->14");
//
//    avio_flush(pOutFormatContext->pb);
//    avio_close(pOutFormatContext->pb);
//    LOGD("------------------->15");
//
//    if(filterContext != 0){
//        av_bitstream_filter_close(filterContext);
//        filterContext = 0;
//    }
//
//    LOGD("------------------->16");
//    av_free(pOutFormatContext);
//    av_free(pFormatContext);
//    LOGD("------------------->17");
//    return 0;

    int res = 0;
    LOGD("------------------->1");
    const char* strInputMediaFileName = (*env)->GetStringUTFChars(env, mp4, 0);
    const char* strOutMediaFileName = (*env)->GetStringUTFChars(env, ts, 0);;
    LOGD("------------------->2");
    av_register_all();
    LOGD("------------------->3");
    AVFormatContext* pFormatContext = 0;
    res = avformat_open_input(&pFormatContext, strInputMediaFileName, 0, 0);
    if(res != 0){
        return res;
    }
    AVFormatContext* pOutFormatContext = 0;
    avformat_alloc_output_context2(&pOutFormatContext, 0, 0, strOutMediaFileName);
    LOGD("------------------->5");

    for(int nStreamIndex = 0; nStreamIndex < pFormatContext->nb_streams; nStreamIndex++){
        AVStream* pStream = avformat_new_stream(pOutFormatContext, 0);
        avcodec_copy_context(pStream->codec, pFormatContext->streams[nStreamIndex]->codec);
    }
    LOGD("------------------->6");

    AVDictionary* code_opts = 0;
    av_dict_set(&code_opts, "hls_time", "40", 0);
    av_dict_set(&code_opts, "hls_list_size", "0", 0);
    res = avformat_write_header(pOutFormatContext, &code_opts);
    LOGD("------------------->7");
    if(res < 0){
        return -1;
    }
    av_dict_free(&code_opts);
    AVPacket packet;
    av_init_packet(&packet);

    LOGD("------------------->8 0");
    while (av_read_frame(pFormatContext, &packet) == 0){
        if(av_dup_packet(&packet) < 0){
            av_packet_unref(&packet);
            LOGD("------------------->8 1");
            break;
        }

        packet.pts = av_rescale_q_rnd(
                packet.pts,
                pFormatContext->streams[packet.stream_index]->time_base,
                pOutFormatContext->streams[packet.stream_index]->time_base,
                (AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX)
        );

        LOGD("------------------->8 2");
        packet.dts = av_rescale_q_rnd(
                packet.dts,
                pFormatContext->streams[packet.stream_index]->time_base,
                pOutFormatContext->streams[packet.stream_index]->time_base,
                (AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX)
        );

        LOGD("------------------->8 3");
        packet.duration = av_rescale_q_rnd(
                packet.duration,
                pFormatContext->streams[packet.stream_index]->time_base,
                pOutFormatContext->streams[packet.stream_index]->time_base,
                (AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX)
        );

        LOGD("------------------->8 4");
        av_interleaved_write_frame(pOutFormatContext, &packet);
        LOGD("------------------->8 5");
        av_packet_unref(&packet);
        LOGD("------------------->8 6");
    }
    LOGD("------------------->9");

    av_write_trailer(pOutFormatContext);
    avformat_close_input(&pFormatContext);
    avformat_free_context(pOutFormatContext);
    LOGD("------------------->10");
    return res;
}