/******************************************************************************
* Author        David
* Reviewer      Binyamin Haymann
* Description   UID module - Header_File
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/

#ifndef __UID_OL_110_H__
#define __UID_OL_110_H__

#include <unistd.h>    /* pid_t getpid(void);                               */
#include <sys/types.h> /* pid_t, time_t, (also include definition of uid_t) */
#include <time.h>      /* time_t time(time_t *);                            */

struct uid
{
    size_t __counter__;
    pid_t __process_id__;
    time_t __time_ind__;
};

typedef struct uid uuid_t;

uuid_t GetUID(void);

int IsEqualUID(uuid_t uid1, uuid_t uid2);

extern const uuid_t BAD_UID;

#endif /* __UID_OL_110_H__ */
