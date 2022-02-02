//
// Created by user on 2021-11-02.
//

#ifndef DIRECTORYTRAVERSALCPP_TRAVERSE_H
#define DIRECTORYTRAVERSALCPP_TRAVERSE_H

#include <jni.h>
#include <android/log.h>

#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>

#endif //DIRECTORYTRAVERSALCPP_TRAVERSE_H

#define LOG_TAG "TraversalNative"

#ifndef NDEBUG

#define ANDROID_LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define ANDROID_LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define ANDROID_LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define ANDROID_LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define ANDROID_LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__)

#else //NDEBUG

#define ANDROID_LOGI(...)
#define ANDROID_LOGE(...)
#define ANDROID_LOGW(...)
#define ANDROID_LOGD(...)
#define ANDROID_LOGV(...)

#endif //NDEBUG

typedef char DIR_LIST[256];
typedef struct stat Stat;

char *current_path();

std::vector<std::string> DirectoryFullSearch(const char *path);

std::unordered_map<std::string, std::string> FileInfo(const char *path);

char *check_perm(Stat attr);

std::string CurrentPath();

std::string GetPath(const char* path);

std::vector<std::string> test();