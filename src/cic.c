#include "cic.h"

void cic_init_state(cic_state_t* st) {
  for (int j=0; j < CIC_N; j++) {
    st->inte_state[j] = 0;
    st->comb_state[j] = 0;
  }
}

// Cascaded Integrator Comb (CIC) low pass filter
int cic_filter(cic_state_t* st, int len, int* in_buffer, int* out_buffer) {
  int index = 0;

  for (int i=0; i < len; i++) {
    int x = in_buffer[i];

    for (int j=0; j<CIC_N; j++) {
      st->inte_state[j] += x;
      x = st->inte_state[j];
    }

    if (i % CIC_R == 0) {
      for (int j=0; j < CIC_N; j++) {
        int tmp = st->comb_state[j];
        st->comb_state[j] = x;
        x = x - tmp;
      }

      out_buffer[index] = x;
      index++;
    }
  }

  return index;
}
