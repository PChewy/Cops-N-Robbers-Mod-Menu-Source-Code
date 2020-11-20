  
#include <pthread.h>
#include <jni.h>
#include <memory.h>
#include <dlfcn.h>
#include <cstdio>
#include <cstdlib>
#include <Includes/Vector3.hpp>
#include <Includes/Unity.h>
#include <Includes/Utils.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <thread>
#include <bits/sysconf.h>
#include <sys/mman.h>

#include "Includes/Logger.h"
#include "Patching/Patch.h"
#import "Includes/Utils.h"
#include "Includes/Offsets.h"
#include "Includes/Strings.h"


#if defined(__armv7__)
#include "X64Hook/And64InlineHook.hpp"
#else
#include "Substrate/CydiaSubstrate.h"
#endif

bool IsDual = false;
bool Reload = false;
bool IsRecoil = false;
bool IsFireRate = false;
bool IsFireRate2 = false;
bool isName = false;
bool Isammo = false;
bool Isammo2 = false;
bool IsStore = false;
bool IsAccuracy = false;
bool IsAccuracy2 = false;
bool IsReloadTime = false;
bool IsReloadTime2 = false;
bool IsAttackRange = false;
bool IsAttackRange2 = false;
bool IsExplosion = false;
bool IsAim = false;
bool IsMine = false;
bool IsDeath = false;
bool IsKilled = false;

struct Patches{
    Patch *miniMap;
}patch;

bool speedHackDetectorHook = false;

void(*old_SpeedHackDetector)(void *instance);
void SpeedHackDetector(void *instance) {
    if(instance != NULL) {
        {
            *(int *) ((uint64_t) instance + 0x24) = 0; //SpeedHackDetector: public int coolDown
        }
        if(!speedHackDetectorHook){
            speedHackDetectorHook = true;
            LOGI("GameManager_LateUpdate hooked");
        }
    }
    old_SpeedHackDetector(instance);
}

bool (*old_Dual)(void *instance);
bool Dual(void *instance) {
    if (instance != NULL) {
        if (IsDual) {
            return true;
        }
    }
    return old_Dual(instance);
}

bool (*old_AutoReload)(void *instance);
bool AutoReload(void *instance) {
    if (instance != NULL) {
        if (Reload) {
            return true;
        }
    }
    return old_AutoReload(instance);
}

bool (*old_recoil)(void *instance);
bool recoil(void *instance) {
    if (instance != NULL) {
        if (IsRecoil) {
            return false;
        }
    }
    return old_recoil(instance);
}

float (*old_Firerate)(void *instance);
float Firerate(void *instance) {
    if (instance != NULL) {
        if (IsFireRate) {
            return 9999.9f;
        }
    }
    return old_Firerate(instance);
}

int (*old_Firerate2)(void *instance);
int Firerate2(void *instance) {
    if (instance != NULL) {
        if (IsFireRate2) {
            return 9999;
        }
    }
    return old_Firerate2(instance);
}

monoString* (*old_playername)(void *instance);
monoString* playername(void *instance) {
    if(instance!=NULL) {
        if (isName) {
            return CreateMonoString("Add whatever you want hare");
        }
    }
    return old_playername(instance);
}

int (*old_CurrentInAmmo)(void *instance);
int CurrentInAmmo(void *instance) {
    if (instance != NULL) {
        if (Isammo) {
            return 2147483647;
        }
    }
    return old_CurrentInAmmo(instance);
}

float (*old_CurrentInAmmo2)(void *instance);
float CurrentInAmmo2(void *instance) {
    if (instance != NULL) {
        if (Isammo2) {
            return 2147483647.0f;
        }
    }
    return old_CurrentInAmmo2(instance);
}

bool (*old_Store)(void *instance);
bool Store(void *instance) {
    if (instance != NULL) {
        if (IsStore) {
            return true;
        }
    }
    return old_Store(instance);
}

float (*old_AccuracyPoint)(void *instance);
float AccuracyPoint(void *instance) {
    if (instance != NULL) {
        if (IsAccuracy) {
            return 0.0f;
        }
    }
    return old_AccuracyPoint(instance);
}

