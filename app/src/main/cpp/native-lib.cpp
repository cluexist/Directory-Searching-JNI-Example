#include <jni.h>
#include <string>
#include "traverse.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_directorytraversalcpp_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_directorytraversalcpp_MainActivity_getCurrentPath(
        JNIEnv *env,
        jobject /* this */) {

    std::string path = CurrentPath();
    return env->NewStringUTF(path.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_directorytraversalcpp_MainActivity_getPath(
        JNIEnv *env,
        jobject /* this */,
        jstring jStr) {

    const char *path = (env)->GetStringUTFChars(jStr, (jboolean *) 0);
    std::string full_path = GetPath(path);
    return env->NewStringUTF(full_path.c_str());
}

extern "C" JNIEXPORT jobjectArray  JNICALL
Java_com_example_directorytraversalcpp_MainActivity_getPathList(
        JNIEnv *env,
        jobject /* this */,
        jstring jStr) {

    const char *path = (env)->GetStringUTFChars(jStr, (jboolean *) 0);
    std::vector<std::string> path_list = DirectoryFullSearch(path);

    if(path_list.empty()){
        return nullptr;
    }

    jclass clazz = (env)->FindClass("java/lang/String");
    jobjectArray objarray = (env)->NewObjectArray(path_list.size(), clazz, 0);

    for (int i = 0; i < path_list.size(); i++) {

        std::string s = path_list[i];

        jstring jstr = (env)->NewStringUTF(s.c_str());

        (env)->SetObjectArrayElement(objarray, i, jstr);

        env->DeleteLocalRef(jstr);
    }

    return objarray;
}

extern "C" JNIEXPORT jobject JNICALL
Java_com_example_directorytraversalcpp_MainActivity_getFileInfo(
        JNIEnv *env,
        jobject /* this */,
        jstring jStr) {

    const char *path = (env)->GetStringUTFChars(jStr, (jboolean *) 0);
    std::unordered_map<std::string, std::string> file_info_map = FileInfo(path);

    if(file_info_map.empty()){
        ANDROID_LOGE("NULL OBJECT");
        return nullptr;
    }

    jclass mapClass = env->FindClass("java/util/HashMap");
    jmethodID init = env->GetMethodID(mapClass, "<init>", "()V");
    jobject hashMap = env->NewObject(mapClass, init);
    jmethodID put = env->GetMethodID(mapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

    for (std::unordered_map<std::string, std::string>::iterator it = file_info_map.begin(); it != file_info_map.end(); ++it) {
        jstring keyJava = env->NewStringUTF(it->first.c_str());
        jstring valueJava = env->NewStringUTF(it->second.c_str());

        env->CallObjectMethod(hashMap, put, keyJava, valueJava);

        env->DeleteLocalRef(keyJava);
        env->DeleteLocalRef(valueJava);
    }

    return hashMap;
}
