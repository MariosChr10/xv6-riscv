
#ifndef _KERNEL_PSTAT_H_
#define _KERNEL_PSTAT_H_

#include "kernel/types.h"
#include "kernel/param.h"

#define PSTAT_NAME_LEN 16

struct pstat {
  // 1 αν η εγγραφή αντιστοιχεί σε μη-UNUSED διεργασία, αλλιώς 0.
  int inuse[NPROC];

  // Βασικά στοιχεία διεργασίας.
  int pid[NPROC];
  int ppid[NPROC];

  // Κατάσταση διεργασίας 
  int state[NPROC];

  int qlevel[NPROC];   
  int qticks[NPROC];   // ticks που έχουν καταναλωθεί στο τρέχον quantum

  // Μέγεθος μνήμης.
  uint64 sz[NPROC];

  // Όνομα διεργασίας.
  char name[NPROC][PSTAT_NAME_LEN];
};

#endif
