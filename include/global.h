#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "dm6437.h"

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


#define TRUE    1
#define FALSE  0

#define MIN(X, Y) ((X)<(Y)?(X):(Y))
#define MAX(X, Y) ((X)>(Y)?(X):(Y))  

/****************************MACRO About IMAGE PROCESS**************************************/
#define RAW_IMAGE_W 1280
#define RAW_IMAGE_H  720

#define IMAGE_W  800
#define IMAGE_H  480





/*GPIO Current voltage Level*/
#define HIGH_LEVEL 1
#define LOW_LEVEL 0

typedef enum {

    REAL_PLAY_MODE = 0,
    PLAY_BACK_MODE,
    
}SYS_WORK_MODE;


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __GLOBAL_H__ */