int (*old_AccuracyPointAdded)(void *instance);
int AccuracyPointAdded(void *instance) {
    if (instance != NULL) {
        if (IsAccuracy2) {
            return 0;
        }
    }
    return old_AccuracyPointAdded(instance);
}

float (*old_ReloadTimePoint)(void *instance);
float ReloadTimePoint(void *instance) {
    if (instance != NULL) {
        if (IsReloadTime) {
            return 999.9f;
        }
    }
    return old_ReloadTimePoint(instance);
}

int (*old_ReloadTimePointAdded)(void *instance);
int ReloadTimePointAdded(void *instance) {
    if (instance != NULL) {
        if (IsReloadTime2) {
            return 999;
        }
    }
    return ReloadTimePointAdded(instance);
}

float (*old_AttackRangePoint)(void *instance);
float AttackRangePoint(void *instance) {
    if (instance != NULL) {
        if (IsAttackRange) {
            return 99999999.9f;
        }
    }
    return old_AttackRangePoint(instance);
}

int (*old_AttackRangePointAdded)(void *instance);
int AttackRangePointAdded(void *instance) {
    if (instance != NULL) {
        if (IsAttackRange2) {
            return 99999999;
        }
    }
    return old_AttackRangePointAdded(instance);
}

float (*old_ExplosionRangePoint)(void *instance);
float ExplosionRangePoint(void *instance) {
    if (instance != NULL) {
        if (IsExplosion) {
            return 99999999.9f;
        }
    }
    return old_ExplosionRangePoint(instance);
}

bool (*old_CanAim)(void *instance);
bool CanAim(void *instance) {
    if (instance != NULL) {
        if (IsAim) {
            return true;
        }
    }
    return old_CanAim(instance);
}

bool (*old_Mine)(void *instance);
bool Mine(void *instance) {
    if (instance != NULL) {
        if (IsMine) {
            return true;
        }
    }
    return old_Mine(instance);
}

int (*old_DeathNum)(void *instance);
int DeathNum(void *instance) {
    if (instance != NULL) {
        if (IsDeath) {
            return 0;
        }
    }
    return old_DeathNum(instance);
}

int (*old_KilledNum)(void *instance);
int KilledNum(void *instance) {
    if (instance != NULL) {
        if (IsKilled) {
            return 50;
        }
    }
    return old_KilledNum(instance);
}

