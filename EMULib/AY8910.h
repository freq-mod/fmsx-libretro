/** EMULib Emulation Library *********************************/
/**                                                         **/
/**                         AY8910.h                        **/
/**                                                         **/
/** This file contains emulation for the AY8910 sound chip  **/
/** produced by General Instruments, Yamaha, etc. See       **/
/** AY8910.c for the actual code.                           **/
/**                                                         **/
/** Copyright (C) Marat Fayzullin 1996-2021                 **/
/**     You are not allowed to distribute this software     **/
/**     commercially. Please, notify me, if you make any    **/
/**     changes to this file.                               **/
/*************************************************************/
#ifndef AY8910_H
#define AY8910_H
#ifdef __cplusplus
extern "C" {
#endif

#define AY8910_CHANNELS 6      /* 3 melodic + 3 noise chanls */

#define AY8910_ASYNC    0      /* Asynchronous emulation     */
#define AY8910_SYNC     1      /* Synchronous emulation      */
#define AY8910_FLUSH    2      /* Flush buffers only         */

#ifndef BYTE_TYPE_DEFINED
#define BYTE_TYPE_DEFINED
typedef unsigned char byte;
#endif

/** AY8910 ***************************************************/
/** This data structure stores AY8910 state.                **/
/*************************************************************/
#pragma pack(4)
typedef struct
{
  byte R[16];                  /* PSG registers contents     */

  /* THESE VALUES ARE NOT USED BUT KEPT FOR BACKWARD COMPATIBILITY */
  int Freq[AY8910_CHANNELS];   /* Frequencies (0 for off)    */
  int Volume[AY8910_CHANNELS]; /* Volumes (0..255)           */

  int Clock;                   /* Base clock rate (Fin/16)   */
  int First;                   /* First used Sound() channel */
  byte Changed;                /* Bitmap of changed channels */
  byte Sync;                   /* AY8910_SYNC/AY8910_ASYNC   */
  byte Latch;                  /* Latch for the register num */
  int EPeriod;                 /* Envelope step in microsecs */
  int ECount;                  /* Envelope step counter      */
  int EPhase;                  /* Envelope phase             */
} AY8910;
#pragma pack()

/** Reset8910() **********************************************/
/** Reset the sound chip and use sound channels from the    **/
/** one given in First.                                     **/
/*************************************************************/
void Reset8910(AY8910 *D,int ClockHz,int First);

/** Write8910() **********************************************/
/** Call this function to output a value V into the sound   **/
/** chip.                                                   **/
/*************************************************************/
void Write8910(AY8910 *D,byte R,byte V);

/** WrCtrl8910() *********************************************/
/** Write a value V to the PSG Control Port.                **/
/*************************************************************/
void WrCtrl8910(AY8910 *D,byte V);

/** WrData8910() *********************************************/
/** Write a value V to the PSG Data Port.                   **/
/*************************************************************/
void WrData8910(AY8910 *D,byte V);

/** RdData8910() *********************************************/
/** Read a value from the PSG Data Port.                    **/
/*************************************************************/
byte RdData8910(AY8910 *D);

/** Sync8910() ***********************************************/
/** Flush all accumulated changes by issuing Sound() calls  **/
/** and set the synchronization on/off. The second argument **/
/** should be AY8910_SYNC/AY8910_ASYNC to set/reset sync,   **/
/** or AY8910_FLUSH to leave sync mode as it is.            **/
/*************************************************************/
void Sync8910(AY8910 *D,byte Sync);

/** Loop8910() ***********************************************/
/** Call this function periodically to update volume        **/
/** envelopes. Use uSec to pass the time since the last     **/
/** call of Loop8910() in microseconds.                     **/
/*************************************************************/
void Loop8910(AY8910 *D,int uSec);

#ifdef __cplusplus
}
#endif
#endif /* AY8910_H */
