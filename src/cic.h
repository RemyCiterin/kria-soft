#ifndef CIC_H
#define CIC_H

#ifndef CIC_N
#define CIC_N 5
#endif

#ifndef CIC_R
#define CIC_R 64
#endif

typedef struct {
  int inte_state[CIC_N];
  int comb_state[CIC_N];
} cic_state_t;

void cic_init_state(cic_state_t* st);

int cic_filter(cic_state_t* st, int len, int* in_buffer, int* out_buffer);

#endif
