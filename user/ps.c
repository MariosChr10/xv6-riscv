// user/ps.c
// Εμφανίζει πληροφορίες διεργασιών χρησιμοποιώντας getpinfo().

#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/pstat.h"
#include "user/user.h"

static char*
stname(int s)
{
  // Αντιστοίχιση καταστάσεων xv6 σε μικρά strings.
  // enum procstate: UNUSED=0, USED=1, SLEEPING=2, RUNNABLE=3, RUNNING=4, ZOMBIE=5.
  if(s == 0) return "UNUSED";
  if(s == 1) return "USED";
  if(s == 2) return "SLEEP";
  if(s == 3) return "RUNNBL";
  if(s == 4) return "RUN";
  if(s == 5) return "ZOMB";
  return "UNK";
}

int
main(void)
{
  struct pstat st;

  if(getpinfo(&st) < 0){
    fprintf(2, "ps: getpinfo failed\n");
    exit(1);
  }

  // Εκτύπωση κεφαλίδας (έχει και το επίπεδο προτεραιότητας όπως ζητά η εκφώνηση).
  printf("PID PPID STATE   QL QT SZ        NAME\n");

  for(int i = 0; i < NPROC; i++){
    if(st.inuse[i] == 0)
      continue;

        // Το xv6 printf ΔΕΝ υποστηρίζει πλάτη/στοίχιση τύπου "%-6s", άρα κρατάμε απλά "%s".
    printf("%d %d %s %d %d %d %s\n",
           st.pid[i],
           st.ppid[i],
           stname(st.state[i]),
           st.qlevel[i],
           st.qticks[i],
           (int)st.sz[i],
           st.name[i]);
  }

  exit(0);
}