// we will run our patches in a new thread so our while loop doesn't block process main thread
void* hack_thread(void*) {
    LOGI("I have been loaded. Mwuahahahaha");
    // loop until our target library is found
    do {
        sleep(1);
    } while (!isLibraryLoaded(libName));
    LOGI("I found the il2cpp lib. Address is: %p", (void*)findLibrary(libName));
    LOGI("Hooking GameManager_LateUpdate");
    octo_hook((void*)getAbsoluteAddress( Offsets::SpeedHackDetector), (void*)SpeedHackDetector, (void**)&old_SpeedHackDetector);
    octo_hook((void*)getAbsoluteAddress( Offsets::Dual), (void*)Dual, (void**)&old_Dual);
    octo_hook((void*)getAbsoluteAddress( Offsets::AutoReload), (void*)AutoReload, (void**)&old_AutoReload);
    octo_hook((void*)getAbsoluteAddress( Offsets::recoil), (void*)recoil, (void**)&old_recoil);
    octo_hook((void*)getAbsoluteAddress( Offsets::Firerate), (void*)Firerate, (void**)&old_Firerate);
    octo_hook((void*)getAbsoluteAddress( Offsets::Firerate2), (void*)Firerate2, (void**)&old_Firerate2);
    octo_hook((void*)getAbsoluteAddress( Offsets::playername), (void*)playername, (void**)&old_playername);
    octo_hook((void*)getAbsoluteAddress( Offsets::CurrentInAmmo), (void*)CurrentInAmmo, (void**)&old_CurrentInAmmo);
    octo_hook((void*)getAbsoluteAddress( Offsets::CurrentInAmmo2), (void*)CurrentInAmmo2, (void**)&old_CurrentInAmmo2);
    octo_hook((void*)getAbsoluteAddress( Offsets::Store), (void*)Store, (void**)&old_Store);
    octo_hook((void*)getAbsoluteAddress( Offsets::AccuracyPoint), (void*)AccuracyPoint, (void**)&old_AccuracyPoint);
    octo_hook((void*)getAbsoluteAddress( Offsets::AccuracyPointAdded), (void*)AccuracyPointAdded, (void**)&old_AccuracyPointAdded);
    octo_hook((void*)getAbsoluteAddress( Offsets::ReloadTimePoint), (void*)ReloadTimePoint, (void**)&old_ReloadTimePoint);
    octo_hook((void*)getAbsoluteAddress( Offsets::ReloadTimePointAdded), (void*)ReloadTimePointAdded, (void**)&old_ReloadTimePointAdded);
    octo_hook((void*)getAbsoluteAddress( Offsets::AttackRangePoint), (void*)AttackRangePoint, (void**)&old_AttackRangePoint);
    octo_hook((void*)getAbsoluteAddress( Offsets::AttackRangePointAdded), (void*)AttackRangePointAdded, (void**)&old_AttackRangePointAdded);
    octo_hook((void*)getAbsoluteAddress( Offsets::ExplosionRangePoint), (void*)ExplosionRangePoint, (void**)&old_ExplosionRangePoint);
    octo_hook((void*)getAbsoluteAddress( Offsets::CanAim), (void*)CanAim, (void**)&old_CanAim);
    octo_hook((void*)getAbsoluteAddress( Offsets::Mine), (void*)Mine, (void**)&old_Mine);
    octo_hook((void*)getAbsoluteAddress( Offsets::DeathNum), (void*)DeathNum, (void**)&old_DeathNum);
    octo_hook((void*)getAbsoluteAddress( Offsets::KilledNum), (void*)KilledNum, (void**)&old_KilledNum);


    /*patch.miniMap = Patch::Setup((void*)getAbsoluteAddress(0xF09D64), (char*)"\x01\x00\xa0\xe3\x1e\xff\x2f\xe1", 8);*/

    Patch::Setup((void*)getAbsoluteAddress(0x2ACA814), (char*)"\x1e\xff\x2f\xe1", 4)->Apply(); //clientapp$$onKicked
    Patch::Setup((void*)getAbsoluteAddress(0xF5EE68), (char*)"\x00\x00\xA0\xE3\x1e\xff\x2f\xe1", 8)->Apply(); //ActDetectorBase
    Patch::Setup((void*)getAbsoluteAddress(0xF5EDC4), (char*)"\x00\x00\xA0\xE3\x1e\xff\x2f\xe1", 8)->Apply(); //ActDetectorBase$$DetectorHasCallbacks
    Patch::Setup((void*)getAbsoluteAddress(0xF5EDE8), (char*)"\x01\x00\xa0\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //ActDetectorBase$$StopDetectionInternal
    Patch::Setup((void*)getAbsoluteAddress(0xF5EA04), (char*)"\x00\x00\xA0\xE3\x1e\xff\x2f\xe1", 8)->Apply(); //ActDetectorBase$$OnCheatingDetected
    Patch::Setup((void*)getAbsoluteAddress(0xF5E858), (char*)"\x00\x00\xA0\xE3\x1e\xff\x2f\xe1", 8)->Apply(); //ActDetectorBase$$OnApplicationQuit
    Patch::Setup((void*)getAbsoluteAddress(0xF5F5D0), (char*)"\x00\x00\xA0\xE3\x1e\xff\x2f\xe1", 8)->Apply(); //InjectionDetector$$StartDetectionInterna
    Patch::Setup((void*)getAbsoluteAddress(0xF5EDE8), (char*)"\x01\x00\xa0\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //InjectionDetector$$StopDetection
    Patch::Setup((void*)getAbsoluteAddress(0xF608A0), (char*)"\x01\x00\xa0\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //SpeedHackDetector$$StopDetection
    Patch::Setup((void*)getAbsoluteAddress(0xF64664), (char*)"\x01\x00\xa0\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //TimeCheatingDetector$$StopDetectionInternal
    Patch::Setup((void*)getAbsoluteAddress(0xF62BBC), (char*)"\x01\x00\xa0\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //TimeCheatingDetector$$StopDetection
    Patch::Setup((void*)getAbsoluteAddress(0xF6AEAC), (char*)"\x01\x00\xa0\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //WallHackDetector$$StopDetectionInternal
    return NULL;
}

extern "C"
JNIEXPORT jobjectArray JNICALL Java_com_dark_force_NativeLibrary_getListFT(JNIEnv *env, jclass jobj){
    jobjectArray ret;
    int i;
    const char *features[]= {"Dual Weapons", "Auto Reload", "No Recoil", "Rapid Fire", "Name Changer", "More Ammo", "Show Hidden Store", "Accuracy Hack", "Fast Reload", "Range Hack", "Aim Button", "50/0"};
    int Total_Feature = (sizeof features / sizeof features[0]); //Now you dont have to manually update the number everytime
    ret= (jobjectArray)env->NewObjectArray(Total_Feature,
                                           env->FindClass("java/lang/String"),
                                           env->NewStringUTF(""));

    for(i=0;i<Total_Feature;i++) {
        env->SetObjectArrayElement(
                ret,i,env->NewStringUTF(features[i]));
    }
    return(ret);
}


extern "C"
JNIEXPORT void JNICALL Java_com_dark_force_NativeLibrary_changeToggle(JNIEnv *env, jclass thisObj, jint number) {
    int i = (int) number;
    switch (i) {
        case 0:
            IsDual = !IsDual;
            break;
        case 1:
            Reload = !Reload;
            break;
        case 2:
            IsRecoil = !IsRecoil;
            break;
        case 3:
            IsFireRate = !IsFireRate;
            IsFireRate2 = !IsFireRate2;
            break;
        case 4:
            isName = !isName;
            break;
        case 5:
            Isammo = !Isammo;
            Isammo2 = !Isammo2;
            break;
        case 6:
            IsStore = !IsStore;
            break;
        case 7:
            IsAccuracy = !IsAccuracy;
            IsAccuracy2 = !IsAccuracy2;
            break;
        case 8:
            IsReloadTime = !IsReloadTime;
            IsReloadTime2 = !IsReloadTime2;
            break;
        case 9:
            IsAttackRange = !IsAttackRange;
            IsAttackRange2 = !IsAttackRange2;
            IsExplosion = !IsExplosion;
            break;
        case 10:
            IsAim = !IsAim;
            break;
        case 11:
            IsMine = !IsMine;
            IsDeath = !IsDeath;
            IsKilled = !IsKilled;
            break;
        default:
            break;
    }
    return;
}

extern "C"
JNIEXPORT void JNICALL Java_com_dark_force_NativeLibrary_init(JNIEnv * env, jclass obj, jobject thiz){
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);

    //Add our toast in here so it wont be easy to change by simply editing the smali and cant
    //be cut out because this method is needed to start the hack (I'm smart)
    jstring jstr = env->NewStringUTF("Mod Menu by Chewy"); //Edit this text to your desired toast message!
    jclass toast = env->FindClass("android/widget/Toast");
    jmethodID methodMakeText =
            env->GetStaticMethodID(
                    toast,
                    "makeText",
                    "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;");
    if (methodMakeText == NULL) {
        LOGE("toast.makeText not Found");
        return;
    }
    //The last int is the length on how long the toast should be displayed
    //0 = Short, 1 = Long
    jobject toastobj = env->CallStaticObjectMethod(toast, methodMakeText,
                                                   thiz, jstr, 1);

    jmethodID methodShow = env->GetMethodID(toast, "show", "()V");
    if (methodShow == NULL) {
        LOGE("toast.show not Found");
        return;
    }
    env->CallVoidMethod(toastobj, methodShow);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_dark_force_NativeLibrary_changeSeekBar(JNIEnv *env, jclass clazz, jint i, jint seekbarValue) {
    int li = (int) i;
    switch (li) {
        case 0:
            break;
        default:
            break;
    }
    return;
}
